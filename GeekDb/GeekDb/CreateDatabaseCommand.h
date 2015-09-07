#pragma once
#include "IGeekDbCommand.h"
namespace geek{
	class CreateDatabaseCommand :public IGeekDbCommand {
	public:
		GeekResult Excute() {
			return GEEK_SUCCESS;
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