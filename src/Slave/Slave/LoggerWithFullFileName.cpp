#include "stdafx.h"

#include "LoggerWithFullFileName.h"


CLoggerWithFullFileName::CLoggerWithFullFileName()
{
	m_pLogFileName = 0;

		try
		{
			m_pLogFileName = new FileName;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("Can't create logger", bWriteDuplicates);
		}
}
// End of CLoggerWithFullFileName


CLoggerWithFullFileName::~CLoggerWithFullFileName()
{
	DoDeleteEverything();
}
// End of ~CLoggerWithFullFileName()


void CLoggerWithFullFileName::DoDeleteEverything()
{
		if (m_pLogFileName)
		{
			delete m_pLogFileName;
			m_pLogFileName = 0;
		}
}
// End of DoDeleteEverything()
