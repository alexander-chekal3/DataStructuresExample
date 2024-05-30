//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.h
//-----------------------------------------------------------------------------

#ifndef HASHOPENADDRESSING_H
#define HASHOPENADDRESSING_H

#include "util.h"
#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
//DONE
class HashOpenAddressing
{
	public:
		HashOpenAddressing(int size);
		~HashOpenAddressing();
		
        void search(int courseYear, int courseNumber, string profId);		
		void bulkInsert(string filename);
		
        void displayAllCourses();
		void displayCourseInfo(Course* c);
		
		int hash(int courseNumber);

		void split(string a, char b, string c[]);

		ProfBST profDb;
		
	private:
		int hashTableSize;
		Course **hashTable;
};

#endif