#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
	Super::BeginPlay();
	Isograms = GetValidWords(Words);
	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput)
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(PlayerInput);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the bull cows!"));
	bGameOver = false;
	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
	HiddenWordLength = HiddenWord.Len();
	Lives = 5;

	PrintLine(TEXT("Guess the %i letter word"), HiddenWordLength);
	PrintLine(TEXT("You have total %i lives."), Lives);
	PrintLine(TEXT("\nType in your guess. \npress enter to continue..."));
	//PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& guess)
{
	//checking player guess
	if (guess == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}
	if (!IsIsogram(guess))
	{
		PrintLine(TEXT("\nNo repeating letters, guess again"));
		return;
	}
	Lives--;
	PrintLine(TEXT("Lost a life"));
	if (guess.Len() != HiddenWordLength)
	{
		PrintLine(TEXT("Sorry, try guessing again!\nyou have %i lives remaining\n"), Lives);
		PrintLine(TEXT("The hidden word is %i letter long"), HiddenWordLength);
	}
	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("Game over! you are out of lives."));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

		EndGame();
		return;
	}
	FBullCowCount Score = GetBullCows(guess);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
	PrintLine(TEXT("Guess again! You have %i lives left"), Lives);
}

const bool UBullCowCartridge::IsIsogram(const FString& word)
{
	for (int32 Index = 0; Index < word.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < word.Len(); Comparison++)
			if (word[Index] == word[Comparison])
			{
				return false;
			}
	}
	return true;
}

const TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList)
{
	TArray<FString> ValidWords;

	for (FString word : WordList)
	{
		if (word.Len() >= 4 && word.Len() <= 8 && IsIsogram(word))
		{
			ValidWords.Emplace(word);
		}
	}
	return ValidWords;
}

const FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess)
{
	FBullCowCount Count;
	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex ++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			Count.Bulls++;
			continue;
		}
		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex ++)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}
