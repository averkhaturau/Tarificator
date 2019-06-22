/*
	Описывает шаблон класса-контейнера, способный хранить,
	добавлять и т.п. объекты по ссылке. Основная фича -
	не	должен хранить непроинициализированные	указатели, или
	указатели на непроинициализированные объекты.
*/
#ifndef _LX_CONTAINER_INCLUDED_
#define _LX_CONTAINER_INCLUDED_

#include <vector>
//#include <list>

// Declaration of general templeate CActiveContainer
template<class CResident, class CBaseContainer = std::vector<CResident*> >
	class CActiveContainer
{
	typedef CActiveContainer myT_;
public:
	typedef CBaseContainer CBaseContainer;
	typedef CBaseContainer::size_type size_type;
	typedef CBaseContainer::iterator iterator;
	typedef CBaseContainer::const_iterator const_iterator;

	CActiveContainer(const bool a_bResponsable=true){SetResponsable(a_bResponsable);};
	virtual ~CActiveContainer(){Clear();}; // освобождает память и CBaseContainer

	// копирует себе Resident и вставляет в CBaseContainer
	inline CBaseContainer::reference AddResidentBack(CResident& Resident)
	{
#pragma warning( push )
#pragma warning( disable : 4172 )
		try{
			CResident* pNewResident;
			if (IsResponsable())
			{
				pNewResident = new CResident;

				*pNewResident = Resident;
				m_BaseContainer.push_back(pNewResident);
			}
			else // not responsable for memory
			{
				pNewResident = &Resident;
				m_BaseContainer.push_back(pNewResident);
			}
			return pNewResident;
		}catch(std::exception &e){
			throw std::runtime_error((std::string)"AddResident failed "+std::string(e.what()));
		}catch(...){
			throw std::runtime_error((std::string)"AddResident failed: Unknown exception");
		}
#pragma warning( pop )
	};

	inline CBaseContainer::reference AddResidentFront(CResident& Resident)
	{
#pragma warning( push )
#pragma warning( disable : 4172 )
		try{
			CResident* pNewResident;
			if (IsResponsable())
			{
				pNewResident = new CResident;

				*pNewResident = Resident;
				m_BaseContainer.push_front(pNewResident);
			}
			else // not responsable for memory
			{
				pNewResident = &Resident;
				m_BaseContainer.push_front(pNewResident);
			}
			return pNewResident;
		}catch(std::exception &e){
			throw std::runtime_error((std::string)"AddResident failed "+std::string(e.what()));
		}catch(...){
			throw std::runtime_error((std::string)"AddResident failed: Unknown exception");
		}
#pragma warning( pop )
	};

	inline CBaseContainer::reference AddResident(CResident& Resident)
	{
		return AddResidentBack(Resident);
	};


	// При отсутстии такого райсит std::logic_error
	inline void DeleteResident(CResident& Deseased)
	{
		CBaseContainer::iterator _iter = 
				FindResident(Deseased);
		if (_iter != m_BaseContainer.end())
		{
			if (IsResponsable())
				delete *_iter;
			m_BaseContainer.erase(_iter);
		}
		else
		{
			throw std::logic_error("Wrong parameter in DeleteResident");
		}
	};

	// удаляет все
	inline void Clear()
	{
		if (IsResponsable())
		{
			while (!m_BaseContainer.empty())
			{
				delete m_BaseContainer.back();
				m_BaseContainer.pop_back();
			}
		}
		else
		{
			m_BaseContainer.clear();
		}
	};

	// количество интевалов
	inline size_type size() const
		{ return m_BaseContainer.size(); };

	// использование не рекомендуется
	inline CBaseContainer GetData() const
		{ return m_BaseContainer; };

	CBaseContainer* GetData()
		{ return &m_BaseContainer; };


	// копирует m_ListIntervals
	myT_& operator =(const myT_& NewValue)
	{
		// надо выделить память для всех элементов
		// и скопировать все элементы

		// чтобы было const
		CBaseContainer NewDataContainer = NewValue.GetData();

		Clear();
		for (const_iterator _Iter = NewDataContainer.begin();
				_Iter != NewDataContainer.end(); ++_Iter)
		{
			AddResident(**_Iter);
		}

		return *this;
	};

	// выдаёт итератор, указывающий на точнотакойжий или const_iterator CBaseContainer::end()
	iterator FindResident(CResident Wanted)
	{
		iterator _iter;
		for (_iter = m_BaseContainer.begin();
				_iter != m_BaseContainer.end(); ++_iter)
		{
			if ((**_iter) == Wanted)
				break;
		}

		return _iter;
	};

	// доступ к ответственности за выделяемую память
	bool IsResponsable()const{return m_bIsResponsible;};
private:
	void SetResponsable(const bool a_bResponsible){m_bIsResponsible = a_bResponsible;};
protected:
	CBaseContainer m_BaseContainer;

	// определяем ответственность за очистку.выделение памяти как в auto_ptr
	bool m_bIsResponsible;
};

/*
	Copyright Alex Verkhoturov
*/
#endif //_LX_CONTAINER_INCLUDED_