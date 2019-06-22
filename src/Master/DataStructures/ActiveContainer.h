/*
	��������� ������ ������-����������, ��������� �������,
	��������� � �.�. ������� �� ������. �������� ���� -
	��	������ ������� �����������������������	���������, ���
	��������� �� ����������������������� �������.
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
	virtual ~CActiveContainer(){Clear();}; // ����������� ������ � CBaseContainer

	// �������� ���� Resident � ��������� � CBaseContainer
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


	// ��� ��������� ������ ������ std::logic_error
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

	// ������� ���
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

	// ���������� ���������
	inline size_type size() const
		{ return m_BaseContainer.size(); };

	// ������������� �� �������������
	inline CBaseContainer GetData() const
		{ return m_BaseContainer; };

	CBaseContainer* GetData()
		{ return &m_BaseContainer; };


	// �������� m_ListIntervals
	myT_& operator =(const myT_& NewValue)
	{
		// ���� �������� ������ ��� ���� ���������
		// � ����������� ��� ��������

		// ����� ���� const
		CBaseContainer NewDataContainer = NewValue.GetData();

		Clear();
		for (const_iterator _Iter = NewDataContainer.begin();
				_Iter != NewDataContainer.end(); ++_Iter)
		{
			AddResident(**_Iter);
		}

		return *this;
	};

	// ����� ��������, ����������� �� ������������� ��� const_iterator CBaseContainer::end()
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

	// ������ � ��������������� �� ���������� ������
	bool IsResponsable()const{return m_bIsResponsible;};
private:
	void SetResponsable(const bool a_bResponsible){m_bIsResponsible = a_bResponsible;};
protected:
	CBaseContainer m_BaseContainer;

	// ���������� ��������������� �� �������.��������� ������ ��� � auto_ptr
	bool m_bIsResponsible;
};

/*
	Copyright Alex Verkhoturov
*/
#endif //_LX_CONTAINER_INCLUDED_