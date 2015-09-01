#include "stdafx.h"
#include "FileLogger.h"

geek::GeekResult geek::FileLogger::debug(LoggerContext & context) {
	PushData(L"debug", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::info(LoggerContext & context) {
	PushData(L"info", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::notice(LoggerContext & context) {
	PushData(L"notice", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::warning(LoggerContext & context) {
	PushData(L"warning", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::error(LoggerContext & context) {
	PushData(L"error", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::critical(LoggerContext & context) {
	PushData(L"critical", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::alert(LoggerContext & context) {
	PushData(L"alert", context.msg);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::FileLogger::emergency(LoggerContext & context) {
	PushData(L"emergency", context.msg);
	return GEEK_SUCCESS;
}
