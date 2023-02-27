// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHud.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHud : public AHUD
{
	GENERATED_BODY()
	
public:
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
