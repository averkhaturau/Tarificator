#include "StdAfx.h"

#include "MashineLinesGrid.h"
#include "IntervalsCell.h"
#include "..\DataStructures\ClubSettings\IntervalAddition.h"


BEGIN_MESSAGE_MAP(CMashineLinesGrid, CGridCtrl)
	//{{AFX_MSG_MAP(CMashineLinesGrid)
	ON_WM_SIZE()
	ON_WM_KEYUP()
	//ON_WM_CAPTURECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMashineLinesGrid::CMashineLinesGrid()
{
	m_pMashinesCollection = 0;
	SetFrameFocusCell(false);
	SetTrackFocusCell(false);
	SetFixedRowCount(1);
	SetEditable(false);
	SetListMode(true);
	EnableDragAndDrop(false);
	SetColumnResize(false);

	//GetFont();

	SetColumnCount(NUM_HEADERS_IN_GRID);
	for (int i = 0; i < NUM_HEADERS_IN_GRID; ++i)
	{
		SetItemText(0, i,_cHeaders[i].c_str());
	}
	SetHeaderSort(true);
};

void CMashineLinesGrid::DisplayMashines()
{
		try
		{
			if (m_pMashinesCollection != 0)
			{
				bool bNeedRedraw = false;
				if (GetRowCount() != m_pMashinesCollection->size()+1)
				{
					SetRowCount(m_pMashinesCollection->size() + 1/*1 for captions*/);
					m_vMashineIndexes.resize(m_pMashinesCollection->size());
					for (int i = 0; i < m_pMashinesCollection->size(); ++i)
					{
						m_vMashineIndexes[i] = i;
					}

					bNeedRedraw = true;
				}

				for (int i = 0; i < m_pMashinesCollection->size(); ++i)
				{
					if (!m_vMashineIndexes.size())
						break;

					GetCell(i+1, 0)->SetText(m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetMashineName().c_str());
					if (bNeedRedraw)
					{
						SetCellType(i+1, 2, RUNTIME_CLASS(CIntervalsCell));
					}

					((CIntervalsCell*)GetCell(i+1, 2))->
						GetIntervalsLine()->GetIntervalsCollection()->
						operator =(*(m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetBusyIntervalsCollection()));

					((CIntervalsCell*)GetCell(i+1, 2))->GetIntervalsLine()->SetMashineData(&(*m_pMashinesCollection)[m_vMashineIndexes[i]]);

					switch (m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetCurrentMashineState())
					{
					case msBusy:
						{
							CTimeStorage CurrentTime_ = CurrentTime();
							CTimeStorage DeltaTime =
								m_pMashinesCollection->operator [](m_vMashineIndexes[i]).
									GetBusyIntervalsCollection()->
										GetTimeRemaining(CurrentTime_);

							GetCell(i+1, 1)->SetText(
								std::string(_cMashineStates[msBusy] +
								" "+ IntervalAddition::DescribeTime(&DeltaTime)).c_str());

							GetCell(i+1, 3)->SetText(
									m_pTarifPlansCollection->operator [](
												(*m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetBusyIntervalsCollection()->
													GetIntervalAtTime(CurrentTime_))->GetCurrentInterval()->GetTarifPlanNumber()
									).GetName().c_str()
							);
						}
						break;
					case msUnknown:
						{
							GetCell(i+1, 1)->SetImage(1);
							GetCell(i+1, 1)->SetText(_cMashineStates[m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetCurrentMashineState()].c_str());
						}
						break;
					case msFree:
						{
							GetCell(i+1, 1)->SetImage(0);
							GetCell(i+1, 3)->SetText("");
						}
					default:
						GetCell(i+1, 1)->SetText(_cMashineStates[m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetCurrentMashineState()].c_str());
					};
					// Test Version
					if (m_pMashinesCollection->operator [](m_vMashineIndexes[i]).GetLastSuccessCommunication()->IsTimeExpired())
					{
						GetCell(i+1, 1)->SetImage(1);
					}
					else
					{
						GetCell(i+1, 1)->SetImage(0);
					}
					RedrawRow(i+1);
				}
				RedrawRow(0);
			}
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMashineLinesGrid::DisplayMashines: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString.c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMashineLinesGrid::DisplayMashines", bDoNotWriteDuplicates);
		}
}

void CMashineLinesGrid::OnSize(UINT nType, int cx, int cy)
{
	static bool IsExecutingOnSize = false;

	if (!IsExecutingOnSize)
	{
		IsExecutingOnSize = true;

		CGridCtrl::OnSize(nType, cx, cy);
		DoRelayout();

		IsExecutingOnSize = false;
	}
}
// End of OnResize()

void CMashineLinesGrid::DoRelayout()
{
		try
		{
			CRect Rect;
			GetWindowRect(Rect);

			DWORD dwControlWidth = (Rect.Width());
			DisplayMashines();
			AutoSizeColumns();
			DWORD dwColumnsWidth = GetVirtualWidth();
			signed int i;
			/*double dCoef = (double)dwColumnWidth/dwNeededWidth;
			for (i=GetColumnCount()-1; i>=0; --i)
			{
				SetColumnWidth(i, (int)(GetColumnWidth(i)*dCoef));
			}*/

			if (dwControlWidth > dwColumnsWidth)
				SetColumnWidth(2, GetColumnWidth(2) + dwControlWidth-dwColumnsWidth-5);

			for (i=GetRowCount()-1; i>0; --i)
				SetRowHeight(i, GetRowHeight(0)+3);
		}
		catch(CAnyLogableException& Error)
		{
			std::string ErrorString = "An error occured in CMashineLinesGrid::DoRelayout: ";
			ErrorString += Error.what();
			throw CAnyLogableException(ErrorString.c_str(), Error.GetWriteDuplicatesToLog());
		}
		catch(...)
		{
			throw CAnyLogableException("An unknown error occured in CMashineLinesGrid::DoRelayout", bDoNotWriteDuplicates);
		}
}

void CMashineLinesGrid::Refresh()
{
	DoRelayout();
	CGridCtrl::Refresh();
}


void CMashineLinesGrid::OnFixedRowClick(CCellID& cell)
{
    if (!IsValid(cell))
        return;

    if (GetHeaderSort())
    {
        CWaitCursor waiter;
        if (cell.col == GetSortColumn())
		{
			SetSortColumn(cell.col);
			SetSortAscending(!GetSortAscending());
			ResetSelectedRange();
			SetFocusCell(-1, - 1);

			if (m_pfnCompare == NULL)
				CMashineLinesGrid::SortItems(pfnCellTextCompare, cell.col, !GetSortAscending(), 0, GetFixedRowCount(), -1);
			else
				CMashineLinesGrid::SortItems(m_pfnCompare, cell.col, !GetSortAscending(), 0, GetFixedRowCount(), -1);
		}
		else
		{
			SetSortColumn(cell.col);
			SetSortAscending(TRUE);
			ResetSelectedRange();
			SetFocusCell(-1, - 1);

			if (m_pfnCompare == NULL)
				CMashineLinesGrid::SortItems(pfnCellTextCompare, cell.col, TRUE, 0, GetFixedRowCount(), -1);
			else
				CMashineLinesGrid::SortItems(m_pfnCompare, cell.col, TRUE, 0, GetFixedRowCount(), -1);
		}
        Invalidate();
    }

    if (GetFixedRowSelection())
    {
        if (cell.col < GetFixedColumnCount())
        {
            m_MouseMode = MOUSE_SELECT_ALL;
            OnSelecting(cell);
        }
        else 
        {
            m_MouseMode = MOUSE_SELECT_COL;
            OnSelecting(cell);
        }
    }
}

// private recursive sort implementation
BOOL CMashineLinesGrid::SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data,
                          int low, int high)
{
    if (nCol >= GetColumnCount())
        return FALSE;

    if (high == -1)
        high = GetRowCount() - 1;

    int lo = low;
    int hi = high;
    
    if (hi <= lo)
        return FALSE;
    
    //LPARAM midItem = GetItemData((lo + hi)/2, nCol);
	LPARAM pMidCell = (LPARAM) GetCell((lo + hi)/2, nCol);
    
    // loop through the list until indices cross
    while (lo <= hi)
    {
        // Find the first element that is greater than or equal to the partition 
        // element starting from the left Index.
        if (bAscending)
            while (lo < high  && pfnCompare( (LPARAM)GetCell(lo, nCol), (LPARAM) pMidCell, data) < 0)
                ++lo;
        else
            while (lo < high && pfnCompare((LPARAM)GetCell(lo, nCol), pMidCell, data) > 0)
				++lo;
                
		// Find an element that is smaller than or equal to  the partition 
		// element starting from the right Index.
		if (bAscending)
			while (hi > low && pfnCompare((LPARAM)GetCell(hi, nCol), pMidCell, data) > 0)
				--hi;
		else
			while (hi > low && pfnCompare((LPARAM)GetCell(hi, nCol), pMidCell, data) < 0)
				--hi;
                        
        // If the indexes have not crossed, swap if the items are not equal
        if (lo <= hi)
        {
			// swap only if the items are not equal
            if (pfnCompare((LPARAM)GetCell(lo, nCol), (LPARAM)GetCell(hi, nCol), data) != 0)
            {
				for (int col = 0; col < GetColumnCount(); col++)
                {
					CGridCellBase *pCell = GetCell(lo, col);
                    SetCell(lo, col, GetCell(hi, col));
                    SetCell(hi, col, pCell);
                }
                UINT nRowHeight = m_arRowHeights[lo];
                m_arRowHeights[lo] = m_arRowHeights[hi];
                m_arRowHeights[hi] = nRowHeight;

				int MashineIndex = m_vMashineIndexes[lo-1];
				m_vMashineIndexes[lo-1] = m_vMashineIndexes[hi-1];
				m_vMashineIndexes[hi-1] = MashineIndex;
            }
                            
            ++lo;
            --hi;
         }
    }
    
    // If the right index has not reached the left side of array
    // must now sort the left partition.
    if (low < hi)
        SortItems(pfnCompare, nCol, bAscending, data, low, hi);
    
    // If the left index has not reached the right side of array
    // must now sort the right partition.
    if (lo < high)
        SortItems(pfnCompare, nCol, bAscending, data, lo, high);
    
    return TRUE;
}

void CMashineLinesGrid::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == 27/*Esc.*/)
		SetSelectedRange(-1, -1, -1, -1);
	else
		CGridCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMashineLinesGrid::AddSelectedMashines(CMashinesCollection* a_pSelectedMashines)
{
	for (signed int i = GetRowCount()-1; i > 0; --i)
	{
		if (IsCellSelected(i, 0))
		{
			a_pSelectedMashines->AddResident(m_pMashinesCollection->operator [](m_vMashineIndexes[i-1]));
		}
	}
}

void CMashineLinesGrid::OnTimer(UINT nIDEvent)
{
	DisplayMashines();
	//DoRelayout();
}
