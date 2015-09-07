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

			insertCommand(new CreateDatabaseCommand(m_DbManager));
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