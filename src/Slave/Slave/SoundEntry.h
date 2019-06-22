#ifndef __SOUNDENTRY_H__
#define __SOUNDENTRY_H__

#include <string>


class CSoundEntry
{
	public:
		typedef std::string CSoundName;
	private:
	protected:
		CSoundName m_Name;
		bool m_bPlaying;
	public:
		CSoundEntry();
		virtual ~CSoundEntry();

		bool operator==(CSoundEntry& a_Entry);
		CSoundEntry& operator=(CSoundEntry& a_Entry);

		// Обертки
		CSoundName* GetName() {return &m_Name;};
		bool GetPlaying() {return m_bPlaying;};
		void SetPlaying(bool a_bPlaying) {m_bPlaying = a_bPlaying;};
};

#endif // __SOUNDENTRY_H__