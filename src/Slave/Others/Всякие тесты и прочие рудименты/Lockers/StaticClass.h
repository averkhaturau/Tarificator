#ifndef __STATICCLASS_H__
#define __STATICCLASS_H__


// Вспомогательный класс. Юзается в иерархии CInputLocker, CMouseLocker,
// CKeyboardLocker. Нужен только для того, чтобы хранить static
// data member m_hModule, т.к. по-другому не получается (static
// data member, прописанный в класс-предке CInputLocker, принадлежит
// этому классу или любому классу-наследнику, поэтому не получается
// организовать единое на всю иерархию хранилище).
class CStaticClass
{
	private:
	protected:
		static HMODULE m_hModule;
	public:
		HMODULE& GetModule() {return m_hModule;};
};

#endif //__STATICCLASS_H__