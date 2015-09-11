#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class UnOrderDatabase :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to undo order :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->UnOrderDatabase(dbname);
			return result;
		}
		std::wstring toString() {
			return L"UnOrder";
		}
		std::wstring description() {
			return L"undo order database.";
		}

		UnOrderDatabase(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}