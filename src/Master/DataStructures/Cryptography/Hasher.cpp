/*implementation of CHasher*/
#include "stdafx.h"

#include "Hasher.h"

__int64 CHasher::Str2i64(const std::string& Pswrd)
{
	__int64 Result = 0xf397e8af3b6149d8; // ������ ����� �����, ����� �� 0
	const unsigned int _PswrdSize = Pswrd.size();
	if (!_PswrdSize) return Result;
	std::string _sPswrd = Pswrd;

	// ��������� ����� ���������� ��������� ����� � ������������ � ������ ������
	srand((_PswrdSize|(_PswrdSize<<3)|(_PswrdSize<<6))
		+((_PswrdSize<<4)|(_PswrdSize<<5)));

	// �������� ��� ������

	bool _cycle_is_not_over;
	do{
		_cycle_is_not_over = false;
		// �������� �� ����
		int i; // ��� ������������� � MS Visual C++ � Borland C++ ������������
		for (i = 0; i < 63; ++i)
		{
			int _Index = rand() % _PswrdSize; // ����� ����
			Result += (__int64)(_sPswrd[_Index] ^= (char)rand()) << i;
		}
		// ���������, ����� �� ��������� ����
		for (i = 0; i < _PswrdSize; ++i)
			_cycle_is_not_over |= (_sPswrd[i] == Pswrd[i]);

	}while(_cycle_is_not_over);

	return Result;
}
// end of __int64 CHasher::Str2i64(const std::string& Pswrd)
