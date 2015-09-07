#pragma once
#include "GeekErrorCode.h"
#include <string>

namespace geek {
	class CommandContext {
	public:
		virtual ~CommandContext() {}
	};
	class ICommand {
	public:
		virtual GeekResult Excute() = 0;
		virtual std::wstring toString() = 0;
		virtual std::wstring description() = 0;
	public:
		virtual ~ICommand() {}
	};
}