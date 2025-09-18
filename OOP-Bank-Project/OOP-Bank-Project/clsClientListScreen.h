#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>

class clsClientListScreen :protected clsScreen
{
	static void _PrintClientRecordLine(clsBankClient& Client)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance << endl;
	}

	static void _DrawHorizontalBorder()
	{
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

public:
	static void ShowClientsList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
			return;

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t  Client List Screen";
		string Subtitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_DrawScreenHeader(Title, Subtitle);

		_DrawHorizontalBorder();
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		_DrawHorizontalBorder();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
			for (clsBankClient& Client : vClients)
				_PrintClientRecordLine(Client);
		_DrawHorizontalBorder();
	}
};

