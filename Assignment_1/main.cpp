
/********************************************/
/*    Groovy Music End-of-Year Inventory    */
/*	        James Singleton             */
/*            CSC 3380_97 Section 1         */
/*               Assignment 1               */
/* Instructor: Douglas  	            */
/* Program due date:  February 2, 2016      */
/********************************************/

/* PROBLEM SPECIFICATION: To create a functioning DVD inventory list that allows removal of outdated items.

   PROBLEM ANALYSIS: This program will take input from a data file containing the store DVD inventory.
   It will request a cut off date from the user via command line then remove all items at or below the cut off date.
   The program will display the original list, the items to be removed, and the updated list in a file named "Report.out".
	
   IMPLEMENTATION DIRECTIONS: The program consists of two cpp files named main.cpp and DVD_Data.cpp. 
   To compile the program, navigate to the directory prog1 and use the g++ compiler in the terminal.
   Execute the following commands via the terminal:
    - To compile the program: g++ -c DVD_Data.cpp
                              g++ -c main.cpp
                              g++ DVD_Data.o main.o -o prog1
    - To execute the program: ./prog1
	   
   The program takes input from an input file named "Music2015.data" and prints output to a file named "Report.out".
*/

#include "DVD_Data.h"
using namespace std;


int main()
{
	ifstream inFile;
	inFile.open("Music2015.data");
	ofstream outFile;
	outFile.open("Report.out");
	DVD_Data *inventory = new DVD_Data;

	inventory->insert(inFile);
	inventory->display(outFile);
	inventory->get_total_inventory_value(outFile);

	inventory->scan_for_removal(outFile, inventory->get_cut_off_date());

	inventory->display(outFile);
	inventory->get_total_inventory_value(outFile);

	outFile.close();
	return 0;
}
