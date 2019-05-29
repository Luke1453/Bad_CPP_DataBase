#include "Entry.h"

Entry::Entry(std::string in_customer_name, int in_price, int in_tip, std::string in_car_id){
	
	this->car_id = in_car_id;
	this->customer_name = in_customer_name;
	this->tip = in_tip;
	this->price = in_price;
	this->service_time = time(nullptr);

}

Entry::~Entry(){

}
