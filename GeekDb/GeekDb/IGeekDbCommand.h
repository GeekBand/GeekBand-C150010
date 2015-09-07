#pragma once
#include "GeekDbManager.h"
#include "ICommand.h"
#include <string>
namespace geek {

	class GeekDbCommandContext :public CommandContext {
	public:
		GeekDbCommandContext(GeekKeyValue entry):Entry(entry){}
		GeekKeyValue Entry;

	public:
		virtual ~GeekDbCommandContext(){}
	};

	class IGeekDbCommand: public ICommand{
	public:
		IGeekDbCommand(GeekDbManager *manager) {
			m_manager = manager;
		}
		virtual ~IGeekDbCommand(){}
	private:
		GeekDbManager *m_manager;
	};
}