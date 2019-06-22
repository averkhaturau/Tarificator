#ifndef __DATAREADER_H__
#define __DATAREADER_H__

#include "Exceptions.h"

#include <string>


class CDataReader
{
	private:
	protected:
		// генеряет имена для нумерующихся объектов (Mashine001, Interval002...)
		std::string GenerateName(const std::string sObjName, DWORD Number,
			const unsigned short int _NumDigits = 3) const
		{
			try{
				const unsigned short int _mod = 10;
				char _buf[225];
				_buf[_NumDigits] = 0;
				for (int i = _NumDigits-1; i >= 0; --i)
				{
					_buf[i] = '0'+ Number % _mod;
					Number /= _mod; // id est (Number-_a_digit)/_mod
				};
				return sObjName + std::string(_buf);
			}catch(std::exception &e){
				throw CAnyLogableException(std::string("Error generating name: ")+
					std::string(e.what()), bDoNotWriteDuplicates);
			}catch(...){
				throw CAnyLogableException("Error generating name: unknown exception",
					bDoNotWriteDuplicates);
			};
		};
	public:
		CDataReader() {};
		~CDataReader() {};
};

#endif // __DATAREADER_H__