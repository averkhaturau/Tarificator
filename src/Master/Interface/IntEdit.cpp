// doubleedit.cpp : implementation file
//

#include "stdafx.h"
#include "IntEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoubleEdit


BEGIN_MESSAGE_MAP(CIntEdit, CEdit)
	//{{AFX_MSG_MAP(CIntEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CIntEdit::CIntEdit()
{

}

CIntEdit::~CIntEdit()
{

}


void CIntEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL IsAlphaNum    = IsCharAlphaNumeric((TCHAR)nChar);
	BOOL IsAlpha       = IsCharAlpha((TCHAR)nChar);
	// ����� ���������� ��������� �������
	BOOL IsSubServient = (nChar < 0x20);
	// �����?
	/*BOOL IsPeriod      = (nChar == '.');
	BOOL Ise           = (nChar == 'e');
	BOOL IsE           = (nChar == 'E');*/
	// �����?
	BOOL IsMinus       = (nChar == '-');

	/*CString WindowText;
	GetWindowText(WindowText);

	BOOL bIsStringTooLong = (WindowText.GetLength() > 9);*/

		if ((IsAlphaNum && !IsAlpha) || IsSubServient || IsMinus /*|| IsPeriod
					|| Ise || IsE*/)
		{
				//if (!bIsStringTooLong)
					CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
}
// End of OnChar


DWORD CIntEdit::Convert()
{
	CString WindowText;
	GetWindowText(WindowText);

		if (WindowText.GetLength() <= 9)
			return atoi(WindowText);
		else
			return 0;
}
// End of Convert


void CIntEdit::FillEdit(DWORD Data)
{
	// ����� ��� �������� � ������
	char CharBuffer[50];

	// �������������� Data � String
	_itoa(Data, CharBuffer, 10);

	CString TempString = (CString)CharBuffer;

		// ���� ��������� ������ � ������ - �����:
		if (TempString[TempString.GetLength() - 1] == '.')
		{
			// ������� ��� �����:
			TempString.SetAt(TempString.GetLength() - 1, '\0');
		}

	SetWindowText(TempString);
}
// End of FillEdit
