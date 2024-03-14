// day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

int findBuffer(std::vector<char> db);
void display(std::vector<char>db, int number);


int main()
{
    std::string file = "day6.txt";

    // Input file stream object
    std::ifstream inputFile(file);

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return 1; // return an error code
    }
    else {
        std::cout << "File is open: " << file << std::endl;
    }

    std::vector<std::vector<char>> datastreamBuffers;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        datastreamBuffers.push_back(row);
    }

    inputFile.close();

    // i std::vector<char>
    for (auto i : datastreamBuffers) {    
        int numb = findBuffer(i);
        display(i, numb);
    }
}


int findBuffer(std::vector<char> db) {

    const int RANGE = 4;
    
    for (int i = 0; i < db.size() - 4; ++i) {

        std::unordered_set<char> ch;
        int isUnique = 0; // count if sequence of 4 is unique

        for (int j = i; j < i+RANGE; ++j) {

            char currentChar = db[j];

            if(ch.find(currentChar) == ch.end()) {
                isUnique++;
            }
            ch.insert(currentChar);
            
            if (isUnique == RANGE) {
                return j+1;
            }
        }
    }
    return -1;
}


void display(std::vector<char>db, int number) {

    const int MARKER = -1;

    for(auto i : db) {
        std::cout << i;
    }

    if (number == MARKER) {
        std::cout << ": No marker found!\n";
    }
    else {
        std::cout << ": First marker after character "<< number <<"\n";
    }
}
