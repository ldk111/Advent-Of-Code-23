#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <math.h>
#include <algorithm>

int main() {

    std::string inputLine;
    std::ifstream inputText("day4.txt");

    std::vector<std::vector<int>> prizeTotal;
    std::vector<int> prizeLine;

    std::vector<std::vector<int>> scratchTotal;
    std::vector<int> scratchLine;

    while (getline(inputText, inputLine)) {

        int i = 0;

        while (inputLine[i] != ':') {
            i++;
        }

        while (inputLine[i] != '|') {
            
            if (isdigit(inputLine[i])) {
                int num = 0;
                while (isdigit(inputLine[i])) {
                    num *= 10;
                    num += inputLine[i] - '0';
                    i++;
                }
                prizeLine.push_back(num);
            }
            i++;
        }
        prizeTotal.push_back(prizeLine);
        prizeLine.clear();

        while (i < inputLine.size()) {
            if (isdigit(inputLine[i])) {
                int num = 0;
                while (isdigit(inputLine[i])) {
                    num *= 10;
                    num += inputLine[i] - '0';
                    i++;
                }
                scratchLine.push_back(num);
            }
            i++;
        }
        scratchTotal.push_back(scratchLine);
        scratchLine.clear();
    }

    double score = 0.0;

    for (int i = 0; i < prizeTotal.size(); i++) {
        int matches = 0;
        for (int j = 0; j < prizeTotal[i].size(); j++) {
            if(std::find(scratchTotal[i].begin(), scratchTotal[i].end(), prizeTotal[i][j]) != scratchTotal[i].end()) {
            matches++;
            }
        }
        if (matches > 0) {
            score += std::pow(2.0, matches - 1);
        }
    }

    std::cout << score << std::endl;

    std::vector<int> cards(199, 1);

    for (int i = 0; i < prizeTotal.size(); i++) {
        int matches = 0;
        for (int j = 0; j < prizeTotal[i].size(); j++) {
            if(std::find(scratchTotal[i].begin(), scratchTotal[i].end(), prizeTotal[i][j]) != scratchTotal[i].end()) {
            matches++;
            }
        }
        for (int k = 0; k < matches; k++) {
            cards[i+k+1] += cards[i];
        }
    }

    int totalCards = 0;

    for (auto i: cards) {
        totalCards += i;
    }

    std::cout << totalCards << std::endl;

return 0;
}

