#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& guess);
	const bool IsIsogram(const FString& word);
	const TArray<FString> GetValidWords(const TArray<FString>& WordList);
	const FBullCowCount GetBullCows(const FString& Guess);

private:
	FString HiddenWord;
	int32 HiddenWordLength;
	int32 Lives;
	bool bGameOver;
	TArray<FString> Isograms;
};
