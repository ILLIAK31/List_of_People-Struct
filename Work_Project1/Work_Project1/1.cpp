#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int person_size = 0;
int person_size2 = 0;
vector <int> array1 ;
vector <string> name2;
vector <string> surname2;
vector <string> age2;
vector <string> pesel2;
vector <string> gender2;

struct Person {
    string name;
    string surname;
    int age;
    int pesel;
    char gender;
    Person* last;
    Person* next;
};

Person* back = new Person;
Person* head = new Person;
Person* current = new Person;
Person* current2 = new Person;
Person* back_back = new Person;

bool Wrong_gender(char Gender)
{
    if ((Gender == 'M')||(Gender == 'F'))
    {
        return false;
    }
    return true;
}

bool Search_Person(struct Person* Head,string Name_surname)
{
    int res = 0;
    current = Head->next;
    Person* current2 = new Person;
    current2 = current;
    for (int i = 0; i < person_size; ++i)
    {
        if (((current2->name) == Name_surname)||((current2->surname) == Name_surname))
        {
            current = current2;
            res = 1;
        }
        current2 = current2->next;
    }
    delete current2;
    if (res == 1)
        return true;
    return false;
}

bool Search_Pesel(int Pesel)
{
    for (int i = 0;i < array1.size();++i)
    {
        if (Pesel == array1[i])
            return true;
    }
    return false;
}

bool Add_Person()
{
    Person* user = new Person;
    if (person_size == 1)
        head->next = user;
    current = user;
    cout << "Give name: ";
    cin >> user->name;
    cout << "Give surname: ";
    cin >> user->surname;
    cout << "Give age: ";
    cin >> user->age;
    cout << "Give pesel: ";
    cin >> user->pesel;
    if (Search_Pesel(user->pesel))
    {
        cout << "Wrong Pesel" << endl;
        return true;
    }
    else
    {
        array1.push_back(user->pesel);
    }
    cout << "Give gender: ";
    cin >> user->gender;
    if (Wrong_gender(user->gender))
    {
        cout << "Wrong gender" << endl;
        return true;
    }
    return false;
}

bool delete_person(struct Person* Head, string Surname)
{
    int res = 0;
    current = Head->next;
    for (int i = 0; i < person_size; ++i)
    {
        if ((current->surname) == Surname)
        {
            back = current->last;
            back->next = current->next;
            delete current;
            i = person_size;
            --person_size;
            res = 1;
        }
        else
            current = current->next;
    }
    if (res == 1)
        return true;
    return false;
}

void Print(struct Person* Head)
{
    current = Head->next;
    for (int i = 0; i < person_size; ++i)
    {
        cout << "| NAME : " << current->name << "   SURNAME : " << current->surname << "   AGE : " << current->age << "   PESEL : " << current->pesel << "   GENDER : " << current->gender << endl;
        current = current->next;
    }
}

bool Add_Person_file(struct Person* HEAD)
{
    int to_int_num1 , to_int_num2 , res = 0;
    char tochar[2] ;
    current = HEAD;
    for (int i = 0; i < person_size; ++i)
    {
        current = current->next;
    }
    for (int i = 0; i < person_size2; ++i)
    {
        Person* user = new Person;
        user->last = current;
        user->name = name2[i];
        user->surname = surname2[i];
        to_int_num1 = stoi(age2[i]);
        user->age = to_int_num1;
        to_int_num2 = stoi(pesel2[i]);
        user->pesel = to_int_num2;
        tochar[0] = NULL;
        strcpy_s(tochar, gender2[i].size()+1 , gender2[i].c_str());
        user->gender = tochar[0];
        user->next = NULL;
        ++person_size;
        current->next = user;
        current = user;
        back = user;
        if (Search_Pesel(user->pesel))
        {
            cout << "Wrong Pesel" << endl;
            res = 1;
          
        }
        else
        {
            array1.push_back(user->pesel);
        }
        if (Wrong_gender(user->gender))
        {
            cout << "Wrong gender" << endl;
            res = 1;
        }
    }
    if (res == 1)
        return true;
    return false;
}

bool Read_doc(struct Person* Head)
{
    person_size2 = 0;
    int nums = 0 , res2 = 0;
    string line;
    ifstream fin;
    fin.open("Filenumone.txt");
    if (fin.is_open())
    {
        while(getline(fin,line))
        {
            if (nums == 0)
                name2.push_back(line);
            else if (nums == 1)
                surname2.push_back(line);
            else if (nums == 2)
                age2.push_back(line);
            else if (nums == 3)
            {
                pesel2.push_back(line);
                int l = pesel2.size();
                current = Head->next;
                for (int i = 0; i < person_size; ++i)
                {
                    if (current->pesel == stoi(line))
                    {
                        name2.erase(name2.begin() + (l-1));
                        surname2.erase(surname2.begin() + (l - 1));
                        age2.erase(age2.begin() + (l - 1));
                        pesel2.erase(pesel2.begin() + (l - 1));
                        res2 = 1;
                        break;
                    }
                    current = current->next;
                }
            }
            else
            {
                if (res2 == 0)
                {
                    gender2.push_back(line);
                    ++person_size2;
                }
                nums -= 5;
            }
            ++nums;
        }
    }
    fin.close();
    if (person_size2 == 0)
        return true;
    if (Add_Person_file(Head))
        return true;
    return false;
}

void Write_to_file(struct Person* Head)
{
    ofstream fin;
    fin.open("Filenumtwo.txt");
    if (fin.is_open())
    {
        current = Head->next;
        for (int i = 0; i < person_size; ++i)
        {
            fin << "|Person " << (i+1) << "   |Name : " << current->name << "  |Surname : " << current->surname << "   |Age : " << current->age << "   |Pesel : " << current->pesel << "   |Gender : " << current->gender << "   |" << endl;
            current = current->next;
        }
    }
    fin.close();
}

void Autoposition(struct Person* Head)
{
    int position = 2;
    string str1 , str2;
    current = Head->next;
    back_back = Head;
    back = current;
    current = current->next;
    for (int i = 0; i < (person_size * person_size); ++i)
    {
        str1 = current->surname;
        str2 = back->surname;
        cout << toupper(str1[0])<< str2[0] << endl;
        if (toupper(str1[0]) < toupper(str2[0]))
        {
            back_back->next = current;
            current->last = back_back;
            current->next = back;
            back->last = current;
            if ((position + 1) < person_size)
                back->next = current->next;
            else
                back->next = NULL;
            current2 = current;
            current = back;
            back = current2;
        }
        if ((position + 1) > person_size)
        {
            position -= (person_size - 3);
            current = Head->next;
            back_back = Head;
            back = current;
        }
        current = current->next;
        back = back->next;
        back_back = back_back->next;
        ++position;
    }
}

int main()
{
    int number;
    char cont;
    head->last = NULL;
    head->next = NULL;
    back = head;
    do{
        cout << "Menu:\n" << "1.Add person\n2.Search Person\n3.Delete person\n4.Print all person\n5.Read from doc\n6.Write to doc\n7.Autoposition (surnames)\n" << "Choose option: ";
        cin >> number;
        if (number == 1)
        {
            ++person_size;
            if (Add_Person())
                break;
            current->next = NULL;
            current->last = back;
            back->next = current;
            back = current;
        }
        else if (number == 2)
        {
            if (person_size == 0)
                break;
            string name_surname;
            cout << "Give name or surname" << endl;
            cin >> name_surname;
            if (Search_Person(head, name_surname))
                cout << "| NAME : " << current->name << " SURNAME : " << current->surname << endl << "| AGE : " << current->age << " PESEL : " << current->pesel << endl << "|GENDER : " << current->gender << endl;
            else
                cout << "Person not detected" << endl;
        }
        else if (number == 3)
        {
            string surname2;
            cout << "Give surname to delete person : ";
            cin >> surname2;
            if (delete_person(head,surname2))
                cout << "Person was deleted\n";
            else
                cout << "Person was not founded\n";
        }
        else if (number == 4)
        {
            Print(head);
        }
        else if (number == 5)
        {
            if (Read_doc(head))
                cout << "File is empty or person data is uncorect" << endl;
            else
                cout << "Person added from file" << endl;
        }
        else if (number == 6)
        {
            if (person_size == 0)
                cout << "List is empty" << endl;
            else
            {
                Write_to_file(head);
                cout << "Data was write to doc" << endl;
            }
        }
        else if (number == 7)
        {
            if ((person_size == 0) || (person_size == 1))
                cout << "List is too small" << endl;
            else
            {
                Autoposition(head);
                cout << "Autoposition is correctly ended" << endl;
            }
        }
        else
        {
            cout << "Wrong menu command\n";
        }
        cout << "Continue?\nYes(Y/y) or No(N/n)\n";
        cin >> cont;
        if ((cont == 'N') || (cont == 'n'))
            break;
        else if ((cont == 'Y') || (cont == 'y'))
            continue;
        else
        {
            cout << "Unacceptable char" << endl;
            break;
        }
    }while(true);
    back = NULL;
    head = NULL;
    current = NULL;
    current2 = NULL;
    back_back = NULL;
    delete back;
    delete head;
    delete current;
    delete current2;
    delete back_back;
	return 0;
}