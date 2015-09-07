#include "stdafx.h"
#include "CommandSystem.h"

void geek::CommandSystem::Run() {
	while (true) {
		ShowMenu();
		std::wstring command;
		std::wcin >> command;
		std::wcout << std::endl;
		//system("cls");
		ExcuteCommand(command);
	}
}

void geek::CommandSystem::ShowMenu() {
	PrintManyTimesCharInLine(L"=", 80);

	std::wcout << L"Welcome to GeekDb.\nyou can save, update, delete, query your database by command\n"
		<< L"input commands to excute\n(or input 'help' to watch commands, 'exit' to exit) \n:";

}

void geek::CommandSystem::help() {
	//using namespace std;
	std::wcout << L"you can input these commands:" << std::endl;
	int index = 1;
	for (auto &commandPiar : m_CommandMap) {
		std::wcout << index++ << L". command: " << commandPiar.second->toString() << "\n   description: " <<
			commandPiar.second->description() << std::endl;
	}

}

void geek::CommandSystem::exit() {
	::exit(0);
}

geek::GeekResult geek::CommandSystem::ExcuteCommand(std::wstring command) {
	if (command == L"help") {
		help();
		return GEEK_SUCCESS;
	}
	if (command == L"exit") {
		std::wcout << L"Are you exit?'y' or 'n' :";
		std::wstring s;
		std::wcin >> s;
		if (s == L"y") {
			exit();
		}
		else {
			return GEEK_SUCCESS;
		}
	}
	auto &it = m_CommandMap.find(command);
	if (it == m_CommandMap.end()) {
		std::cout << "Command Not Find.\n";
		return GEEK_ERROR_COMMANDNOTFIND;
	}
	GeekResult result = it->second->Excute();
	return result;
}
