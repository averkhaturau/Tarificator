#ifndef __FILEUPDATEMANAGER_H__
#define __FILEUPDATEMANAGER_H__

#include "UpdateManager.h"
#include "Saving\MasterBoundStorer.h"

#include <string>


// Реализован в том предположении, что при переименовании файлов
// выключение питания или иные непредвиденные ситуации не способны
// привести к наличию одновременно двух файлов - с новым и старым
// именами.
class CFileUpdateManager : public CUpdateManager
{
	public:
		typedef std::string CFileName;

	private:
	protected:
		// Путь к каталогу, в котором будет происходить сохранение и
		// обновление. Перед использованием манагера надо обязательно
		// его проинициализировать. Надо, чтобы в конце обязательно
		// стоял '\'.
		CFileName m_DirectoryPath;
		// По умолчанию - тильда
		char m_cTempSymbol;
		// Базовое имя файла. Его надо задать перед вызовом
		// GetValidFileName, DoPrepareBeforeUpdate и т.д..
		CFileName m_BaseFileName;

		void DoRemoveReadOnlyAttribute(CFileName* pName);
		void DoCheckFilesExistance(bool& bBaseFileExists, bool& bTempFileExists);
	public:
		CFileUpdateManager();

		CFileUpdateManager(CMasterBoundStorer* pStorer);

		virtual ~CFileUpdateManager();


		// Перед вызовом этой пачки функций надо проинить m_BaseFileName

		// Возвращает имя (с полным путем) валидного файла. Если нет
		// ни одного такого файла - возвращает пустую строку.
		virtual CFileName GetValidFileName();
		// Выполняет подготовку перед обновлением файла. Возвращает имя
		// файла (с полным путем) для сохранения. 
		virtual CFileName DoPrepareBeforeUpdate();
		// Выполняет завершающую стадию обновления
		virtual void DoFinalizeUpdate();

		// Обертки
		void SetDirectoryPath(CFileName* pNew) {m_DirectoryPath = *pNew;};
		CFileName* GetDirectoryPath() {return &m_DirectoryPath;};
		void SetTempSymbol(char cNew) {m_cTempSymbol = cNew;};
		char GetTempSymbol() {return m_cTempSymbol;};
		void SetBaseFileName(CFileName* pNew) {m_BaseFileName = *pNew;};
		CFileName* GetBaseFileName() {return &m_BaseFileName;};
};

#endif // __FILEUPDATEMANAGER_H__