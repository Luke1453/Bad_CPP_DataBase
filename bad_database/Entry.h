#pragma once

#include <iostream>
#include <ctime>

class Entry{
public:
	std::string customer_name;
	time_t service_time;
	int price;
	int tip;
	std::string car_id;

	enum service {
		Interior_wash,
		Waxing,
		Exterior_wash
	}service_type;

	Entry(std::string in_customer_name, int in_price, int in_tip, std::string in_car_id);
	virtual ~Entry();
};