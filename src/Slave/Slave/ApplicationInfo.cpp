#include "stdafx.h"

#include "ApplicationInfo.h"
#include "Messages.h"


CApplicationInfo::CApplicationInfo()
{
	m_dwSessionId = 0;
	m_dwMainThreadId = 0;
	m_sUserName = "";
}
// End of CApplicationInfo()


CApplicationInfo::~CApplicationInfo()
{

}
// End of ~CApplicationInfo()


bool CApplicationInfo::operator==(CApplicationInfo& a_Info)
{
	return ( (m_dwSessionId == a_Info.m_dwSessionId) &&
				(m_dwMainThreadId == a_Info.m_dwMainThreadId) );
}
// End of operator==
