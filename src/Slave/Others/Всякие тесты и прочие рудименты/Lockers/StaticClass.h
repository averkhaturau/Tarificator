#ifndef __STATICCLASS_H__
#define __STATICCLASS_H__


// ��������������� �����. ������� � �������� CInputLocker, CMouseLocker,
// CKeyboardLocker. ����� ������ ��� ����, ����� ������� static
// data member m_hModule, �.�. ��-������� �� ���������� (static
// data member, ����������� � �����-������ CInputLocker, �����������
// ����� ������ ��� ������ ������-����������, ������� �� ����������
// ������������ ������ �� ��� �������� ���������).
class CStaticClass
{
	private:
	protected:
		static HMODULE m_hModule;
	public:
		HMODULE& GetModule() {return m_hModule;};
};

#endif //__STATICCLASS_H__