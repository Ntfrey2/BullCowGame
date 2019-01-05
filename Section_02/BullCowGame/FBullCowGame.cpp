#pragma once

#include "FBullCowGame.h"

//to make syntax Unreal friendly
using int32 = int;

/*
	default constructor
*/
FBullCowGame::FBullCowGame() { Reset(); }

/*
	returns the number of tries the user has used
*/
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
/*
	returns the number of letters in the hidden word
*/
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
/*
	checks if the game is won or not
*/
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

/*
	Map of number of guesses and tries, so as the lenght of the word increase
	so do the number of tries
	returns the amount of tries
*/
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> GuessLengthToMaxTries{ {3, 5}, {4, 8}, {5, 11}, {6, 14}, {7, 17} };

	return GuessLengthToMaxTries[MyHiddenWord.length()];
}

/*
	intializies and resets all the variablea in the class
*/
void FBullCowGame::Reset()
{;
	MyHiddenWord = ChooseWord(HiddenWordLength);

	bIsGameWon = false;
	MyCurrentTry = 1;
	return;
}

void FBullCowGame::SetHiddenWordLength(int32 WordLength)
{
	HiddenWordLength = WordLength;
}

/*
	Checks 3 different criteria for a guess to see if the guess is valid.
	Returns the error or nothing if it passes
*/
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess))//if the guess isn't all lower case 
	{
		return EGuessStatus::Not_Lower_Case;
	} 
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	} 
	else
	{ 
		return EGuessStatus::OK;
	}
		
}

/*
	recieves a valid guess, increments turn 
	returns count
*/
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int WordLength = MyHiddenWord.length(); //assuming the same length as guess

	//loop through all variables in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		//compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
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
	if (GetHiddenWordLength() == BullCowCount.Bulls)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}

	return BullCowCount;
}

/*
	Helper function for checking validity of a guess
*/
bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
		
	return true;
}

/*
	Helper function for checking validity of a guess
*/
bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) 
		{
			return false;
		}
	}

	return true;
}

FString FBullCowGame::ChooseWord(int32 Choice) const
{
	switch (Choice)
	{
	case 3:
		return "ant";
	case 4:
		return "lamp";
	case 5:
		return "ranch";
	case 6:
		return "planet";
	case 7:
		return "spanish";
	default:
		return "";
	}
}
