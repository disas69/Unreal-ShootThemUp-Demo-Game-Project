// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "Player/STUPlayerState.h"

class FSTUUtils
{
public:
    template <typename T>
    static T* GetPlayerComponent(AActor* PlayerActor)
    {
        if (!PlayerActor)
        {
            return nullptr;
        }

        return PlayerActor->FindComponentByClass<T>();
    }

    static bool IsEnemy(const AController* Controller1, const AController* Controller2)
    {
        if (Controller1 == nullptr || Controller2 == nullptr || Controller1 == Controller2)
        {
            return false;
        }

        const ASTUPlayerState* PlayerState1 = Controller1->GetPlayerState<ASTUPlayerState>();
        const ASTUPlayerState* PlayerState2 = Controller2->GetPlayerState<ASTUPlayerState>();

        if (PlayerState1 == nullptr || PlayerState2 == nullptr)
        {
            return false;
        }

        return PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
};