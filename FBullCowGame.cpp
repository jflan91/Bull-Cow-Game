#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map



void FBullCowGame::Reset()
{ 
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "grape";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	bWin = false;
	
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bWin;
}


EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
	
}

//recieves Valid guess and returns Bull/ Cow count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	MyCurrentTry++;
	FBullCowCount FBullCowCount;

	//loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++)
	{
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			if (MyHiddenWord[HWChar] == Guess[GChar])
			{
				if (HWChar == GChar)
				{
					FBullCowCount.Bulls++;
				}
				else
				{
					FBullCowCount.Cows++;
				}
			}


		}
	}

	if (FBullCowCount.Bulls == HiddenWordLength)
	{
		bWin = true;
	}
	//compare letters against the hidden word

	return FBullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
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

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
