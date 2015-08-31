#pragma once
#include "GeekErrorCode.h"
#include <string>
namespace geek {

	class LoggerContext {
	public:
		std::wstring msg;
		virtual ~LoggerContext(){}
	};
	class ILogger {
	public:

		virtual GeekResult debug(LoggerContext& context) = 0;
		virtual GeekResult info(LoggerContext& context) = 0;
		virtual GeekResult notice(LoggerContext& context) = 0;
		virtual GeekResult warning(LoggerContext& context) = 0;
		virtual GeekResult error(LoggerContext& context) = 0;
		virtual GeekResult critical(LoggerContext& context) = 0;
		virtual GeekResult alert(LoggerContext& context) = 0;
		virtual GeekResult emergency(LoggerContext& context) = 0;
	public:
		virtual ~ILogger() {}
	};
}