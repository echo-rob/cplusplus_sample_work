/*
    Start date:		2020-Nov-18
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

string parse_name(string no_space_str) {
    string first_name;
    string middle_initial; 
    string last_name;

    // determine position of comma in string
    size_t comma_pos = 0;
    comma_pos = no_space_str.find(",");
    //cout << "DEBUG comma_pos: " << comma_pos << endl;
         
    // from 0 index to comma position, assign to last_name
    last_name = no_space_str.substr(0, comma_pos);
    //cout << "DEBUG last_name: " << last_name << endl;

    //get first name and middle initial (if present) 
    string first_half = no_space_str.substr(comma_pos + 1, no_space_str.length());

    // iterate over first half of name
    int capital_letters = 0;
    for ( int i = 0; i < first_half.size(); i++) {

        // find capital letters to 
        if (isupper(first_half[i])) {

            //first capital is part of first name
            if (capital_letters < 1) {
                first_name += first_half[i];
                capital_letters += 1;
            }

            //second capital is the middle initial 
            else {
                middle_initial += first_half[i];
            }
        }
        
        //get the rest of the letters in the first name, besides punctuation
        else if (!ispunct(first_half[i])) {
            first_name += first_half[i];
        }
    }

    // if present, append period to middle initial
    if (middle_initial.size() > 0) {
        middle_initial += ". ";
    }

    //combine the parts of the name
    string parsed_name = first_name + " " + middle_initial + last_name;
  
    return parsed_name; 
}

string remove_whitespace(string line) {
    
    // remove whitespace and assign to temp_str 
    string temp_str;
    for ( int i = 2; i < line.size(); i++) {
        if (!isspace(line[i])) {
            temp_str += line[i];
        }
    }

    return temp_str;
}

int determine_marital_status(char status_char) {

    // define marital status enum
    enum MARITAL_STATUS { SINGLE = 0, MARRIED = 1, DIVORCED = 0 };

    //MARITAL_STATUS status; 

    if (status_char == 'M') {
        return MARITAL_STATUS::MARRIED;
    }
    else if (status_char == 'S') {
        return MARITAL_STATUS::SINGLE;
    }
    else if (status_char == 'D') {
        return MARITAL_STATUS::DIVORCED;
    }
    else {
        // return error, though it should happen with supplied input file
        return -1;
    }

}

vector<string> open_file() {

    // open file
    ifstream infile("mp6Names.txt");

    // if read is successful, continue.
    if (infile.good() == false) {
        cout << "Error. Unable to open the file." << endl;
        cout << "Please verify the text file and this program are in the same directory and try again." << endl;
    }

    string line;
    vector<string> input_data;

    while (!infile.eof()) {
        getline(infile, line);
        //cout << "DEBUG line: " << line << endl;
        input_data.push_back(line);
    }

    infile.close();

    return input_data;
}

int main()
{
    cout << "String Parsing and Formatting\n\n";

    // open file
    vector<string> infile = open_file();

    cout << setw(35) << left << "Original Name" << left << setw(30) << "Formatted Name\n" << endl;
    
    for ( int i = 0; i < infile.size(); i++) {
        // get gender and marital status
        string line = infile[i]; 

        // get marital status
        string name_prefix; 

        // if male
        if (line[0] == 'M') {
            name_prefix = "Mr.";
        }

        // if female
        if (line[0] == 'F') {

            // if this returns bool:true (person is married), then 'mrs' 
            if (determine_marital_status(line[1])) {
                name_prefix = "Mrs.";
            }
            // print error. shouldnt happen for this project 
            else if (determine_marital_status(line[1]) == -1) {
                cout << "Warning. No marital status found for user." << endl;
            }
            // else 'ms.'
            else {
                name_prefix = "Ms.";
            }
          
        }
        
        // effective remove first two chars of string 
        string original_name = line.substr(2);

        // remove whitespace from string to make parsing easier 
        string no_space_str = remove_whitespace(line); 

        // parse string into first/middle/last name 
        string parsed_name = parse_name(no_space_str);

        // combine prefix and name 
        string formatted_name = name_prefix + ' ' + parsed_name;
                
        // print data to console
        cout << setw(35) << left << original_name << left << setw(30) << formatted_name << endl;

    }

    cout << "\n\nPlease press any key to continue..." << endl;

    return 0;

}
