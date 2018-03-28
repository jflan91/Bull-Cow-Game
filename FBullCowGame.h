#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase



};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;


	bool IsGameWon() const; 
	EWordStatus CheckGuessValidity(FString) const;


	void Reset(); //ToDo make a more rich return value.
	// Provide a method for counting bulls and cows and increasing try number assuming valid guess
	FBullCowCount SubmitValidGuess(FString);


private:
	//see consturctor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bWin;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	
};