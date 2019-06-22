#ifndef __REGISTRYCLASS_H__
#define __REGISTRYCLASS_H__

#include <string>


class CRegistryClass
{
	// �� ���� ����������� ������, ���������� � ��������

	private:
		void DoDeleteEverything();
	protected:
		// ������ ��� RegOpenKeyEx:
		// ����
		HKEY m_hKey;
		// Subkey name
		std::string* m_sSubKeyName;
		// Security access mask
		REGSAM m_SAM;
	public:
		CRegistryClass();
		virtual ~CRegistryClass();

		// �������
		HKEY GetKey() {return m_hKey;};
		void SetKey(HKEY hNewKey) {m_hKey = hNewKey;};
		std::string* GetSubKeyName() {return m_sSubKeyName;};
		REGSAM GetSecurityAccessMask() {return m_SAM;};
		void SetSecurityAccessMask(REGSAM NewSAM) {m_SAM = NewSAM;};
};


#endif // __REGISTRYCLASS_H__