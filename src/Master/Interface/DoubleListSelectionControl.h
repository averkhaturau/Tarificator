#ifndef __DOUBLELISTSELECTIONCONTROL_H__
#define __DOUBLELISTSELECTIONCONTROL_H__


class CDoubleListSelectionControl : public CButton
{
	private:
		void DoDeleteEverything();
	protected:
		CButton* m_pAddButton;
		CButton* m_pRemoveButton;
		CListBox* m_pAddedList;
		CListBox* m_pNotAddedList;

		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnMove(int x, int y);
		afx_msg void AddButtonClicked();
		afx_msg void RemoveButtonClicked();

		void ReAlign();

		void MoveSelectedItems(CListBox* a_pSource, CListBox* a_pDestination);
		void SetProperHorizontalExtent(CListBox* a_pBox);

		// Заполняет NotAddedList
		void Fill(bool a_bDoSelectAll = true);

		DWORD m_dwButtonsHeight, m_dwButtonsWidth;

		virtual void CreateAllItems() = 0;

		DECLARE_MESSAGE_MAP()
	public:
		CDoubleListSelectionControl();
		virtual ~CDoubleListSelectionControl();

		BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
					const RECT& rect, CWnd* pParentWnd, UINT nID);

		void SetFont(CFont* pFont, BOOL bRedraw = TRUE);

		// Обертки
		DWORD GetButtonsHeight() {return m_dwButtonsHeight;};
		DWORD GetButtonsWidth() {return m_dwButtonsWidth;};
		void SetButtonsHeight(DWORD a_dwNew) {m_dwButtonsHeight = a_dwNew;};
		void SetButtonsWidth(DWORD a_dwNew) {m_dwButtonsWidth = a_dwNew;};
		CListBox* GetAddedListBox() {return m_pAddedList;};
		CListBox* GetNotAddedListBox() {return m_pNotAddedList;};
};


#endif // __DOUBLELISTSELECTIONCONTROL_H__