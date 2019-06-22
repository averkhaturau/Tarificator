#if !defined(AFX_INTERFACEDOC_H__68D8BD28_DA04_4016_B077_CC6919094D0D__INCLUDED_)
#define AFX_INTERFACEDOC_H__68D8BD28_DA04_4016_B077_CC6919094D0D__INCLUDED_

#include "..\DATASTRUCTURES\MASTERMANAGER\MasterManager.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Slave\Slave\ErrorsLogger.h"
#include "NewIntervalDialog.h"
#include "PswrdDialog.h"
#include "TakeOfDlg.h"
#include "ShutdownDialog.h"


class CInterfaceDoc : public CDocument
{
private:
	void DoDeleteEverything();
protected:
	
	typedef BOOL (TestTheView) (const CView*);

	CNewIntervalDialog* m_pNewIntervalDialog;
	CTakeOfDlg* m_pTakeOfDialog;
	CShutdownDialog* m_pShutdownDialog;

	// Состояние диалога m_pNewIntervalDialog
	CDialogState m_DialogState;

	// Состояние парольного диалога
public:	CPasswordDialogState m_PasswordDialogState;
		void OnIdle();
protected:
	CMasterManager* m_pMasterManager;

	CInterfaceDoc();

	DECLARE_DYNCREATE(CInterfaceDoc)
	//{{AFX_MSG(CInterfaceDoc)
	afx_msg void OnNewInterval();
	afx_msg void OnTakeOff();
	afx_msg void OnShutdownHosts();
	afx_msg void OnLogOffClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	/* Навороченная фича. Выдает указатель на первый View из списка
	Views документа, для которого TestFunction возвращает true. Если
	такого экземпляра нет - выдает NULL. Использует однострочные
	static функции, определенные в .cpp. */
	CView* GetViewOfType(TestTheView* TestFunction);

	void OnShowBusyView();
	void OnShowCashView();

	void OnShowAnyView(CView* pView, CDocTemplate* pTemplate);

public:
	virtual ~CInterfaceDoc();

	//virtual void OnCloseDocument();

	//{{AFX_VIRTUAL(CInterfaceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	virtual BOOL DoFileSave();

	void SetStatusBarText(CString Text);

	bool DoOperatorAuthentication(CPermission a_Permission);

	// Возвращает указатель на BusyView
	CBusyView* GetBusyView();

	CErrorsLogger* GetErrorsLogger();
	CMasterManager* GetMasterManager();

	bool OnTimer();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//#define LOG_LOADINGANDTERMINATINGOFPROGRAM

#endif // !defined(AFX_INTERFACEDOC_H__68D8BD28_DA04_4016_B077_CC6919094D0D__INCLUDED_)
