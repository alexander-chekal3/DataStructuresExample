//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;
//DONE

//Purpose: Construct the Chaining Hash Table
//Inputs: Size of the table
//Outputs: None
HashChaining::HashChaining(int size) //DONE!!!
{
    this->hashTableSize = size;
    hashTable = new Course*[hashTableSize];
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = NULL;
    }
}

//Purpose: Destructs the Chaining Hash Table
//Inputs: None
//Outputs: None
HashChaining::~HashChaining() //DONE!!!
{
    for(int i = 0; i < hashTableSize; i++)
    {
        delete hashTable[i];
    }
    delete[] hashTable;
}

//Purpose: Get the Hash value
//Inputs: The course number to be hashed
//Outputs: the hash value
int HashChaining::hash(int courseNumber) //DONE!!!
{
    return (courseNumber % hashTableSize);
}

//Purpose: Inserts all courses from a file into the hash table
//Inputs: the file name
//Outputs: none
void HashChaining::bulkInsert(string filename) //DONE!!!
{
    ifstream myfile;
    myfile.open(filename);
    string line;
    int coll2 = 0, sCount2 = 0;
    if(myfile.is_open())
    {
        while(getline(myfile, line))
        { 
            string words[7];
            string year, department, courseNum, courseName, id, proFName, proLName, nameTot;
            int cNum, yNum = 0;
            //skips line 1
            if(line[0] != '2')
            {
                continue;
            }
            //splits line
            split(line, ',', words);
            year = words[0];
            department = words[1];
            courseNum = words[2];
            courseName = words[3];
            id = words[4];
            proFName = words[5];
            proLName = words[6];

            //creates prof
            nameTot = proFName + " " + proLName;
            profDb.addProfessor(id, nameTot);
            Professor *p = profDb.searchProfessor(id);

            //casts
            cNum = atoi(courseNum.c_str());
            yNum = atoi(year.c_str());

            //creates course
            Course* add = new Course(yNum, department, cNum, courseName, p);
            p->coursesTaught.push_back(add);

            int index = hash(cNum);
            
            //Empty from start
            if(hashTable[index] == NULL)
            {
                hashTable[index] = add;
            }
            else 
            {
                //Collision Control
                Course *curr = hashTable[index];
                while(curr->next != NULL) 
                {
                    curr = curr->next;
                    sCount2++;
                }
                add->previous = curr;
                curr->next = add;
                coll2++;
                sCount2++;

            }

        }
    }
    else
    {
        cout << "Failed to open the file: " << filename << endl;
    }

    myfile.close();
    cout << "[CHAINING] Hash table populated" << endl << "--------------------------------------------------------" << endl;
    cout << "Collisions using chaining: " << coll2 << endl;
    cout << "Search operations using chaining: " << sCount2 << endl << endl;
}

//Purpose: Finds a specific course taught by a certain professor
//Inputs: course year, course number, professor id number
//Outputs: none
void HashChaining::search(int courseYear, int courseNumber, string profId) //DONE!!!
{
    int h = hash(courseNumber);
    int search = 0;

    Course *curr = hashTable[h];
    while(curr != NULL)
    {
        if(curr->year == courseYear && curr->courseNum == courseNumber && curr->prof->profId == profId)
        {
            cout << "[CHAINING] Search for a course" << endl << "-------------------------------------" << endl;
            cout << "Search operations using chaining: " << search << endl << endl;
            displayCourseInfo(curr);
            return;
        }
        curr = curr->next;
        search++;
    }
    cout << "Chaining could not find course." << endl;
    
}

//Purpose: Displays all courses in the hash table
//Inputs: none
//Outputs: none
void HashChaining::displayAllCourses() //DONE!!!
{
    cout << "[CHAINING] Display all courses:" << endl;
    for(int x = 0; x < hashTableSize; x++)
    {
        if(hashTable[x] != NULL)
        {
            Course *curr = hashTable[x];
            while(curr != NULL)
            {
                displayCourseInfo(curr);
                curr = curr->next;
            }
        }
    }
}

//Purpose: Displays all info about a course
//Inputs: the course to display
//Outputs: none
void HashChaining::displayCourseInfo(Course* c) //DONE!!!
{
    if(c == NULL)
    {
        cout << "Could not find course." << endl;
    }
    else
    {
        cout << c->year << " " << c->courseName << " " << c->courseNum << " " << c->prof->profName<< endl;
    }
}

//Purpose: Splits a string
//Inputs: the string, the character to split at, array to input split strings
//Outputs: none
void HashChaining::split(string a, char b, string c[])
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