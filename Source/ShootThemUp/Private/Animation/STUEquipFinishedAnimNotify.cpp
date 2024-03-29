// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    OnNotify.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation, EventReference);
}