#include "stdafx.h"

//#include "Wave\Include\animate.h"

#include "AsyncSoundPlayer.h"
#include "Exceptions.h"
#include "Messages.h"

#include "Mmsystem.h"



CAsyncSoundPlayer::CAsyncSoundPlayer()
{
	m_pWave = 0;
		try
		{
			//m_pWave = new CWave;
		}
		catch(...)
		{
			DoDeleteEverything();
			throw CAnyLogableException("An unknown error occured in CAsyncSoundPlayer::CAsyncSoundPlayer()", bDoNotWriteDuplicates);
		}
}
// End of CAsyncSoundPlayer()


void CAsyncSoundPlayer::DoDeleteEverything()
{
		if (m_pWave)
		{
			delete m_pWave;
			m_pWave = 0;
		}
}
// End of DoDeleteEverything()


CAsyncSoundPlayer::~CAsyncSoundPlayer()
{
	DoDeleteEverything();
}
// End of ~CAsyncSoundPlayer()


void CAsyncSoundPlayer::AddAndPlay(CSoundEntry::CSoundName* a_psName)
{
		try
		{
				if (a_psName)
					m_SoundsList.DoAddSound(a_psName);

			bool bPlaying = false;
			CSoundsList::iterator Iter = m_SoundsList.GetData()->begin(),
						EndIter = m_SoundsList.GetData()->end();
				for (; Iter != EndIter; ++Iter)
				{
					bPlaying |= (*Iter)->GetPlaying();
				}

				if (bPlaying)
					return;

			CSoundEntry* pEntry = 0;
				if (m_SoundsList.GetData()->begin() != m_SoundsList.GetData()->end())
					pEntry = *(m_SoundsList.GetData()->begin());

				if (m_pWave)
				{
					delete m_pWave;
					m_pWave = 0;
				}

				if (!pEntry)
					return;

			m_pWave = new CWave;
			pEntry->SetPlaying(true);
			m_pWave->Load(pEntry->GetName()->c_str());
			m_pWave->Play(0 ,this);
		}
		catch(...)
		{
			throw CAnyLogableException("An error occured in CAsyncSoundPlayer::AddAndPlay", bDoNotWriteDuplicates);
		}
}
// End of AddAndPlay


void CAsyncSoundPlayer::NewData(CWave *pWave, CWaveBlock* pBlock)
{
}
// End of NewData


void CAsyncSoundPlayer::EndPlayback(CWave *pWave)
{
	m_SoundsList.DoRemovePlayingSound();
}
// End of EndPlayback


void CAsyncSoundPlayer::DoStopPlaying()
{
		if (m_pWave)
			m_pWave->Stop();
}
// End of DoStopPlaying()


void CAsyncSoundPlayer::OnTimer()
{
	AddAndPlay(0);
}
// End of OnTimer()
