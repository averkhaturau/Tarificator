#ifndef _LX_HASHER_H_INCLUDED__
#define _LX_HASHER_H_INCLUDED__

#include <string>

/* ���������� ���������� ��������� �����*/
class CHasher
{
public:
	static __int64 Str2i64(const std::string& Pswrd);
};

#endif // _LX_HASHER_H_INCLUDED__