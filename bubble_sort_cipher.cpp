/*
    Start date:		2020-Nov-04
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// define characters to fill out cipher 
char alphabet_list[25] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y' };


char search_cipher(char character, char key[5][5]) {

    // variables for char coordinates 
    int row_pos;
    int col_pos;

    // search the cipher for the char
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key[i][j] == character) {
                row_pos = i;
                col_pos = j;
            }
        }
    }

    // swap the coordinates of the row and column to adhere to algorithm 
    swap(row_pos, col_pos);

    // get the character at the new coordinates 
    char cipher_char = key[row_pos][col_pos];

    return cipher_char;
}


void build_cipher_key(string keyword, char key[5][5]) {

    cout << "The keyword is: " << keyword << endl;

    vector<char> cipher_chars;
    // remove duplicate letters from intial keyword
    for (unsigned int i = 0; i < keyword.length(); i++) {

        // if char in cipher, do nothing
        if (find(cipher_chars.begin(), cipher_chars.end(), keyword[i]) != cipher_chars.end()) {
            continue;
        }
        // else add char to cipher
        else {
            cipher_chars.push_back(keyword[i]);
        }
    }

    //pad cipher with remaining letters 
    for (unsigned int i = 0; i < sizeof(alphabet_list); i++) {
        if (find(cipher_chars.begin(), cipher_chars.end(), alphabet_list[i]) != cipher_chars.end()) {
            continue;
        }
        else {
            cipher_chars.push_back(alphabet_list[i]);
        }
    }

    // with cipher_chars, build the 5-by-5 2d array 
    int index = 0;
    for (unsigned int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key[i][j] = cipher_chars[index];
            index += 1;
        }
    }
}


vector<string> open_file() {

    // open file
    ifstream infile("mp5input.txt");

    // if read is successful, continue.
    if (infile.good() == false) {
        cout << "Error. Unable to open the file." << endl;
        cout << "Please verify the text file and this program are in the same directory and try again." << endl;
    }

    string line;
    vector<string> input_data;

    while (!infile.eof()) {
        getline(infile, line);
        input_data.push_back(line);
    }

    infile.close(); 

    return input_data;
}


int main()
{
    cout << "Cipher\n\n";
    cout << "************************************\n";

    // open file
    vector<string> input_data = open_file();

    // define cipher key and populate with values 
    char key[5][5];
    build_cipher_key(input_data[0], key);


    //print cipher key
    cout << "************************************\n";
    cout << "Contents of 2-D array: " << endl;
    for (unsigned int i = 0; i < 5; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            cout << key[i][j] << ' ';
        }
        cout << endl;
    }


    // iterate over input 
    for (unsigned int line_num = 1; line_num < input_data.size(); line_num++) {

        cout << "************************************\n";
        cout << input_data[line_num].substr(2) << endl;


        // process encrypt input
        if (input_data[line_num][0] == 'E') {

            // iterate through string
            string encrypted_string;
            for (unsigned int i = 2; i < size(input_data[line_num]); i++) {

                // catch 'z' character
                if (input_data[line_num][i] == 'z') {
                    encrypted_string += input_data[line_num][i];
                }

                // check if alpha is in cipher key
                else if (isalpha(input_data[line_num][i])) {
                    char encrypted_char = search_cipher(toupper(input_data[line_num][i]), key);
                    encrypted_string += encrypted_char;
                }

                // append all non-alpha chars 
                else {
                    encrypted_string += input_data[line_num][i];
                }
            }
            cout << "Encrypts to: " << encrypted_string << endl;

        }

        // process decrypt input
        if (input_data[line_num][0] == 'D') {

            // iterate through string
            string decrypted_string;
            for (unsigned int i = 2; i < size(input_data[line_num]); i++) {

                // check if alpha is in cipher key
                if (isalpha(input_data[line_num][i])) {
                    char decrypted_char = search_cipher(input_data[line_num][i], key);
                    decrypted_string += tolower(decrypted_char);
                }

                // append all non-alpha chars 
                else {
                    decrypted_string += input_data[line_num][i];
                }

            }

            cout << "Decrypts to: " << decrypted_string << endl;

        }

    }

    cout << "\nPlease press any key to continue..." << endl;

    return 0;
}
