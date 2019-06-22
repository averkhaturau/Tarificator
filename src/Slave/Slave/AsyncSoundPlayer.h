#ifndef __ASYNCSOUNDPLAYER_H__
#define __ASYNCSOUNDPLAYER_H__

#include "MultiThreadManager.h"
#include "SoundsList.h"
#include "Wave\Include\animate.h"


// Predefinition
class CAsyncSoundPlayer;
class CWave;
class CWaveNotifyObj;

/*class CAsyncSoundParameters : public CThreadParameters
{
	private:
	protected:
		CAsyncSoundPlayer* m_pAsyncSoundPlayer;
		CSoundEntry* m_pEntry;
	public:
		CAsyncSoundParameters()
		{
			m_pAsyncSoundPlayer = 0;
		};
		~CAsyncSoundParameters() {};

		// Обертки
		void SetAsyncSoundPlayer(CAsyncSoundPlayer* a_pNew) {m_pAsyncSoundPlayer = a_pNew;};
		CAsyncSoundPlayer* GetAsyncSoundPlayer() {return m_pAsyncSoundPlayer;};
		void SetEntry(CSoundEntry* a_pNew) {m_pEntry = a_pNew;};
		CSoundEntry* GetEntry() {return m_pEntry;};
};*/


class CAsyncSoundPlayer : public CWaveNotifyObj// : public CMultiThreadManager
{
	private:
		void DoDeleteEverything();
	protected:
		CSoundsList m_SoundsList;
		CWave* m_pWave;

		virtual void NewData(CWave *pWave, CWaveBlock* pBlock);
		virtual void EndPlayback(CWave *pWave);
	public:
		CAsyncSoundPlayer();
		virtual ~CAsyncSoundPlayer();

		void DoStopPlaying();

		void OnTimer();

		void AddAndPlay(CSoundEntry::CSoundName* a_psName);
};


#endif // __ASYNCSOUNDPLAYER_H__