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

	bool addNewRequest(Request *request); // ���������� ����� ������, ���� � ������ ���� ��������� �����
	                                     // ���� �� ���, ���������� 1
	Request rejOldaddNewRequest(Request *request); // ����� ������ ������ � ���������� ����� �� ��������� �����

//private:
	Buffer buffer;



};

#endif //PRODUCTION_MANAGER_H