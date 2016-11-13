// Fill out your copyright notice in the Description page of Project Settings.

#include "RuntimeObj.h"
#include "MyObjPawn.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <random>
#include <string>
#include <filesystem> // std::tr2::sys::path etc.
#include <fstream>   // ifstream, ofstream
#include <sstream>   // istringstream
#include <string>
#include <vector>
#include <unordered_map>

struct vertex_index {
    int v_idx, vt_idx, vn_idx;
    vertex_index() {};
    vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) {};
    vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) {};
};

inline bool isSpace(const char c) {
    return (c == ' ') || (c == '\t');
}

inline bool isNewLine(const char c) {
    return (c == '\r') || (c == '\n') || (c == '\0');
}

// Make index zero-base, and also support relative index. 
inline int fixIndex(int idx, int n)
{
    int i;

    if (idx > 0) {
        i = idx - 1;
    }
    else if (idx == 0) {
        i = 0;
    }
    else { // negative value = relative
        i = n + idx;
    }
    return i;
}

inline float parseFloat(const char*& token)
{
    token += strspn(token, " \t");
    float f = (float)atof(token);
    token += strcspn(token, " \t\r");
    return f;
}

inline void parseFloat2(
    float& x, float& y,
    const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
}

inline void parseFloat3(
    float& x, float& y, float& z,
    const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
    z = parseFloat(token);
}

// Parse triples: i, i/j/k, i//k, i/j
vertex_index parseTriple(
    const char* &token,
    int vsize,
    int vnsize,
    int vtsize)
{
    vertex_index vi(-1);

    vi.v_idx = fixIndex(atoi(token), vsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }
    token++;

    // i//k
    if (token[0] == '/') {
        token++;
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }

    // i/j/k or i/j
    vi.vt_idx = fixIndex(atoi(token), vtsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }

    // i/j/k
    token++;  // skip '/'
    vi.vn_idx = fixIndex(atoi(token), vnsize);
    token += strcspn(token, "/ \t\r");
    return vi;
}

void ObjectParser( TArray<FVector>& positions, TArray<FVector>& normals, TArray<FVector2D>& uvs, TArray<int32>& indices )
{
    char filepath[1024];

    sprintf_s(filepath, "../../../../../../Siggraph2017/assets/Simplygon/InfinityBlade/InfinityBladeAdversaries/Enemy_Bear/clean_Enemy_Bear_099.obj");
    std::ifstream ifs(filepath);
    if (!ifs)
    {
        UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"オブジェクトファイルの読み込みに失敗しました");
    }

    int maxchars = 8192;  // Alloc enough size.
    std::vector<char> buf(maxchars);  // Alloc enough size.
    while (ifs.peek() != -1) {
        ifs.getline(&buf[0], maxchars);

        std::string linebuf(&buf[0]);

        // Trim newline '\r\n' or '\r'
        if (linebuf.size() > 0) {
            if (linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
        }
        if (linebuf.size() > 0) {
            if (linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
        }

        // Skip if empty line.
        if (linebuf.empty()) {
            continue;
        }

        // Skip leading space.
        const char* token = linebuf.c_str();
        token += strspn(token, " \t");

        assert(token);
        if (token[0] == '\0') continue; // empty line

        if (token[0] == '#') continue;  // comment line

        // vertex
        if (token[0] == 'v' && isSpace((token[1]))) {
            token += 2;
            float xyz[3];
            parseFloat3(xyz[0], xyz[1], xyz[2], token);
            positions.Add(FVector(xyz[0], xyz[1], xyz[2]));
            continue;
        }

        // normal
        if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2]))) {
            token += 3;
            float xyz[3];
            parseFloat3(xyz[0], xyz[1], xyz[2], token);
            normals.Add(FVector(xyz[0], xyz[1], xyz[2]));
            continue;
        }

        // texcoord
        if (token[0] == 'v' && token[1] == 't' && isSpace((token[2]))) {
            token += 3;
            float uv[2];
            parseFloat2(uv[0], uv[1], token);
            uvs.Add(FVector2D(uv[0], 1.0f - uv[1]));
            continue;
        }

        // face
        if (token[0] == 'f' && isSpace((token[1]))) {
            token += 2;
            token += strspn(token, " \t");

            std::vector<vertex_index> face;
            int tmp[3];
            int tmp_index = 0;
            while (!isNewLine(token[0])) {
                vertex_index vi = parseTriple(token, 3, 3, 2);
                tmp[tmp_index] = vi.v_idx; tmp_index++;
                int n = strspn(token, " \t\r");
                token += n;
            }
            indices.Add(tmp[2]);
            indices.Add(tmp[1]);
            indices.Add(tmp[0]);
            continue;
        }

        // use mtl
        if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6]))) {
            continue;
        }

        // load mtl
        if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6]))) {
            continue;
        }

        // group name
        if (token[0] == 'g' && isSpace((token[1]))) {
            continue;
        }

        // object name
        if (token[0] == 'o' && isSpace((token[1]))) {
            continue;
        }

        // Ignore unknown command.
    }
}

// Sets default values
AMyObjPawn::AMyObjPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player (このポーンが最小値のプレイヤーで制御されるように設定)
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // ダミーキャラクターを置く
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a dummy root component we can attach things to.(親子付け可能なダミーのルートコンポーネントを作成)
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

    // Attach our camera and visible object to our root component. (カメラと可視オブジェクトをルートコンポーネントに親子付け。カメラをオフセットして回転)
    OurCamera->AttachTo(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-350.0f, 0.0f, 100.0f));
    OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

    /**
    *	Create/replace a section for this procedural mesh component.
    *	@param	SectionIndex		Index of the section to create or replace.
    *	@param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
    *	@param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3.
    *	@param	Normals				Optional array of normal vectors for each vertex. If supplied, must be same length as Vertices array.
    *	@param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
    *	@param	VertexColors		Optional array of colors for each vertex. If supplied, must be same length as Vertices array.
    *	@param	Tangents			Optional array of tangent vector for each vertex. If supplied, must be same length as Vertices array.
    *	@param	bCreateCollision	Indicates whether collision should be created for this section. This adds significant cost.
    */

    // 動的オブジェクトを置く
    mProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));

    TArray<FVector> positions;
    TArray<FVector> normals;
    TArray<FVector2D> uvs;
    TArray<FColor> colors;
    TArray<FProcMeshTangent> tangents;
    TArray<int32> indices;

    ObjectParser(positions, normals, uvs, indices);

    for (size_t i = 0; i < positions.Num(); i++)
    {
        colors.Add(FColor(255, 255, 255, 255));
        tangents.Add(FProcMeshTangent(1, 1, 1));
    }

    ConstructorHelpers::FObjectFinder<UMaterial>* pMaterialAsset = new ConstructorHelpers::FObjectFinder<UMaterial>(
        _T("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Materials/M_Bear_Master.M_Bear_Master")
        );
    if (pMaterialAsset->Succeeded())
    {
        mMaterial = pMaterialAsset->Object;
        UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"マテリアルロードに成功しました");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("output : %s"), L"マテリアルロードに失敗しました");
    }

    mProceduralMeshComponent->CreateMeshSection(0, positions, indices, normals, uvs, colors, tangents, false);
    mProceduralMeshComponent->SetMaterial(0, mMaterial);
    mProceduralMeshComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMyObjPawn::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AMyObjPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyObjPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

}


