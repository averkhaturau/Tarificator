#ifndef __WINDOWSVERSIONDEFINER_H__
#define __WINDOWSVERSIONDEFINER_H__


enum CVersions {Win9x, WinNT};

// ����� ������������ ������ Windows
class CWindowsVersionDefiner
{
	private:
	protected:
		// ������ ������. Read-only, �����������.
		CVersions m_Version;
	public:
		// ��� ���������� ���������� ����������� ������ � ���������
		// ���� ���� � m_Version
		CWindowsVersionDefiner();
		~CWindowsVersionDefiner();

		// �������
		CVersions GetVersion() {return m_Version;};
};


#endif // __WINDOWSVERSIONDEFINER_H__