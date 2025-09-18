#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen :protected clsScreen
{
	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = clsInputValidate<float>::ReadNumber();
		return Amount;
	}

	static clsCurrency _GetCurrency(string Message)
	{
		cout << Message;
		string CurrencyCode = clsInputValidate<string>::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Not Found, Please Enter Valid Currency Code: ";
			CurrencyCode = clsInputValidate<string>::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency& Currency, string Title = "Currency Card:")
	{
		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency& Currency1, clsCurrency& Currency2)
	{
		_PrintCurrencyCard(Currency1, "Convert From:");
		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
			return;
		cout << "\nConverting from USD to " << Currency2.CurrencyCode() << "...\n";
		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();
	}
public:
	static void ShowCurrencyCalculatorScreen()
	{
		char Continue{ 'y' };

		while (toupper(Continue) == 'Y')
		{
			system("cls");

			_DrawScreenHeader("\tUpdate Currency Screen");

			clsCurrency CurrencyFrom = _GetCurrency("Enter Currency Code to Convert From:");
			clsCurrency CurrencyTo = _GetCurrency("Enter Currency Code to Convert To:");

			float Amount = _ReadAmount();
			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
			cout << "\n\nDo you want to perform another calculation? [Y/N]: ";
			cin >> Continue;
		}
	}
};

