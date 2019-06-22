#ifndef _LX_CASHSTORER_H_
#define _LX_CASHSTORER_H_

class CCashdesk;

class CCashStorer
{
public:

	virtual void ReadCash(CCashdesk *Cash)=0;
	virtual void SaveCash(CCashdesk *Cash)=0;
};

#endif //_LX_CASHSTORER_H_
