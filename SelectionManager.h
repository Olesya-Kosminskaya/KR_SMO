#ifndef SELECTION_MANAGER_H
#define SELECTION_MANAGER_H

#include <vector>
#include "Request.h"
#include "Buffer.h"
#include "Consumer.h"

class SelectionManager
{
public:
	SelectionManager(Buffer& buffer, std::vector<Consumer>& consumers);
	Request selectRequest();
	int selectConsumer();
	
//private:
	Buffer buffer;                   // Буфер
	std::vector<Consumer> consumers; // Приборы
	int current_consumer_index = 0;  // "Указатель" - индекс текущего доступного прибора для выбора по кольцу 

};

#endif //SELECTION_MANAGER_H