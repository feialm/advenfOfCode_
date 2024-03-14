// day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::string> playCombinations = {"AX","AY","AZ","BX","BY","BZ","CX","CY","CZ"};

const std::vector<int> playCombScore = {4,8,3,1,5,9,7,2,6};
/*
const int AX = 4;
const int AY = 8;
const int AZ = 3;

const int BX = 1;
const int BY = 5;
const int BZ = 9;

const int CX = 7;
const int CY = 2;
const int CZ = 6;
*/

int calcScore(const std::string input);


int main()
{
    
    std::string file = "strategyGuide.txt";

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

    std::string line;
    int totScore = 0;

    while (std::getline(inputFile, line)) {
        std::cout << line << "\n";

        std::istringstream iss(line);
        std::string input;
        if (iss >> input) {
            std::cout << line << "\n";
            totScore += calcScore(input);
        }
        else {
            std::cout <<"Wrong type if input\n";
        }
    }

    inputFile.close();

    std::cout << "Total score: " << totScore;

}


int calcScore(const std::string input) {

    int score = 0;

    for (int i = 0; i < std::size(playCombinations); ++i) {
        
        if (playCombinations[i] == input) {
            std::cout << playCombScore[i] << "\n";
            score += playCombScore[i];
            std::cout << "tot score : " << score << "\n";
        }
    }
    return score;
}

