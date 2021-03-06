// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyConst.h"
#include "CameraWithSpawn.generated.h"

UCLASS()
class SUNTEMPLE_API ACameraWithSpawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ACameraWithSpawn(const FObjectInitializer& ObjectInitializer);

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UStaticMeshComponent* mStaticMeshComponent;
    UStaticMesh* mStaticMesh[NUM_OBJECT];
    UMaterial*  mMaterial[NUM_MATERIAL];

    // タイマー
    float accumulateTime;

    // スクリーンショットの変数
    bool bStartCapture, bScreenShotFlag, bDummyScreenShotFlag;
    int remeshType, objectIndex, materialIndex;
    int variationIndex, lodIndex, rotationIndex, iterationIndex, cameraIndex;
    float currentYRotation, currentDistance;

    //Input variables (入力変数)
    FVector2D MovementInput;
    FVector2D CameraInput;

    //Input functions (入力関数)
    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void PitchCamera(float AxisValue);
    void YawCamera(float AxisValue);
    void StartCapture();
};

