#ifndef __NAMESCOLLECTION_H__
#define __NAMESCOLLECTION_H__

#include <vector>
#include <string>


typedef std::string FileName;
typedef std::vector<FileName*> CNamesVector;

typedef unsigned long int SizeType;


class CNamesCollection
{
	private:
	protected:
		CNamesVector* m_pNames;
	public:
		// ����������� �� ���������
		CNamesCollection();
		// ����������� � ��������� ���������� �������
		CNamesCollection(SizeType InitialSize);
		// ���������� �� ���������
		~CNamesCollection();

		// ������ ������ (���-�� ����)
		void resize(SizeType NewSize);
		FileName& operator[](SizeType Index);
		// ���������� ���-�� ����
		SizeType size();

		// ��������� ���
		void AddName(LPCTSTR a_psName);

		CNamesVector::iterator LookForName(LPCTSTR a_psName);
};


#endif // __NAMESCOLLECTION_H__