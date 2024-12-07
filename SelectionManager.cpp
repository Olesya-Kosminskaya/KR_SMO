#include "SelectionManager.h"
#include <limits>

SelectionManager::SelectionManager(Buffer& buffer_, std::vector<Consumer>& consumers_) {
	this->buffer = buffer_;
	this->consumers = consumers_;
}

// ����� ������
// ��������� �� ������ ���������
Request SelectionManager::selectRequest() {
	Request retRequest(0, 0); // ������������ ������
	if (this->buffer.current_requests_count == 0)
	{
		// ���� � ������ ��� ������
		retRequest.producer_number = -1;  // ���������� ��������, ������������ ���������� ������
		retRequest.generation_time = -1;
	}
	else {
		int selectIndex = 0;                  // ������ ���������� ������
		retRequest.producer_number = INT_MAX; // ���������� ������
		//Request request(INT_MAX, 0);  
		//int prNum = 0;             // ����� ���������
		Request cleanRequest(0, 0);           // ������ ��� �������� ����� ���������
		for (int i = 0; i < this->buffer.size; i++) { // ���������� ����� ���������
			if (this->buffer.bufVect[i].producer_number == 0) {
				continue;
			}
			// ���� ����� ��������� ����� ��, �� ����� � ������ ������, ��� ���� ����� ��������� ������
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
		this->buffer.bufVect[selectIndex] = cleanRequest; // ������ ����� ��������� ������ ������
		                                                  // ����� �������� � ������ �� ����������
		this->buffer.current_requests_count--;   // ��������� ������� ���������� ������ � ������
	}
	return retRequest; // ���������� ��������� ������ ��� �������� ����������
}


// ����� �������
// ���������� ���������� �� ������������: ����� ������� �� ������
int SelectionManager::selectConsumer() {
	int consIndex = 0;  // ������������ ������ �������
	for (int i = 0; i < this->consumers.size(); i++) {
		// ���������, �������� �� ��������� ������ � ������� ��������
		if (this->consumers[this->current_consumer_index].isFree) {
			consIndex = current_consumer_index;
			this->consumers[this->current_consumer_index].isFree = false;
			break;
		}
		if (i == this->consumers.size() - 1) {
			// ��� ��������� ��������
			consIndex = -1; // ���������� ��������, ������������ ���������� ��������� ��������
		}
		current_consumer_index++;   // �������� ������ �� ���� �����, ���� �� ����� ��������� ������ 
		// ���� ��� ��� ��������� ������
		if (current_consumer_index == this->consumers.size()) {
			current_consumer_index = 0; // ��������� �� ������
		}
	}
	
	//if (this->consumers[this->current_consumer_index].isFree)
	//{
	//	consIndex = current_consumer_index;
	//	// ���� ��� ��� ��������� ������
	//	if (current_consumer_index == this->consumers.size() - 1) {	
	//		current_consumer_index = 0; // ��������� �� ������
	//	}
	//	else {
	//		current_consumer_index++;   // ��� �������� ������ �� ���� �����
	//	}
	//}
	//else
	//{
	//	// ��� ��������� ��������
	//	consIndex = -1; // ���������� ��������, ������������ ���������� ��������� ��������
	//}
	return consIndex;
}