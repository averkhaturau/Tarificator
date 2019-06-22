#ifndef __CLUBDEFINER_H__
#define __CLUBDEFINER_H__

#include "resource.h"


#define NUMBER_ORION 0
#define NUMBER_TRAFFIC 1
#define NUMBER_CURSOR 2



// ���������� ��� ������� ���� ������ ��� ����� �����
#define CLUB_NUMBER NUMBER_ORION
//#define CLUB_TRAFFIC NUMBER_TRAFFIC
//#define CLUB_NUMBER NUMBER_TRAFFIC



#define ORION_SMALL MAKEINTRESOURCE(IDB_ORION_SMALL)
#define TRAFFIC_SMALL MAKEINTRESOURCE(IDB_TRAFFIC_SMALL)
#define CURSOR_SMALL MAKEINTRESOURCE(IDB_CURSOR_SMALL)

#define ORION_BIG MAKEINTRESOURCE(IDB_ORION_BIG)
#define TRAFFIC_BIG MAKEINTRESOURCE(IDB_TRAFFIC_BIG)
#define CURSOR_BIG MAKEINTRESOURCE(IDB_CURSOR_BIG)

#define TRAFFIC_INFO_TEXT IDS_TRAFFIC_INFO
#define ORION_INFO_TEXT IDS_ORION_INFO
#define CURSOR_INFO_TEXT IDS_CURSOR_INFO



	#if CLUB_NUMBER == NUMBER_ORION
		#define SMALL_BITMAP ORION_SMALL
		#define BIG_BITMAP ORION_BIG
		#define CLUB_INFO ORION_INFO_TEXT
	#endif // CLUB_NUMBER == 0



	#if CLUB_NUMBER == NUMBER_TRAFFIC
		#define SMALL_BITMAP TRAFFIC_SMALL
		#define BIG_BITMAP TRAFFIC_BIG
		#define CLUB_INFO TRAFFIC_INFO_TEXT
	#endif // CLUB_NUMBER == 1

	#if CLUB_NUMBER == NUMBER_CURSOR
		#define SMALL_BITMAP CURSOR_SMALL
		#define BIG_BITMAP CURSOR_BIG
		#define CLUB_INFO CURSOR_INFO_TEXT
	#endif // CLUB_NUMBER == 2


#endif // __CLUBDEFINER_H__