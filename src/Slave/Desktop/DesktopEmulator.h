#ifndef __DESKTOPEMULATOR_H__
#define __DESKTOPEMULATOR_H__


#include "IconButtonsCollection.h"
#include "..\Slave\SlaveDataReader.h"
#include "..\Slave\Logger.h"
#include "IconsWindow.h"
#include "RemainingTimeSlaveDescription.h"
#include "StatusBar.h"
#include "ApplicationWaiter.h"
#include "TaskbarEmulator.h"
#include "..\Slave\ApplicationInfosCollection.h"


const cdeHideTaskbar = true;
const cdeUnHideTaskbar = false;


class CDesktopEmulator
{
	public:
		typedef void CALLBACK CTimerProcedure(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	private:
		void DoDeleteEverything();
	protected:
		void InitializeForNewUser(std::string* a_pUserName);
		void DoHideTaskbar(bool a_bHide);

		void DoFillIcons(HINSTANCE a_hInst);
		void DoFillIconButtonsCollection(CIconButtonsCollection* a_pButtons,
					FileName& a_Dir, DWORD* a_pdwAdded, FileName& a_Extention);
		void DoCalcSpecialWindowExtends(DWORD a_dwSppecialLinks);
		void DoFillStatusBar();

		void EnableIconsWindow(bool a_bEnabled);

		//HANDLE GetCurrentUserPrimaryToken();

		void CreateDesktopEmulationWindow();
		// Задает требуемое положение окон. Вызывается по таймеру и из
		// DoFillIcons. Возвращает true, если окна были успешно перемещены.
		bool DoRePosWindows();

		// Возвращает координату левого края в пикселах для кнопки с
		// иконой номер dwXPos. Нумерация с 0.
		//DWORD GetIconButtonXCoord(DWORD dwXPos);
		// Возвращает координату верхнего края в пикселах для кнопки с
		// иконой номер dwYPos. Нумерация с 0.
		//DWORD GetIconButtonYCoord(DWORD dwYPos);

		HWND m_hDesktopEmulation;

		CIconsWindow* m_pIconsWindow;
		CIconsWindow* m_pSpecialIconsWindow;

		FileName m_sPreliminaryIconsFolderPath;
		// Полное имя файла Runner'а
		FileName m_sRunnerName;

		CApplicationWaiter* m_pApplicationWaiter;
		CApplicationWaiter* m_pPreliminaryAppWaiter;

		CSlaveStatusBar* m_pStatusBar;
		CApplicationInfosCollection* m_pAllowedSessionsCollection;

		// Возвращает handle запущенного приложения или 0 (для слежения
		// за выходом этого приложения)
		HANDLE RunShortcut(CShortcutInfo* a_pShortcut);
		// Primary token юзера
		HANDLE m_hPrimaryToken;
		// Impersonating token юзера
		HANDLE m_hImpersonatingToken;
		DWORD m_dwSessionId;
		BOOL m_bNeedToCloseSysTray;

		bool m_bEnabled;
		bool m_bIconsFilledForThisUser;
		bool m_bFillingIcons;
		bool m_bOnlyOneApplication;
		bool m_bIsTaskbarArtificial;

		// Тут заоминается полное имя ярлыка, который потом надо запустить
		FileName m_sFullName;

		CTaskbarEmulator* m_pTaskbarEmulator;

		// Устанавливается после того, как успешно скрыт TaskBar
		bool m_bTaskbarHidden;

		bool m_bLockNeeded;

		CRemainingTimeSlaveDescription m_Remaining;

		HINSTANCE m_hInst;

		// Таймер
		UINT_PTR m_uiTimerIdentifier;
	public:
		CDesktopEmulator(HINSTANCE a_hInst, bool a_bEnabled, std::string* a_pUserName, CRemainingTimeSlaveDescription* a_pRemaining, CSlaveDataReader* a_pReader, HANDLE a_hPrimaryToken, HANDLE a_hImpersonatingToken, DWORD a_dwSessionId);
		virtual ~CDesktopEmulator();

		// Вызывает убивание десктопа. Нужно, чтобы можно было иметь
		// возможность грузить slave до логина.
		void OnTimer();

		void StartTimer(CTimerProcedure* Procedure);

		// Вызывается при активации окна с иконами
		void OnActivated(HWND a_hActivatedWindow);

		void OnWaitedApplicationEnded(CMultiThreadManager* a_pManager);
		void OnIconButtonClicked(CIconButton* a_pButton);

		void NeedToActivate();

		// true, если юзер не суперский
		bool IsUserRestricted();

		// Обертки
		CIconsWindow* GetIconsWindow() {return m_pIconsWindow;};
		CIconsWindow* GetSpecialIconsWindow() {return m_pSpecialIconsWindow;};
		CRemainingTimeSlaveDescription* GetRemainingDescription() {return &m_Remaining;};
		bool GetOnlyOneApplication() {return m_bOnlyOneApplication;};
		void SetOnlyOneApplication(bool a_bNew) {m_bOnlyOneApplication = a_bNew;};
		FileName* GetPreliminaryIconsFolderPath() {return &m_sPreliminaryIconsFolderPath;};
		FileName* GetRunnerName() {return &m_sRunnerName;};
		bool GetLockNeeded() {return m_bLockNeeded;};
		void SetLockNeeded(bool a_bNew) {m_bLockNeeded = a_bNew;};
		CApplicationInfosCollection* GetAllowedSessionsCollection() {return m_pAllowedSessionsCollection;};
		bool GetIsTaskbarArtificial() {return m_bIsTaskbarArtificial;};
		void SetIsTaskbarArtificial(bool a_bNew) {m_bIsTaskbarArtificial = a_bNew;};
		bool GetNeedToCloseSysTray() {return m_bNeedToCloseSysTray;};
		void SetNeedToCloseSysTray(bool a_bNew) {m_bNeedToCloseSysTray = a_bNew;};
};

#endif // __DESKTOPEMULATOR_H__