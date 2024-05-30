//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.h
//-----------------------------------------------------------------------------

#ifndef HASHCHAINING_H
#define HASHCHAINING_H

#include "ProfBST.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
//DONE
class HashChaining
{
	public:
		HashChaining(int size);
		~HashChaining();
		
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