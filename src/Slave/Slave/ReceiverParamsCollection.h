#ifndef __RECEIVEPARAMSCOLLECTION_H__
#define __RECEIVEPARAMSCOLLECTION_H__

#include "MultiThreadManager.h"
#include "Exceptions.h"
#include "TimeOutManager.h"

#include <vector>
#include "Winsock2.h"


typedef unsigned long int SizeType;

class CTCP_IP_Receiver;

class CReceiveParameters: public CThreadParameters
{
	public:
		typedef std::vector<char> CVector;

	private:
		void DoDeleteEverything()
		{
			if (m_pVectorBuffer)
			{
				delete m_pVectorBuffer;
				m_pVectorBuffer = 0;
			}
			if (m_pTimeOutManager)
			{
				delete m_pTimeOutManager;
				m_pTimeOutManager = 0;
			}
			if (m_Socket)
			{
				closesocket(m_Socket);
				m_Socket = INVALID_SOCKET;
			}
		};
	protected:
		// ��������������� �������
		CTCP_IP_Receiver* m_pReceiver;
		// ������ ��
		bool m_bUsed;
		// �������. ��� �������� OnBegin ������ ���, ����� ��������
		// SetUsed(true). �������� �������� ���� ������ �� �������,
		// ������� ������ ����� � ������������.
		CTimeOutManager* m_pTimeOutManager;

		//DWORD m_dwBytesRead;

		SOCKET m_Socket;
		CVector* m_pVectorBuffer;
	public:
		CReceiveParameters()
		{
			m_pReceiver = 0;
			m_bUsed = false;
			m_Socket = INVALID_SOCKET;

			//m_dwBytesRead = 0;

			m_pVectorBuffer = 0;
				try
				{
					m_pVectorBuffer = new CVector;

					m_pTimeOutManager = new CTimeOutManager;
					m_pTimeOutManager->SetEnabled(true);
					// 5 �����
					m_pTimeOutManager->SetTimeOut( CTimeStorage(5 * A_Minute.GetTime()) );
					m_pTimeOutManager->OnBegin();
				}
				catch(...)
				{
					DoDeleteEverything();
					throw CAnyLogableException("An unknown error occured in CReceiveParameters::CReceiveParameters", bDoNotWriteDuplicates);
				}
		};
		virtual ~CReceiveParameters()
		{
			DoDeleteEverything();
		};

		// ��� ������� ���� �� �������� �� �������, �� ��� �� �����
		// ���������� �� ��������� ��� ������ ���������� ����������
		void OnTimer()
		{
				if (m_pTimeOutManager->IsTimeExpired())
				{
					m_bUsed = false;

						if (m_Socket)
						{
							closesocket(m_Socket);
							m_Socket = 0;
						}
				}
		};

		// �������
		CTCP_IP_Receiver* GetReceiver() {return m_pReceiver;};
		void SetReceiver(CTCP_IP_Receiver* pNew) {m_pReceiver = pNew;};
		bool GetUsed() {return m_bUsed;};
		void SetUsed(bool bNew)
		{
			m_bUsed = bNew;
				if (bNew)
					m_pTimeOutManager->OnBegin();
		};
		SOCKET GetSocket() {return m_Socket;};
		void SetSocket(SOCKET Socket) {m_Socket = Socket;};
		DWORD GetSize() {return m_pVectorBuffer->size();};

		CVector* GetVectorBuffer() {return m_pVectorBuffer;};
		char* GetBuffer() {return m_pVectorBuffer->begin();};
};


class CReceiverParamsCollection
{
	public:
		typedef std::vector<CReceiveParameters*> CVector;

	private:
		void DoDeleteEverything();
	protected:
		CVector* m_pData;
	public:
		CReceiverParamsCollection();
		virtual ~CReceiverParamsCollection();


		// ������ parameter, ������� ����� �������, ��� 0, ���� ���
		// ��� ��� �������
		CReceiveParameters* GetFreeParams();

		SizeType size();
		void resize(SizeType uiNewSize);

		// �������
		CVector* GetData() {return m_pData;};
};


#endif // __RECEIVEPARAMSCOLLECTION_H__