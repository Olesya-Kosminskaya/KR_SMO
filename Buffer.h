#include <iostream>
#include <list>

#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <vector>
#include "Request.h"

class Buffer
{
public:
	int size = 0;  // ������
	int current_requests_count = 0; // ������� ���-�� ������
	std::vector<Request> bufVect;

	Buffer() {};// 
	Buffer(int size_);
	void printBuffer();

};

#endif //BUFFER_H