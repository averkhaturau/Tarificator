#ifndef __SLAVESOUNDMANAGER_H__
#define __SLAVESOUNDMANAGER_H__

#include "AsyncSoundPlayer.h"


class CSlaveSoundManager
{
	private:
	protected:
		CSoundEntry::CSoundName m_EarlyWarnName, m_LateWarnName, m_FinishedName;
		CAsyncSoundPlayer m_Player;
	public:
		CSlaveSoundManager();
		~CSlaveSoundManager();

		void PlayEarlyWarn();
		void PlayLateWarn();
		void PlayFinished();

		void DoStopPlaying();

		void OnTimer();

		// Обертки
		CSoundEntry::CSoundName& GetEarlyWarnName() {return m_EarlyWarnName;};
		CSoundEntry::CSoundName& GetLateWarnName() {return m_LateWarnName;};
		CSoundEntry::CSoundName& GetFinishedName() {return m_FinishedName;};
};


#endif // __SLAVESOUNDMANAGER_H__