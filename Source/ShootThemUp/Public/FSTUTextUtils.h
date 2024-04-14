// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

class FSTUTextUtils
{
public:
    static FString FormatTime(float TimeSeconds)
    {
        const int32 TotalSeconds = FMath::RoundToInt(TimeSeconds);
        const int32 Minutes = TotalSeconds / 60;
        const int32 Seconds = TotalSeconds % 60;

        const FString StrMinutes = FString::Printf(TEXT("%02d"), Minutes);
        const FString StrSeconds = FString::Printf(TEXT("%02d"), Seconds);

        return FString::Printf(TEXT("%s:%s"), *StrMinutes, *StrSeconds);
    }

    static FText TextFromInt(int32 Number)
    {
        return FText::FromString(FString::FromInt(Number));
    }

    static FText TextFromFloat(float Number)
    {
        return FText::FromString(FString::SanitizeFloat(Number));
    }

    static FText TextFromString(const FString& String)
    {
        return FText::FromString(String);
    }
};
