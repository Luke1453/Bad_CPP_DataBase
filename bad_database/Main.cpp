#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <string>
#include <conio.h>// todo can i get this with out _getch()?
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Entry.h"

using namespace std;

void setup();
void add_db_entry();
void view_database();

int main() {

	while (true) {

		system("cls");

		char choice;

		setup();

		choice = _getch();

		switch (choice) {

		case 27:
			exit(0);

		case 65:
		case 97:
			system("cls");
			add_db_entry();
			break;

		case 81:
		case 113:
			system("cls");
			view_database();
			break;

		default:
			system("cls");
			setup();
			break;
		}

	}

	system("pause");
	return 0;
}

//functions---------------------------------------------------------------------------

void setup() {

	cout << "Bad Car Wash Database.\n\n";
	cout << "(A) Add an entry.\n";
	cout << "(Q) View Data base\n";
	cout << "(ESC) Exit.\n";
}

void add_db_entry() {

	string customer_name;
	//time_t service_time;
	int price;
	int tip;
	string car_id;

	cout << "Adding entry to Car Wash DataBase...\n\n";
	cout << "Client Name: ";
	cin >> customer_name;
	cout << "Client's Car ID: ";
	cin >> car_id;
	cout << "Price paid: ";
	cin >> price;
	cout << "Tip (0 if none): ";
	cin >> tip;
	cout << endl;

	Entry* entry;
	entry = new Entry(customer_name, price, tip, car_id);

	cout << "Chose service time:\n" <<
		"(Q) Exterior wash.\n" <<
		"(A) Interior wash.\n" <<
		"(Z) Waxing.\n";

	while (true)
	{
		char choice = _getch();

		switch (choice) {

		case 90:	//Z || z
		case 122:
			entry->service_type = Entry::Waxing;
			cout << 'z';
			break;

		case 65:	//A || a
		case 97:
			entry->service_type = Entry::Interior_wash;
			cout << 'a';
			break;

		case 81:	//Q || q
		case 113:
			entry->service_type = Entry::Exterior_wash;
			cout << 'q';
			break;

		default:
			continue;
		}
		break;
	}

	ofstream output("DataBase.json", ofstream::app);
	json file;
	file = json{ { "name",entry->customer_name },{ "time",entry->service_time },{ "service type",entry->service_type },{ "price",entry->price },{ "tip",entry->tip },{ "car id",entry->car_id } };
	output << file << endl;

}
//i need to do it with map (college requrements)
void view_database() {

	ifstream input("DataBase.json", ifstream::in);
	json database;
	map<int, Entry> entry_map;


	unsigned int nr_of_lines=0;
	for (string line; getline(input, line);) {
		nr_of_lines++;
	}

	input.clear();
	input.seekg(0, ios::beg);

	for (int i = 1; i <= nr_of_lines; i++) {
		input >> database;
		
		Entry entry_tomap(database.at("name"), database.at("price"), database.at("tip"), database.at("car id"));
		entry_tomap.service_time = database.at("time");
		entry_tomap.service_type = database.at("service type");

		entry_map.insert(pair<time_t, Entry>(entry_tomap.service_time, entry_tomap));
	}
	//todo sorting by info / view / search by keyword?? change this shit to search to car id

	cout << "Choose the action: \n\n";
	cout << "(W) View Entries sorted by time. (ascending)\n";
	cout << "(X) View Entries sorted by time. (descending)\n";
	cout << "(S) Search by date.\n";


	char choice;
	choice = _getch();

	switch (choice) {

	case 87:		//W
	case 119:
		system("cls");
		////////////////////////////////////////////////////////////////////////////////////////////
		cout << "Viewing Car Wash DataBase Entries...(sorted by time, ascending)\n\n";

		for (const auto& entry : entry_map) {

#pragma warning(disable:4996)
			cout << "Entry Time: " << asctime(localtime(&entry.second.service_time));// << endl;
			cout << "Customer name: " << entry.second.customer_name << endl;
			cout << "Price payed: " << entry.second.price << "  Tip: " << entry.second.tip << endl;
			cout << "Customer car ID: " << entry.second.car_id << endl;

			if (entry.second.service_type == 0) {
				cout << "Service type: Interior_wash\n\n";
			}
			else if (entry.second.service_type == 1) {
				cout << "Service type: Waxing\n\n";
			}
			else if (entry.second.service_type == 2) {
				cout << "Service type: Exterior_wash\n\n";
			}
			else {
				cout << "Service type: IDK ERROR I GUESS\n\n";
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////
		system("pause");
		break;

	case 88:
	case 120:		//X
		system("cls");
		////////////////////////////////////////////////////////////////////////////////////////////
		cout << "Viewing Car Wash DataBase Entries...(sorted by time, descending)\n\n";

		for (auto it = entry_map.rbegin(); it != entry_map.rend(); ++it) {

#pragma warning(disable:4996)
			cout << "Entry Time: " << asctime(localtime(&it->second.service_time));// << endl;
			cout << "Customer name: " << it->second.customer_name << endl;
			cout << "Price payed: " << it->second.price << "  Tip: " << it->second.tip << endl;
			cout << "Customer car ID: " << it->second.car_id << endl;

			if (it->second.service_type == 0) {
				cout << "Service type: Interior_wash\n\n";
			}
			else if (it->second.service_type == 1) {
				cout << "Service type: Waxing\n\n";
			}
			else if (it->second.service_type == 2) {
				cout << "Service type: Exterior_wash\n\n";
			}
			else {
				cout << "Service type: IDK ERROR I GUESS\n\n";
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////
		system("pause");
		break;

	case 83:
	case 115:		//S
		system("cls");
		////////////////////////////////////////////////////////////////////////////////////////////
		int search_year, search_month, search_day;

		cout << "Searching Car Wash DataBase Entries...\n\n";
		cout << "Year: ";
		cin >> search_year;
		cout << "Month: ";
		cin >> search_month;
		cout << "Day: ";
		cin >> search_day;
		cout << endl << endl;

		time_t search_q;
		time(&search_q);
		struct tm search_time_info;
		search_time_info = *localtime(&search_q);

		search_time_info.tm_year = search_year - 1900;
		search_time_info.tm_mon = search_month - 1;
		search_time_info.tm_mday = search_day;
		search_q = mktime(&search_time_info);

		for (const auto& entry : entry_map) {

			if (search_q >= entry.second.service_time && search_q <= entry.second.service_time+ 86400)
			{
#pragma warning(disable:4996)
				cout << "Entry Time: " << asctime(localtime(&entry.second.service_time));// << endl;
				cout << "Customer name: " << entry.second.customer_name << endl;
				cout << "Price payed: " << entry.second.price << "  Tip: " << entry.second.tip << endl;
				cout << "Customer car ID: " << entry.second.car_id << endl;

				if (entry.second.service_type == 0) {
					cout << "Service type: Interior_wash\n\n";
				}
				else if (entry.second.service_type == 1) {
					cout << "Service type: Waxing\n\n";
				}
				else if (entry.second.service_type == 2) {
					cout << "Service type: Exterior_wash\n\n";
				}
				else {
					cout << "Service type: IDK ERROR I GUESS\n\n";
				}
			}
		}


		////////////////////////////////////////////////////////////////////////////////////////////
		system("pause");
		break;

	default:
		system("cls");
		view_database();
		break;
	}
}