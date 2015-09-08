#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class ModifyDataCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to operate :";
			std::wstring dbname;
			std::wcin >> dbname;
			std::wcout << std::endl;
			std::wcout << L"please input key of the Data you want to modify :";
			std::wstring key;
			std::wcin >> key;
			std::wcout << std::endl;
			std::wcout << L"please input value of the key :";
			std::wstring value;
			std::wcin >> value;
			GeekResult result = m_manager->UpdateDatabase(dbname,{key, value});
			return result;
		}
		std::wstring toString() {
			return L"Modify";
		}
		std::wstring description() {
			return L"Modify a data.";
		}

		ModifyDataCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}