#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

int main();

void AskForDifficulty();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;


// Entry point for the application 
int main()
{

	bool bPlayAgain = false;
	do 
	{
		AskForDifficulty();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain == true);

	
}

void AskForDifficulty()
{
	FString Response;
	std::cout << "Write a number between 1 and 9, in order to select a specific hidden word.\n";
    std::cout << "The difficulty increases as the number does. \n";
	std::getline(std::cin, BCGame.GetHiddenWordArray);
	//std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    //std::cout << " letter isogram I'm thinking of?\n";
	BCGame.Reset();
}

void PrintIntro()
{
	// introduce the game
	//constexpr int32 WORD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{

	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	//constexpr int32 NUMBER_OF_TURNS = 5;
	//for (int32 count = 1; count <= MaxTries; count++)

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{

		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << "| Cows= " << BullCowCount.Cows << std::endl << std::endl;
	}
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurrentTry << " out of " << BCGame.GetMaxTries() << std::endl;
		std::cout << "Enter your guess:";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters. \n\n";
			break;

		default:
			break;
		}
		return Guess;

	} while (Status != EGuessStatus::OK);
}

bool AskToPlayAgain()
{
	PrintGameSummary();

	std::cout << "Do you want to play again (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS!!! YOU WON \n\n";
	}

	else if (!BCGame.bGameIsWon)
	{
		std::cout << "SORRY :(...Better luck next time \n\n";
	}
}

