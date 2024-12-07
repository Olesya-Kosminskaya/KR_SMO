#ifndef IVENTCALENDAR_H
#define IVENTCALENDAR_H

#include <iostream>
#include <vector>
#include <limits>

#include "SpecialEvent.h"
#include "Request.h"
#include "Producer.h"
#include "Consumer.h"


class EventCalendar
{
public:
	int producersCount = 0;   //  оличество источников
	int consumersCount = 0;   //  оличество приборов
	int maxRequestsCount = 0; // ћаксимальное количество генерируемых за€вок (до конца моделировани€)
	double** calendarArray;   // ћассив со значени€ми календар€
	int arrayRows = 0;        // ќбщее количество источников и приборов (строк в календаре) + строка дл€ конца моделировани€

	EventCalendar(int producersCount, int consumersCount, int maxRequestsCount);
	EventCalendar() {};
	~EventCalendar();
	
	void printCalendar();  
	void updateCalendar(SpecialEvent event);
	SpecialEvent chooseEvent();

};

#endif //IVENTCALENDAR_H