#pragma once
#include "GeekDbManager.h"
#include "Commands.h"
#include <unordered_map>
namespace geek {
	class CommandSystem {
	public:
		void Run();
		static CommandSystem& Create() {
			static CommandSystem csystem;
			return csystem;
		}
	private:
		void ShowMenu();
		void help();
		void exit();
		GeekResult ExcuteCommand(std::wstring command);
		CommandSystem() {
			m_DbManager = new GeekDbManager();

			//base commands
			insertCommand(new CreateDatabaseCommand(m_DbManager));
			insertCommand(new CreateDataCommand(m_DbManager));
			insertCommand(new DeleteDatabaseCommand(m_DbManager));
			insertCommand(new DeleteDataCommand(m_DbManager));
			insertCommand(new DumpDatabaseCommand(m_DbManager));
			insertCommand(new ListDatabaseCommand(m_DbManager));
			insertCommand(new ModifyDataCommand(m_DbManager));
			insertCommand(new LoadDatabaseCommand(m_DbManager));
			insertCommand(new QueryDataCommand(m_DbManager));

			//order commands
			insertCommand(new OrderDatabase(m_DbManager));
			insertCommand(new UnOrderDatabase(m_DbManager));
			//advance commands
		}
		CommandSystem(const CommandSystem& t);

	private:
		void insertCommand(IGeekDbCommand *command) {
			if (command != nullptr) {
				auto &it = m_CommandMap.find(command->toString());
				if (it != m_CommandMap.end()) {
					return;
				}
				m_CommandMap.insert({ command->toString(), command });
			}
		}
	private:
		std::unordered_map<std::wstring, IGeekDbCommand*> m_CommandMap;
		GeekDbManager *m_DbManager;
		friend class HelpCommand;
	};
}