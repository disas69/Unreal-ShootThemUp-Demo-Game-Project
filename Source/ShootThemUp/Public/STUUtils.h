// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

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
};