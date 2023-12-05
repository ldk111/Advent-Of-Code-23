// Day 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <unordered_map>

using namespace std;

int PartOne();
int PartTwo();

int main() {   

    PartOne();
    PartTwo();

    return 0;
}


int PartOne() {
    
    std::cout << "Part 1 \n";

    string myText;

    ifstream MyReadFile("day1.txt");

    int tot = 0;

    while (getline(MyReadFile, myText)) {

        int first_digit = 0;
        int curr_digit = 0;

        //std::cout << myText + "\n";

        for (int i = 0; i < myText.length(); i++) {

            if (isdigit(myText[i])) {

                 curr_digit = myText[i] - '0'; 

            }
        }

        if (first_digit == 0) {

            first_digit = curr_digit;

        }

        tot += first_digit * 10 + curr_digit;

        //std::cout << first_digit * 10 + curr_digit;
        //std::cout << "\n";

    }

    MyReadFile.close();

    std::cout << tot;
    std::cout << "\n";

    return 0;
}

int PartTwo() {

    std::cout << "Part 2 \n";

    string myText;

    ifstream MyReadFile("day1.txt");

    int tot = 0;

    std::unordered_map<std::string, int> char_map =
    {
    {"one", 3},
    {"two", 3},
    {"three", 5},
    {"four", 4},
    {"five", 4},
    {"six", 3},
    {"seven", 5},
    {"eight", 5},
    {"nine", 4}
    };

    std::unordered_map<std::string, int> val_map =
    {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
    };

    while (getline(MyReadFile, myText)) {

        int i = 0;
        int first_digit = 0;
        int curr_digit = 0;

        //std::cout << myText + "\n";

        while (i < myText.length()) {

            if (isdigit(myText[i])) {


                curr_digit = myText[i] - '0';

            }

            else {

                for (auto & it : char_map) {

                    int nchar = it.second;
                    int value = it.second;

                    if (myText[i] == it.first[0] and myText.substr(i, nchar) == it.first) {

                        curr_digit = val_map[it.first];

                    }
                }
            }
           
            if (first_digit == 0) {

                first_digit = curr_digit;

            }

            i += 1;

        }
        
        tot += first_digit * 10 + curr_digit;

        //std::cout << first_digit * 10 + curr_digit;
        //std::cout << "\n";

    }

    MyReadFile.close();

    std::cout << tot;
    std::cout << "\n";

    return 0;
}
