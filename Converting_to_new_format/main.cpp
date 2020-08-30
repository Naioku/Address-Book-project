#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person
{
    int id;
    string name;
    string surname;
    string phone_number;
    string email;
    string address;
};

vector<Person> load_friends_from_file(string file_name, vector<Person> friends)
{
    cout << "Loading data from file..." << endl;
    fstream file;
    string line;
    Person record;
    file.open(file_name, ios::in);
    if (file.good())
    {
        int which_line = 1;
        while(getline(file, line))
        {
            switch(which_line % 6)
            {
                case 1: record.id = atoi(line.c_str()); break;
                case 2: record.name = line; break;
                case 3: record.surname = line; break;
                case 4: record.phone_number = line; break;
                case 5: record.email = line; break;
                case 0: record.address = line; break;
            }
            if (which_line % 6 == 0)
            {
                friends.push_back(record);
            }

            which_line++;
        }
    }
    else
    {
        cout << endl << "The file " << file_name << " doesn't exist. Please, create it first." << endl;
        system("pause");
        exit(0);
    }
    file.close();

    cout << "...completed." << endl;

    return friends;
}

void save_friends_to_file(string file_name, vector<Person> &friends)
{
    cout << "Saving data to file..." << endl;
    int people_in_database = friends.size();
    fstream file;
    file.open(file_name, ios::out);

    for (int index = 0; index < people_in_database; index++)
    {
        file << friends[index].id << "|";
        file << friends[index].name << "|";
        file << friends[index].surname << "|";
        file << friends[index].phone_number << "|";
        file << friends[index].email << "|";
        file << friends[index].address << "|" << endl;
    }
    file.close();
    cout << "...completed." << endl;
}

void show_one_friend(Person record)
{
    cout << record.id << ". Member" << endl;
    cout << "id: " << record.id << endl;
    cout << "Name: " << record.name << endl;
    cout << "Surname: " << record.surname << endl;
    cout << "Phone_number: " << record.phone_number << endl;
    cout << "email: " << record.email << endl;
    cout << "address: " << record.address << endl;
    cout << endl;
}

char load_char()
{
    string input_str = "";
    char character  = {0};

    while (true)
    {
        cin.clear();
        cin.sync();
        getline(cin, input_str);

        if (input_str.length() == 1)
        {
            character = input_str[0];
            break;
        }
        cout << "This isn't single character. Please, try again: ";
    }
    return character;
}

int main()
{
    string file_name;
    string file_name_with_extension;
    string file_name2;
    vector<Person> friends;
    char answer;

    while (true)
    {
        cout << "This function converts old format notation to new." << endl << endl;
        cout << "Old format:" << endl;
        cout << "ID" << endl;
        cout << "Name" << endl;
        cout << "Surname" << endl;
        cout << "Phone_number" << endl;
        cout << "Email" << endl;
        cout << "Address" << endl << endl;
        cout << "New format: ID|Name|Surname|Phone_number|Email|Address|" << endl << endl;
        cout << "File with old format have to be in the same folder, where the execute file (.exe) you have already run is." << endl << endl;

        cout << "1. Proceed" << endl;
        cout << "9. Exit" << endl;
        cout << "Answer: ";
        answer = load_char();
        if (answer == '1')
        {
            cout << "Enter the text file name (without extension): ";
            cin >> file_name;
            cout << endl;
            file_name_with_extension = file_name + ".txt";
            friends = load_friends_from_file(file_name_with_extension, friends);
            cout << endl;

            file_name2 = file_name + "_new_format.txt";
            save_friends_to_file(file_name2, friends);
            cout << endl;
            exit(0);
        }
        else if (answer == '9') exit(0);
    }

    return 0;
}
