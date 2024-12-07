#include "Request.h";


Request::Request(int producer_number_, /*int package_number_,*/ double generation_time_)
{
	this->producer_number = producer_number_;
	//this->package_number = package_number_;
	this->generation_time = generation_time_;
}

void Request::printRequest() {
	/*
	int producer_number = 0;            // Номер источника
	int consumer_number = 0;            // Номер прибора
	int package_number = 0;             // Номер заявки в пакете
	double generation_time = 0;         // Время генерации
	double processing_starts_time = 0;  // Время начала обработки
	double processed_time = 0;          // Время обработки
	double buffer_receipt_time = 0;     // Время поступления в буфер
	double consumer_receipt_time = 0;   // Время поступления на прибор
	double waiting_buffer_time = 0;     // Время ожидания в буфере
	*/
	std::cout << std::setprecision(3) << "Номер источника: " << producer_number 
		<< " Номер заявки в пакете: " << package_number << " Номер прибора: " << consumer_number 
		<< "\nВремя генерации: " << generation_time
		<< " Время начала обработки: " << processing_starts_time << " Время обработки: " << processed_time
		<< "\nВремя поступления в буфер: " << buffer_receipt_time << " Время поступления на прибор: "
		<< consumer_receipt_time << " Время ожидания в буфере: " << waiting_buffer_time << "\n\n";
}