// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Animation/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    OnNotify.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation, EventReference);
}