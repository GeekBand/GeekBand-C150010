#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class QueryDataCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::wcout << L"please input name of the database you want to operate :";
			std::wstring dbname;
			std::wcin >> dbname;
			std::wcout << std::endl;
			std::wcout << L"please input key of the Data you want to query :";
			std::wstring key;
			std::wcin >> key;
			std::wcout << std::endl;
			std::vector <GeekKeyValue> entries;
			GeekResult result = m_manager->QueryDatabase(dbname, key, entries);
			std::wcout << L"query result as follow :\n";
			for (size_t i = 0; i < entries.size(); ++i) {
				std::wcout << L"- " << entries[i].second << std::endl;
			}
			return result;
		}
		std::wstring toString() {
			return L"Query";
		}
		std::wstring description() {
			return L"Qeury a data.";
		}

		QueryDataCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}