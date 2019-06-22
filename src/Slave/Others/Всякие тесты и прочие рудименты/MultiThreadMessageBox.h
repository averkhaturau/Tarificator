#ifndef __MULTITHREADMESSAGEBOX_H__
#define __MULTITHREADMESSAGEBOX_H__

#include <string>

#include "ErrorsLogger.h"


class CMultiThreadMessageBox
{
	// ����� ��� ������ MessageBox �� ������� ������, �.�. ��� ������
	// �� ���� �� ������ ���������� ���������� � ���� �� ������������
	// �������. ���� parent ������� NULL, �� �� ����������� �� ���������.

	public:
			struct CMessageBoxParameters
			{
				// ��������� ��� �������� � ������� ������� ������

				// ��������� ��� MessageBox
				HWND hWnd;
				LPSTR lpText;
				LPSTR lpCaption;
				UINT uType;

				// ��� �������� �����
				CMultiThreadMessageBox* pParentClass;
			};
	private:
	protected:
		CMessageBoxParameters m_Parameters;
		// Handle ������� ������. ��� ����������� �������������.
		HANDLE m_hAnotherThread;
		// Instance ����������
		HINSTANCE m_hInstance;
		// Atom ��� ������������ �������� ���������� ����
		ATOM m_ClassAtom;
		// ��� �������� handle'� ���������������� ����
		HWND m_hWnd;
		// ��������������� �������. ������ �������� ��������� �� �������.
		CErrorsLogger* m_pErrorsLogger;

		void OnAnotherThreadEnds();
		void DoDeleteEverything();

		friend DWORD WINAPI DoShowMessageBox(LPVOID lpParameter);
	public:
		// �����������. � �������� ��������� ���� �������� ��� instance,
		// ������� ���������� �������� � �������� ��������� WinMain.
		CMultiThreadMessageBox(HINSTANCE hInstance, CErrorsLogger* pErrorsLogger);
		// ����������
		~CMultiThreadMessageBox();

		void MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
};


#endif // __MULTITHREADMESSAGEBOX_H__