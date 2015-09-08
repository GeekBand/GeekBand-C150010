#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class LoadDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to load :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->LoadDatabase<GeekMapDb>(dbname, dbname);
			return result;
		}
		std::wstring toString() {
			return L"LoadDb";
		}
		std::wstring description() {
			return L"Load a database.";
		}

		LoadDatabaseCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}