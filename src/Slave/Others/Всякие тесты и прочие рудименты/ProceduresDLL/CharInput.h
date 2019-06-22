#ifndef __CHARINPUT_H__
#define __CHARINPUT_H__


#include "..\..\Master\DataStructures\ClubSettings\TimeStorage.h"


// Отвечает за хранение истории нажатия одной клавиши
class CCharInput
{
	private:
	protected:
		char m_cChar;
		CTimeStorage m_Time;

		void Initialize();
	public:
		// Конструктор по умолчанию
		CCharInput();
		// Конструктор. Записывает cChar и текущее время.
		CCharInput(char cChar);
		// Конструктор с уазанием буквы и времени
		CCharInput(char cChar, CTimeContainer i64Time);
		// Деструктор
		~CCharInput();

		// Возвращает давность
		CTimeContainer GetRemoteness();

		CCharInput& operator=(CCharInput& CharInput);

		// Обертки
		char GetChar() {return m_cChar;};
		void SetChar(char cChar) {m_cChar = cChar;};
		CTimeStorage& GetTime() {return m_Time;};
};


#endif // __CHARINPUT_H__