#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class OrderDatabase :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to order :";
			std::wstring dbname;
			std::wcin >> dbname;
			GeekResult result = m_manager->OrderDatabase(dbname);
			return result;
		}
		std::wstring toString() {
			return L"Order";
		}
		std::wstring description() {
			return L"Notify when database changed.";
		}

		OrderDatabase(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}