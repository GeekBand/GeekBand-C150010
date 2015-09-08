#pragma once
#include "IGeekDbCommand.h"
namespace geek {
	class ListDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			std::vector<std::wstring> names = m_manager->GetDBNames();
			int i = 0;
			for (auto &n : names) {
				std::wcout << ++i << ": " << n << std::endl;
			}
			return GEEK_SUCCESS;
		}
		std::wstring toString() {
			return L"ListDb";
		}
		std::wstring description() {
			return L"Look all databases.";
		}

		ListDatabaseCommand(GeekDbManager *mananger) :IGeekDbCommand(mananger) {}
	};
}