#include "ProductionManager.h"
#include <limits>

ProductionManager::ProductionManager(Buffer& buffer_) {
	//Buffer buffer_(bufferSize);
	this->buffer = buffer_;
}

// ������� ���������� ������ � �����, ���������� ������

void ProductionManager::addRequest(Request *request) {
	// ���� ��� ����� � ������ ���������
	if (this->buffer.current_requests_count == this->buffer.size)
	{
		// ����� ����� ������ ������ � ������
		double minTime = DBL_MAX; // ��������� �������� �������, � ������� ����������
		int indexOld = 0;         // ���������� ��� ������� ����� ������ ������
		for (int i = 0; i < this->buffer.size; i++) {
			if (this->buffer.bufVect[i].buffer_receipt_time <= minTime) {
				indexOld = i;
			}
		}

		// �������� ����� ������ ������ �� ������
		// � ������� ����� �� � �����
		this->buffer.bufVect[indexOld] = (*request);
		(*request).buffer_receipt_time = (*request).generation_time;
	}
	// ���� � ������ ���� ��������� �����
	else
	{
		this->buffer.current_requests_count++; // ����������� ���������� ������� ������
		int indexNew = 0;
		// ���� ������ ����� ��� ������� ����� ������
		for (int i = 0; i < this->buffer.bufVect.size(); i++) {
			if (this->buffer.bufVect[i].producer_number == 0) {
				indexNew = i;
				break;
			}
		}
		this->buffer.bufVect[indexNew] = (*request); // ��������� ����� ������ �� ������ �����
		(*request).buffer_receipt_time = (*request).generation_time;
	}
	(*request).printRequest();
	this->buffer.printBuffer();
}

// ���������� ����� ������, ���� � ������ ���� ��������� �����
bool ProductionManager::addNewRequest(Request *request) {
	// ���� ���� �����
	if (this->buffer.current_requests_count < this->buffer.size) {
		this->buffer.current_requests_count++; // ����������� ���������� ������� ������
		int indexNew = 0;
		// ���� ������ ����� ��� ������� ����� ������
		for (int i = 0; i < this->buffer.bufVect.size(); i++) {
			if (this->buffer.bufVect[i].producer_number == 0) {
				indexNew = i;
				break;
			}
		}
		(*request).buffer_receipt_time = (*request).generation_time;
		this->buffer.bufVect[indexNew] = (*request); // ��������� ����� ������ �� ������ �����
		std::cout << "\nRequest " << (*request).producer_number << "." << (*request).package_number
			<< " was put in buffer\n";
		(*request).printRequest();
		this->buffer.printBuffer();
		return 0;
	}
	else { // ���� ��� ����
		return 1;
	}
}

// ����� ������ ������ � ���������� ����� �� ��������� �����
Request ProductionManager::rejOldaddNewRequest(Request *newRequest) {
	
	// ����� ����� ������ ������ � ������
	double minTime = DBL_MAX; // ��������� �������� �������, � ������� ����������
	Request oldRequest(0, 0);
	int indexOld = 0;      // ���������� ��� ������� ����� ������ ������
	for (int i = 0; i < this->buffer.bufVect.size(); i++) {
		if (this->buffer.bufVect[i].buffer_receipt_time <= minTime) {
			oldRequest = this->buffer.bufVect[i];
			indexOld = i;
			minTime = this->buffer.bufVect[i].buffer_receipt_time;
		}
	}
	// �������� ����� ������ ������ �� ������
	// � ������� ����� �� � �����
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