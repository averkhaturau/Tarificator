#include "stdafx.h"

#include "MultiThreadMessageBox.h"


// Собственно создает второй поток и в нем показывает MessageBox
DWORD WINAPI DoShowMessageBox(LPVOID lpParameter)
{
	CMultiThreadMessageBox::CMessageBoxParameters* pParameters = (CMultiThreadMessageBox::CMessageBoxParameters*)lpParameter;
	MessageBox(pParameters->hWnd, pParameters->lpText, pParameters->lpCaption, pParameters->uType);

		if (pParameters->pParentClass)
		{
			pParameters->pParentClass->OnAnotherThreadEnds();
		}

	return 0;
}
// End of ::DoShowMessageBox


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }

  return 0;
}
// End of WindowProcedure


CMultiThreadMessageBox::CMultiThreadMessageBox(HINSTANCE hInstance, CErrorsLogger* pErrorsLogger)
{
	m_hAnotherThread = 0;

	m_Parameters.hWnd = 0;
	m_Parameters.lpCaption = 0;
	m_Parameters.lpText = 0;
	m_Parameters.uType = 0;
	m_Parameters.pParentClass = this;

	m_hWnd = 0;
	m_ClassAtom = 0;

	m_hInstance = hInstance;

	m_pErrorsLogger = pErrorsLogger;

		try
		{
			// Это все для создания служебного окна
			char cClassName[50] = "CMultiThreadMessageBox Window Class";

			WNDCLASS WndClass;
			WndClass.style = 0;
			WndClass.lpfnWndProc = WindowProcedure;
			WndClass.cbClsExtra = 0;
			WndClass.cbWndExtra = 0;
			WndClass.hInstance = hInstance;
			WndClass.hIcon = NULL;
			WndClass.hCursor = NULL;
			WndClass.hbrBackground = NULL;
			WndClass.lpszMenuName = NULL;
			WndClass.lpszClassName = &(cClassName[0]);

			m_ClassAtom = RegisterClass(&WndClass);

				if (!m_ClassAtom)
					throw CAnyLogableException("can't register window class 8-/", bDoNotWriteDuplicates);

			char cTitle[5] = " ";

			m_hWnd = CreateWindowEx(
						WS_EX_TOOLWINDOW,
						(LPCTSTR)m_ClassAtom,
						&(cTitle[0]),
						WS_DISABLED | WS_CHILD,
						0, 0, 10, 10,
						GetDesktopWindow(),
						NULL,
						m_hInstance,
						NULL);
			//m_hWnd = (HWND)1;

				if (!m_hWnd)
					throw CAnyLogableException("can't create window 8-/", bDoNotWriteDuplicates);
		}
		catch(CAnyLogableException& Error)
		{
			DoDeleteEverything();

			std::string ErrorString = "An error occured in CMultiThreadMessageBox::CMultiThreadMessageBox : ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			DoDeleteEverything();

			throw CAnyLogableException("An unknown error occured in CMultiThreadMessageBox::CMultiThreadMessageBox", bDoNotWriteDuplicates);
		}
}
// End of CMultiThreadMessageBox()


CMultiThreadMessageBox::~CMultiThreadMessageBox()
{
	DoDeleteEverything();
}
// End of ~CMultiThreadMessageBox()


void CMultiThreadMessageBox::DoDeleteEverything()
{
		if (m_hAnotherThread)
		{
			TerminateThread(m_hAnotherThread, 0);
			m_hAnotherThread = 0;
		}
		if (m_Parameters.lpText)
		{
			delete[] m_Parameters.lpText;
			m_Parameters.lpText = 0;
		}
		if (m_Parameters.lpCaption)
		{
			delete[] m_Parameters.lpCaption;
			m_Parameters.lpCaption = 0;
		}
}
// End of DoDeleteEverything()


void CMultiThreadMessageBox::MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
		try
		{
				if (m_hAnotherThread)
					return;

				// Копирую параметры в структуру для передачи
				if (hWnd)
					m_Parameters.hWnd = hWnd;
				else
					m_Parameters.hWnd = m_hWnd;

				if (m_Parameters.lpText)
				{
					delete[] m_Parameters.lpText;
					m_Parameters.lpText = 0;
				}
			m_Parameters.lpText = new char[strlen(lpText) + 1];
			strcpy(m_Parameters.lpText, lpText);

				if (m_Parameters.lpCaption)
				{
					delete[] m_Parameters.lpCaption;
					m_Parameters.lpCaption = 0;
				}
			m_Parameters.lpCaption = new char[strlen(lpCaption) + 1];
			strcpy(m_Parameters.lpCaption, lpCaption);

			m_Parameters.uType = uType;


			DWORD dwThreadID;
			HANDLE hThread = CreateThread(NULL, 0, DoShowMessageBox, &m_Parameters, 0, &dwThreadID);
			// Так хитро надо для того, чтобы не было глюка, если второй
			// поток закончит выполнение и обнулит m_hAnotherThread раньше,
			// чем пройдет проверка
			m_hAnotherThread = hThread;
				if (!hThread)
					throw CAnyLogableException("can't create thread 8-/", bDoNotWriteDuplicates);
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMultiThreadMessageBox::MessageBox : ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString, Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMultiThreadMessageBox::MessageBox", bDoNotWriteDuplicates);
		}
}
// End of MessageBox


void CMultiThreadMessageBox::OnAnotherThreadEnds()
{
		if (m_hAnotherThread)
		{
			CloseHandle(m_hAnotherThread);
			m_hAnotherThread = 0;
		}
}
// End of OnAnotherThreadEnds()
