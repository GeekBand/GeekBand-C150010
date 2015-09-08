#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class DeleteDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to Delete :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->DisposeDatabase(dbname);
			return result;
		}
		std::wstring toString() {
			return L"DeleteDb";
		}
		std::wstring description() {
			return L"Delete a database.";
		}

		DeleteDatabaseCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}