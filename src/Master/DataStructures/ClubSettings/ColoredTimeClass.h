#ifndef _LX_COLOREDTIMECLASS_H_INCLUDED_
#define _LX_COLOREDTIMECLASS_H_INCLUDED_

#include <windows.h>

const COLORREF ciDefaultBusyColor = RGB(0xff, 0, 0);
const COLORREF ciSelectedBusyColor = RGB(0, 0, 0xff);
const COLORREF ciDefaultFreeColor = RGB(0, 0x7f, 0);
const COLORREF ciSelectedFreeColor = RGB(0x7f, 0xff, 0);


class CColoredClass
{
public:
	void SetColor(const COLORREF& Color){ m_Color = Color; };
	COLORREF GetColor() const {return m_Color;};

protected:
	COLORREF m_Color;
};

#endif //_LX_COLOREDTIMECLASS_H_INCLUDED_