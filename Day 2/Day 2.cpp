// Day 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <unordered_map>

void PartOne();
void PartTwo();


using namespace std;

int main() {

    PartOne();
    PartTwo(); 

    return 0;
}

void PartOne() {

    std::unordered_map<char, int> cube_map =
    {
    {'r', 12},
    {'g', 13},
    {'b', 14}
    };

    std::unordered_map<char, int> length_map =
    {
    {'r', 3},
    {'g', 5},
    {'b', 4}
    };

    string myText;
    ifstream MyReadFile("day2.txt");
    int tot = 0;

    while (getline(MyReadFile, myText)) {

        int game_id = 0;
        bool valid_game = true;
        int i = 5;

        while (myText[i] != ':') {

            game_id = game_id * 10;
            game_id += myText[i] - '0';
            i += 1;
        }

        i += 2;

        while (i < myText.length()) {
            int n_colour = 0;

            while (myText[i] != ' ') {
                n_colour = n_colour * 10;
                n_colour += myText[i] - '0';
                i += 1;
            }

            i += 1;

            if (cube_map[myText[i]] < n_colour) {
                valid_game = false;
            }

            i += length_map[myText[i]];

            i += 2;
        }

        if (valid_game) {
            tot += game_id;
        }

    }

    MyReadFile.close();

    std::cout << "TOTAL = ";
    std::cout << tot;

}

void PartTwo() {
    std::unordered_map<char, int> cube_map =
    {
    {'r', 0},
    {'g', 0},
    {'b', 0}
    };

    std::unordered_map<char, int> length_map =
    {
    {'r', 3},
    {'g', 5},
    {'b', 4}
    };

    string myText;
    ifstream MyReadFile("day2.txt");
    int tot = 0;

    while (getline(MyReadFile, myText)) {

        for (auto& it : cube_map) {
            it.second = 0;
        }

        int i = 5;

        while (myText[i] != ':') {

            i += 1;
        }

        i += 2;

        while (i < myText.length()) {

            int n_colour = 0;

            while (myText[i] != ' ') {
                n_colour = n_colour * 10;
                n_colour += myText[i] - '0';
                i += 1;
            }

            i += 1;

            cube_map[myText[i]] = max(cube_map[myText[i]], n_colour);

            i += length_map[myText[i]];

            i += 2;
        }

        int power = 1;

        for (auto& it : cube_map) {
            power = power * it.second;
        }
        
        tot += power;

    }
    
    MyReadFile.close();

    std::cout << "TOTAL POWER = ";
    std::cout << tot;
}