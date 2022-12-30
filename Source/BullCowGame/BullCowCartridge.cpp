#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
	Super::BeginPlay();

	SetupGame();

	//prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the bull cows!"));
	bGameOver = false;
	HiddenWord = TEXT("cakes");
	HiddenWordLength = HiddenWord.Len();
	Lives = 5;

	PrintLine(TEXT("Guess the %i letter word"), HiddenWordLength);
	PrintLine(TEXT("Type in your guess. \npress enter to continue..."));

	const TCHAR HW[] = TEXT("cakes");
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString guess)
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
	if (guess.Len() != HiddenWordLength)
	{
		PrintLine(TEXT("Sorry, try guessing again!\nyou have %i lives remaining\n"), Lives);
		PrintLine(TEXT("The hidden word is %i letter long"), HiddenWordLength);
		return;
	}
	Lives--;
	PrintLine(TEXT("Lost a life"));
	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("Game over! you are out of lives."));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

		EndGame();
		return;
	}
	PrintLine(TEXT("Guess again! You have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString word)
{
	return true;
}
