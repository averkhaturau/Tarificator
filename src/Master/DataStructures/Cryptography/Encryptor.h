#ifndef _LX_ENCRYPTION_H_INCLUDED__
#define _LX_ENCRYPTION_H_INCLUDED__

#include <string>

// class CEncryptor ������������ ��� �������� - ����������� ������
class CEncryptor
{
public:
	CEncryptor(){ m_Key = 0x39df4aec; };
	// ������� �������������, ��� ��������� ��� �������
	// �������� ���� �����
	std::string CryptString(const std::string& sPassword);
	std::string EncryptString(const std::string& sPassword);

protected:
	// ����� ������ �������� � �������� �����, �� �� ����, ������ ����
	int m_Key;
};

#endif // _LX_ENCRYPTION_H_INCLUDED__
