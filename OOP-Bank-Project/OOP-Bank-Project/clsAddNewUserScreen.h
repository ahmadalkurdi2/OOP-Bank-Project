#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
#include<iomanip>

class clsAddNewUserScreen :protected clsScreen
{
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter First Name: ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Last Name: ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate<string>::ReadString();

		cout << "\nEnter Permissions: ";
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

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			return -1;
		cout << "\nDo you want to give access to : \n ";
		cout << "\nShow Client List? y/n? ";
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

		cout << "\nShow Transactions? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pTranactions;

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
			Permissions += clsUser::enPermissions::pManageUsers;

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd New User Screen");
		string UserName;

		cout << "\nEnter User Name: ";
		UserName = clsInputValidate<string>::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name already exists, please enter another User Name: ";
			UserName = clsInputValidate<string>::ReadString();
		}
		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser added successfully.\n";
			_PrintUser(NewUser);
			break;
		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nError User was not saved because it's Empty";
			break;
		case clsUser::enSaveResults::svFaildUserExists:
			cout << "\nError User was not saved because UserName is used!\n";
			break;
		}
	}
};

