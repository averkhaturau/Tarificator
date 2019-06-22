#ifndef _LX_ACTIVECONTAINERResizable_H_INCLUDED_
#define _LX_ACTIVECONTAINERResizable_H_INCLUDED_

#include "ActiveContainer.h"

template <class CResident>
	class CActiveContainerResizable
		: public CActiveContainer<CResident,std::vector<CResident*> >
{
	typedef CActiveContainerResizable myT_;
public:

	CActiveContainerResizable(const bool a_bResponsable=true)
		: CActiveContainer<CResident>(a_bResponsable){};

	// the main feature
	void resize(const size_type NewSize)
	{
		if (NewSize > 0)
		{
			if (IsResponsable())
			{
				const CBaseContainer::size_type initsize = size();
				if (initsize == NewSize) return;
				if (NewSize < initsize)
				{ // NewSize < size()
					for (CBaseContainer::iterator _Element = m_BaseContainer.begin() + NewSize;
							_Element != m_BaseContainer.end(); ++_Element)
						delete (*_Element);
					m_BaseContainer.resize(NewSize);
				}
				else
				{ // NewSize > size()
					m_BaseContainer.resize(NewSize);
					for (CBaseContainer::iterator _Element = m_BaseContainer.begin()+initsize;
						_Element != m_BaseContainer.end(); ++_Element)
							(*_Element) = new CResident();
				}
			}
			else // not responsable
			{
				m_BaseContainer.resize(NewSize);
			}
		}
		else
		{
			Clear();
		}
	}; // end of void resize(const size_type NewSize)

	CResident& operator[](const size_type Index)
		{ return *m_BaseContainer[Index]; };


};

#endif // _LX_ACTIVECONTAINERResizable_H_INCLUDED_