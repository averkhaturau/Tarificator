#include "stdafx.h"

#include "DoubleListSelectionControl.h"



const DWORD dwAddButtonID = 15756;
const DWORD dwRemoveButtonID = 15757;


BEGIN_MESSAGE_MAP(CDoubleListSelectionControl, CButton)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_BN_CLICKED(dwAddButtonID, AddButtonClicked)
	ON_BN_CLICKED(dwRemoveButtonID, RemoveButtonClicked)
END_MESSAGE_MAP()



CDoubleListSelectionControl::CDoubleListSelectionControl()
{
	m_pAddButton = 0;
	m_pRemoveButton = 0;
	m_pAddedList = 0;
	m_pNotAddedList = 0;

	m_dwButtonsHeight = 20;
	m_dwButtonsWidth = 30;

		try
		{
			m_pAddButton = new CButton;
			m_pRemoveButton = new CButton;
			m_pAddedList = new CListBox;
			m_pNotAddedList = new CListBox;
		}
		catch(...)
		{
			DoDeleteEverything();
		}
}
// End of CDoubleListSelectionControl()


CDoubleListSelectionControl::~CDoubleListSelectionControl()
{

}
// End of ~CDoubleListSelectionControl()


void CDoubleListSelectionControl::DoDeleteEverything()
{
		if (m_pAddButton)
		{
			delete m_pAddButton;
			m_pAddButton = 0;
		}
		if (m_pRemoveButton)
		{
			delete m_pRemoveButton;
			m_pRemoveButton = 0;
		}
		if (m_pAddedList)
		{
			delete m_pAddedList;
			m_pAddedList = 0;
		}
		if (m_pNotAddedList)
		{
			delete m_pNotAddedList;
			m_pNotAddedList = 0;
		}
}
// End of DoDeleteEverything()


BOOL CDoubleListSelectionControl::Create(LPCTSTR lpszCaption,
			DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL bResult = CButton::Create(lpszCaption, dwStyle | BS_GROUPBOX, rect, pParentWnd, nID);

	m_pAddButton->Create("->", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0),
				this, dwAddButtonID);
	m_pRemoveButton->Create("<-", WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0),
				this, dwRemoveButtonID);
	m_pAddedList->CreateEx(
				0,
				"Listbox",
				"",
				WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_NOINTEGRALHEIGHT | LBS_STANDARD | LBS_DISABLENOSCROLL,
				0, 0, 0, 0,
				this->GetSafeHwnd(),
				0, 0);
	m_pNotAddedList->CreateEx(
				0,
				"Listbox",
				"",
				WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_NOINTEGRALHEIGHT | LBS_STANDARD | LBS_DISABLENOSCROLL,
				0, 0, 0, 0,
				this->GetSafeHwnd(),
				0, 0);

	return bResult;
}
// End of Create


void CDoubleListSelectionControl::OnSize(UINT nType, int cx, int cy)
{
	CButton::OnSize(nType, cx, cy);

	ReAlign();
}
// End of OnSize


void CDoubleListSelectionControl::OnMove(int x, int y)
{
	CButton::OnMove(x, y);

	ReAlign();
}
// End of OnMove


void CDoubleListSelectionControl::ReAlign()
{
		if ( (!m_pAddedList->GetSafeHwnd()) || (!m_pNotAddedList->GetSafeHwnd())
					|| (!m_pAddButton->GetSafeHwnd()) || (!m_pRemoveButton->GetSafeHwnd()) )
			return;

	CRect Rect;
	/*GetWindowRect(&Rect);
	GetParent()->ScreenToClient(&Rect);*/
	GetClientRect(&Rect);

		if ( (Rect.Height() < 90) || (Rect.Width() < 90) )
		{
			m_pNotAddedList->ShowWindow(false);
			m_pAddedList->ShowWindow(false);
			m_pAddButton->ShowWindow(false);
			m_pRemoveButton->ShowWindow(false);
		}
		else
		{
			m_pNotAddedList->ShowWindow(true);
			m_pAddedList->ShowWindow(true);
			m_pAddButton->ShowWindow(true);
			m_pRemoveButton->ShowWindow(true);
		}

	m_pNotAddedList->SetWindowPos(&wndTop,
				Rect.left + 5,
				Rect.top + 20,
				Rect.Width()/2 - m_dwButtonsWidth/2 - 10,
				Rect.Height() - 23,
				0);

	m_pAddedList->SetWindowPos(&wndTop,
				Rect.Width()/2 + m_dwButtonsWidth/2 + 5 + Rect.left,
				Rect.top + 20,
				Rect.Width()/2 - m_dwButtonsWidth/2 - 10,
				Rect.Height() - 23,
				0);

	m_pAddButton->SetWindowPos(&wndTop,
				Rect.Width()/2 - m_dwButtonsWidth/2 + Rect.left,
				Rect.Height()/2 + 5 - m_dwButtonsHeight + Rect.top,
				m_dwButtonsWidth,
				m_dwButtonsHeight,
				0);

	m_pRemoveButton->SetWindowPos(&wndTop,
				Rect.Width()/2 - m_dwButtonsWidth/2 + Rect.left,
				Rect.Height()/2 + 15 + Rect.top,
				m_dwButtonsWidth,
				m_dwButtonsHeight,
				0);
}
// End of ReAlign()


void CDoubleListSelectionControl::AddButtonClicked()
{
	MoveSelectedItems(m_pNotAddedList, m_pAddedList);
}
// End of AddButtonClicked()


void CDoubleListSelectionControl::RemoveButtonClicked()
{
	MoveSelectedItems(m_pAddedList, m_pNotAddedList);
}
// End of RemoveButtonClicked()


void CDoubleListSelectionControl::MoveSelectedItems(CListBox* a_pSource, CListBox* a_pDestination)
{
		if ( (!a_pSource) || (!a_pDestination) )
			return;

	DWORD dwData;
	int iRes;
	signed long int i;
	CString Str;
		for (i = 0; i < a_pSource->GetCount(); ++i)
		{
				if (a_pSource->GetSel(i))
				{
					dwData = a_pSource->GetItemData(i);
					a_pSource->GetText(i, Str);

					iRes = a_pDestination->AddString(Str);
					a_pDestination->SetItemData(iRes, dwData);
				}
		}

		for (i = a_pSource->GetCount(); i >= 0; --i)
		{
				if ( a_pSource->GetSel(i) )
				{
					a_pSource->DeleteString(i);
				}
		}

	SetProperHorizontalExtent(a_pSource);
	SetProperHorizontalExtent(a_pDestination);
}
// End of MoveSelectedItems


void CDoubleListSelectionControl::SetFont(CFont* pFont, BOOL bRedraw)
{
	CButton::SetFont(pFont, bRedraw);

		if (m_pAddedList->GetSafeHwnd())
		{
			m_pAddedList->SetFont(pFont, bRedraw);
			SetProperHorizontalExtent(m_pAddedList);
		}
		if (m_pNotAddedList->GetSafeHwnd())
		{
			m_pNotAddedList->SetFont(pFont, bRedraw);
			SetProperHorizontalExtent(m_pNotAddedList);
		}
		if (m_pAddButton->GetSafeHwnd())
			m_pAddButton->SetFont(pFont, bRedraw);
		if (m_pRemoveButton->GetSafeHwnd())
			m_pRemoveButton->SetFont(pFont, bRedraw);
}
// End of SetFont


void CDoubleListSelectionControl::SetProperHorizontalExtent(CListBox* a_pBox)
{
		if (!a_pBox)
			return;

	// Find the longest string in the list box.
	CString str;
	CSize sz;
	int dx = 0;
	CDC* pDC = a_pBox->GetDC();
	CFont* pOldFont = pDC->SelectObject(a_pBox->GetFont());
		for (int i=0; i < a_pBox->GetCount(); ++i)
		{
			a_pBox->GetText(i, str);
			sz = pDC->GetTextExtent(str);

				if (sz.cx > dx)
					dx = sz.cx;
		}
	pDC->SelectObject(pOldFont);
	a_pBox->ReleaseDC(pDC);

	dx += GetSystemMetrics(SM_CXVSCROLL);

	// Set the horizontal extent so every character of all strings 
	// can be scrolled to.
	a_pBox->SetHorizontalExtent(dx);
}
// End of SetProperHorizontalExtent


void CDoubleListSelectionControl::Fill(bool a_bDoSelectAll)
{
	m_pNotAddedList->ResetContent();
	m_pAddedList->ResetContent();

	CreateAllItems();

		if (a_bDoSelectAll)
				for (int i = 0; i < m_pNotAddedList->GetCount(); ++i)
					m_pNotAddedList->SetSel(i);

	SetProperHorizontalExtent(m_pNotAddedList);
	SetProperHorizontalExtent(m_pAddedList);
}
// End of Fill()
