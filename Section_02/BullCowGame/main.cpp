/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void Printintro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

/*
	the entry point for our application
*/
int main()
{	
	do
	{
		Printintro();
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0;
}


void Printintro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |----- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	int32 LengthOfWord = 0;
	std::cout << "Choose the length of the word(3-7): ";
	std::cin >> LengthOfWord;
	BCGame.SetHiddenWordLength(LengthOfWord);
	std::cout << "Can you guess the " << LengthOfWord << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

/*
	First resets the game then checks validity of guess and if valid
	checks to see if it is right. Repeats until game is won or the
	player has run out of turns.
*/
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;

	//loop asking for guesses while the game
	//is NOT won and there are still trys remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		//checks to see if guess was valid
		FText Guess = GetValidGuess();

		//Submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cow = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU DID IT - YOU WON.\n";
	}
	else
	{
		std::cout << "Sorry, better luck next time.\n";
	}

	return;
}

/*
	loop continually until the user gives a valid guess
*/
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//get the guess from the user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Please enter your word in lower case.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}

/*
	Asks the player if they want to play again. If the first letter begins with
	an y/Y it will restart the game otherwise it will end the game
*/
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word?(y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
