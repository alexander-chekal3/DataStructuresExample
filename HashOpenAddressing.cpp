//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;
//DONE

//Purpose: Contructs the Open A hash table
//Inputs: size of the hash table
//Outputs: none
HashOpenAddressing::HashOpenAddressing(int size) //DONE!!!
{
    this->hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL;
    }
}

//Purpose: destructs the open A hash table
//Inputs: none
//Outputs: none
HashOpenAddressing::~HashOpenAddressing()//DONE!!!
{
    for(int i = 0; i < hashTableSize; i++)
    {
        delete hashTable[i];
    }
    delete[] hashTable;
}

//Purpose: calculates the hash value
//Inputs: course number to hash
//Outputs: the hash value
int HashOpenAddressing::hash(int courseNumber) //DONE!!!
{
    //Checks basic hash spot
    return (courseNumber % hashTableSize); 
}

//Purpose: Inserts all courses from a file into the hash table
//Inputs: the file name
//Outputs: none
void HashOpenAddressing::bulkInsert(string filename)
{
    ifstream myfile;
    myfile.open(filename);

    if (!myfile.is_open())
    {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }


    string line;
    int coll = 0, sCount = 0;

    while (getline(myfile, line))
    {
        string words[7];
        string year, department, courseNum, courseName, id, proFName, proLName, nameTot;
        int cNum, yNum, index, x = 0;

        // Skips line 1 if it does not start with a digit
        if (line[0] < '0' || line[0] > '9')
        {
            continue;
        }

        // Splits line
        split(line, ',', words);
        year = words[0];
        department = words[1];
        courseNum = words[2];
        courseName = words[3];
        id = words[4];
        proFName = words[5];
        proLName = words[6];

        // Creates professor
        nameTot = proFName + " " + proLName;
        profDb.addProfessor(id, nameTot);
        Professor *p = profDb.searchProfessor(id);

        // Casts
        cNum = atoi(courseNum.c_str());
        yNum = atoi(year.c_str());

        // Creates course
        Course* add = new Course(yNum, department, cNum, courseName, p);
        p->coursesTaught.push_back(add);

        index = hash(cNum);


        // Empty from start
        if (hashTable[index] == NULL)
        {
            hashTable[index] = add;
        }
        else // Uses quadratic probing
        {
            coll++;
            while (hashTable[index] != NULL)
            {
                sCount++;
                x++;
                // Computing the new hash value
                index = (index + x * x) % hashTableSize;
                if (index < 0)
                {
                    index += hashTableSize; // Ensure positive index
                }

                if (x > hashTableSize)
                {
                    // Prevent infinite loop by breaking out if probing exceeds table size
                    break;
                }
            }
            if (hashTable[index] == NULL)
            {
                hashTable[index] = add;
            }
        }
    }

    myfile.close(); // Ensure the file is closed

    cout << "[OPEN ADDRESSING] Hash table populated" << endl << "--------------------------------------------------------" << endl;
    cout << "Collisions using open addressing: " << coll << endl;
    cout << "Search operations using open addressing: " << sCount << endl << endl;
}





//Purpose: Finds a specific course taught by a certain professor
//Inputs: course year, course number, professor id number
//Outputs: none 
void HashOpenAddressing::search(int courseYear, int courseNumber, string profId) //DONE!!!
{
    int h = hash(courseNumber);
    int search = 0;
    int x = 0;

    while(hashTable[h] != NULL)
    {
        if(hashTable[h]->year == courseYear && hashTable[h]->courseNum == courseNumber && hashTable[h]->prof->profId == profId)
        {
            cout << "[OPEN ADDRESSING] Search for a course" << endl << "-------------------------------------" << endl;
            cout << "Search operations using open addressing: " << search << endl << endl;
            displayCourseInfo(hashTable[h]);
            return;
        }
        search++;
        h = (h + x * x) % hashTableSize;
        x++;
    }
        
    cout << "Open addressing could not find course." << endl;
}

//Purpose: Displays all courses in the hash table
//Inputs: none
//Outputs: none
void HashOpenAddressing::displayAllCourses()//DONE!!!
{
    cout << "[OPEN ADDRESSING] Display all courses:" << endl;
    for(int x = 0; x < hashTableSize; x++)
    {
        if(hashTable[x] != NULL)
        {
            displayCourseInfo(hashTable[x]);
        }
    }
}

//Purpose: Displays all info about a course
//Inputs: the course to display
//Outputs: none
void HashOpenAddressing::displayCourseInfo(Course* c) //DONE!!!
{
	if(c == NULL)
    {
        cout << "Could not find course." << endl;
    }
    else
    {
        cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName << endl;
    }
}

//Purpose: Splits a string
//Inputs: the string, the character to split at, array to input split strings
//Outputs: none
void HashOpenAddressing::split(string a, char b, string c[])
{
    string grab;
    int x = 0;
    size_t p = 0;

    while((p = a.find(b)) != string::npos)
    {
        grab = a.substr(0, p);
        c[x] = grab;
        a.erase(0, p + 1);
        x++;
    }
    c[x] = a;
}