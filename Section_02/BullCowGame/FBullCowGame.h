/* 
	The game logic (no view code or direct user interaction). 
	The game is a simple gues the word game based on Mastermind
*/

#pragma once
#include <string>
#include <map>
#include <iostream>

//to make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lower_Case
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FString ChooseWord(int32) const;

	void Reset();
	void SetHiddenWordLength(int32);
	FBullCowCount SubmitValidGuess(FString);


private:
	//see constructor for intialization
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	int32 HiddenWordLength;
};
