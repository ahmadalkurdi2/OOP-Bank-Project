#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsString.h"
#include"clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode { EmptyMode, UpdateMode, AddNewMode };
	enMode _Mode;

	string _AccountNumber, _PinCode;
	float _AccountBalance{ 0 };
	bool _MarkedForDelete{ false };

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClientData = clsString::Split(Line, Separator);
		return clsBankClient(enMode::UpdateMode, vClientData.at(0), vClientData.at(1),
			vClientData.at(2), vClientData.at(3),
			vClientData.at(4), vClientData.at(5), stof(vClientData.at(6)));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient& Client, string Separator = "#//#")
	{
		string sClientRecord;
		sClientRecord += Client.FirstName + Separator;
		sClientRecord += Client.LastName + Separator;
		sClientRecord += Client.Email + Separator;
		sClientRecord += Client.Phone + Separator;
		sClientRecord += Client.AccountNumber() + Separator;
		sClientRecord += Client.PinCode + Separator;
		sClientRecord += to_string(Client.AccountBalance);

		return sClientRecord;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient>& vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
			for (clsBankClient& C : vClients)
				if (C.MarkedForDeleted() == false)
					MyFile << _ConvertClientObjectToLine(C) << endl;
		MyFile.close();
	}

	void _Update()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string sDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << sDataLine << endl;
			MyFile.close();
		}
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient& DestinationClient, string UserName, string Separator = "#//#")
	{
		string TansferLogRecord;
		TansferLogRecord += clsDate::GetSystemDateTimeString() + Separator;
		TansferLogRecord += AccountNumber() + Separator;
		TansferLogRecord += DestinationClient.AccountNumber() + Separator;
		TansferLogRecord += to_string(Amount) + Separator;
		TansferLogRecord += to_string(AccountBalance) + Separator;
		TansferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TansferLogRecord += UserName;
		return TansferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	struct stTransferLogRecord;

	static stTransferLogRecord  _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;

		vector<string> vTransferLogRecordLine = clsString::Split(Line, Separator);
		TransferLogRecord.DateTime = vTransferLogRecordLine.at(0);
		TransferLogRecord.SourceAccountNumber = vTransferLogRecordLine.at(1);
		TransferLogRecord.DestinationAccountNumber = vTransferLogRecordLine.at(2);
		TransferLogRecord.Amount = stof(vTransferLogRecordLine.at(3));
		TransferLogRecord.srcBalanceAfter = stof(vTransferLogRecordLine.at(4));
		TransferLogRecord.destBalanceAfter = stof(vTransferLogRecordLine.at(5));
		TransferLogRecord.UserName = vTransferLogRecordLine.at(6);

		return TransferLogRecord;
	}

public:

	struct stTransferLogRecord
	{
		string DateTime, SourceAccountNumber, DestinationAccountNumber, UserName;
		float Amount, srcBalanceAfter, destBalanceAfter;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	_declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return !Client.IsEmpty();
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveResults { svFaildEmptyObject, svSucceeded, svFaildAccountNumberExists };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
			TotalBalances += Client.AccountBalance;
		return TotalBalances;
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
			return false;

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector<stTransferLogRecord> GetTransferLogList()
	{
		vector<stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{
				TransferRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLogRecord.push_back(TransferRecord);
			}
			MyFile.close();
		}
		return vTransferLogRecord;
	}

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}*/
};