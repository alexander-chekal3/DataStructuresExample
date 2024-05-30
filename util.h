//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: util.h
//-----------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Professor;

struct Course
{
	int year;            // e.g. 2021
	string department;   // e.g. CSCI
    int courseNum;       // e.g. 2270
    string courseName;   // e.g. COMP SCI II: DATA STRUCT
    Professor *prof;     // Pointer to the Professor object

	Course *next = NULL;
	Course *previous = NULL;

	Course() {}
	Course(int newYear, string newDepartment, int newCourseNum, string newCourseName, Professor *newProf = nullptr)
	{
        year = newYear;
        department = newDepartment;
        courseNum = newCourseNum;
        courseName = newCourseName;
		prof = newProf;
		next = NULL;
		previous = NULL;
    }
};

#endif