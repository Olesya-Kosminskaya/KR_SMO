#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <iostream>
#include "Request.h"

class SpecialEvent
{
public:
	int type = 0; // 1 - поступление за€вки, 2 - освобождение прибора, 3 - конец моделировани€
	bool sign = 0; // признак: 0 Ц известен момент наступлени€ очередного ќ—
				           //  1 Ц неизвестен момент наступлени€ очередного ќ—
	double moment = 0; // момент поступлени€
	int number = 0;    // номер источника или прибора

	SpecialEvent() {};
	SpecialEvent(int type, bool sign, double moment, int number);
};

#endif //SPECIALEVENT_H