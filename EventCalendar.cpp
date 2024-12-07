#include "EventCalendar.h"

EventCalendar::EventCalendar(int producersCount_, int consumersCount_, int maxRequestsCount_)
{
    this->producersCount = producersCount_;
	this->consumersCount = consumersCount_;
    this->maxRequestsCount = maxRequestsCount_;
    // Кол-во строк календаря = кол-во источников и приборов + строка для обозначения конца моделирования 
	this->arrayRows = this->producersCount + this->consumersCount + 1;

	calendarArray = new double* [arrayRows]{};
	for (int i = 0; i < arrayRows; ++i) {
		calendarArray[i] = new double[2] {0.0};
	}
}


EventCalendar::~EventCalendar() 
{    
    for (int i = 0; i < arrayRows; ++i) {
        delete[] calendarArray[i];
    }
    delete[] calendarArray;
}

void EventCalendar::updateCalendar(SpecialEvent event)
{
    if (event.type == 1) // Поступление заявки
    {
        int rowNumber = event.number - 1;
        if ((rowNumber >= 0) && (rowNumber < arrayRows))
        {
            calendarArray[rowNumber][0] = event.moment;
            calendarArray[rowNumber][1] = event.sign;
        }
        else
        {
            std::cerr << "Incorrect number of producer\n";
        }
    }
    else if (event.type == 2) // Освобождение прибора
    {
        int rowNumber = event.number - 1 + producersCount;
        if ((rowNumber >= 0) && (rowNumber < arrayRows))
        {
            calendarArray[rowNumber][0] = event.moment;
            calendarArray[rowNumber][1] = event.sign;
        }
        else
        {
            std::cerr << "Incorrect number of consumer\n";
        }
    }
    else if (event.type == 3) // Конец моделирования
    {
        calendarArray[arrayRows-1][0] = event.moment;
        calendarArray[arrayRows-1][1] = event.sign;
        printCalendar();
    }
    else
    {
        std::cerr << "Incorrect type of event\n";
        return;
    }
}

void EventCalendar::printCalendar()
{
    std::cout << "\n";
    std::cout << "  Событие   |    Время    |   Признак  \n";
    std::cout << "---------------------------------------\n";
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < arrayRows; ++i) {
        if (i + 1 <= this->producersCount)
        {
            std::cout << std::fixed << std::setprecision(3) << "     И" << i + 1 << "     |    " 
                << this->calendarArray[i][0] << "    |      "
                << std::fixed << std::setprecision(0) << this->calendarArray[i][1] << "\n";
        }
        else if (i + 1 > this->producersCount && i + 1 - this->producersCount <= this->consumersCount)
        {
            std::cout << std::fixed << std::setprecision(3) << "     П" << i - producersCount + 1 
                << "     |    " << this->calendarArray[i][0] << "    |      " 
                << std::fixed << std::setprecision(0) << this->calendarArray[i][1] << "\n";
        }
        else if (i == arrayRows-1)
        {
            std::cout << " Конец мод. |    " << this->calendarArray[i][0] << "     |      " 
                << this->calendarArray[i][1] << "\n\n";
        }
    }
}

SpecialEvent EventCalendar::chooseEvent() {
    SpecialEvent minEvent(0, 0, DBL_MAX, 0); // Искомое событие
    double minTime = DBL_MAX;
    int type = 0; 
    bool sign = 0; 
    double moment = 0;
    int number = 0;

    for (int i = 0; i < this->arrayRows; i++) {

        // Получаем i-ое событие из календаря
        if (i < producersCount) { type = 1; number = i + 1; sign = calendarArray[i][1]; moment = calendarArray[i][0]; }
        else { type = 2; number = i + 1 - producersCount; sign = calendarArray[i][1]; moment = calendarArray[i][0]; }
        if (i + 1 == arrayRows) { type = 3; number = arrayRows; sign = calendarArray[i][1]; moment = calendarArray[i][0]; }

        SpecialEvent event(type, sign, moment, number);

        // Ищем событие с минимальным временем при признаке 0
        if (event.sign == 0) {
            if (event.moment < minEvent.moment) {
                minEvent = event;
            }
        }
    }
    return minEvent;
}

