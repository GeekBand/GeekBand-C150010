#include "stdafx.h"
#include "GeekMapDb.h"
#include "GeekUtils.h"
#include <map>
#include <algorithm>

geek::GeekResult geek::GeekMapDb::InsertKeyValue(INPARAM const GeekKeyValue & entry) {
	m_kvContainer.insert(entry);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::UpdateKeyValue(INPARAM const GeekKeyValue & entry) {
	KeyValueIterator it = m_kvContainer.find(entry.first);
	if (it == m_kvContainer.end()) {
		return GEEK_ERROR_ENTRYNOTFOUND;
	}

	(*it).second = entry.second;
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::DeleteKeyValue(INPARAM const std::wstring & wszKey) {
	if (IsNullOrEmpty(wszKey)) {
		return GEEK_ERROR_INVALIDPARAM;
	}

	KeyValueIterator it = m_kvContainer.find(wszKey);
	if (it == m_kvContainer.end()) {
		return GEEK_ERROR_ENTRYNOTFOUND;
	}

	m_kvContainer.erase(wszKey);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::QueryKeyValue(
	INPARAM const std::wstring & wszKey,
	OUTPARAM std::vector<GeekKeyValue>& entries) {

	if (IsNullOrEmpty(wszKey)) {
		return GEEK_ERROR_INVALIDPARAM;
	}
	KeyValueIterator it = m_kvContainer.find(wszKey);
	if (it == m_kvContainer.end()) {
		return GEEK_ERROR_ENTRYNOTFOUND;
	}
	entries.push_back(*it);
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::DumpKeyValues(INPARAM const std::wstring & wszFileName) {
	if (IsNullOrEmpty(wszFileName)) {
		return GEEK_ERROR_INVALIDPARAM;
	}

	GeekDbStorage *p_stg = new GeekDbStorage(wszFileName, this->m_Metadata, true);
	if (p_stg == nullptr) {
		return GEEK_ERROR_OUTOFMEMORY;
	}
	
	GeekResult result = p_stg->AddRange(m_kvContainer.cbegin(),m_kvContainer.cend());
	DISPOSE_OBJECT(p_stg);
	
	return result;
}

geek::GeekResult geek::GeekMapDb::LoadKeyValues(
	INPARAM const std::wstring & wszFileName,
	OUTPARAM std::wstring & wszName) {

	if (IsNullOrEmpty(wszFileName)) {
		return GEEK_ERROR_INVALIDPARAM;
	}
	GeekDbStorage* pstg = new GeekDbStorage(wszFileName, this->m_Metadata, false);
	if (pstg == nullptr) {
		return GEEK_ERROR_FILENOTFOUND;
	}
	KeyValueContainer().swap(m_kvContainer);
	wszName.clear();

	GeekResult result = pstg->LoadAll(m_Metadata, m_kvContainer);
	wszName.assign(m_Metadata.wszName);
	DISPOSE_OBJECT(pstg);
	return GEEK_SUCCESS;
}

void geek::GeekMapDb::TraverseKeyVaues(void) {
	std::for_each(m_kvContainer.begin(), m_kvContainer.end(),
		geek::PrintKeyValue());
}

const std::size_t geek::GeekMapDb::GetSize(void) const {
	return m_kvContainer.size();
}
