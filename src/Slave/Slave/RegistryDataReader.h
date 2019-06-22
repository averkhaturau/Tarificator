#ifndef __REGISTRYDATAREADER_H__
#define __REGISTRYDATAREADER_H__

#include "NamesCollection.h"
#include "RegistryClass.h"


class CRegistryDataReader : public virtual CRegistryClass
{
	// �����, ��������������� ���, ��� ���� ��� ������ � ��������.
	private:
		// ������ ������ � ���� ���� - ������� exception. ������������ �
		// ReadOneName.
		void DoReadRegistryString(PHKEY phkRegistryKey,
					const std::string& ValueName, unsigned char* pValueData, DWORD& nSize);
	protected:
		// ��������� ���� �������. ����� �������� ����������.
		void DoOpenRegistryKey(PHKEY phkKey);
		// ���� ���� - ��������� ���� �������
		void DoCloseRegistryKey(PHKEY phkKey);
		// ��� ������� ���� ������������, ����� ��������� ������ �� �������
		void DoReadOneRegistryName(PHKEY phkRegistryKey, const std::string& ValueName, FileName& ValueData);
		// ������ DWORD � ����� �������� ����������
		void DoReadRegistryNumber(PHKEY phkRegistryKey,
					const std::string& ValueName, DWORD& ValueData);
		// ������ ���� �������� ��� �����, ������������� ����������
		// ���������. ���� bSlashEnded - ������, ����� ��������� ��������
		// ��� '\\'.
		void DoReadRegistryPath(PHKEY phkRegistryKey,
					const std::string& ValueName, std::string* pValueData, bool bSlashEnded);
		void DoReadRegistryInt64(PHKEY phkRegistryKey,
					const std::string& ValueName, __int64& ValueData);
	public:
		// ����������� �� ���������
		CRegistryDataReader();
		// ����������
		virtual ~CRegistryDataReader();
};


#endif // __REGISTRYDATAREADER_H__