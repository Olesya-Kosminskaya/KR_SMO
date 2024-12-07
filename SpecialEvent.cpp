#include "SpecialEvent.h"

SpecialEvent::SpecialEvent(int type_, bool sign_, double moment_, int number_) {
	this->type = type_;
	this->sign = sign_;
	this->moment = moment_;
	this->number = number_;
}
