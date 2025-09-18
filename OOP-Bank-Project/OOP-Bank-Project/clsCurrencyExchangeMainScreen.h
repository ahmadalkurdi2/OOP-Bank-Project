#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"
#include <iomanip>

using namespace std;

class clsCurrencyExchangeMainScreen :protected clsScreen
{
	enum enCurrenciesMainMenuOptions {
		eListCurrencies = 1, eFindCurrency, eUpdateCurrencyRate, eCurrencyCalculator
		, eMainMenu
	};

	static enCurrenciesMainMenuOptions _ReadCurrenciesMainMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return enCurrenciesMainMenuOptions(Choice);
	}

	static void _GoBackToCurrenciesMenu()
	{
		cout << "\n\nPress any key to go back to Currencies Menu...";
		system("pause>0");
		ShowCurrenciesMenu();
	}

	static void _ShowCurrenciesListScreen()
	{
		//cout << "\nCurrencies List Screen Will be here...\n";
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will be here...\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateCurrencyRateScreen()
	{
		//cout << "\nUpdate Currency Rate Screen Will be here...\n";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}
	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will be here...\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMainMenuOption(enCurrenciesMainMenuOptions CurrenciesMainMenuOptions)
	{
		switch (CurrenciesMainMenuOptions)
		{
		case enCurrenciesMainMenuOptions::eListCurrencies:
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenu();
			break;
		}
		case enCurrenciesMainMenuOptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenu();
			break;
		}
		case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenu();
			break;
		}
		case enCurrenciesMainMenuOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrenciesMenu();
			break;
		}
		case enCurrenciesMainMenuOptions::eMainMenu:
		{
			//do nothing here the main screen will handle it :-) ;
		}
		}
	}
public:
	static void ShowCurrenciesMenu()
	{
		system("cls");
		_DrawScreenHeader("Currency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrenciesMainMenuOption(_ReadCurrenciesMainMenuOption());
	}
};

