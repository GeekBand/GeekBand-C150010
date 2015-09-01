#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <map>
#include "ILogger.h"
#include "GeekDefs.h"
#include "GeekUtils.h"

namespace geek {
	class FileLogger : public ILogger {
	public:
		GeekResult debug(LoggerContext& context);
		GeekResult info(LoggerContext& context);
		GeekResult notice(LoggerContext& context);
		GeekResult warning(LoggerContext& context);
		GeekResult error(LoggerContext& context);
		GeekResult critical(LoggerContext& context);
		GeekResult alert(LoggerContext& context);
		GeekResult emergency(LoggerContext& context);

	public:
		void Save() {
			_mkdir("DbLogFile");
			fs = std::wofstream(path, std::ios::app | std::ios::out);
			for (auto &logItem : LogData) {
				fs << ws2s(logItem).c_str() << std::endl;
			}
			LogData.clear();
		}
	public:
		FileLogger(const GeekDbMetadata& meta) {
			path = std::wstring(L"DbLogFile/") + meta.wszName + L".log";
		}
		~FileLogger() {}
	private:
		std::vector<std::wstring> LogData;
		std::wofstream fs;
		std::wstring path;

	private:
		GeekResult PushData(const std::wstring& level, const std::wstring& data) {
			LogData.push_back(GetCurrentDate() + L" " + level + L":" + data);
			return GEEK_SUCCESS;
		}
	};
}