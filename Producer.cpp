#include "Producer.h"

int gen_rand(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

Producer::Producer(int number_)
{
	this->number = number_;
	this->lambda = (rand() % (10 - 0 + 1) + 0) * 0.1;
}

Request Producer::generateRequest()
{
	received_requests_number++;
	double r = (rand() % (90 - 0 + 1) + 0) * 0.01;
	double generation_time = previous_request_generation_time + -1.0 / this->lambda * std::log(r); // Генерация по пуассоновскому закону
	previous_request_generation_time = generation_time;
	return Request(this->number, generation_time);
}

// У каждого источника при создании генерируется и задаётся своя лямбда,
// а время через неё для каждой заявки вычисляется отдельно