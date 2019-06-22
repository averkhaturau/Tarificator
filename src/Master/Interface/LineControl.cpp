#include "stdafx.h"
#include "Interface.h"
#include "LineControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CLineControl::CLineControl()
{
	try{
		m_BorderBrush.CreateSolidBrush(RGB(0, 0, 0));
		m_BackgroundColor = RGB(255, 255, 255);

	}catch(std::exception& Error){
		throw CAnyLogableException((std::string)"An error occured in CLineControl::CLineControl: "
			+ (std::string)Error.what(), bDoNotWriteDuplicates);
	}catch(...){
		throw CAnyLogableException("An unknown error occured in CLineControl::CLineControl", bDoNotWriteDuplicates);
	}
}


CLineControl::~CLineControl()
{
}

