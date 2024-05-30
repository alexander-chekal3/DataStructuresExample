//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.h
//-----------------------------------------------------------------------------

#ifndef PROFBST_H
#define PROFBST_H

#include "util.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
//DONE
struct Professor
{
	string profId;
	string profName;
	vector<Course*> coursesTaught;
	Professor *left;
	Professor *right;

	Professor() {}
	Professor(string pId, string pName) { 
		profId = pId; 
		profName = pName;
		left = nullptr; right = nullptr; 
	}
};

// Professor BST class
class ProfBST
{
    public:
        ProfBST();
        ~ProfBST();
		void destroyNode(Professor *current);
		Professor *addHelper(Professor *current, Professor *newNode);
        void addProfessor(string profId, string profName);
		void publicSearchProfessor(string profId);
		Professor *searchHelper(Professor *current, string id);
        Professor *searchProfessor(string profId);
		void displayProfessorInfo(Professor* p);

    private:
		// add helpers here (if needed)
        Professor *root;
};

#endif