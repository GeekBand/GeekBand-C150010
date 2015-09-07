//******************************************************************
// Module:  GeekSequenceDb.cpp
//          Defines the entry point for the console application.
//
// Notices: Copyright (c) 2015 Zhang Wenjie
//******************************************************************

#include "stdafx.h"
#include "GeekDbManager.h"
#include "CommandSystem.h"
#include <iostream>
using namespace geek;

// The global database manager.
//geek::GeekDbManager g_DbManager;
//void CreateSequenceDatabase(const std::wstring& wszDumpFileName)
//{
//	std::wstring wszFileName = wszDumpFileName;
//	if (geek::IsNullOrEmpty(wszFileName))
//		wszFileName = L"sequence01.geekdb";
//		
//	geek::GeekKeyValue gkv[] = {
//		geek::GeekKeyValue(L"name", L"zhangwenjie"),
//		geek::GeekKeyValue(L"age", L"30"),
//		geek::GeekKeyValue(L"class", L"AABBCCC"),
//		geek::GeekKeyValue(L"grade", L"900"),
//		geek::GeekKeyValue(L"language", L"us-en"),
//		geek::GeekKeyValue(L"sex", L"male"),
//	};
//
//	g_DbManager.CreateDatabase<geek::GeekSequenceDb>(L"Testdb01");
//	g_DbManager.CreateDatabase<geek::GeekMapDb>(L"Testdb02");
//
//
//	g_DbManager.InsertDatabase(L"Testdb01", 
//		std::vector<geek::GeekKeyValue>(gkv, gkv + 6));
//	g_DbManager.InsertDatabase(L"Testdb02",
//		std::vector<geek::GeekKeyValue>(gkv, gkv + 6));
//
//	g_DbManager.TraverseDatabase(L"Testdb01");
//	std::cout << "------------------------\n";
//	g_DbManager.TraverseDatabase(L"Testdb02");
//	geek::GeekResult r = g_DbManager.DumpDatabase(L"Testdb01", 
//		wszFileName);
//	g_DbManager.DumpDatabase(L"Testdb02", wszFileName + L"2");
//}
//
//int main()
//{
//	CreateSequenceDatabase(L"db.geekdb");
//	
//	std::wstring wszName;
//	geek::GeekResult r = g_DbManager.LoadDatabase<geek::GeekSequenceDb>(
//		L"db.geekdb", wszName);
//	std::cout << "----------------------\n";
//	g_DbManager.TraverseDatabase(wszName);
//
//	getchar();
//	return 0;
//}

int main() {
	CommandSystem &system = CommandSystem::Create();
	system.Run();
	return 0;
}

