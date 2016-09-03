// Fill out your copyright notice in the Description page of Project Settings.

#include "SunTemple.h"
#include "CameraWithSpawn.h"
#include "ConstAssetPath.h"
#include "CameraLocations.h"

#define CAPTURE_FINAL (1)

const int startVariationIndex = 0;

// Sets default values
ACameraWithSpawn::ACameraWithSpawn(const FObjectInitializer& ObjectInitializer)
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

    for (size_t i = 0; i < NUM_MATERIAL; i++)
    {
        ConstructorHelpers::FObjectFinder<UMaterial>* pMaterialAsset = new ConstructorHelpers::FObjectFinder<UMaterial>(materialList[i]);
        if (pMaterialAsset->Succeeded())
        {
            mMaterial[i] = pMaterialAsset->Object;
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), materialList[i], L"マテリアルロードに成功しました");
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), materialList[i], L"マテリアルロードに失敗しました");
        }
    }

    variationIndex = 0;
    for (size_t j = 0; j < 3; j++)
    {
        for (size_t i = 0; i < NUM_OBJECT; i++)
        {
            int lodtype = FMath::RandRange(0, 2);
            ConstructorHelpers::FObjectFinder<UStaticMesh>* pMeshAsset;
            if(j == 0)
                pMeshAsset = new ConstructorHelpers::FObjectFinder<UStaticMesh>(objectList1[i]);
            else if (j == 1)
                pMeshAsset = new ConstructorHelpers::FObjectFinder<UStaticMesh>(objectList2[i]);
            else
                pMeshAsset = new ConstructorHelpers::FObjectFinder<UStaticMesh>(objectList3[i]);

            if ( pMeshAsset->Succeeded() )
            {
                mStaticMesh[j][i] = pMeshAsset->Object;
                mStaticMesh[j][i]->Materials[0] = mMaterial[i / NUM_LOD];
                UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), objectList1[i], L"メッシュロードに成功しました");
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("output : %s %s"), objectList1[i], L"メッシュロードに失敗しました");
            }
        }
    }

    mStaticMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshName"));
    // オブジェクトが生成出来ました
    if (mStaticMeshComponent)
    {
        mStaticMeshComponent->SetStaticMesh(mStaticMesh[0][0]);
        mStaticMeshComponent->AttachTo(RootComponent);
    }
}

// Called when the game starts or when spawned
void ACameraWithSpawn::BeginPlay()
{
    Super::BeginPlay();

}

void GetRandomObjectId(int& remeshType, int& materialIndex, int& objectIdx, float& rotation)
{
    remeshType = FMath::RandRange(0, NUM_LOD_TYPE-1);
    materialIndex = FMath::RandRange(0, NUM_MATERIAL - 1);
    objectIdx = materialIndex * NUM_LOD;
    rotation = FMath::RandRange(-89.0f, -1.0f);
}

// Called every frame
void ACameraWithSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if CAPTURE_FINAL
    if (bStartCapture)
    {
        const float timeToNextObject = 0.4f;

        if ( cameraIndex == numCameraLocation )
        {
            // キャプチャを終了する
            bStartCapture = false;
            accumulateTime = 0;
            cameraIndex = materialIndex = objectIndex = lodIndex = 0;
            mStaticMeshComponent->SetStaticMesh(mStaticMesh[0][0]);
            mStaticMeshComponent->SetRelativeScale3D(FVector(scaleList[0]));
            mStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, currentYRotation, 0.0f));
        }
        else if ( (accumulateTime > timeToNextObject / 2) && bScreenShotFlag )
        {
            TCHAR tmpchar[128]; FString filename;
            // 比較を行うバリエーション / リメッシュのバリエーション
            _stprintf_s(tmpchar, sizeof(tmpchar), _T("%.7d_%.1d_%.1d.png"), startVariationIndex + variationIndex, rotationIndex, lodIndex);
            filename.AppendChars(tmpchar, sizeof(tmpchar));

            // スクリーンショットの撮影
                FScreenshotRequest screenshot = FScreenshotRequest();
            if (bDummyScreenShotFlag)
            {
                screenshot.RequestScreenshot("dummy.jpg", false, false);
                bDummyScreenShotFlag = bScreenShotFlag = false;
            }
            else
            {
                screenshot.RequestScreenshot(filename, false, false);
                bScreenShotFlag = false;
            }
        }
        else if ( accumulateTime > timeToNextObject )
        {
            if (currentYRotation > 270.0f)
            {
                lodIndex++;
                if (lodIndex == NUM_LOD)
                {
                    // 次のジオメトリに飛ぶ
                    GetRandomObjectId(remeshType, materialIndex, objectIndex, currentYRotation);
                    accumulateTime = -1.0f;
                    lodIndex = 0;
                    variationIndex++; iterationIndex++;
                    rotationIndex = -1;

                    if (iterationIndex == NUM_ONE_ITERATION)
                    {
                        iterationIndex = 0;
                        cameraIndex++;
                        SetActorLocation(cameraLocation[cameraIndex].actorLocation);
                        SetActorRotation(cameraLocation[cameraIndex].actorRotation);
                    }
                    bDummyScreenShotFlag = true;
                }
                else
                {
                    // 次の LOD に飛ぶ
                    currentYRotation -= 270.0f;
                    accumulateTime = -0.2f;
                    objectIndex++;
                    rotationIndex = 0;
                }
                UE_LOG(LogTemp, Warning, TEXT("remeshinType is %d, object index is %d"), remeshType, objectIndex);
                mStaticMeshComponent->SetStaticMesh(mStaticMesh[remeshType][objectIndex]);
            }
            else
            {
                // ローテーションのバリエーションを行う
                rotationIndex++;
                currentYRotation += 90.0f;
                accumulateTime = -0.2f;
            }
            mStaticMeshComponent->SetRelativeScale3D(FVector(scaleList[materialIndex]));
            mStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, currentYRotation, 0.0f));

            bScreenShotFlag = true;
        }
        else {
            accumulateTime += DeltaTime;
        }
    }
#else
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += CameraInput.X;
    SetActorRotation(NewRotation);

    if (!MovementInput.IsZero())
    {
        //Scale our movement input axis values by 100 units per second (移動入力軸の値を 1 秒あたり 100 単位でスケーリング)
        MovementInput = MovementInput.SafeNormal() * 100.0f;
        FVector NewLocation = GetActorLocation();
        NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime * 5.0f;
        NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime * 5.0f;
        SetActorLocation(NewLocation);
    }
#endif

}

// Called to bind functionality to input
void ACameraWithSpawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    //Hook up every-frame handling for our four axes (4 つの軸に各フレーム処理を接続)
    InputComponent->BindAxis("MoveForward", this, &ACameraWithSpawn::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ACameraWithSpawn::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &ACameraWithSpawn::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &ACameraWithSpawn::YawCamera);

    // Respond when our "Grow" key is pressed or released. (StartCapture キーがリリースされた時に反応)
    InputComponent->BindAction("StartCapture", IE_Pressed, this, &ACameraWithSpawn::StartCapture);
}

//Input functions (入力関数)
void ACameraWithSpawn::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACameraWithSpawn::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ACameraWithSpawn::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void ACameraWithSpawn::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void ACameraWithSpawn::StartCapture()
{
#if CAPTURE_FINAL
    bStartCapture = bScreenShotFlag = true; bDummyScreenShotFlag = true;
    variationIndex = lodIndex = cameraIndex = iterationIndex = 0;
    rotationIndex = -1;
    
    GetRandomObjectId(remeshType, materialIndex, objectIndex, currentYRotation);
    SetActorLocation(cameraLocation[0].actorLocation);
    SetActorRotation(cameraLocation[0].actorRotation);
    mStaticMeshComponent->SetStaticMesh(mStaticMesh[remeshType][objectIndex]);
    mStaticMeshComponent->SetRelativeScale3D(FVector(scaleList[materialIndex]));
    mStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, currentYRotation, 0.0f));
    accumulateTime = -0.2f;
#else
    FVector actorLocation = GetActorLocation();
    FRotator actorRotation = GetActorRotation();

    UE_LOG(LogTemp, Log, TEXT("Kinuwaki4 :     { FVector(%f, %f, %f), FRotator(%f, %f, %f) },\n") , actorLocation[0], actorLocation[1], actorLocation[2],
        actorRotation.Pitch, actorRotation.Yaw, actorRotation.Roll);
#endif
}