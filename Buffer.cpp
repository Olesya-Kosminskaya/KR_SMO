#include "Buffer.h"

Buffer::Buffer(int size_) {
	this->size = size_;                              // Устанавливаем размер буфера
	// Создаём вектор нужного размера с нулевыми заявками
	this->bufVect.resize(this->size); 
	for (int i = 0; i < size; i++)
	{
		this->bufVect[i] = Request(0, 0);
	}
}

void Buffer::printBuffer() {
	std::cout << "\n-----BUFFER-----\n";
	std::cout << "  -----------\n";
	for (int i = 0; i < this->size; i++) {
		std::cout << "  |   " << this->bufVect[i].producer_number << "."
			<< this->bufVect[i].package_number << "   |" << std::endl;
		std::cout << "  -----------\n";
	}
	std::cout << "\n";
}
