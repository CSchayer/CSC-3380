// CD_Data.h

#ifndef CD_DATA_H
#define CD_DATA_H

#include <iostream>
#include <fstream>
using namespace std;

// Size of list array
const int SIZE = 20;

struct data {
	int ID;
	int category;
	int release_year;
	double selling_price;
	int inventory_count;
	string artist_name;
	string title;
	double inventory_value;
};


class CD_Data {
public:
	CD_Data();
	void insert(ifstream &stream);
	void insert(data data_entry);
	void delete_item(int index);
	void display(ofstream &outFile);
	void display(ofstream &outFile, int index);
	double get_inventory_value(int index);
	void get_total_inventory_value(ofstream &outFile);
	int get_cut_off_date();
	void sort_by_ID();
	void scan_for_removal(ofstream &outFile, int cut_off_date);

private:
	data list[SIZE];
};

#endif
