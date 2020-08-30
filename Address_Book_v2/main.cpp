#include <iostream>
#include <fstream>
#include <vector>

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

struct Dimensions
{
    int id_width;
    int name_width;
    int surname_width;
    int phone_number_width;
    int email_width;
    int address_width;
};

char load_char();
void print_text_in_table(string text, int characters_quantity, string ending);

void add_friend(vector<Person> &friends);
void delete_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting);
string change_name(string name);
string change_surname(string surname);
string change_phone_number(string phone_number);
string change_email(string email);
string change_address(string address);
Person edit_record(Person record, Dimensions setting);
void change_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting);

void print_headers(Dimensions setting);
void show_one_friend(Person record, Dimensions setting);
void search_by_name_and_show(vector<Person> &friends, Dimensions setting);
void search_by_surname_and_show(vector<Person> &friends, Dimensions setting);
void show_all(vector<Person> &friends, Dimensions setting);

void save_friends_to_file(string file_name, vector<Person> &friends);
string get_word_from_line_splited_by_character(string &text_line, char splitting_character);
vector<Person> load_friends_from_file(string file_name, vector<Person> friends);

int main()
{
    vector<Person> friends;

    string file_name = "Address_Book_new_format.txt";
    friends = load_friends_from_file(file_name, friends);

    Dimensions setting1;
    setting1.id_width = 4;
    setting1.name_width = 20;
    setting1.surname_width = 20;
    setting1.phone_number_width = 12;
    setting1.email_width = 30;
    setting1.address_width = 50;

    // Starting program
    int choice;
    int id;

    while (true)
    {
        choice = 0;
        system("cls");
        cout << "Welcome to address book!"<< endl;
        cout << "People in database: " << friends.size() << endl;
        cout << endl;
        cout << "MAIN MENU"<< endl;
        cout << endl;
        cout << "What do you want to do?" << endl;
        cout << "1. Add friend" << endl;
        cout << "2. Search friend(s)..." << endl;
        cout << "3. Change record's data" << endl;
        cout << "4. Delete record's data" << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "Your choice: ";
        choice = load_char();
        cout << endl;
        if (choice == '1') // Adding new friends
        {
            add_friend(friends);
            save_friends_to_file(file_name, friends);
            system("pause");
        }
        else if (choice == '2') // Searching friends
        {
            while (true)
            {
                system("cls");
                cout << "SEARCHING MENU" << endl;
                cout << endl;
                cout << "1. ...by name" << endl;
                cout << "2. ...by surname" << endl;
                cout << "3. Show all!" << endl;
                cout << "9. Back to main menu" << endl;
                cout << endl;

                cout << "Your choice: ";
                choice = load_char();
                cout << endl;
                if (choice == '1') // By name
                {
                    search_by_name_and_show(friends, setting1);
                    cout << endl;
                    system("pause");
                }
                else if (choice == '2') // By surname
                {
                    search_by_surname_and_show(friends, setting1);
                    cout << endl;
                    system("pause");
                }
                else if (choice == '3') // Show all
                {
                    show_all(friends, setting1);
                    cout << endl;
                    system("pause");
                }
                else if (choice == '9')
                {
                    break;
                }
            }
        }
        else if (choice == '3') // Changing record's data
        {
            cout << "Enter the id here: ";
            cin >> id;
            cout << endl << endl;
            change_record_with_searching_by_id(friends, id, setting1);
            cout << endl;
            save_friends_to_file(file_name, friends);
            system("pause");
        }
        else if (choice == '4') // Deleting record's data
        {
            cout << "Enter the id here: ";
            cin >> id;
            cout << endl << endl;
            delete_record_with_searching_by_id(friends, id, setting1);
            cout << endl;
            save_friends_to_file(file_name, friends);
            system("pause");
        }
        else if (choice == '9') // Exiting
        {
            exit(0);
        }
    }

    return 0;
}

//######################################### CRASH SECURITY #########################################

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

//######################################### ADDING PEOPLE #########################################

void add_friend(vector<Person> &friends)
{
    int people_in_database = friends.size();
    Person record;
    cout << "Please, write data in." << endl;

    cout << "Name: ";
    cin.clear();
    cin.sync();
    getline(cin, record.name);

    cout << "Surname: ";
    cin.clear();
    cin.sync();
    getline(cin, record.surname);

    cout << "Phone number: ";
    cin.clear();
    cin.sync();
    getline(cin, record.phone_number);

    cout << "E-mail address: ";
    cin.clear();
    cin.sync();
    getline(cin, record.email);

    cout << "Address for correspondence: ";
    cin.clear();
    cin.sync();
    getline(cin, record.address);

    if (friends.size() != 0)
    {
        vector<Person>::iterator itr = friends.end();
        --itr;
        record.id = (*itr).id + 1;
    }
    else record.id = people_in_database + 1;

    friends.push_back(record);
}

//######################################### DELETING PEOPLE #########################################

void delete_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting)
{
    string answer;
    string deleting_answer = "n";
    string existence = "NO";
    Person record;

    print_headers(setting);
    for (vector<Person>::iterator itr = friends.begin(), stop = friends.end(); itr != stop; ++itr)
    {
        if (id == (*itr).id)
        {
            record = (*itr);
            show_one_friend(record, setting);
            cout << endl << "Is this record, which you are looking for?" << endl;
            cout << "Answer (y/n): ";
            cin >> answer;
            cout << endl;

            if (answer == "y")
            {
                existence = "YES";
                cout << "Are you sure you want to DELETE this record?(y/n)";
                cin >> deleting_answer;
                if (deleting_answer == "y")
                {
                    friends.erase(itr);
                    cout << "Deleting completed successfully!" << endl;
                }
            }
        }
    }

    if (existence == "NO") cout << "That's all you have in the book." << endl;
}


//######################################### CHANGING RECORDS #########################################

string change_name(string name)
{
    cout << "New name: ";
    cin >> name;
    return name;
}

string change_surname(string surname)
{
    cout << "New surname: ";
    cin >> surname;
    return surname;
}

string change_phone_number(string phone_number)
{
    cout << "New phone_number: ";
    cin >> phone_number;
    return phone_number;
}

string change_email(string email)
{
    cout << "New email: ";
    cin >> email;
    return email;
}

string change_address(string address)
{
    cout << "New address: ";
    cin >> address;
    return address;
}

Person edit_record(Person record, Dimensions setting)
{
    while (true)
    {
        char answer;
        system("cls");
        print_headers(setting);
        show_one_friend(record, setting);
        cout << endl;
        cout << "What do you want to change?" << endl;
        cout << "1. Name" << endl;
        cout << "2. Surname" << endl;
        cout << "3. Phone number"<< endl;
        cout << "4. Email" << endl;
        cout << "5. Address for correspondence" << endl;
        cout << "9. Back to main menu" << endl;
        cout << "Answer: ";
        answer = load_char();

        if (answer == '1')
        {
            record.name = change_name(record.name);
            return record;
        }
        else if (answer == '2')
        {
            record.surname = change_surname(record.surname);
            return record;
        }
        else if (answer == '3')
        {
            record.phone_number = change_phone_number(record.phone_number);
            return record;
        }
        else if (answer == '4')
        {
            record.email = change_email(record.email);
            return record;
        }
        else if (answer == '5')
        {
            record.address = change_address(record.address);
            return record;
        }
        else if (answer == '9') return record;

    }
}

void change_record_with_searching_by_id(vector<Person> &friends, int id, Dimensions setting)
{
    int people_in_database = friends.size();
    string answer;
    string existence = "NO";
    Person record;

    print_headers(setting);
    for (int index = 0; index < people_in_database; index++)
    {
        if (id == friends[index].id)
        {
            record = friends[index];
            show_one_friend(record, setting);
            cout << endl << "Is this record, which you are looking for?" << endl;
            cout << "Answer (y/n): ";
            cin >> answer;
            cout << endl;

            if (answer == "y")
            {
                existence = "YES";
                record = edit_record(record, setting);
                friends[index] = record;
                cout << "Changing completed successfully!" << endl;
            }
        }

    }

    if (existence == "NO") cout << "That's all you have in the book." << endl << endl;
}

//######################################### SHOWING PEOPLE IN TABLE #########################################

void print_text_in_table(string text, int characters_quantity, string ending = "|")
{
    int text_length = text.length();
    string result;
    if (text_length < characters_quantity)
    {
        int space_char_quantity = characters_quantity - text_length;
        string space = "";
        for (int i = 0; i < space_char_quantity; i++)
        {
            space += " ";
        }

        result = text + space + ending;
    }
    else
    {
        result = text + ending;
    }
    cout << result;

}

void print_headers(Dimensions setting)
{
    print_text_in_table("id", setting.id_width);
    print_text_in_table("Name", setting.name_width);
    print_text_in_table("Surname", setting.surname_width);
    print_text_in_table("Phone number", setting.phone_number_width);
    print_text_in_table("Email address", setting.email_width);
    print_text_in_table("Address for correspondence", setting.address_width, "\n");
    string underscore = "";
    int widths_plus_functions_quantity = 132 + 5;
    for (int i = 0; i < widths_plus_functions_quantity; i++)
    {
        underscore += "=";
    }
    cout << underscore << endl;
}

void show_one_friend(Person record, Dimensions setting)
{
    print_text_in_table(to_string(record.id), setting.id_width);
    print_text_in_table(record.name, setting.name_width);
    print_text_in_table(record.surname, setting.surname_width);
    print_text_in_table(record.phone_number, setting.phone_number_width);
    print_text_in_table(record.email, setting.email_width);
    print_text_in_table(record.address, setting.address_width, "\n");
}

//######################################### SEARCHING PEOPLE #########################################

void search_by_name_and_show(vector<Person> &friends, Dimensions setting)
{
    int people_in_database = friends.size();
    string name;
    string existence = "NO";
    string answer;
    Person record;

    cout << "Name: ";
    cin >> name;
    cout << endl << endl;

    print_headers(setting);
    for (int index = 0; index < people_in_database; index++)
    {
        if (name == friends[index].name)
        {
            record = friends[index];
            show_one_friend(record, setting);
            existence = "YES";
        }

    }
    if (existence == "NO")
    {
        cout << endl << "There is no one with that name. Want to add? (y/n)" << endl;
        cin >> answer;

        if (answer == "y")
        {
            add_friend(friends);
        }
    }
}

void search_by_surname_and_show(vector<Person> &friends, Dimensions setting)
{
    int people_in_database = friends.size();
    string surname;
    string existence = "NO";
    string answer;
    Person record;

    cout << "Surname: ";
    cin >> surname;
    cout << endl << endl;

    print_headers(setting);
    for (int index = 0; index < people_in_database; index++)
    {
        if (surname == friends[index].surname)
        {
            record = friends[index];
            show_one_friend(record, setting);
            existence = "YES";
        }

    }
    if (existence == "NO")
    {
        cout << endl << "There is no one with that name. Want to add? (y/n)" << endl;
        cin >> answer;
        if (answer == "y")
        {
            add_friend(friends);
        }
    }
}

void show_all(vector<Person> &friends, Dimensions setting)
{
    int people_in_database = friends.size();
    Person record;
    print_headers(setting);

    for (int index = 0; index < people_in_database; index++)
    {
        record = friends[index];
        show_one_friend(record, setting);
    }
}

//######################################### SAVING AND LOADING #########################################

void save_friends_to_file(string file_name, vector<Person> &friends)
{
    int people_in_database = friends.size();
    cout << "Saving data to file..." << endl;
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

string get_word_from_line_splited_by_character(string &text_line, char splitting_character)
{
    string word = "";

    int starting_position = 0;
    int character_position = 0;
    char character = text_line[character_position];

    while (character != splitting_character)
    {
        word += character;
        character_position++;
        character = text_line[character_position];
    }
    text_line.erase(starting_position, character_position+1);

    return word;
}

vector<Person> load_friends_from_file(string file_name, vector<Person> friends)
{
    cout << "Loading data from file..." << endl;
    Person record;
    char splitting_character = '|';
    string word;
    fstream file;
    string line;
    file.open(file_name, ios::in);
    if (file.good())
    {
        int which_word = 1;
        while(getline(file, line))
        {
            while(line.length() != 0)
            {
                word = get_word_from_line_splited_by_character(line, splitting_character);
                switch(which_word % 6)
                {
                    case 1: record.id = atoi(word.c_str()); break;
                    case 2: record.name = word; break;
                    case 3: record.surname = word; break;
                    case 4: record.phone_number = word; break;
                    case 5: record.email = word; break;
                    case 0: record.address = word; break;
                }
                if (which_word % 6 == 0)
                {
                    friends.push_back(record);
                }

                which_word++;
            }
        }
    }
    file.close();

    cout << "...completed." << endl;

    return friends;
}
