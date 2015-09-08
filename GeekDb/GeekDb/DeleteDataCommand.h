#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class DeleteDataCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of database you want to operate :";
			std::wstring dbname;
			std::wcin >> dbname;
			std::wcout << std::endl;
			std::wcout << L"please input key of the Data you want to create :";
			std::wstring key;
			std::wcin >> key;
			GeekResult result = m_manager->DeleteDatabase(dbname, key);
			return result;
		}
		std::wstring toString() {
			return L"Create";
		}
		std::wstring description() {
			return L"Create a data.";
		}

		DeleteDataCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
};