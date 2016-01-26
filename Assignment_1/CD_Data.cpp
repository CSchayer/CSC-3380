#include "CD_Data.h"
#include <string>
#include <iomanip>
using namespace std;


// Constructor
CD_Data::CD_Data()
{
	for (int i = 0; i < SIZE; i++)
	{
		list[i].ID = -1;
		list[i].category = -1;
		list[i].release_year = -1;
		list[i].selling_price = -1;
		list[i].inventory_count = -1;
		list[i].artist_name = "N/A";
		list[i].title = "N/A";
		list[i].inventory_value = -1;
	}
}



// Insert method that fills the list from an input file
void CD_Data::insert(ifstream &stream)
{
	for (int i = 0; i < SIZE; i++)
	{
		stream >> list[i].ID;
		stream >> list[i].category;
		stream >> list[i].release_year;
		stream >> list[i].selling_price;
		stream >> list[i].inventory_count;
		stream.ignore();
		getline(stream, list[i].artist_name);
		getline(stream, list[i].title);
		list[i].inventory_value = get_inventory_value(i);
	}

	stream.close();
}



// Insert method inserts a single record into the list (not currently used in this program)
void CD_Data::insert(data data_entry)
{
	int null_index = SIZE + 1;
		
	// If the list contains a null entry, find the index
	for (int i = 0; i < SIZE; i++)
	{
		if (list[i].ID == -1)
		{
			null_index = i;
			break;
		}
	}

	// If there is a null entry, add the new entry, else notify user that the list is full
	if (null_index < SIZE)
	{
		list[null_index].ID = data_entry.ID;
		list[null_index].category = data_entry.category;
		list[null_index].release_year = data_entry.release_year;
		list[null_index].selling_price = data_entry.selling_price;
		list[null_index].inventory_count = data_entry.inventory_count;
		list[null_index].artist_name = data_entry.artist_name;
		list[null_index].title = data_entry.title;
		list[null_index].inventory_value = get_inventory_value(null_index);
	}
	else
	{
		cout << "Error: New entry cannot be added. The list is full.\n";
	}
}



// Scan method traverses the list and deletes items on or before the specified cut off date
void CD_Data::scan_for_removal(ofstream &outFile, int cut_off_date)
{
	outFile << "\n----------------------------------------------------------------------------------------------------------------------------";
	outFile << "\nITEMS TO BE REMOVED\n";
	double inventory_value = 0;

	for (int i = 0; i < SIZE; i++)
	{
		if (list[i].release_year <= cut_off_date && list[i].ID != -1)
		{
			display(outFile, i);
			inventory_value += list[i].inventory_value;
			delete_item(i);
		}
	}

	outFile << "----------------------------------------\n";
	outFile << "TOTAL VALUE OF REMOVED ITEMS: $" << fixed << setprecision(2) << inventory_value;
	outFile << "\n----------------------------------------";
}



// Deletes a list item at a given index by resetting it to the default value
void CD_Data::delete_item(int index)
{
	list[index].ID = -1;
	list[index].category = -1;
	list[index].release_year = -1;
	list[index].selling_price = -1;
	list[index].inventory_count = -1;
	list[index].artist_name = "N/A";
	list[index].title = "N/A";
	list[index].inventory_value = -1;
}



// Sorts list by ID in ascending order and places null entries at the bottom of the list
void CD_Data::sort_by_ID()
{
	bool swap = true;
	int i = 0;
	int temp_ID;
	int temp_category;
	int temp_release_year;
	double temp_selling_price;
	int temp_inventory_count;
	string temp_artist_name;
	string temp_title;
	double temp_inventory_value;

	// Bubble Sort
	while (swap)
	{
		swap = false;
		i++;
		for (int j = 0; j < SIZE - i; j++)
		{
			if (list[j].ID > list[j + 1].ID)
			{
				temp_ID = list[j].ID;
				temp_category = list[j].category;
				temp_release_year = list[j].release_year;
				temp_selling_price = list[j].selling_price;
				temp_inventory_count = list[j].inventory_count;
				temp_artist_name = list[j].artist_name;
				temp_title = list[j].title;
				temp_inventory_value = list[j].inventory_value;


				list[j].ID = list[j + 1].ID;
				list[j].category = list[j + 1].category;
				list[j].release_year = list[j + 1].release_year;
				list[j].selling_price = list[j + 1].selling_price;
				list[j].inventory_count = list[j + 1].inventory_count;
				list[j].artist_name = list[j + 1].artist_name;
				list[j].title = list[j + 1].title;
				list[j].inventory_value = list[j + 1].inventory_value;


				list[j + 1].ID = temp_ID;
				list[j + 1].category = temp_category;
				list[j + 1].release_year = temp_release_year;
				list[j + 1].selling_price = temp_selling_price;
				list[j + 1].inventory_count = temp_inventory_count;
				list[j + 1].artist_name = temp_artist_name;
				list[j + 1].title = temp_title;
				list[j + 1].inventory_value = temp_inventory_value;


				swap = true;
			}
		}
	}

	// After the bubble sort, all of the null entries (ID = -1) are at the top of the list.
	// We need to move all non-null entries to the top of the list.

	int count = 0;
	// Count non-null entries
	for (int i = 0; i < SIZE; i++)
	{
		if (list[i].ID != -1)
			count++;
	}

	// Set index of first non-null entry
	int index = SIZE - count;
	int j = 0;
	// Take the non-null entries from the bottom and swap them with the null entries at the top of the list
	for (index; index < SIZE; index++)
	{
		temp_ID = list[index].ID;
		temp_category = list[index].category;
		temp_release_year = list[index].release_year;
		temp_selling_price = list[index].selling_price;
		temp_inventory_count = list[index].inventory_count;
		temp_artist_name = list[index].artist_name;
		temp_title = list[index].title;
		temp_inventory_value = list[index].inventory_value;

		list[index].ID = list[j].ID;
		list[index].category = list[j].category;
		list[index].release_year = list[j].release_year;
		list[index].selling_price = list[j].selling_price;
		list[index].inventory_count = list[j].inventory_count;
		list[index].artist_name = list[j].artist_name;
		list[index].title = list[j].title;
		list[index].inventory_value = list[j].inventory_value;

		list[j].ID = temp_ID;
		list[j].category = temp_category;
		list[j].release_year = temp_release_year;
		list[j].selling_price = temp_selling_price;
		list[j].inventory_count = temp_inventory_count;
		list[j].artist_name = temp_artist_name;
		list[j].title = temp_title;
		list[j].inventory_value = temp_inventory_value;

		j++;
	}
}



// Display all items in the list excluding the null values (ID = -1)
void CD_Data::display(ofstream &outFile)
{
	// Sort the list by ID in ascending order
	sort_by_ID();

	// Column headings
	outFile << "\n----------------------------------------------------------------------------------------------------------------------------\n";
	outFile << left << setw(5) << "ID";
	outFile << setw(10) << "CATEGORY";
	outFile << setw(6) << "RELEASE YEAR";
	outFile << right << setw(10) << "PRICE\t";
	outFile << setw(10) << "INVENTORY\t";
	outFile << left << setw(26) << "ARTIST NAME";
	outFile << setw(26) << "ALBUM TITLE";
	outFile << "INVENTORY VALUE\n";
	for (int i = 0; i < SIZE; i++)
	{
		// Display all non-null entries
		if (list[i].ID != -1)
		{
			outFile << left << setw(7) << list[i].ID << " ";
			outFile << setw(10) << list[i].category << " ";
			outFile << setw(6) << list[i].release_year << " ";
			outFile << right << fixed << showpoint << setprecision(2) << setw(10) << list[i].selling_price << " ";
			outFile << setw(10) << list[i].inventory_count << "\t\t";
			outFile << left << setw(25) << list[i].artist_name << " ";
			outFile << setw(25) << list[i].title << " ";
			outFile << list[i].inventory_value << "\n";
		}
	}
}


// Overloaded display method that displays a single record when given a specific index location
void CD_Data::display(ofstream &outFile, int index)
{
	outFile << left << setw(7) << list[index].ID << " ";
	outFile << setw(10) << list[index].category << " ";
	outFile << setw(6) << list[index].release_year << " ";
	outFile << right << fixed << showpoint << setprecision(2) << setw(10) << list[index].selling_price << " ";
	outFile << setw(10) << list[index].inventory_count << "\t\t";
	outFile << left << setw(25) << list[index].artist_name << " ";
	outFile << setw(25) << list[index].title << " ";
	outFile << list[index].inventory_value << "\n";
}



// Method to calculate inventory value of a single item in the list
double CD_Data::get_inventory_value(int index)
{
	return list[index].inventory_count * list[index].selling_price;
}


// Calculates total inventory value and prints to the outfile
void CD_Data::get_total_inventory_value(ofstream &outFile)
{
	double total_value = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (list[i].ID != -1){
			total_value += get_inventory_value(i);
		}	
	}

	outFile << "---------------------------------\n";
	outFile << "TOTAL INVENTORY VALUE: $" << fixed << setprecision(2) << total_value;
	outFile << "\n---------------------------------";
}



// Requests a cut-off year from the user via command line
int CD_Data::get_cut_off_date()
{
	int cut_off_date;

	cout << "Please enter a cut-off year in the range from 2006 to 2016: ";
	cin >> cut_off_date;

	// Input validation
	while (cut_off_date < 2006 || cut_off_date > 2016)
	{
		cout << "Invalid entry. Please enter a cut-off year in the range from 2006 to 2016: ";
		cin >> cut_off_date;
	}

	return cut_off_date;
}
