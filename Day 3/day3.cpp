#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h> //isdigit
#include <vector>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

bool check_char(std::vector<std::vector<char>> matrix, int i, int j, bool part_number) {

        if (!part_number) {
            if (!isdigit(matrix[i][j]) && matrix[i][j] != '.') {
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }

int part_one() {

    std::string myText;
    std::ifstream myReadFile("day3.txt");

    std::vector<std::vector<char>> matrix;

    while (getline(myReadFile, myText)) {
        std::vector<char> line(myText.begin(), myText.end());
        matrix.push_back(line);
    }
    int tot = 0;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            char curr_char = matrix[i][j];

            if (isdigit(curr_char)) {
                bool part_number = false;
                int j_prime = j;
                int len_num = 1;
                int part_tot = 0;

                while (j_prime + 1 < matrix[i].size() && isdigit(matrix[i][j_prime + 1])) {
                    len_num++;
                    j_prime++;
                }

                //check top corners
                if (i != 0) {
                    if (j != 0) {
                        part_number = check_char(matrix, i - 1, j - 1, part_number);
                    }
                    if (j + len_num < matrix[i - 1].size()) {
                        part_number = check_char(matrix, i - 1, j + len_num, part_number);
                    }
                }

                //check bottom corners
                if (i != matrix.size() - 1) {
                    if (j != 0) {
                        part_number = check_char(matrix, i + 1, j - 1, part_number);
                    }

                    if (j + len_num < matrix[i + 1].size()) {
                        part_number = check_char(matrix, i + 1, j + len_num, part_number);
                    }
                }

                //check middle sides
                if (j != 0) {
                    part_number = check_char(matrix, i, j - 1, part_number);
                }
                if (j + len_num < matrix[i].size()) {
                    part_number = check_char(matrix, i, j + len_num, part_number);
                }

                //check middle top and middle bottom
                for (int k = 0; k < len_num; k++) {
                    if (i != 0) {
                        part_number = check_char(matrix, i - 1, j + k, part_number);
                    }
                    if (i != matrix.size() - 1) {
                        part_number = check_char(matrix, i + 1, j + k, part_number);
                    }
                }

                if (part_number) {
                    for (int l = 0; l < len_num; l++) {
                        int offset = (int)pow(10, len_num - l - 1);
                        part_tot += (matrix[i][j + l] - '0') * offset;
                    }
                    tot += part_tot;
                }
                j = j_prime;
            }
        }

    }
    std::cout << "Part 1 Total: \n";
    std::cout << tot;
    std::cout << "\n";
    return tot;
}

int trace_number(std::vector<std::vector<char>> matrix, int i, int j){
    if (isdigit(matrix[i][j])) {
        int j_prime = j;

        while (j_prime > 0 && isdigit(matrix[i][j_prime-1])) {
            j_prime--;
        }

        int j_begin = j_prime;

        while (j_prime + 1 < matrix[i].size() && isdigit(matrix[i][j_prime + 1])) {
            j_prime++;
        }

        int num = 0;

        for (int k = j_begin; k < j_prime + 1; k++) {
            num = num * 10 + matrix[i][k] - '0';
        }

        return num;
    }

    return 0;

}

void check_duplicates(int check_1, int check_2, int check_3, std::vector<int> & nums){
    if (check_1 == check_2 && check_2 == check_3) {
        nums.push_back(check_1);
    }
    else {
        if (check_3 != check_1 && check_3 != check_2 && check_3 != 0) {
            nums.push_back(check_3);
        }
        else {
            nums.push_back(check_1);
            nums.push_back(check_2);
        }
    }
}

int part_two() {
    std::string myText;
    std::ifstream myReadFile("day3.txt");

    std::vector<std::vector<char>> matrix;

    while (getline(myReadFile, myText)) {
        std::vector<char> line(myText.begin(), myText.end());
        matrix.push_back(line);
    }
    int tot = 0;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {

            char curr_char = matrix[i][j];

            if (curr_char == '*') {

                std::vector<int> nums;
                int num_one = 0;
                int num_two = 0;

                int check_1 = 0;
                int check_2 = 0;
                int check_3 = 0;

                //check top
                if (i != 0) {
                    if (j != 0) {
                        check_1 = trace_number(matrix, i - 1, j - 1);
                    }
                    if (j + 1 < matrix[i - 1].size()) {
                        check_2 = trace_number(matrix, i - 1, j + 1);
                    }
                    check_3 = trace_number(matrix, i - 1, j);
                }

                check_duplicates(check_1, check_2, check_3, nums);

                check_1 = 0;
                check_2 = 0;
                check_3 = 0;

                //check bottom
                if (i != matrix.size() - 1) {
                    if (j != 0) {
                        check_1 = trace_number(matrix, i + 1, j - 1);
                    }

                    if (j + 1 < matrix[i + 1].size()) {
                        check_2 = trace_number(matrix, i + 1, j + 1);
                    }
                    check_3 = trace_number(matrix, i + 1, j);
                }

                check_duplicates(check_1, check_2, check_3, nums);

                //check middle sides
                if (j != 0) {
                    nums.push_back(trace_number(matrix, i, j - 1));
                }
                if (j + 1 < matrix[i].size()) {
                    nums.push_back(trace_number(matrix, i, j + 1));
                }
                int count = 0;
                for (auto & k :nums){
                    if (k != num_one && num_one == 0) {
                        num_one = k;
                    }
                    else {
                        if (k != num_two && num_two == 0) {
                            num_two = k;
                        }
                    }
                    if (k != 0) {
                        count++;
                    }
                }
                if (count > 2) {
                    num_one, num_two = 0;
                }

                tot += num_one * num_two;
                nums.clear();
            }
        }

    }
    std::cout << "Part 2 Total: \n";
    std::cout << tot;
    std::cout << "\n";
    return tot;
}


int main() {

    int tot_one = part_one();

    int tot_two = part_two();

}