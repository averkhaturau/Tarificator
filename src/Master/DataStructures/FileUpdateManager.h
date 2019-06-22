#ifndef __FILEUPDATEMANAGER_H__
#define __FILEUPDATEMANAGER_H__

#include "UpdateManager.h"
#include "Saving\MasterBoundStorer.h"

#include <string>


// ���������� � ��� �������������, ��� ��� �������������� ������
// ���������� ������� ��� ���� �������������� �������� �� ��������
// �������� � ������� ������������ ���� ������ - � ����� � ������
// �������.
class CFileUpdateManager : public CUpdateManager
{
	public:
		typedef std::string CFileName;

	private:
	protected:
		// ���� � ��������, � ������� ����� ����������� ���������� �
		// ����������. ����� �������������� �������� ���� �����������
		// ��� �������������������. ����, ����� � ����� �����������
		// ����� '\'.
		CFileName m_DirectoryPath;
		// �� ��������� - ������
		char m_cTempSymbol;
		// ������� ��� �����. ��� ���� ������ ����� �������
		// GetValidFileName, DoPrepareBeforeUpdate � �.�..
		CFileName m_BaseFileName;

		void DoRemoveReadOnlyAttribute(CFileName* pName);
		void DoCheckFilesExistance(bool& bBaseFileExists, bool& bTempFileExists);
	public:
		CFileUpdateManager();

		CFileUpdateManager(CMasterBoundStorer* pStorer);

		virtual ~CFileUpdateManager();


		// ����� ������� ���� ����� ������� ���� �������� m_BaseFileName

		// ���������� ��� (� ������ �����) ��������� �����. ���� ���
		// �� ������ ������ ����� - ���������� ������ ������.
		virtual CFileName GetValidFileName();
		// ��������� ���������� ����� ����������� �����. ���������� ���
		// ����� (� ������ �����) ��� ����������. 
		virtual CFileName DoPrepareBeforeUpdate();
		// ��������� ����������� ������ ����������
		virtual void DoFinalizeUpdate();

		// �������
		void SetDirectoryPath(CFileName* pNew) {m_DirectoryPath = *pNew;};
		CFileName* GetDirectoryPath() {return &m_DirectoryPath;};
		void SetTempSymbol(char cNew) {m_cTempSymbol = cNew;};
		char GetTempSymbol() {return m_cTempSymbol;};
		void SetBaseFileName(CFileName* pNew) {m_BaseFileName = *pNew;};
		CFileName* GetBaseFileName() {return &m_BaseFileName;};
};

#endif // __FILEUPDATEMANAGER_H__