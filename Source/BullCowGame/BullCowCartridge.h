#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(FString guess);
bool IsIsogram(FString word);

	// Your declarations go below!
private:
	FString HiddenWord;
	int32 HiddenWordLength;
	int32 Lives;
	bool bGameOver;
	bool bIsIsogram;
};
