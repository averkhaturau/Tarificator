#include "stdafx.h"

#include "Encryptor.h"
#include "Hasher.h"

std::string CEncryptor::CryptString(const std::string& sPassword)
{
	// пока что это временная затычка для первой(ых) версии
	srand(m_Key);
	std::string _sResult = "";
	for (int i = 0; i < sPassword.size(); ++i)
		_sResult += sPassword[i] ^ rand();

	return _sResult;
}

std::string CEncryptor::EncryptString(const std::string& sPassword)
{
	// временно, пользуясь симметричностью
	return CryptString(sPassword);
}