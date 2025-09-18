#pragma once
#include<iostream>
#include<string>
#include"clsString.h"
#include<vector>
#include<fstream>

class clsCurrency
{
	enum enMode { EmptyMode, UpdateMode };
	enMode _Mode;

	string _Country, _CurrencyCode, _CurrencyName;
	float _Rate{ 0.0 };

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(Line, Separator);
		return clsCurrency(enMode::UpdateMode, vCurrencyData.at(0),
			vCurrencyData.at(1), vCurrencyData.at(2), stof(vCurrencyData.at(3)));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency& Currency, string Separator = "#//#")
	{
		return Currency.Country() + Separator + Currency.CurrencyCode() + Separator
			+ Currency.CurrencyName() + Separator + to_string(Currency.Rate());
	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector<clsCurrency> vCurrencys;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				vCurrencys.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencys;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency>& vCurrencys)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;
		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrencys)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> _vCurrencys = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : _vCurrencys)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencys);
	}

	static clsCurrency _GetEmptyCurrenyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	string Country()
	{
		return _Country;
	}
	string CurrencyCode()
	{
		return _CurrencyCode;
	}
	string CurrencyName()
	{
		return _CurrencyName;
	}
	float Rate()
	{
		return _Rate;
	}

	static vector<clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencyDataFromFile();
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrenyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrenyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return !C1.IsEmpty();
	}

	static vector<clsCurrency>GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return Amount / Rate();
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency& OtherCurrency)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (OtherCurrency.CurrencyCode() == "USD")
			return AmountInUSD;
		return AmountInUSD * OtherCurrency.Rate();
	}
};

