#ifndef __INPUTSCOLLECTION_H__
#define __INPUTSCOLLECTION_H__


#include "CharInput.h"


typedef unsigned long int SizeType;

// ��� �������� ������� ������� ������. ��������� � �����������
// ������, �.�. ������� � dll.
template<SizeType uiSize> class CInputsCollection
{
	private:
	protected:
		CTimeContainer m_i64TimeOut;
		CCharInput m_Data[uiSize];
	public:
		// ����������� � ��������� ������������ �������
		CInputsCollection(char cChar);
		// ����������
		~CInputsCollection();

		CCharInput& operator[](SizeType uiIndex);
		// ��� �������������
		CInputsCollection& operator=(char cChar);

		// ��������� �������, ������ ��� ���� ����������
		void Add(CCharInput& CharInputToAdd);
		// cpPassword - null-terminated. true, ���� ���������.
		bool CompareWithPassword(char* pcPassword);

		// �������
		void SetTimeOut(CTimeContainer i64NewTimeOut) {m_i64TimeOut = i64NewTimeOut;};
		CTimeContainer GetTimeOut() {return m_i64TimeOut;};
};




// -------------------------
// Implementation
// -------------------------




template<SizeType uiSize> CInputsCollection<uiSize>::CInputsCollection(char cChar)
{
	*this = cChar;

	m_i64TimeOut = 0;
}
// End of CInputsCollection


template<SizeType uiSize> CInputsCollection<uiSize>::~CInputsCollection()
{

}
// End of ~CInputsCollection()


template<SizeType uiSize> CCharInput& CInputsCollection<uiSize>::operator[](SizeType uiIndex)
{
	return *m_Data[uiIndex];
}
// End of operator[]


template<SizeType uiSize> CInputsCollection<uiSize>& CInputsCollection<uiSize>::operator=(char cChar)
{
	CCharInput* pEnd = &(m_Data[uiSize - 1]);
		for (CCharInput* pInput = &(m_Data[0]); pInput < pEnd; pInput++)
		{
			CCharInput CharInput(cChar);
			(*pInput) = CharInput;
		}

	return *this;
}
// End of operator=


template<SizeType uiSize> void CInputsCollection<uiSize>::Add(CCharInput& CharInputToAdd)
{
	CCharInput* pFrom = &(m_Data[uiSize - 2]), *pTo = &(m_Data[uiSize - 1]);

		// ������� ��� �������� �� 1 ������
		for (; pFrom >= &(m_Data[0]); pFrom--, pTo--)
		{
			*pTo = *pFrom;
		}

		for (CCharInput* pIter = &(m_Data[0]); pIter < &(m_Data[uiSize]); pIter++)
		{
				if (pIter->GetRemoteness() > m_i64TimeOut)
				{
					pIter->SetChar(0);
				}
		}

	m_Data[0] = CharInputToAdd;

	// ���������� � uppercase
	char cTemp = CharInputToAdd.GetChar();
	_toupper(cTemp);
	m_Data[0].SetChar(cTemp);
}
// End of Add


template<SizeType uiSize> bool CInputsCollection<uiSize>::CompareWithPassword(char* pcPassword)
{
	bool bResult = true;
	char* pcPasswordIter = pcPassword;
	CCharInput* pDataIter = &(m_Data[0]);
		for (; ( (*pcPasswordIter) && (pDataIter < &(m_Data[uiSize])) && (bResult) );
					pcPasswordIter++, pDataIter++)
		{
				if ( (*pcPasswordIter) != pDataIter->GetChar() )
				{
					bResult = false;
				}
		}

	return bResult;
}
// End of CompareWithPassword


#endif // __INPUTSCOLLECTION_H__