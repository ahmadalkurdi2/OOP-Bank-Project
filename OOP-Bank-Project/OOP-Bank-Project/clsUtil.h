#pragma once
#include<iostream>
#include<string>
#include<ctime>
#include"clsDate.h"

using namespace std;

class clsUtil
{
public:
	enum enCharType { SmallLetter = 1, CapitalLetter, Digit, MixChars, SpecialCharacter };

	static void Srand()
	{
		srand(unsigned(time(NULL)));
	}

	static int RandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

	static char GetRandomCharacter(enCharType CharType)
	{
		if (CharType == MixChars)
			CharType = enCharType(RandomNumber(1, 3));
		switch (CharType)
		{
		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));
		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));
		case enCharType::Digit:
			return char(RandomNumber(48, 57));
		default:
			return char(RandomNumber(65, 90));
		}
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word;
		for (short i{ 0 }; i < Length; i++)
			Word += GetRandomCharacter(CharType);
		return Word;
	}

	static string GenerateKey(enCharType CharType = CapitalLetter)
	{
		string Key = GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		for (short i{ 0 }; i < NumberOfKeys; i++)
		{
			cout << "Key [" << i + 1 << "]: " << GenerateKey(CharType) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
	{
		for (short i{ 0 }; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short WordLength)
	{
		for (short i{ 0 }; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, WordLength);
	}

	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
	{
		for (short i{ 0 }; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static void Swap(int& A, int& B)
	{
		int Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(double& A, double& B)
	{
		double Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(bool& A, bool& B)
	{
		bool Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(char& A, char& B)
	{
		char Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& A, string& B)
	{
		string Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{
		Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
	}

	static void ShuffleArray(string arr[100], int arrLength)
	{
		Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
	}

	static string Tabs(short NumberOfTabs)
	{
		string t;
		for (short i{ 0 }; i < NumberOfTabs; i++)
			t += "\t";
		return t;
	}

	static string NumberToText(int Number)
	{
		if (Number == 0)
			return "";
		if (Number >= 1 && Number <= 19)
		{
			string arr[]{ "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return arr[Number - 1] + " ";
		}
		if (Number >= 20 && Number <= 99)
		{
			string arr[]{ "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return arr[Number / 10 - 2] + " " + NumberToText(Number % 10);
		}
		if (Number >= 100 && Number <= 199)
			return "One Hundred " + NumberToText(Number % 100);
		if (Number >= 200 && Number <= 999)
			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		if (Number >= 1000 && Number <= 1999)
			return "One Thousand " + NumberToText(Number % 1000);
		if (Number >= 2000 && Number <= 999999)
			return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		if (Number >= 1000000 && Number <= 1999999)
			return  "One Million " + NumberToText(Number % 1000000);
		if (Number >= 2000000 && Number <= 999999999)
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);

		if (Number >= 1000000000 && Number <= 1999999999)
			return  "One Billion " + NumberToText(Number % 1000000000);
		else
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
	}

	static string EncryptText(string Text, short EncryptionKey = 2)
	{
		for (short i{ 0 }; i < Text.length(); i++)
			Text[i] = char(int(Text[i]) + EncryptionKey);
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2)
	{
		for (short i{ 0 }; i < Text.length(); i++)
			Text[i] = char(int(Text[i]) - EncryptionKey);
		return Text;
	}
};

