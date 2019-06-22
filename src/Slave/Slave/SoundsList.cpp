#include "stdafx.h"

#include "SoundsList.h"
#include "Messages.h"


CSoundsList::CSoundsList()
{

}
// End of CSoundsList()


CSoundsList::~CSoundsList()
{

}
// End of ~CSoundsList()


CSoundEntry* CSoundsList::DoAddSound(CSoundEntry::CSoundName* a_psName)
{
	CSoundEntry Entry;
	Entry.SetPlaying(false);
	*Entry.GetName() = *a_psName;

	return AddResidentBack(Entry);
}
// End of DoAddPlayingSound


void CSoundsList::DoRemovePlayingSound()
{
	iterator Iter = GetData()->begin(), EndIter = GetData()->end();
		for (; Iter != EndIter; ++Iter)
		{
				if ( (*Iter)->GetPlaying() )
				{
					DeleteResident(**Iter);
					break;
				}
		}
}
// End of DoRemovePlayingSound()
