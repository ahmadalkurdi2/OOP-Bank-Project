#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen :protected clsScreen
{
	static void _PrintCurrencyRecordLine(clsCurrency& Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate() << endl;
	}

	static void _PrintHorizontalLine()
	{
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;
	}
public:
	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency> vCurrencys = clsCurrency::GetCurrenciesList();
		string Title = "\tCurrencies List Screen";
		string Subtitle = "\t (" + to_string(vCurrencys.size()) + ") Currencies Found";

		_DrawScreenHeader(Title, Subtitle);

		_PrintHorizontalLine();
		
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";

		_PrintHorizontalLine();

		if(vCurrencys.size()==0)
			cout << "\t\t\t\tNo Currencies Available In the System!";
		else
			for(clsCurrency &Currency:vCurrencys)
				_PrintCurrencyRecordLine(Currency);
		_PrintHorizontalLine();

	}
};

