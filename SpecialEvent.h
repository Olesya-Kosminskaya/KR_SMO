#ifndef SPECIALEVENT_H
#define SPECIALEVENT_H

#include <iostream>
#include "Request.h"

class SpecialEvent
{
public:
	int type = 0; // 1 - ����������� ������, 2 - ������������ �������, 3 - ����� �������������
	bool sign = 0; // �������: 0 � �������� ������ ����������� ���������� ��
				           //  1 � ���������� ������ ����������� ���������� ��
	double moment = 0; // ������ �����������
	int number = 0;    // ����� ��������� ��� �������

	SpecialEvent() {};
	SpecialEvent(int type, bool sign, double moment, int number);
};

#endif //SPECIALEVENT_H