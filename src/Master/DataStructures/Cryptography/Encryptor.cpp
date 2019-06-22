#include "stdafx.h"

#include "Encryptor.h"
#include "Hasher.h"

std::string CEncryptor::CryptString(const std::string& sPassword)
{
	// ���� ��� ��� ��������� ������� ��� ������(��) ������
	srand(m_Key);
	std::string _sResult = "";
	for (int i = 0; i < sPassword.size(); ++i)
		_sResult += sPassword[i] ^ rand();

	return _sResult;
}

std::string CEncryptor::EncryptString(const std::string& sPassword)
{
	// ��������, ��������� ���������������
	return CryptString(sPassword);
}