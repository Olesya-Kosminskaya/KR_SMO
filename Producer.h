#ifndef PRODUCER_H
#define PRODUCER_H

#include <iostream>
#include "Request.h"

class Producer
{
public:
	int received_requests_number = 0;    // ���-�� ����������� ������
	int number = 0;                      // ����� ���������
	int rejected_requests_number = 0;    // ���-�� ������, ���������� �����
	int served_requests_number = 0;      // ���-�� ������ �� ����� ���������, ������� ���������
	double sum_served_requests_time = 0; // ��������� ����� ������������ ������ ������� ���������
	double lambda/*requests_flow_intensity*/ = 0;  // ������������� ������ ������ (lambda)
	double previous_request_generation_time = 0; // ����� ��������� ���������� ������

//private:
	Producer() {};
	Producer(int number);
	Request generateRequest();

};



#endif //PRODUCER_H
