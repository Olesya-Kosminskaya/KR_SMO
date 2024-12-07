#include "Consumer.h";
#include "windows.h"

//int Consumer::gen_rand(int start, int end)
//{
//	return rand() % (end - start + 1) + start;
//}

Consumer::Consumer(int number_, int start, int end)
{
	this->number = number_;
	//int start = 10;
	//int end = 50;
	this->request_processing_time = (rand() % (end - start + 1) + start) * 0.1;
}

void Consumer::process(Request *request)
{   // Время генерируется по равномерному закону
	(*request).processed_time = (*request).processing_starts_time + this->request_processing_time;
	(*request).consumer_receipt_time = (*request).processing_starts_time;
	if ((*request).buffer_receipt_time != 0) {
		(*request).waiting_buffer_time = (*request).consumer_receipt_time - (*request).buffer_receipt_time;
	}
	(*request).consumer_number = this->number;
	std::cout << "Request " << (*request).producer_number << "."
		<< (*request).package_number << " is under processing...\n";
	//Sleep(this->request_processing_time * 1000);
}


// У каждого прибора при создании генерируется время обслуживания (один раз) и дальше используется