//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;
//DONE

//Purpose: Constructs the BST
//Inputs: none
//Outputs: none
ProfBST::ProfBST() //DONE!!!
{
    root = NULL;
}

//Purpose: detructs the bst
//Inputs: none
//Outputs: none
ProfBST::~ProfBST()//DONE!!!
{
    destroyNode(root);
}

//Purpose: deletes all nodes under the root for the destructor
//Inputs: the current node to delete
//Outputs: none
void ProfBST::destroyNode(Professor *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

//Purpose: adds a professor the bst
//Inputs: new professor id, new professor name
//Outputs: none
void ProfBST::addProfessor(string profId, string profName)//DONE!!!
{
    if (root == nullptr)
    {
        root = new Professor(profId, profName);
        return;
    }

    root = addHelper(root, new Professor(profId, profName));
}

//Purpose: helps the add function
//Inputs: the current node to add from, and the adding node
//Outputs: a professor object
Professor* ProfBST::addHelper(Professor *current, Professor *newNode)//DONE!!!
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->profId > newNode->profId)
    {
        current->left = addHelper(current->left, newNode);
    }
    else
    {
        current->right = addHelper(current->right, newNode);
    }

    return current;
}

//Purpose: Finds a professor in the BST
//Inputs: the professor id
//Outputs: the professor's object
Professor* ProfBST::searchProfessor(string profId) //DONE!!!
{
    return (searchHelper(root, profId));
}
//Purpose: helps the searchProf function
//Inputs: current node to operate on, the prof id to look for
//Outputs: the found professor
Professor* ProfBST::searchHelper(Professor *current, string id)
{
    if (current == NULL)
    {
        return NULL;
    }
    if (current->profId == id)
    {
        return current;
    }
    if (current->profId > id)
    {
        return searchHelper(current->left, id);
    }
    return searchHelper(current->right, id);
}

//Purpose: finds the professor and outputs info
//Inputs: professor id
//Outputs: none
void ProfBST::publicSearchProfessor(string profId)//DONE!!!
{
    Professor *curr = root;
    while(curr != NULL)
    {
        if(curr->profId == profId)
        {
            break;
        }
        if(curr->profId > profId)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    
    if(curr == NULL)
    {
        cout << "Professor not found" << endl;
    }
    else
    {
        displayProfessorInfo(curr);
    }
}

//Purpose: prints professor info
//Inputs: the professor to print
//Outputs: none
void ProfBST::displayProfessorInfo(Professor* p)//DONE!!!
{
    cout << "Name: " << p->profName << endl;
    for(int i=0; i < p->coursesTaught.size(); i++)
    {
        cout << p->coursesTaught.at(i)->courseNum << ": " << p->coursesTaught.at(i)->courseName << ", " << p->coursesTaught.at(i)->year << endl;
    }
}
