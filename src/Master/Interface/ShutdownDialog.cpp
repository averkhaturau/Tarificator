// ShutdownDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "ShutdownDialog.h"
#include "AdditionalResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CShutdownDialog dialog


CShutdownDialog::CShutdownDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShutdownDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShutdownDialog)
	//}}AFX_DATA_INIT
	m_pSelectedMashines = 0;
}

CShutdownDialog::CShutdownDialog(CMashinesCollection* a_pAllMashines, CMashinesCollection* a_pSelectedMashines)
	: CDialog(CShutdownDialog::IDD, NULL)
{
	//m_MSelctnCtrl.SetMashinesCollection(a_pAllMashines);
	// ещё не мешало бы выделить уже выделение во View машины (a_pSelectedMashines)
	m_pSelectedMashines = a_pSelectedMashines;
}

void CShutdownDialog::DoDeleteEverything()
{
}

void CShutdownDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShutdownDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShutdownDialog, CDialog)
	//{{AFX_MSG_MAP(CShutdownDialog)
	ON_BN_CLICKED(ID_BUTTON_SHUTDOWN, OnShutdown)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, OnReboot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CShutdownDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	try{

		if (!m_pSelectedMashines)
			throw CAnyLogableException("Selected mashines has not initialized", bDoNotWriteDuplicates);

		/*CRect MyRect, ButtonRect;
		GetClientRect(MyRect);
		CButton *pMainButton = (CButton*)GetDlgItem(IDOK);
		pMainButton->GetWindowRect(ButtonRect);
		MyRect.right -= ButtonRect.Width();
		MyRect.DeflateRect(20, 10);
		m_MSelctnCtrl.Create("Перезагрузить машины",
			WS_CHILD|WS_VISIBLE,
			MyRect, this, dwMashinesSelectionID);
		*/

		// облегчённый вариант

		CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_STATIC_MASHINES);
		
		std::string Str1 = "Выбраны следующие машины:\n";
		for (CMashinesCollection::iterator Iter = m_pSelectedMashines->GetData()->begin();
				Iter != m_pSelectedMashines->GetData()->end(); ++Iter)
		{
			Str1 += (*Iter)->GetMashineName() + '\n';
		}

		pStaticText->SetWindowText(Str1.c_str());

	}catch(...)
	{
		return FALSE;
	}

	return TRUE;
}

void CShutdownDialog::OnShutdown() 
{
	for (CMashinesCollection::iterator Iter = m_pSelectedMashines->GetData()->begin();
			Iter != m_pSelectedMashines->GetData()->end(); ++Iter)
	{
		//_LX: Input here
	}

	OnCancel();
}

void CShutdownDialog::OnReboot() 
{
	for (CMashinesCollection::iterator Iter = m_pSelectedMashines->GetData()->begin();
			Iter != m_pSelectedMashines->GetData()->end(); ++Iter)
	{
		//_LX: Input here
	}

	OnCancel();
}
