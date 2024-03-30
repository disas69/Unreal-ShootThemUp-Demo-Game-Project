// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

class FAnimUtils
{
public:
    template <typename T>
    static T* FindAnimNotify(UAnimSequenceBase* Animation)
    {
        if (Animation != nullptr)
        {
            TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;
            for (const FAnimNotifyEvent& NotifyEvent : NotifyEvents)
            {
                T* TargetAnimNotify = Cast<T>(NotifyEvent.Notify);
                if (TargetAnimNotify != nullptr)
                {
                    return TargetAnimNotify;
                }
            }
        }

        return nullptr;
    }
};