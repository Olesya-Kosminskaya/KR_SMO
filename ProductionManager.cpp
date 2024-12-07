#include "ProductionManager.h"
#include <limits>

ProductionManager::ProductionManager(Buffer& buffer_) {
	//Buffer buffer_(bufferSize);
	this->buffer = buffer_;
}

// Функция добавления заявки в буфер, дисциплина отказа

void ProductionManager::addRequest(Request *request) {
	// Если все места в буфере заполнены
	if (this->buffer.current_requests_count == this->buffer.size)
	{
		// Поиск самой старой заявки в буфере
		double minTime = DBL_MAX; // Начальное значение времени, с которым сравниваем
		int indexOld = 0;         // Переменная для индекса самой старой заявки
		for (int i = 0; i < this->buffer.size; i++) {
			if (this->buffer.bufVect[i].buffer_receipt_time <= minTime) {
				indexOld = i;
			}
		}

		// Удаление самой старой заявки из буфера
		// И вставка новой на её место
		this->buffer.bufVect[indexOld] = (*request);
		(*request).buffer_receipt_time = (*request).generation_time;
	}
	// Если в буфере есть свободные места
	else
	{
		this->buffer.current_requests_count++; // Увеличиваем количество текущих заявок
		int indexNew = 0;
		// Ищем пустое место для вставки новой заявки
		for (int i = 0; i < this->buffer.bufVect.size(); i++) {
			if (this->buffer.bufVect[i].producer_number == 0) {
				indexNew = i;
				break;
			}
		}
		this->buffer.bufVect[indexNew] = (*request); // Добавляем новую заявку на пустое место
		(*request).buffer_receipt_time = (*request).generation_time;
	}
	(*request).printRequest();
	this->buffer.printBuffer();
}

// Добавление новой заявки, если в буфере есть свободные места
bool ProductionManager::addNewRequest(Request *request) {
	// Если есть места
	if (this->buffer.current_requests_count < this->buffer.size) {
		this->buffer.current_requests_count++; // Увеличиваем количество текущих заявок
		int indexNew = 0;
		// Ищем пустое место для вставки новой заявки
		for (int i = 0; i < this->buffer.bufVect.size(); i++) {
			if (this->buffer.bufVect[i].producer_number == 0) {
				indexNew = i;
				break;
			}
		}
		(*request).buffer_receipt_time = (*request).generation_time;
		this->buffer.bufVect[indexNew] = (*request); // Добавляем новую заявку на пустое место
		std::cout << "\nRequest " << (*request).producer_number << "." << (*request).package_number
			<< " was put in buffer\n";
		(*request).printRequest();
		this->buffer.printBuffer();
		return 0;
	}
	else { // Если нет мест
		return 1;
	}
}

// Отказ старой заявке и добавление новой на свободное место
Request ProductionManager::rejOldaddNewRequest(Request *newRequest) {
	
	// Поиск самой старой заявки в буфере
	double minTime = DBL_MAX; // Начальное значение времени, с которым сравниваем
	Request oldRequest(0, 0);
	int indexOld = 0;      // Переменная для индекса самой старой заявки
	for (int i = 0; i < this->buffer.bufVect.size(); i++) {
		if (this->buffer.bufVect[i].buffer_receipt_time <= minTime) {
			oldRequest = this->buffer.bufVect[i];
			indexOld = i;
			minTime = this->buffer.bufVect[i].buffer_receipt_time;
		}
	}
	// Удаление самой старой заявки из буфера
	// И вставка новой на её место
	(*newRequest).buffer_receipt_time = (*newRequest).generation_time;
	this->buffer.bufVect[indexOld] = (*newRequest);
	std::cout << "\nRequest " << oldRequest.producer_number << "." << oldRequest.package_number
		<< " was rejected\n";
	oldRequest.printRequest();
	std::cout << "\nRequest " << (*newRequest).producer_number << "." << (*newRequest).package_number
		<< " was put in buffer\n";
	(*newRequest).printRequest();
	this->buffer.printBuffer();
	return oldRequest;
}