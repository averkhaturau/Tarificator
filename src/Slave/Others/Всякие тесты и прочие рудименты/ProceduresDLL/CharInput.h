#ifndef __CHARINPUT_H__
#define __CHARINPUT_H__


#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


// �������� �� �������� ������� ������� ����� �������
class CCharInput
{
	private:
	protected:
		char m_cChar;
		CTimeStorage m_Time;

		void Initialize();
	public:
		// ����������� �� ���������
		CCharInput();
		// �����������. ���������� cChar � ������� �����.
		CCharInput(char cChar);
		// ����������� � �������� ����� � �������
		CCharInput(char cChar, CTimeContainer i64Time);
		// ����������
		~CCharInput();

		// ���������� ��������
		CTimeContainer GetRemoteness();

		CCharInput& operator=(CCharInput& CharInput);

		// �������
		char GetChar() {return m_cChar;};
		void SetChar(char cChar) {m_cChar = cChar;};
		CTimeStorage& GetTime() {return m_Time;};
};


#endif // __CHARINPUT_H__