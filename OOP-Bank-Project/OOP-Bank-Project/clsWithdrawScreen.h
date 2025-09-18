#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsWithdrawScreen :protected clsScreen
{
	static void _PrintClient(clsBankClient& Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t   Withdraw Screen");

		cout << "Please enter client account number? ";
		string AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.";
			cout << "\nPlease enter a valid account number? ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nPlease enter Withdraw amount? ";
		double Amount = clsInputValidate<double>::ReadNumber();

		cout << "\nAre you sure you want to perform this transaction? ";
		char Answer{ 'n' };
		cin >> Answer;

		if (toupper(Answer) == 'Y')
			if (Client.Withdraw(Amount))
			{
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
			else
			{
				while (!Client.Withdraw(Amount))
				{
					cout << "\nCannot withdraw, Insufficient Balance!\n";
					cout << "\nAmount to withdraw is: " << Amount;
					cout << "\nYour Balance is: " << Client.AccountBalance;
					cout << "\nPlease enter valid Withdraw amount? ";
					Amount = clsInputValidate<double>::ReadNumber();
				}
				cout << "\n\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client.AccountBalance;
			}
		else
			cout << "\nOperation was canceled.\n";
	}
};

