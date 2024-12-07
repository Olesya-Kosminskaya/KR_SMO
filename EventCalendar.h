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
	int producersCount = 0;   // ���������� ����������
	int consumersCount = 0;   // ���������� ��������
	int maxRequestsCount = 0; // ������������ ���������� ������������ ������ (�� ����� �������������)
	double** calendarArray;   // ������ �� ���������� ���������
	int arrayRows = 0;        // ����� ���������� ���������� � �������� (����� � ���������) + ������ ��� ����� �������������

	EventCalendar(int producersCount, int consumersCount, int maxRequestsCount);
	EventCalendar() {};
	~EventCalendar();
	
	void printCalendar();  
	void updateCalendar(SpecialEvent event);
	SpecialEvent chooseEvent();

};

#endif //IVENTCALENDAR_H