#ifndef _LX_ENCRYPTION_H_INCLUDED__
#define _LX_ENCRYPTION_H_INCLUDED__

#include <string>

// class CEncryptor предназначен для шифровки - расшифровки данных
class CEncryptor
{
public:
	CEncryptor(){ m_Key = 0x39df4aec; };
	// классом гарантируется, что следующие две функции
	// инверсны друг друга
	std::string CryptString(const std::string& sPassword);
	std::string EncryptString(const std::string& sPassword);

protected:
	// здесь храним открытый и закрытый ключи, но не знаю, какого типа
	int m_Key;
};

#endif // _LX_ENCRYPTION_H_INCLUDED__
