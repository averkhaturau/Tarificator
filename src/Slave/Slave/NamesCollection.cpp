#include "stdafx.h"

#include "NamesCollection.h"


CNamesCollection::CNamesCollection()
{
	m_pNames = new CNamesVector;
}
// End of CNamesCollection()


CNamesCollection::CNamesCollection(SizeType InitialSize)
{
	m_pNames = new CNamesVector;
	resize(InitialSize);
}
// End of CNamesCollection(SizeType)


CNamesCollection::~CNamesCollection()
{
	resize(0);
		if (m_pNames)
		{
			delete m_pNames;
			m_pNames = 0;
		}
}
// End of ~CNamesCollection()


void CNamesCollection::resize(SizeType NewSize)
{
	SizeType OldSize = m_pNames->size();

		if (NewSize > OldSize)
		{
			// Создаю новые строки
			m_pNames->resize(NewSize);
				for (CNamesVector::iterator iter = m_pNames->begin() + OldSize;
						iter < m_pNames->end();
						iter++)
				{
					*iter = new FileName;
				}
		}
		else
		{
				// Убиваю строки. Если size == OldSize, цикл не выполняется ни разу.
				for (CNamesVector::iterator iter = m_pNames->begin() + NewSize;
						iter < m_pNames->end();
						iter++)
				{
					delete *iter;
				}
			m_pNames->resize(NewSize);
		}
}
// End of resize


FileName& CNamesCollection::operator[](SizeType Index)
{
	return *(*m_pNames)[Index];
}
// End of operator[]


SizeType CNamesCollection::size()
{
	return m_pNames->size();
}
// End of size()


CNamesVector::iterator CNamesCollection::LookForName(LPCTSTR a_psName)
{
	CNamesVector::iterator Iter = m_pNames->begin(),
				EndIter = m_pNames->end();
		for (; Iter < EndIter; ++Iter)
		{
				if (!_stricmp(a_psName, (*Iter)->c_str()))
					return Iter;
		}

	return 0;
}
// End of LookForName


void CNamesCollection::AddName(LPCTSTR a_psName)
{
	resize(size() + 1);
	(*this)[size() - 1].resize(strlen(a_psName));
	strcpy((*this)[size() - 1].begin(), a_psName);
}
// End of AddName
