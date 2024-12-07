#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include "Request.h"

class Consumer
{
public:
	int number = 0;                     // ����� �������
	bool isFree = true;                 // ��������: �����/�������� (� ������ - ��������) (����� �������� � ���������)
	double request_processing_time = 0; // ����� ��������� ������

	/*-  ;
	- ����� ������������ (����� �������� � ���������);
	- ����� ��������� ������, ������� ������ �� �������;
	- ����� ������������� ������� ������������ 
	- ;
	*/
	Consumer(int number, int start, int end);
	void process(Request *request);      // ��������� ������
	//int gen_rand(int start, int end);   // ��������� ������� ��������� ������

};


#endif //CONSUMER_H