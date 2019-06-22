#ifndef __MULTITHREADMESSAGEBOX_H__
#define __MULTITHREADMESSAGEBOX_H__

#include <string>

#include "ErrorsLogger.h"


class CMultiThreadMessageBox
{
	// Нужен для вывода MessageBox из другого потока, т.к. при выводе
	// из того же потока приложение тормозится и даже не обрабатывает
	// мессаги. Если parent мессаги NULL, то он подменяется на служебный.

	public:
			struct CMessageBoxParameters
			{
				// Параметры для передачи в функцию второго потока

				// Параметры для MessageBox
				HWND hWnd;
				LPSTR lpText;
				LPSTR lpCaption;
				UINT uType;

				// Для обратной связи
				CMultiThreadMessageBox* pParentClass;
			};
	private:
	protected:
		CMessageBoxParameters m_Parameters;
		// Handle второго потока. Для внутреннего использования.
		HANDLE m_hAnotherThread;
		// Instance приложения
		HINSTANCE m_hInstance;
		// Atom для последующего создания экземпляра окна
		ATOM m_ClassAtom;
		// Для хранения handle'а вспомогательного окна
		HWND m_hWnd;
		// Ответственность снаружи. Просто хранится указатель на логгера.
		CErrorsLogger* m_pErrorsLogger;

		void OnAnotherThreadEnds();
		void DoDeleteEverything();

		friend DWORD WINAPI DoShowMessageBox(LPVOID lpParameter);
	public:
		// Конструктор. В качестве параметра надо передать тот instance,
		// который приложение получает в качестве параметра WinMain.
		CMultiThreadMessageBox(HINSTANCE hInstance, CErrorsLogger* pErrorsLogger);
		// Деструктор
		~CMultiThreadMessageBox();

		void MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
};


#endif // __MULTITHREADMESSAGEBOX_H__