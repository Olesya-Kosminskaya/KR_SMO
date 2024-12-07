#ifndef PRODUCTION_MANAGER_H
#define PRODUCTION_MANAGER_H

#include <iostream>
#include "Request.h"
#include "Buffer.h"

class ProductionManager
{
public:
	ProductionManager(Buffer& buffer_);
	void addRequest(Request *request);

	bool addNewRequest(Request *request); // Добавление новой заявки, если в буфере есть свободные места
	                                     // Если их нет, возвращает 1
	Request rejOldaddNewRequest(Request *request); // Отказ старой заявке и добавление новой на свободное место

//private:
	Buffer buffer;



};

#endif //PRODUCTION_MANAGER_H