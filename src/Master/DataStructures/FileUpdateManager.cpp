#include "stdafx.h"

#include "FileUpdateManager.h"


CFileUpdateManager::CFileUpdateManager()
{
		try
		{
			m_DirectoryPath = "";
			m_cTempSymbol = '~';
			m_BaseFileName = "";
		}
		catch(...)
		{
			throw ;
		}
}
// End of CFileUpdateManager()

CFileUpdateManager::CFileUpdateManager(CMasterBoundStorer* pStorer)
{
	m_cTempSymbol = '~';
	pStorer->ReadFileUpdateManager(this);
}
// End of CFileUpdateManager()


CFileUpdateManager::~CFileUpdateManager()
{
}
// End of ~CFileUpdateManager()


CFileUpdateManager::CFileName CFileUpdateManager::GetValidFileName()
{
	bool bBaseFileExists, bTempFileExists;
	DoCheckFilesExistance(bBaseFileExists, bTempFileExists);

	CFileName TempFileName = m_DirectoryPath + m_cTempSymbol + m_BaseFileName;

		// Если присутствует временный - он обязательно валидный
		if (bTempFileExists)
		{
			DoRemoveReadOnlyAttribute(&TempFileName);
			rename((TempFileName).c_str(), (m_DirectoryPath + m_BaseFileName).c_str());
			return m_DirectoryPath + m_BaseFileName;
		}
		// Если отсутствует временный файл и присутствует оригинальный -
		// оригинальный является валидным
		if ( bBaseFileExists )
			return m_DirectoryPath + m_BaseFileName;

	return "";
}
// End of GetValidFileName()


CFileUpdateManager::CFileName CFileUpdateManager::DoPrepareBeforeUpdate()
{
	CFileName TempFileName = m_DirectoryPath + m_cTempSymbol + m_BaseFileName;
	DoRemoveReadOnlyAttribute(&TempFileName);
	remove( (TempFileName).c_str() );
	rename((m_DirectoryPath + m_BaseFileName).c_str(),
				(TempFileName).c_str());

	return m_DirectoryPath + m_BaseFileName;
}
// End of DoPrepareBeforeUpdate()


void CFileUpdateManager::DoFinalizeUpdate()
{
	bool bBaseFileExists, bTempFileExists;
	DoCheckFilesExistance(bBaseFileExists, bTempFileExists);

		if (bBaseFileExists)
		{
			CFileName TempFileName = m_DirectoryPath + m_cTempSymbol + m_BaseFileName;
			// Просто удаляет темповый файл
			DoRemoveReadOnlyAttribute(&TempFileName);
			remove( TempFileName.c_str() );
		}
		else
				if (bTempFileExists)
				{
					CFileName TempFileName = m_DirectoryPath + m_cTempSymbol + m_BaseFileName;
					rename((TempFileName).c_str(), (m_DirectoryPath + m_BaseFileName).c_str());
				}

	// Скидывает все на диск
	_flushall();
}
// End of DoFinalizeUpdate()


void CFileUpdateManager::DoRemoveReadOnlyAttribute(CFileName* pName)
{
	DWORD dwFileAttribs = GetFileAttributes(pName->c_str());
	SetFileAttributes(pName->c_str(), dwFileAttribs & (~FILE_ATTRIBUTE_READONLY));
}
// End of DoRemoveReadOnlyAttribute


void CFileUpdateManager::DoCheckFilesExistance(bool& bBaseFileExists, bool& bTempFileExists)
{
	FILE* pFile;
	pFile = fopen((m_DirectoryPath + m_BaseFileName).c_str(), "r");
		if (pFile)
		{
			bBaseFileExists = true;
			fclose(pFile);
		}
		else
		{
			bBaseFileExists = false;
			//fclose(pFile);
		};

	pFile = fopen((m_DirectoryPath + m_cTempSymbol + m_BaseFileName).c_str(), "r");
		if (pFile)
		{
			bTempFileExists = true;
			fclose(pFile);
		}
		else
		{
			bTempFileExists = false;
			// fclose(pFile);
		};
}
// End of DoCheckFilesExistance
