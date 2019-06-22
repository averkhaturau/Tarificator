#include "stdafx.h"

#include "CharInput.h"


CCharInput::CCharInput()
{
	Initialize();

	m_cChar = 0;
}
// End of CCharInput()


CCharInput::CCharInput(char cChar)
{
	Initialize();

	m_cChar = cChar;
}
// End of CCharInput


CCharInput::CCharInput(char cChar, CTimeContainer i64Time)
{
	m_cChar = cChar;
	m_Time = CTimeStorage(i64Time);
}
// End of CCharInput


void CCharInput::Initialize()
{
	SYSTEMTIME Current;
	GetLocalTime(&Current);

	m_Time.SetTime(&Current);
}
// End of Initialize()


CCharInput::~CCharInput()
{

}
// End of ~CCharInput()


CCharInput& CCharInput::operator=(CCharInput& CharInput)
{
	m_cChar = CharInput.m_cChar;
	m_Time = CharInput.m_Time;
	return *this;
}
// End of operator=


CTimeContainer CCharInput::GetRemoteness()
{
	SYSTEMTIME Current;
	GetLocalTime(&Current);

	CTimeStorage CurrentTime(&Current);
	CTimeStorage Result = CurrentTime - m_Time;

	return Result.GetTime();
}
// End of GetRemoteness()
