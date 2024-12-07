#ifndef PRODUCER_H
#define PRODUCER_H

#include <iostream>
#include "Request.h"

class Producer
{
public:
	int received_requests_number = 0;    // Кол-во поступивших заявок
	int number = 0;                      // Номер источника
	int rejected_requests_number = 0;    // Кол-во заявок, получивших отказ
	int served_requests_number = 0;      // Кол-во заявок от этого источника, которые обслужены
	double sum_served_requests_time = 0; // Суммарное время обслуживания заявок данного источника
	double lambda/*requests_flow_intensity*/ = 0;  // Интенсивность потока заявок (lambda)
	double previous_request_generation_time = 0; // Время генерации предыдущей заявки

//private:
	Producer() {};
	Producer(int number);
	Request generateRequest();

};



#endif //PRODUCER_H
