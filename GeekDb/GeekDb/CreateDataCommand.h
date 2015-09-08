#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class CreateDataCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of database you want to operate :";
			std::wstring dbname;
			std::wcin >> dbname;
			std::wcout << std::endl;
			std::wcout << L"please input key of the Data you want to create :";
			std::wstring key;
			std::wcin >> key;
			std::wcout << std::endl;
			std::wcout << L"please input value of key you input :";
			std::wstring value;
			std::wcin >> value;
			GeekResult result = m_manager->InsertDatabase(dbname, { key, value });
			return result;
		}
		std::wstring toString() {
			return L"Create";
		}
		std::wstring description() {
			return L"Create a Data.";
		}

		CreateDataCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}