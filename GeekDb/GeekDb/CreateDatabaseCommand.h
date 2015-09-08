#pragma once
#include "IGeekDbCommand.h"
namespace geek{
	class CreateDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to create :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->CreateDatabase<GeekMapDb>(dbname);
			return result;
		}
		std::wstring toString() {
			return L"CreateDb";
		}
		std::wstring description() {
			return L"Create a database.";
		}

		CreateDatabaseCommand(GeekDbManager *mananger):IGeekDbCommand(mananger){}
	};
}