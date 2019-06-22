#ifndef __ICONBUTTONSCOLLECTION_H__
#define __ICONBUTTONSCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainerResizable.h"
#include "IconButton.h"

#include "shlobj.h"


class CIconButtonsCollection : public CActiveContainerResizable<CIconButton>
{
	private:
	protected:
	public:
		CIconButtonsCollection() {};
		~CIconButtonsCollection() {};

		void ResolveAll(HWND a_hWnd);
};


#endif // __ICONBUTTONSCOLLECTION_H__