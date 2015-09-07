//*************************************************
// Module:  GeekDbStorage.h
// Notices: Copyright (c) 2015 Zhang Wenjie
//*************************************************
#pragma once

#include "GeekUtils.h"
#include "GeekErrorCode.h"
#include "GeekDefs.h"
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <ole2.h>

#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)
#pragma warning(disable : 4995)
#pragma comment(lib, "Ole32.lib")

namespace geek
{
	//
	// Storage implementation for the geek database.
	// By taking the advantages of the IStorage COM interface,
	// key/values could be stored in a compound file structure.
	//
	class GeekDbStorage
	{
	public:
		GeekDbStorage(
			INPARAM const std::wstring& wszFileName,
			INPARAM const GeekDbMetadata& metadata,
			INPARAM const bool createNew)
			: m_wszFileName(wszFileName),
			  m_Metadata(metadata)
		{
			if (createNew)
			{
				this->CreateStorage();
			}
			else
			{
				if (IsFileExists(wszFileName))
					this->OpenStorage();
				else
					this->CreateStorage();
			}
		}

		~GeekDbStorage()
		{
			RELEASE_OLE_OBJECT(m_pstg);
		}

	public:
		GeekResult Add(INPARAM const GeekKeyValue& entry);
		template <typename ConstKeyValueIter>
		GeekResult AddRange(INPARAM const ConstKeyValueIter& begin, INPARAM const ConstKeyValueIter& end);
		GeekResult AddRange(INPARAM const std::vector<GeekKeyValue>& entries);
		
		//
		// Load all key/value entries from the storage.(map)
		//
		GeekResult LoadAll(
			OUTPARAM GeekDbMetadata& metadata,
			OUTPARAM std::map<std::wstring, std::wstring>& entries
			);

		//
		// Load all key/value entries from the storage.(vector)
		//
		GeekResult LoadAll(
			OUTPARAM GeekDbMetadata& metadata,
			OUTPARAM std::vector<GeekKeyValue>& entries
		);

	private:
		//
		// For more information about IStorage and compound files,
		// refer to: https://msdn.microsoft.com/en-us/library/windows/desktop/aa378938(v=vs.85).aspx
		// and: https://msdn.microsoft.com/en-us/library/windows/desktop/aa380015(v=vs.85).aspx
		//
		GeekResult CreateStorage(void);
		GeekResult OpenStorage(void);

		GeekResult WriteStringEntry(
			INPARAM IStream* pstm, 
			INPARAM const std::wstring& wsz
		);

		GeekResult ReadStringEntry(
			INPARAM  IStream*	pstm,
			OUTPARAM WCHAR**	ppwz,
			OUTPARAM DWORD*		pcch
		);

		inline GeekResult ReadExact(
			INPARAM  IStream*	pstm,
			INPARAM  void*		pv,
			INPARAM  ULONG		cb,
			OUTPARAM ULONG*		pcb)
		{
			HRESULT hr		= S_OK;
			ULONG   cbRead	= 0;

			if (pstm == NULL || pv == NULL)
				return GEEK_ERROR_NULLPOINTER;

			if (pcb == NULL)
				pcb = &cbRead;

			hr = pstm->Read(pv, cb, pcb);
			if (SUCCEEDED(hr) && *pcb != cb)
				return GEEK_ERROR_READSTMFAILED;

			return GEEK_SUCCESS;
		}

		inline GeekResult WriteExact(
			INPARAM  IStream*	 pstm,
			INPARAM  void const* pv,
			INPARAM  ULONG		 cb,
			OUTPARAM ULONG*		 pcb)
		{
			if (pstm == NULL || pv == NULL)
				return GEEK_ERROR_INVALIDPARAM;

			HRESULT	hr			= S_OK;
			ULONG	cbWritten	= 0;
			if (pcb == NULL)
				pcb = &cbWritten;

			hr = pstm->Write(pv, cb, pcb);
			if (SUCCEEDED(hr) && *pcb != cb)
				return GEEK_ERROR_WRITESTMFAILED;
			
			return GEEK_SUCCESS;
		}

		//
		// Constants for storage and stream names.
		//
		const wchar_t* const s_wszStorageNameGeekMetadata = L"GeekMetadata";
		const wchar_t* const s_wszStorageNameGeekPackage = L"GeekDatabasePackage";
		const wchar_t* const s_wszStreamNameDatabaseName = L"06DatabaseName";

	private:
		IStorage* m_pstg = NULL;
		std::wstring m_wszFileName;
		GeekDbMetadata m_Metadata;
	};


	template<typename ConstKeyValueIter>
	GeekResult geek::GeekDbStorage::AddRange(INPARAM const ConstKeyValueIter & begin, INPARAM const ConstKeyValueIter & end) {
		if (m_pstg == NULL)
			return GEEK_ERROR_NULLPOINTER;

		HRESULT		hr = S_OK;
		GeekResult	result = GEEK_SUCCESS;
		IStorage*	pstgGeekPackage = NULL;
		IStream*	pstm = NULL;
		ConstKeyValueIter it = begin;

		// Locate the "GeekDatabasePackage" storage.
		hr = this->m_pstg->OpenStorage(
			s_wszStorageNameGeekPackage,
			NULL,
			STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
			NULL, 0, &pstgGeekPackage);
		ON_FAILED_RETURN(hr, result, GEEK_ERROR_CREATESTGFAILED);

		while (it != end) {
			const OLECHAR* wszName = (*it).first.c_str();
			hr = pstgGeekPackage->CreateStream(
				wszName,
				STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
				0,
				0,
				&pstm);
			ON_FAILED_RETURN(hr, result, GEEK_ERROR_CREATESTMFAILED);

			result = this->WriteStringEntry(pstm, (*it).second);
			ON_GEEKFAILED_RETURN(result);

			it++;
		}

		// Commit all changes.
		hr = pstgGeekPackage->Commit(STGC_DEFAULT);
		ON_FAILED_RETURN(hr, result, GEEK_ERROR_COMMITSTGFAILED);

	e_Exit:
		RELEASE_OLE_OBJECT(pstgGeekPackage);
		RELEASE_OLE_OBJECT(pstm);
		return result;
	}
}