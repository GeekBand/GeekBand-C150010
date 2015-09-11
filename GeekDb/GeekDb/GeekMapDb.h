//*************************************************
// Module:  GeekMapDb.h
// Notices: Copyright (c) 2015 blackerXHunter
//*************************************************

#pragma once

#include "GeekDb.h"
#include "GeekDbStorage.h"
#include "FileLogger.h"
#include <map>

namespace geek {
	//
	// Geek database implementation using std::vector
	//
	class GeekMapDb : public GeekDb {
	public:
		GeekMapDb(const GeekDbMetadata& metadata)
			: GeekDb(metadata) {
			context = new ManagerObserverContext();
			logger = new FileLogger(this->m_Metadata);
		}

		~GeekMapDb() { logger->Save(); }

	public:
		GeekResult InsertKeyValue(INPARAM const GeekKeyValue& entry);

		GeekResult UpdateKeyValue(INPARAM const GeekKeyValue& entry);

		GeekResult DeleteKeyValue(INPARAM const std::wstring& wszKey);

		GeekResult QueryKeyValue(
			INPARAM const std::wstring& wszKey,
			OUTPARAM std::vector<GeekKeyValue>& entries
			);

		GeekResult DumpKeyValues(INPARAM const std::wstring& wszFileName);

		GeekResult LoadKeyValues(
			INPARAM const std::wstring& wszFileName,
			OUTPARAM std::wstring& wszName
			);

		void TraverseKeyVaues(void);

		const std::size_t GetSize(void) const;

	private:
		void updateContext(int c = 0, int d = 0, int u = 0, int q = 0) {
			context = new ManagerObserverContext(c, d, u, q);
		}
		typedef std::map<std::wstring, std::wstring> KeyValueContainer;
		typedef KeyValueContainer::iterator KeyValueIterator;
		KeyValueContainer m_kvContainer;
	};

	//
	// Traits returns the concrete database type.
	//
	template<>
	struct GeekDbTraits<GeekMapDb> {
	public:
		typedef GeekMapDb Database;
	};
}