#include "stdafx.h"

#include "SlaveSoundManager.h"
#include "Messages.h"


CSlaveSoundManager::CSlaveSoundManager()
{

}
// End of CSlaveSoundManager()


CSlaveSoundManager::~CSlaveSoundManager()
{

}
// End of ~CSlaveSoundManager()


void CSlaveSoundManager::PlayEarlyWarn()
{
	m_Player.AddAndPlay(&m_EarlyWarnName);
}
// End of PlayEarlyWarn()


void CSlaveSoundManager::PlayLateWarn()
{
	m_Player.AddAndPlay(&m_LateWarnName);
}
// End of PlayLateWarn()


void CSlaveSoundManager::PlayFinished()
{
	m_Player.AddAndPlay(&m_FinishedName);
}
// End of PlayFinished()


void CSlaveSoundManager::DoStopPlaying()
{
	m_Player.DoStopPlaying();
}
// End of DoStopPlaying()


void CSlaveSoundManager::OnTimer()
{
	m_Player.OnTimer();
}
// End of OnTimer()
