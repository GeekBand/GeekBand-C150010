#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class DumpDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to Dump :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->DumpDatabase(dbname,dbname);
			return result;
		}
		std::wstring toString() {
			return L"DumpDb";
		}
		std::wstring description() {
			return L"Dump a database to file.";
		}

		DumpDatabaseCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}