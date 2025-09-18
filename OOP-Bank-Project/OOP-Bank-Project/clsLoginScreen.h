#pragma once
#include <iostream>
#include "clsUser.h"
#include<iomanip>
#include"clsMainScreen.h"
#include"Global.h"

class clsLoginScreen :protected clsScreen
{
	static bool _Login()
	{
		bool LoginFailed{ false };

		string Username, Password;

		short FaildLoginCount{ 0 };

		do
		{
			if (LoginFailed) 
			{
				FaildLoginCount++;
				cout << "\nInvalid username or password. Please try again.\n\n" << endl;
				cout << "\nYou have " << (3-FaildLoginCount) << " trials to login.\n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYou are locked after 3 failed trials.\n\n";
				return false;
			}


			cout << "Enter your username: ";
			getline(cin >> ws, Username);

			cout << "Enter your password: ";
			getline(cin, Password);

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		return _Login();
	}
};
