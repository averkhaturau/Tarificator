#ifndef _LX_CRYPTOR_H_INCLUDED___
#define _LX_CRYPTOR_H_INCLUDED___

#include "Hasher.h"
#include "Encryptor.h"

class CCryptor : public CHasher, public CEncryptor
{
public:
	CCryptor(){};
	virtual ~CCryptor(){};


};

#endif // _LX_CRYPTOR_H_INCLUDED___