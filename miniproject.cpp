#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <regex>
using namespace std;
const int MAX = 100;
struct Contact 
{
    string name;
    string phoneNumber;
    string emailAddress;
    string homeAddress;
};
void saveContactsToFile(const string& fileName, const Contact contacts[], int numContacts) 
{
    ofstream file(fileName.c_str());
    if (!file.is_open()) 
    {
        cout << "Error opening file for writing: " << fileName << endl;
        
        return;
    }

    for (int i = 0; i < numContacts; ++i)
    {
        file << contacts[i].name << ',' << contacts[i].phoneNumber << ','
             << contacts[i].emailAddress << ',' << contacts[i].homeAddress << endl;
    }

    file.close();
}
void loadContactsFromFile(const string& fileName, Contact contacts[], int& numContacts) {
    ifstream file(fileName.c_str());
    if (!file.is_open()) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    numContacts = 0;
    while (getline(file, contacts[numContacts].name, ',')) 
    {
        getline(file, contacts[numContacts].phoneNumber, ',');
        getline(file, contacts[numContacts].emailAddress, ',');
        getline(file, contacts[numContacts].homeAddress);
        ++numContacts;
        if (numContacts >= MAX) 
        {
            cout << "Maximum number of contacts reached!" << endl;
            break;
        }
    }

    file.close();
}

void displayContacts(const Contact contacts[], int numContacts) 
{
    cout << "Address Book:" << endl;
    for (int i = 0; i < numContacts; ++i) 
    {
        cout << "Name: " << contacts[i].name << "\tPhone Number: " << contacts[i].phoneNumber
             << "Email Address: " << contacts[i].emailAddress << "\tHome Address: " << contacts[i].homeAddress << endl;
    }
}

bool check_digits(string x);
bool check_numbers(string x);
bool checkEmailFormat(const string& email);

void addContact(Contact contacts[], int& numContacts)
 {
    if (numContacts < MAX) 
    {
        cout << "Enter the name of the new contact: ";
        getline(cin, contacts[numContacts].name);

        do
        {
            cout << "Enter the phone number of the new contact (10 digits only): ";
            getline(cin, contacts[numContacts].phoneNumber);
        }while (!check_digits(contacts[numContacts].phoneNumber) || !check_numbers(contacts[numContacts].phoneNumber));

        do
        {
            cout << "Enter the email address of the new contact: ";
            getline(cin, contacts[numContacts].emailAddress);
        }while(!checkEmailFormat(contacts[numContacts].emailAddress));

        cout << "Enter the home address of the new contact: ";
        getline(cin, contacts[numContacts].homeAddress);

        ++numContacts;
        cout << "Contact added successfully!" << endl;
    } 
    else
    {
        cout << "Maximum number of contacts reached!" << endl;
    }
}
void searchContact(const Contact contacts[], int numContacts)
{
    string searchName;
    cout << "Enter the name to search: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < numContacts; ++i)
    {
        if (contacts[i].name == searchName) {
            cout << "Contact found:\nName: " << contacts[i].name << "\tPhone Number: " << contacts[i].phoneNumber
                 << "\tEmail Address: " << contacts[i].emailAddress << "\tHome Address: " << contacts[i].homeAddress << endl;
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "Contact not found." << endl;
    }
}

void editContact(Contact contacts[], int numContacts) 
{
    string editName;
    cout << "Enter the name to edit: ";
    getline(cin, editName);

    for (int i = 0; i < numContacts; ++i)
    {
        if (contacts[i].name == editName) 
        {
            cout << "Enter the new name for the contact: ";
            getline(cin, contacts[i].name);

            do
            {
            cout << "Enter the new phone number for the contact: ";
            getline(cin, contacts[i].phoneNumber);
            }while(!check_digits(contacts[i].phoneNumber) || !check_numbers(contacts[i].phoneNumber));

            do
            {
            cout << "Enter the new email address for the contact: ";
            getline(cin, contacts[i].emailAddress);
            }while(!checkEmailFormat(contacts[i].emailAddress));

            cout << "Enter the new home address for the contact: ";
            getline(cin, contacts[i].homeAddress);

            cout << "Contact edited successfully!" << endl;
            return;
        }
    }

    cout << "Contact not found." << endl;
}
void deleteContact(Contact contacts[], int& numContacts) 
{
    string deleteName;
    cout << "Enter the name to delete: ";
    getline(cin, deleteName);
    for (int i = 0; i < numContacts; ++i) 
    {
        if(contacts[i].name == deleteName) 
        {
            for (int j = i; j < numContacts - 1; ++j) 
            {
                contacts[j] = contacts[j + 1];
            }
            --numContacts;
            cout << "Contact deleted successfully!" << endl;
            return;
        }
    }
    cout << "Contact not found." << endl;
}

bool check_digits(string x) 
{ 
    if (x.length() == 10) 
        return true; 
    else
        return false; 
}

bool check_numbers(string x)
{ 
    bool check = true; 
  
    for (long i=0; i<x.length(); i++)
     { 
        if (!(int(x[i]) >= 48 && int(x[i]) <= 57)) 
        { 
            check = false; 
            break; 
        } 
    } 
    if (check == true)
        return true; 
  
    if (check == false)
        return false; 
  
    cout << endl << endl; 
    system("pause"); 
    system("cls");
    return 0;
} 

bool checkEmailFormat(const string& email) 
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}
int main() 
{
    string fileName = "address_book.txt";
    Contact contacts[MAX];
    int numContacts = 0;

    loadContactsFromFile(fileName, contacts, numContacts);

    int choice;
    do {
        cout << "\nChoose an option:\n"
             << "1. Display Contacts\n"
             << "2. Add a Contact\n"
             << "3. Search for a Contact\n"
             << "4. Edit a Contact\n"
             << "5. Delete a Contact\n"
             << "6. Exit\n"
             << "Enter your choice: ";

        string choiceStr;
        getline(cin, choiceStr);
        choice=stoi(choiceStr);

        switch (choice)
        {
            case 1:
                displayContacts(contacts, numContacts);
                break;
            case 2:
                addContact(contacts, numContacts);
                saveContactsToFile(fileName, contacts, numContacts);
                break;
            case 3:
                searchContact(contacts, numContacts);
                break;     
            case 4:
                editContact(contacts, numContacts);
                saveContactsToFile(fileName, contacts, numContacts);
                break;
            case 5:
                deleteContact(contacts, numContacts);
                saveContactsToFile(fileName, contacts, numContacts);
                break;
            case 6:
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice!= 6);

    return 0;
}