#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber(string stDestionation)
	{
		cout << "\nPlease Enter Account Number to Transfer " + stDestionation + ": ";
		string AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient& SourceClient)
	{
		float Amount{ 0 };
		cout << "\nPlease Enter Amount to Transfer: ";
		Amount = clsInputValidate<float>::ReadNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate<float>::ReadNumber();
		}
		return Amount;
	}
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("From"));
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));
		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre you sure you want to perform this operation? [Y/N] ";
		char Answer{ 'n' };
		cin >> Answer;

		if (toupper(Answer) == 'Y')
			if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
				cout << "\nTransfer Succeeded!\n";
			else
				cout << "\nTransfer Failed!\n";
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};

