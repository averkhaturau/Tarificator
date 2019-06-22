/*
	Описывает класс, хранящий данные об операторе
*/
#ifndef _LX_OPERATOR_H_INCLUDED_
#define _LX_OPERATOR_H_INCLUDED_

#include <string>

// уровень доступа к ресурсам
typedef unsigned long int CPermission;

// в чём храним хэш пассворда
typedef __int64 CPasswordHash;

class COperator
{
public:
	COperator() { SetPermission(0); };
	COperator(const std::string& Name, const CPasswordHash& PasswordHash = (CPasswordHash)0,
		const CPermission& Permission = 0)
	{SetName(Name); SetPasswordHash(PasswordHash); SetPermission(Permission);};

	virtual ~COperator(){};

	// доступ к полям
	std::string& GetName() { return m_Name; };
	CPasswordHash GetPasswordHash() const { return m_PasswordHash; };
	CPermission GetPermission() const { return m_Permission; };

	void SetName(const std::string& Name) { m_Name = Name; };
	void SetPasswordHash(const CPasswordHash& PasswordHash)
		{ m_PasswordHash = PasswordHash; };
	void SetPermission(const CPermission& Permission)
		{ m_Permission = Permission; };

	COperator& operator =(COperator& Another)
	{
		SetName(Another.GetName());
		SetPasswordHash(Another.GetPasswordHash());
		SetPermission(Another.GetPermission());
		return *this;
	};

protected:
	// имя оператора
	std::string m_Name;
	// хэш личного пассворда
	CPasswordHash m_PasswordHash;
	// уровень доступа к ресурсам
	CPermission m_Permission;
};

operator == (COperator _1, COperator _2);
operator != (COperator _1, COperator _2);

#endif // _LX_OPERATOR_H_INCLUDED_