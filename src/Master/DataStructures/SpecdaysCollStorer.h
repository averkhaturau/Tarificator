#ifndef _LX_SPECIALDAYSSTORER_H_INCLUDED___
#define _LX_SPECIALDAYSSTORER_H_INCLUDED___

class CSpecDaysCollection;

class CSpecDaysCollStorer
{
	virtual void SaveSpecDays(CSpecDaysCollection * a_SDColl) =0;
	virtual void ReadSpecDays(CSpecDaysCollection * a_SDColl) =0;
};

#endif //_LX_SPECIALDAYSSTORER_H_INCLUDED___
