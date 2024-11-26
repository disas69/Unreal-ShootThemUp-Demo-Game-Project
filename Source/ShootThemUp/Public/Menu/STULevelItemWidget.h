// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STULevelItemWidget.generated.h"

struct FLevelData;
class UButton;
class UTextBlock;
class UImage;

DECLARE_MULTICAST_DELEGATE_OneParam(FLevelItemSelected, int32);

UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

    void SetLevelData(int32 Index, const FLevelData& Data);
    void SetSelected(bool bIsSelected) const;
    void SetFocused(bool bIsFocused) const;

    FLevelItemSelected LevelFocused;
    FLevelItemSelected LevelSelected;

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelName;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelPreview;

    UPROPERTY(meta = (BindWidget))
    UImage* Frame;

    UPROPERTY(meta = (BindWidget))
    UButton* SelectLevelButton;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    int32 LevelIndex = -1;
    
    UFUNCTION()
    void SelectLevel();

    UFUNCTION()
    void FocusLevel();
};
