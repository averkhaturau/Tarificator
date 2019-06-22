#ifndef __TASKBUTTONSCOLLECTION_H__
#define __TASKBUTTONSCOLLECTION_H__

#include "..\..\Master\DataStructures\ActiveContainerResizable.h"
#include "TaskButton.h"


class CTaskButtonsCollection : public CActiveContainerResizable<CTaskButton>
{
	private:
	protected:
	public:
		CTaskButtonsCollection() {};
		virtual ~CTaskButtonsCollection() {};
};


#endif // __TASKBUTTONSCOLLECTION_H__