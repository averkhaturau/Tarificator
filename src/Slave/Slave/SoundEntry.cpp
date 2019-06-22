#include "stdafx.h"

#include "SoundEntry.h"


CSoundEntry::CSoundEntry()
{
	m_Name = "";
	m_bPlaying = false;
}
// End of CSoundEntry()


CSoundEntry::~CSoundEntry()
{

}
// End of ~CSoundEntry()


bool CSoundEntry::operator==(CSoundEntry& a_Entry)
{
	return ( (!strcmp(a_Entry.GetName()->c_str(), m_Name.c_str())) && (a_Entry.GetPlaying() == m_bPlaying) );
}
// End of operator==


CSoundEntry& CSoundEntry::operator=(CSoundEntry& a_Entry)
{
	m_bPlaying = a_Entry.GetPlaying();
	m_Name = *a_Entry.GetName();
	return *this;
}
// End of operator=
