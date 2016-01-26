
/********************************************/
/*    Groovy Music End-of-Year Inventory    */
/*	          James Singleton           */
/* 	       CSC 3380_97 Section 1        */
/*                 Assignment 1             */
/* Instructor: Douglas  	            */
/* Program due date:  February 2, 2016      */
/********************************************/

// PROBLEM SPECIFICATION...

// PROBLEM ANALYSIS...

// IMPLEMENTATION DIRECTIONS...

#include "CD_Data.h";
using namespace std;


int main()
{
	ifstream inFile;
	inFile.open("Music2015.data");
	ofstream outFile;
	outFile.open("Report.out");
	CD_Data *test = new CD_Data;

	test->insert(inFile);
	test->display(outFile);
	test->get_total_inventory_value(outFile);

	test->scan_for_removal(outFile, test->get_cut_off_date());

	test->display(outFile);
	test->get_total_inventory_value(outFile);

	outFile.close();
	return 0;
}
