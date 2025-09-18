#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
{
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate<string>::ReadString();

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(clsUser& User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

	static int _ReadPermissionsToSet()
	{
		int Permissions{ 0 };
		char Answer{ 'n' };

		cout << "\nDo you want to give full access to this user? [Y/N]: ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			return -1;

		cout << "\nDo you want to give access to : \n\nShow Client List? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pListClients;

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pAddNewClient;

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pDeleteClient;

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pUpdateClients;

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pFindClient;

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pTranactions;

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pManageUsers;

		cout << "\nShow LogIn Register? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pShowLogInRegister;

		return Permissions;
	}

public:
	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\tUpdate User Screen");

		string UserName;
		cout << "\nEnter User Name: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name is not found, Enter again: ";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		cout << "\nDo you want to update this user? [Y/N]: ";
		char Answer{ 'n' };
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsUser::enSaveResults::svSucceeded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User);
				break;
			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError User was not saved because it's Empty";
				break;
			}
		}
	}

};

