#include "stdafx.h"
#include "GeekMapDb.h"
#include "GeekUtils.h"
#include <map>
#include <algorithm>

geek::GeekResult geek::GeekMapDb::InsertKeyValue(INPARAM const GeekKeyValue & entry) {
	m_kvContainer.insert(entry);
	logger->info(LoggerContext(L"插入一条数据"));
	Notify();
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::UpdateKeyValue(INPARAM const GeekKeyValue & entry) {
	KeyValueIterator it = m_kvContainer.find(entry.first);
	if (it == m_kvContainer.end()) {
		logger->error(LoggerContext(L"没有找到要修改的数据"));
		return GEEK_ERROR_ENTRYNOTFOUND;
	}

	(*it).second = entry.second;
	logger->error(LoggerContext(L"修改了一条数据"));
	Notify();
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::DeleteKeyValue(INPARAM const std::wstring & wszKey) {
	if (IsNullOrEmpty(wszKey)) {
		logger->error(LoggerContext(L"要修改的数据名为空"));
		return GEEK_ERROR_INVALIDPARAM;
	}

	KeyValueIterator it = m_kvContainer.find(wszKey);
	if (it == m_kvContainer.end()) {
		logger->error(LoggerContext(L"没有找到要删除的数据"));
		return GEEK_ERROR_ENTRYNOTFOUND;
	}

	m_kvContainer.erase(wszKey);
	logger->info(LoggerContext(L"删除了一条数据"));
	Notify();
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::QueryKeyValue(
	INPARAM const std::wstring & wszKey,
	OUTPARAM std::vector<GeekKeyValue>& entries) {

	if (IsNullOrEmpty(wszKey)) {
		logger->error(LoggerContext(L"要查询的数据名为空"));
		return GEEK_ERROR_INVALIDPARAM;
	}
	KeyValueIterator it = m_kvContainer.find(wszKey);
	if (it == m_kvContainer.end()) {
		logger->error(LoggerContext(L"没有找到要查询的数据"));
		return GEEK_ERROR_ENTRYNOTFOUND;
	}
	entries.push_back(*it);
	logger->error(LoggerContext(L"查询到了一条数据"));
	Notify();
	return GEEK_SUCCESS;
}

geek::GeekResult geek::GeekMapDb::DumpKeyValues(INPARAM const std::wstring & wszFileName) {
	if (IsNullOrEmpty(wszFileName)) {
		logger->error(LoggerContext(L"要Dump的文件名为空"));
		return GEEK_ERROR_INVALIDPARAM;
	}

	GeekDbStorage *p_stg = new GeekDbStorage(wszFileName, this->m_Metadata, true);
	if (p_stg == nullptr) {
		logger->error(LoggerContext(L"没有找到要Dump的文件"));
		return GEEK_ERROR_OUTOFMEMORY;
	}

	GeekResult result = p_stg->AddRange(m_kvContainer.cbegin(), m_kvContainer.cend());
	DISPOSE_OBJECT(p_stg);

	if (result == GEEK_SUCCESS) {
		logger->info(LoggerContext(L"文件成功Dump"));
		Notify();
	}
	return result;
}

geek::GeekResult geek::GeekMapDb::LoadKeyValues(
	INPARAM const std::wstring & wszFileName,
	OUTPARAM std::wstring & wszName) {

	if (IsNullOrEmpty(wszFileName)) {
		logger->error(LoggerContext(L"要加载的文件名为空"));
		return GEEK_ERROR_INVALIDPARAM;
	}
	GeekDbStorage* pstg = new GeekDbStorage(wszFileName, this->m_Metadata, false);
	if (pstg == nullptr) {
		logger->error(LoggerContext(L"没有找到要加载的文件"));
		return GEEK_ERROR_FILENOTFOUND;
	}
	KeyValueContainer().swap(m_kvContainer);
	wszName.clear();

	GeekResult result = pstg->LoadAll(m_Metadata, m_kvContainer);
	wszName.assign(m_Metadata.wszName);
	DISPOSE_OBJECT(pstg);

	logger->info(LoggerContext(L"文件成功加载"));
	Notify();
	return GEEK_SUCCESS;
}

void geek::GeekMapDb::TraverseKeyVaues(void) {
	std::for_each(m_kvContainer.begin(), m_kvContainer.end(),
		geek::PrintKeyValue());
	logger->info(LoggerContext(L"遍历了一遍数据库"));
	Notify();
}

const std::size_t geek::GeekMapDb::GetSize(void) const {
	return m_kvContainer.size();
}
