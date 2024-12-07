#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <iomanip>

class Request
{
public:
	int producer_number = 0;            // ����� ���������
	int consumer_number = 0;            // ����� ������� (���� ������ �������� � ������������, �� ����� -1)
	int package_number = 0;             // ����� ������ � ������ (����� ������ �� ����������� �������)
	double generation_time = 0;         // ����� ���������
	double processing_starts_time = 0;  // ����� ������ ���������
	double processed_time = 0;          // ����� ���������
	double buffer_receipt_time = 0;     // ����� ����������� � �����
	double consumer_receipt_time = 0;   // ����� ����������� �� ������
	double waiting_buffer_time = 0;     // ����� �������� � ������
	
//private:
	Request() {};
	Request(int producer_number, /*int package_number,*/ double generation_time);
	void printRequest();   // ����� ���������� � ������ �� �����

};

#endif //REQUEST_H



/*
�����:
- ������ 
- ������� ���-�� ������ 

*/

