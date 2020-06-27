#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTries; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return bGameIsWon; }

FString FBullCowGame::GetHiddenWord(FString Input) const
{
	TMap <FString, FString> InputToHiddenWord = { {"1","art"},{"2", "get"},{"3","cat"},{"4","man"},{"5","hold"},{"6", "grab"},{"7", "card"},{"8", "square" },{"9","phone"}, };
	return InputToHiddenWord[Input];
}

void FBullCowGame::Reset()
{
	MyHiddenWord = GetHiddenWord(GetHiddenWordArray);
	GetHiddenWordLength();
	bGameIsWon = false;
	MyCurrentTries = 1;
	return;
}


int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries{ { 3,6 }, { 4,8 }, { 5,10}, { 6,12} };
	return WordLengthToMaxTries [MyHiddenWord.length()];
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTries++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{


		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j])
			{

				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}

			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1){ return true;}

	TMap <char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	TMap <char, bool> UpperCaseLetter;
	for (auto Letter : Word)
	{
		if (!islower (Letter)) { return false; }
		else { return true; }
	}
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if  (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
    }
}
