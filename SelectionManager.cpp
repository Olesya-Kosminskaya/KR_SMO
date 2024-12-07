#include "SelectionManager.h"
#include <limits>

SelectionManager::SelectionManager(Buffer& buffer_, std::vector<Consumer>& consumers_) {
	this->buffer = buffer_;
	this->consumers = consumers_;
}

// Выбор заявки
// Приоритет по номеру источника
Request SelectionManager::selectRequest() {
	Request retRequest(0, 0); // Возвращаемая заявка
	if (this->buffer.current_requests_count == 0)
	{
		// Если в буфере нет заявок
		retRequest.producer_number = -1;  // Возвращаем значение, обозначающее отсутствие заявок
		retRequest.generation_time = -1;
	}
	else {
		int selectIndex = 0;                  // Индекс выбираемой заявки
		retRequest.producer_number = INT_MAX; // Выбираемая заявка
		//Request request(INT_MAX, 0);  
		//int prNum = 0;             // Номер источника
		Request cleanRequest(0, 0);           // Заявка для очищения места выбранной
		for (int i = 0; i < this->buffer.size; i++) { // Сравниваем номер источника
			if (this->buffer.bufVect[i].producer_number == 0) {
				continue;
			}
			// Если номер источника такой же, но номер в пакете меньше, или если номер источника меньше
			else if ((this->buffer.bufVect[i].producer_number == retRequest.producer_number
				&& this->buffer.bufVect[i].package_number < retRequest.package_number)
				|| (this->buffer.bufVect[i].producer_number < retRequest.producer_number))
			{
				retRequest = this->buffer.bufVect[i];
				selectIndex = i;
			}
			/*if (this->buffer.bufVect[i].producer_number < retRequest.producer_number)
			{
				retRequest = this->buffer.bufVect[i];
				selectIndex = i;
			}*/
		}	
		this->buffer.bufVect[selectIndex] = cleanRequest; // Делаем место выбранной заявки пустым
		                                                  // Чтобы элементы в буфере не сдвигались
		this->buffer.current_requests_count--;   // Уменьшаем текущее количество заявок в буфере
	}
	return retRequest; // Возвращаем выбранную заявку или значение отсутствия
}


// Выбор прибора
// Дисциплины постановки на обслуживание: выбор прибора по кольцу
int SelectionManager::selectConsumer() {
	int consIndex = 0;  // Возвращаемый индекс прибора
	for (int i = 0; i < this->consumers.size(); i++) {
		// Проверяем, является ли свободным прибор с текущим индексом
		if (this->consumers[this->current_consumer_index].isFree) {
			consIndex = current_consumer_index;
			this->consumers[this->current_consumer_index].isFree = false;
			break;
		}
		if (i == this->consumers.size() - 1) {
			// Нет свободных приборов
			consIndex = -1; // Возвращаем значение, обозначающее отсутствие свободных приборов
		}
		current_consumer_index++;   // Сдвигаем индекс на один вперёд, пока не найдём свободный прибор 
		// Если это был последний прибор
		if (current_consumer_index == this->consumers.size()) {
			current_consumer_index = 0; // Переходим на первый
		}
	}
	
	//if (this->consumers[this->current_consumer_index].isFree)
	//{
	//	consIndex = current_consumer_index;
	//	// Если это был последний прибор
	//	if (current_consumer_index == this->consumers.size() - 1) {	
	//		current_consumer_index = 0; // Переходим на первый
	//	}
	//	else {
	//		current_consumer_index++;   // Или сдвигаем индекс на один вперёд
	//	}
	//}
	//else
	//{
	//	// Нет свободных приборов
	//	consIndex = -1; // Возвращаем значение, обозначающее отсутствие свободных приборов
	//}
	return consIndex;
}