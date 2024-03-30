// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

class FSTUUtils
{
public:
    template <typename T>
    static T* GetPlayerComponent(APawn* PlayerPawn)
    {
        if (!PlayerPawn)
        {
            return nullptr;
        }

        return PlayerPawn->FindComponentByClass<T>();
    }
};