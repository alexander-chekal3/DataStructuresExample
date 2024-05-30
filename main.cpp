//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"
#include "ProfBST.h"
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
//DONE

//Full menu function
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Populate hash tables " << endl;
    cout << " 2. Search for a course " << endl;
    cout << " 3. Search for a professor " << endl;
    cout << " 4. Display all courses" << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
}


int main (int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Usage: ./<program name> <csv file> <hashTable size>" << endl;
        return 0;
    }
    int select = 0;
    int hSize = stoi(argv[2]);
    HashOpenAddressing openA(hSize);
    HashChaining chain(hSize);
    

    int cYr = 0;
    int cNm = 0;
    char type;
    string id;
    do
    {
        displayMenu();
        cin >> select;
        cout << "You entered: " << select << endl;
        switch (select)
        {
            //INSERTS ALL COURSES INTO HASH TABLES
            case 1: //DONE!!!
                cout << "Inserting All Courses..." << endl;
                openA.bulkInsert(argv[1]);
                cout << "Done with open, now chaining..." << endl;
                chain.bulkInsert(argv[1]);
                cout << "Done" << endl;
                break;
            
            //FINDS SPECIFIC COURSE WITH PARAMETERS
            case 2: //DONE!!!
                cout << "Enter the course year:" << endl;
                cin >> cYr;
                cout << "Enter a course number:" << endl;
                cin >> cNm;
                cout << "Enter a Professor's ID:" << endl;   
                cin >> id;

                openA.search(cYr, cNm, id);
                chain.search(cYr, cNm, id);
                break;

            //FINDS A SPECIFIC PROFESSOR
            case 3:
                cout << "Enter a Professor's ID:" << endl; 
                cin >> id;

                cout << "[OPEN ADDRESSING] Search for a professor" << endl << "-------------------------------------" << endl;
                openA.profDb.publicSearchProfessor(id);
                cout << endl << endl;
                cout << "[CHAINING] Search for a professor" << endl << "--------------------------------------------------------" << endl;
                chain.profDb.publicSearchProfessor(id);
                break;

            //DISPLAYS ALL CHAINING OR OPEN A HASH TABLE COURSES    
            case 4:
                cout << "Which hash table would you like to display the courses for (O=Open Addressing, C=Chaining)?" << endl;
                cin >> type;

                if(type == 'O' || type == 'o')
                {
                    openA.displayAllCourses();
                }
                else
                {
                    chain.displayAllCourses();
                }
                break;
            case 5:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid Input" << endl;
                break;
        };

    } while (select != 5);

    return 0;
}