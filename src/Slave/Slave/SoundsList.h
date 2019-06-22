#ifndef __SOUNDSLIST_H__
#define __SOUNDSLIST_H__

#include "..\..\Master\DataStructures\ActiveContainer.h"
#include "SoundEntry.h"

#include <list>


class CSoundsList : public CActiveContainer<CSoundEntry, std::list<CSoundEntry*> >
{
	private:
	protected:
	public:
		CSoundsList();
		virtual ~CSoundsList();

		void DoRemovePlayingSound();
		CSoundEntry* DoAddSound(CSoundEntry::CSoundName* a_psName);
};

#endif // __SOUNDSLIST_H__