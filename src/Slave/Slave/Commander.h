#ifndef __COMMANDER_H__
#define __COMMANDER_H__

#include <vector>
#include <string>


// Класс распознавателя и формирователя команд
class CCommander
{
	public:
		typedef std::vector<DWORD> CVector;

	private:
		void DoDeleteEverything();
	protected:
		std::string* m_psPrefix;
		CVector* m_pMessagesTable;
	public:
		// Конструктор. Надо сразу указывать параметры.
		CCommander(std::string sPrefix, const DWORD* pdwMessagesTable, DWORD dwTableLength);
		// Деструктор
		virtual ~CCommander();
};


#endif // __COMMANDER_H__