#include "Request.h";


Request::Request(int producer_number_, /*int package_number_,*/ double generation_time_)
{
	this->producer_number = producer_number_;
	//this->package_number = package_number_;
	this->generation_time = generation_time_;
}

void Request::printRequest() {
	/*
	int producer_number = 0;            // ����� ���������
	int consumer_number = 0;            // ����� �������
	int package_number = 0;             // ����� ������ � ������
	double generation_time = 0;         // ����� ���������
	double processing_starts_time = 0;  // ����� ������ ���������
	double processed_time = 0;          // ����� ���������
	double buffer_receipt_time = 0;     // ����� ����������� � �����
	double consumer_receipt_time = 0;   // ����� ����������� �� ������
	double waiting_buffer_time = 0;     // ����� �������� � ������
	*/
	std::cout << std::setprecision(3) << "����� ���������: " << producer_number 
		<< " ����� ������ � ������: " << package_number << " ����� �������: " << consumer_number 
		<< "\n����� ���������: " << generation_time
		<< " ����� ������ ���������: " << processing_starts_time << " ����� ���������: " << processed_time
		<< "\n����� ����������� � �����: " << buffer_receipt_time << " ����� ����������� �� ������: "
		<< consumer_receipt_time << " ����� �������� � ������: " << waiting_buffer_time << "\n\n";
}