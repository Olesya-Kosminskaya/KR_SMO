#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <iomanip>

class Request
{
public:
	int producer_number = 0;            // Номер источника
	int consumer_number = 0;            // Номер прибора (если заявке отказали в обслуживании, он будет -1)
	int package_number = 0;             // Номер заявки в пакете (среди заявок от конкретного прибора)
	double generation_time = 0;         // Время генерации
	double processing_starts_time = 0;  // Время начала обработки
	double processed_time = 0;          // Время обработки
	double buffer_receipt_time = 0;     // Время поступления в буфер
	double consumer_receipt_time = 0;   // Время поступления на прибор
	double waiting_buffer_time = 0;     // Время ожидания в буфере
	
//private:
	Request() {};
	Request(int producer_number, /*int package_number,*/ double generation_time);
	void printRequest();   // Вывод информации о заявке на экран

};

#endif //REQUEST_H



/*
Буфер:
- размер 
- текущее кол-во заявок 

*/

