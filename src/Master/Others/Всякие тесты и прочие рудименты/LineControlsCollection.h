// LineControlsCollection.h: interface for the LineControlsCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINECONTROLSCOLLECTION_H__0AC9798E_1C42_4668_9CC7_75B459BE033F__INCLUDED_)
#define AFX_LINECONTROLSCOLLECTION_H__0AC9798E_1C42_4668_9CC7_75B459BE033F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MashineLineControl.h"
#include "..\DataStructures\ActiveContainerResizable.h"

class CLineControlsCollection 
		: public CActiveContainerResizable<CMashineLineControl>
{
public:
	CLineControlsCollection();
	virtual ~CLineControlsCollection();
};

#endif // !defined(AFX_LINECONTROLSCOLLECTION_H__0AC9798E_1C42_4668_9CC7_75B459BE033F__INCLUDED_)
