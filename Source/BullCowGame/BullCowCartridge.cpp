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
		//checking player guess
		if (Input == HiddenWord)
		{
			PrintLine(TEXT("You have won!"));
			EndGame();
		}
		else
		{
			if (Input.Len() != HiddenWord.Len())
			{
				PrintLine(TEXT("Hidden word is %i character long.\nYou have lost."), HiddenWordLength);
				EndGame();
			}
		}
	}

	//Check if isogram
	//prompt to guess again
	//Check right number of character
	//prompt to guess again
	//Check if Lives > 0
	//If yes guess again
	//Show lives left
	//if no show game over and hidden word
	//prompt to play again or quit
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to the bull cows!"));

	bGameOver = false;
	HiddenWord = TEXT("pizza");
	HiddenWordLength = HiddenWord.Len();
	Lives = 5;

	PrintLine(TEXT("Guess the %i letter word"), HiddenWordLength);
	PrintLine(TEXT("Type in your guess. \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}
