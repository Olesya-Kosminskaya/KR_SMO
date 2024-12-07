#ifndef CONSUMER_H
#define CONSUMER_H

#include <iostream>
#include "Request.h"

class Consumer
{
public:
	int number = 0;                     // Номер прибора
	bool isFree = true;                 // Параметр: занят/свободен (в начале - свободен) (можно смотреть в календаре)
	double request_processing_time = 0; // Время обработки заявки

	/*-  ;
	- время освобождения (можно смотреть в календаре);
	- время обработки заявки, которая сейчас на приборе;
	- закон распределения времени обслуживания 
	- ;
	*/
	Consumer(int number, int start, int end);
	void process(Request *request);      // Обработка заявки
	//int gen_rand(int start, int end);   // Генерация времени обработки заявки

};


#endif //CONSUMER_H