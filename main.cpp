#include "Request.h"
#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"
#include "SelectionManager.h"
#include "ProductionManager.h"
#include "EventCalendar.h"
#include "SpecialEvent.h"


// class Model
//Fields
int maxRequestsCount = 10;     // ���-�� ������, �������� ����� �������
int currentRequestsCount = 0;  // ������� ���-�� ������

int PRODUCERS_COUNT = 2;       // ���-�� ����������
int CONSUMERS_COUNT = 2;       // ���-�� ��������
int BUFFER_SIZE = 2;           // ���-�� ���� � ������

double startTime = 0;          // ����� ������ �������������
double endTime = 0;            // ����� ����� �������������

//Methods
// ���������� ���������
void fillCalendar(EventCalendar& calendar, std::vector<Producer>& producers, std::vector<Consumer>& consumers,
	std::vector<std::vector<Request>>& requests);

// ���1 - ��, ��� ����������, ���� ������ ������� - ����������� ������ 
void ifGenerateRequestEvent(SpecialEvent& minEvent, EventCalendar& calendar, std::vector<Producer>& producers, 
	std::vector<Consumer>& consumers, std::vector<std::vector<Request>>& requests,
	SelectionManager& selManager, ProductionManager& proManager);

// ���2 - ��, ��� ����������, ���� ������ ������� - ������������ �������
void ifConsumerReleasedEvent(SpecialEvent& minEvent, EventCalendar& calendar, ProductionManager& proManager,
	std::vector<Consumer>& consumers, std::vector<std::vector<Request>>& requests, SelectionManager& selManager);

// ����� �������� ��������� �������
void printCurrentSystemState(EventCalendar& calendar, std::vector<Producer>& producers);

// ����� ������� ������� �����������
void printSummaryTableOfResults(std::vector<Producer>& producers, std::vector<Consumer>& consumers,
	std::vector<std::vector<Request>>& requests, std::vector<double>& totalTime,
	std::vector<double>& processingTime, std::vector<double>& spentInBufferTime,
	std::vector<double>& dP, std::vector<double>& dB, std::vector<double>& usageCoefficient,
	std::vector<double>& rejected_requests_count);

int main() {
	setlocale(LC_ALL, "ru");
	
	std::string mode = "s"; // ��������� �����

	Buffer buffer(BUFFER_SIZE);
	EventCalendar calendar(PRODUCERS_COUNT, CONSUMERS_COUNT, maxRequestsCount);

	std::vector<Producer> producers;
	std::vector<Consumer> consumers;
	std::vector<std::vector<Request>> requests;
	
	fillCalendar(calendar, producers, consumers, requests);

	ProductionManager proManager(buffer);
	SelectionManager selManager(buffer, consumers);

	//����: �������� ������ ������� �� ���������
	SpecialEvent minEvent = calendar.chooseEvent();
	
	if (mode == "s") {
		std::cin >> mode;
		calendar.printCalendar();
		printCurrentSystemState(calendar, producers);
		buffer.printBuffer();
	}

	while (minEvent.type != 3) {
		//���
		if (minEvent.type == 1) {
			//���1
			ifGenerateRequestEvent(minEvent, calendar, producers, consumers, requests, selManager, proManager);
		}

		if (minEvent.type == 2) {
			//���2
			ifConsumerReleasedEvent(minEvent, calendar, proManager, consumers, requests, selManager);
		}

		if (mode == "s") {
			std::cin >> mode;
			//calendar.printCalendar();
			printCurrentSystemState(calendar, producers);
			//buffer.printBuffer();
		}

		//����
		minEvent = calendar.chooseEvent();
	}

	//���3
		std::cout << "\n---END OF MODELING---\n\n";

	// ���� �������������� �����
	if (mode == "a") {
		std::vector<double> rejected_requests_count;
		for (Producer p : producers) {
			// ����������� ������ ������
			rejected_requests_count.push_back((double)p.rejected_requests_number / p.received_requests_number);
		}

		std::vector<double> totalTime;         // ����� �����
		std::vector<double> processingTime;    // ����� ���������
		std::vector<double> spentInBufferTime; // ����� ���������� � ������

		for (int i = 0; i < producers.size(); i++) {
			double t1 = 0; // ����� ���������
			double t2 = 0;
			for (Request request : requests[i]) {
				// ����� ��������
				if (request.processed_time != 0) {
					t1 += request.processed_time - request.processing_starts_time;
				} 
				t2 += request.waiting_buffer_time;
				
			}
			processingTime.push_back(t1 / producers[i].received_requests_number);
			spentInBufferTime.push_back(t2 / producers[i].received_requests_number);
			totalTime.push_back(t1 / producers[i].received_requests_number +
				t2 / producers[i].received_requests_number);
		}

		// ���������

		std::vector<double> dP;
		std::vector<double> dB;

		for (int i = 0; i < producers.size(); i++) {
			double sqSumT1 = 0; // ����� ���������
			double sqSumT2 = 0; // ����� ��������

			for (Request request : requests[i]) {
				sqSumT1 += std::pow(((request.processed_time - request.processing_starts_time)
					- processingTime[i]), 2);
				if (request.buffer_receipt_time == 0) {
					sqSumT2 += std::pow(spentInBufferTime[i], 2);
				}
				else if (request.consumer_number != -1) {
					sqSumT2 += std::pow((request.waiting_buffer_time 
						- spentInBufferTime[i]), 2);
				}
			}
			dP.push_back(sqSumT1 / producers[i].received_requests_number);
			dB.push_back(sqSumT2 / producers[i].received_requests_number);
		}

		std::vector<double> usageCoefficient;
		for (int i = 0; i < consumers.size(); i++) {
			double t = 0; // ����� ���������
			for (int j = 0; j < producers.size(); j++) {
				for (Request request : requests[i]) {
					if (request.consumer_number == i) {
						t += request.processed_time - request.processing_starts_time;
					}
				}
			}
			usageCoefficient.push_back(t / (endTime - startTime));
		}
		printSummaryTableOfResults(producers, consumers, requests, totalTime, processingTime,
			spentInBufferTime, dP, dB, usageCoefficient, rejected_requests_count);
	}
}


void fillCalendar(EventCalendar& calendar, std::vector<Producer>& producers, std::vector<Consumer>& consumers,
	std::vector<std::vector<Request>>& requests) {
	for (int i = 1; i < calendar.producersCount+1; i++) {
		Producer pr(i);
		producers.push_back(pr);
		requests.push_back(std::vector<Request>());
		//  
		if (currentRequestsCount < /*calendar.*/maxRequestsCount) {
			// ���������� �� ����� ������ � ������� ��������� - ������������� ��������� ���������
			Request request = producers[i-1].generateRequest();
			request.package_number = 1; // �. �. ��� ������ ������ �� ���������
			currentRequestsCount++;        // ����������� ����� ���������� ������, ��������������� ��������
			std::cout << "Request " << currentRequestsCount << " was generated\n";
			request.printRequest();
			//producers[i - 1].received_requests_number++; // ����������� ���������� ������ �� ������� ���������

			double time_ = request.generation_time;
			request.package_number = 1;
			SpecialEvent p_event(1, 0, time_, i);
			calendar.updateCalendar(p_event);
			requests[i-1].push_back(request);
		}
		else {
			SpecialEvent p_event(1, 1, 0, i);
			calendar.updateCalendar(p_event);
		}
		calendar.printCalendar();
	}
	
	for (int i = 1; i < calendar.consumersCount+1; i++) {
		Consumer cons(i, 10, 50);
		consumers.push_back(cons);
		SpecialEvent c_event(2, 1, 0, i);
		calendar.updateCalendar(c_event);
		calendar.printCalendar();
	}
	SpecialEvent end_event(3, 0, 100, calendar.arrayRows);
	calendar.updateCalendar(end_event);
	calendar.printCalendar();
}

// ���1 - ��, ��� ����������, ���� ������ ������� - ����������� ������ 
void ifGenerateRequestEvent(SpecialEvent& minEvent, EventCalendar& calendar, std::vector<Producer>& producers,
	std::vector<Consumer>& consumers, std::vector<std::vector<Request>>& requests,
	SelectionManager& selManager, ProductionManager& proManager) {
	int minEventIndex = 0;
	if (minEvent.type == 1) { minEventIndex = minEvent.number - 1; }
	else if (minEvent.type == 2) { minEventIndex = minEvent.number - 1 + calendar.producersCount; }
	else { minEventIndex = calendar.arrayRows - 1; }
	
	Request requestToProcess = requests[minEventIndex][(requests[minEventIndex].size() - 1)];

	int consIndex = selManager.selectConsumer();
	if (consIndex == -1) { // ���� ��� ��������� ��������
		// ���� ���� ��������� ����� � ������ - ���������  
		if (proManager.addNewRequest(&requestToProcess)) { // ���� ��� ��������� ���� � ������
			// ����� ���� ����� ������ � ���������� ������
			Request rejectedRequest = proManager.rejOldaddNewRequest(&requestToProcess);
			// ����������� ���������� ������, ���������� �����, � ������� ���������
			producers[rejectedRequest.producer_number - 1].rejected_requests_number++;
			rejectedRequest.consumer_number = -1;
			// ���������� ������������ ������ �������
			requests[rejectedRequest.producer_number - 1][rejectedRequest.package_number - 1] = rejectedRequest;
		}
		selManager.buffer = proManager.buffer; // ��������� �������� � ������
	}
	else { // ���� ����� ��������� ������
		// ������ �������� ��������������
		requestToProcess.processing_starts_time = minEvent.moment;
		consumers[consIndex].isFree = false;
		consumers[consIndex].process(&requestToProcess);
		// ������ ����� ����� ���������� �������
		calendar.calendarArray[calendar.producersCount + consumers[consIndex].number - 1][0] =
			requestToProcess.processing_starts_time + consumers[consIndex].request_processing_time;
		calendar.calendarArray[calendar.producersCount + consumers[consIndex].number - 1][1] = 0;
		endTime = requestToProcess.processed_time;
	}

	// ���������� ������������ ������ �������
	requests[minEventIndex][(requests[minEventIndex].size() - 1)] = requestToProcess;

	// ���� ��� �� ����� �� ������������� ���������� ������, ���������� ����� �� �������� ���������
	if (currentRequestsCount < maxRequestsCount) {
		Request request = producers[minEventIndex].generateRequest();
		request.package_number = requests[minEventIndex].size() + 1;
		currentRequestsCount++;
		calendar.calendarArray[minEventIndex][0] = request.generation_time;
		requests[minEventIndex].push_back(request);
		std::cout << "Request " << currentRequestsCount << " was generated\n";
		request.printRequest();
	}
	else {
		if (requests[minEventIndex].back().consumer_number != 0 ||
			requests[minEventIndex].back().buffer_receipt_time != 0) {
			calendar.calendarArray[minEventIndex][0] = 0;
			calendar.calendarArray[minEventIndex][1] = 1;
		}
	}

}

// ���2 - ��, ��� ����������, ���� ������ ������� - ������������ �������
void ifConsumerReleasedEvent(SpecialEvent& minEvent, EventCalendar& calendar, ProductionManager& proManager,
	std::vector<Consumer>& consumers, std::vector<std::vector<Request>>& requests, SelectionManager& selManager) {
	//Consumer consumer = consumers[minEvent.number - 1];
	Request request = selManager.selectRequest();
	if (request.producer_number == -1) { // ���� ����� ����
		consumers[minEvent.number - 1].isFree = true; // ����� ������ � �������
		// � �� �� �����, ����� ��������� ��������� �������
		calendar.calendarArray[calendar.producersCount + minEvent.number - 1][1] = 1;
		calendar.calendarArray[calendar.producersCount + minEvent.number - 1][0] = 0;
	}
	else { // ���� �� ������ ������� ������� ������
		request.processing_starts_time = minEvent.moment;
		consumers[minEvent.number - 1].process(&request);   // ����� ��� ������������ �� ������ ��� ���������
		//request.consumer_number = consumers[minEvent.number - 1].number;
		// � �� �����, ����� ��������� ��������� �������
		calendar.calendarArray[calendar.producersCount + minEvent.number - 1][0] = request.processed_time;
		endTime = request.processed_time;
		// ���������� ��������� ������ �������
		requests[request.producer_number - 1][request.package_number - 1] = request;
		proManager.buffer = selManager.buffer; // ��������� �������� � ������
		proManager.buffer.printBuffer();
	}
}

void printCurrentSystemState(EventCalendar& calendar, std::vector<Producer>& producers) {
	std::cout << "\n";
	std::cout << "  �������   |    �����    |   �������  |  ����� ������ |  ����� �������  \n";
	std::cout << "------------------------------------------------------------------------\n";
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < calendar.arrayRows; ++i) {
		if (i + 1 <= calendar.producersCount)
		{
			std::cout << std::fixed << std::setprecision(3) << "     �" << i + 1 << "          " << calendar.calendarArray[i][0] << "           "
				<< std::fixed << std::setprecision(0) << calendar.calendarArray[i][1] 
				<< "              " << producers[i].received_requests_number
				<< "                " << producers[i].rejected_requests_number << "\n";
		}
		else if (i + 1 > calendar.producersCount && i + 1 - calendar.producersCount <= calendar.consumersCount)
		{
			std::cout << std::fixed << std::setprecision(3)  << "     �" << i - calendar.producersCount + 1 
				<< "          " << calendar.calendarArray[i][0] << std::fixed << std::setprecision(0)
				<< "           " << calendar.calendarArray[i][1] << "\n";
		}
		else if (i == calendar.arrayRows - 1)
		{
			std::cout << " ����� ���.      " << calendar.calendarArray[i][0] << "             " 
				<< calendar.calendarArray[i][1] << "\n\n";
		}
	}
}

void printSummaryTableOfResults(std::vector<Producer>& producers, std::vector<Consumer>& consumers,
	std::vector<std::vector<Request>>& requests, std::vector<double>& totalTime, 
	std::vector<double>& processingTime, std::vector<double>& spentInBufferTime,
	std::vector<double>& dP, std::vector<double>& dB, std::vector<double>& usageCoefficient,
	std::vector<double>& rejected_requests_count) {
	//std::cout << "�������������� ���������� ��\n";

	double sumPrej = 0;
	std::cout << "���  |  ���-�� ������   |   P���   |   T���   |   T����   |   T����   |   ���   |  ����� \n"
		<< "-----------------------------------------------------------------------------------------\n";
	for (int i = 0; i < producers.size(); i++) {
		std::cout << " " << i + 1 << "           " << producers[i].received_requests_number << "            "
			<< rejected_requests_count[i] << "       " << totalTime[i] << "      " << processingTime[i]
			<< "       " << spentInBufferTime[i] << "       " << dB[i] << "     " << dP[i] << "\n";
		sumPrej += rejected_requests_count[i];
	}
	
	std::cout << "\n������� ����������� ������: " << sumPrej / rejected_requests_count.size() << std::endl;
}
