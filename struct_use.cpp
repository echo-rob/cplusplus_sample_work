/*
    Start date:		2020-Nov-20
*/

#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// define Winner struct 
struct winner {
    string name;
    double top_score = 0;
} Winner;

// define Driver struct
struct diver {
    string name;
    double difficulty = 0;
    vector<double> raw_scores;
    double total_score = 0;
} Diver;

void print_winner() {

    cout << "\n";
    cout << "Winner: " << Winner.name << endl;
    cout << "Final score: " << Winner.top_score << endl;
}

void compare_scores() {

    // if current score if higher than previous score, current score is top score 
    if (Diver.total_score > Winner.top_score) {
        Winner.top_score = Diver.total_score;
        Winner.name = Diver.name;
    }
}

void print_diver_details() {

    // print diver details for each column
    cout << setw(12) << left << Diver.name << setw(12) << left << fixed << setprecision(1) << Diver.difficulty;

    for (unsigned i = 0; i < Diver.raw_scores.size(); i++) {

        cout << setw(4) << right << fixed << setprecision(1) << Diver.raw_scores[i] << ' '; // setw() needs to reflect score size, not overall size of column
    }

    cout << setw(7) << right << Diver.total_score << endl;
}

void calculate_points() {
    // skip the first and last index from score list per reqs
    double score_sum = 0;
    unsigned i = 1;
    while (i < Diver.raw_scores.size() - 1) {
        score_sum += Diver.raw_scores[i];
        i += 1;
    }

    // calculate total score 
    Diver.total_score = score_sum * Diver.difficulty;
}

void sort_scores() {
    // bubble sort the diver's scores 
    double temp_num;
    for (unsigned i = 0; i < Diver.raw_scores.size(); i++) {

        for (unsigned j = i + 1; j < Diver.raw_scores.size(); j++) {

            if (Diver.raw_scores[i] > Diver.raw_scores[j]) {
                temp_num = Diver.raw_scores[i];
                Diver.raw_scores[i] = Diver.raw_scores[j];
                Diver.raw_scores[j] = temp_num;
            }
        }
    }
}

void parse_line(string line) {

    string name;
    vector<double> decimals;

    // iterate through line. parse name and decimal locations
    for (unsigned i = 0; i < line.size(); i++) {

        // parse diver name 
        if (isalpha(line[i])) {
            name += line[i];
        }

        // if char is period, get the prior 2 numbers, and subsequent 2 numbers 
        if (line[i] == '.') {
            
            int dec_begin = i - 2; 
            string parsed_decimal = line.substr(dec_begin, 4);

            // convert from string to decimal and add to vector 
            double decimal_value = stod(parsed_decimal);
            decimals.push_back(decimal_value);

        }
    }

    // assign values to variables in struct 
    Diver.name = name;
    Diver.difficulty = decimals[0];

    // skip the difficulty from score list and assign scores to new vector 
    vector<double> scores;
    for (unsigned i = 1; i < decimals.size(); i++) {
        scores.push_back(decimals[i]);
    }

    // assign values to struct
    Diver.raw_scores = scores;
}

vector<string> open_file() {

    // open file
    ifstream infile("mp7divers.txt");

    // if read is successful, continue.
    if (infile.good() == false) {
        cout << "Error. Unable to open the file." << endl;
        cout << "Please verify the text file and this program are in the same directory and try again." << endl;
    }

    string line;
    vector<string> input_data;

    while (!infile.eof()) {
        getline(infile, line);
        if (!line.empty()) {
            input_data.push_back(line);
        }
    }

    infile.close();

    return input_data;
}

int main() {

    cout << "Struct Use\n" << endl;

    // open file
    vector<string> infile = open_file();

    // print columns to console 
    cout << setw(12) << left << "Name"
        << setw(13) << left << "Difficulty"
        << setw(45) << left << "Sorted Scores"
        << setw(7) << left << "Points"
        << endl;
    cout << string(76, '-') << setw(76) << endl;

    // iterate over values from input data
    for (unsigned i = 1; i < infile.size(); i++) {

        // parse the line into its various pieces
        parse_line(infile[i]);

        //sort the raw scores 
        sort_scores();

        //calculate the final score for each diver 
        calculate_points();

        //print divers name/score list/final score to console
        print_diver_details();

        //compare previous and current divers' scores
        compare_scores();
    }

    //print winner to console 
    print_winner();

    cout << "\nPlease press any key to continue...\n\n";

    return 0;
}