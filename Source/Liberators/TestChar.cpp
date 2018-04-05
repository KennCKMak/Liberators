// Fill out your copyright notice in the Description page of Project Settings.

#include "TestChar.h"
#include "Engine.h"
#include "OnlineSubsystem.h"
#include "OnlineIdentityInterface.h"

// Sets default values
ATestChar::ATestChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestChar::BeginPlay()
{
	Super::BeginPlay();
	OnControllerConnectionHandle = FCoreDelegates::OnControllerConnectionChange.AddUFunction(this, FName("OnControllerConnectionChange"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Beginning")));


}

void ATestChar::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FCoreDelegates::OnControllerConnectionChange.Remove(OnControllerConnectionHandle);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Ending")));
}

void ATestChar::OnControllerConnectionChange_Implementation(bool Connected, int32 UserID, int32 ControllerID)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Connection change ControllerID: x: %d, Connected: %d"), ControllerID, Connected));
}

FString ATestChar::GetPlayerName_Implementation() {
	auto OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub != nullptr) {
		auto userIdentityPtr = OnlineSub->GetIdentityInterface();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found OnlineSubsystem")));
		if (userIdentityPtr.IsValid())
		{
			FString nickname = userIdentityPtr->GetPlayerNickname(0);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(*("Name: " + nickname)));
			return nickname;
		}
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Found no OnlineSubsystem")));
	}
	return "!!!111";
}

// Called every frame
void ATestChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

