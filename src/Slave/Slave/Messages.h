#ifndef __MESSAGES_H__
#define __MESSAGES_H__


// Тут будут application-defined мессаги для Slave
#define WM_DISABLE_LOCKER								WM_USER + 1
#define WM_ENABLE_LOCKER								WM_USER + 2
#define WM_SHOWINFO											WM_USER + 3
#define WM_DATARECEIVED									WM_USER + 4
#define WM_CONNECTIONACCEPTED						WM_USER + 5
#define WM_CONNECTED										WM_USER + 6
#define WM_NEED_TO_CHECK_STATE					WM_USER + 7
#define WM_LOCK_REQUIRED								WM_USER + 8
#define WM_UNLOCK_REQUIRED							WM_USER + 9
#define WM_CHECK_SPECIAL_KEYS						WM_USER + 10
#define WM_SET_IS_USER_RESTRICTED				WM_USER + 11
#define WM_ACTIVATED										WM_USER + 12
#define WM_NEW_USER_LOGGED							WM_USER + 13
#define WM_WRITE_DEBUG_MESSAGE					WM_USER + 14
#define WM_WAITED_APPLICATION_ENDED			WM_USER + 15
#define WM_ICON_BUTTON_CLICKED					WM_USER + 16
#define WM_NEED_TO_ACTIVATE							WM_USER + 17
#define WM_SLAVE_TIMER									WM_USER + 18
#define WM_WRITE_TEXT_MESSAGE						WM_USER + 19
#define WM_SLAVE_CLOSE									WM_USER + 20
#define WM_RESTART_REQUIRED							WM_USER + 21
#define WM_TURNOFF_REQUIRED							WM_USER + 22
//#define WM_CHAR_ENTERED						WM_USER + 50


#endif // __MESSAGES_H__