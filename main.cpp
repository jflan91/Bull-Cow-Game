/* This is the console exe, that makes use of the bull cow class.
This acts as the view in a MVC pattern and is responsible for all user interaction. 
For game logic see the FBullCowGame class. 
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

//entry point of our application
int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; //exit application
}

void PrintIntro()
{
	

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

//run game logic
void PlayGame()
{
	BCGame.Reset();
	

	// TODO Change for loop to while loop
	//loop through function as many times as the amount of guesses available
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();


		// Submit valid guess to the game
		FBullCowCount FBullCowCount = BCGame.SubmitValidGuess(Guess);
		//Print number of bulls and cows
		std::cout << "Bulls = " << FBullCowCount.Bulls;
		std::cout << ". Cows = " << FBullCowCount.Cows << "\n\n";

		BCGame.IsGameWon();
	}

	// TODO Summarize Game
	PrintGameSummary();
	return;
}


//get guess from player and print it out
	FText GetValidGuess()
{		
		EWordStatus Status = EWordStatus::Invalid_Status;

		do {
			std::cout << "Try: " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". What is your guess? ";
			FText Guess = "";
			std::getline(std::cin, Guess);

			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status)
			{
			case EWordStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;

			case EWordStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;

			case EWordStatus::Not_Lowercase:
				std::cout << "Please use lower case letters only.\n\n";
				break;

			default:
				return Guess;
				break;
			}
			
		} while (Status != EWordStatus::OK);

	
}

//asks player if they want to play again and returns the response
bool AskToPlayAgain()
{

	std::cout << "Do you want to play again with same word? Y/N ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, You Won!!!\n\n";
	}
	else
	{
		std::cout << "Sorry, you lost.\n\n";
	}
}

