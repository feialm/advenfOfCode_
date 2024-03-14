// day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <format>

std::pair<std::string, std::string> identifyPair(std::string assignmentPair, char c_);

int findMax(int a, int b, int c, int d);

std::vector<int> assignmentRanges(int a, int b, int c, int d);

void display(std::vector<std::vector<int>> vec, int maxVal);

int main()
{

    std::vector<std::string> assigment;
    std::vector<std::vector<int>> allAssingmentsPairs;

    std::string file = "day4.txt";

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

    while (std::getline(inputFile, line)) {
        //std::cout << line << "\n";

        std::istringstream iss(line);
        std::string input;
        if (iss >> input) {
            assigment.push_back(input);
        }
        else {
            std::cout << "Wrong type of input\n";
        }
    }

    char comma = ',';
    char dash = '-';
    int maxVal = 1;

    for (auto& assigment_ : assigment) {
        auto pairs = identifyPair(assigment_, comma);
        std::string value1 = pairs.first;
        std::string value2 = pairs.second;

        auto range1 = identifyPair(value1, dash);
        std::string range11 = range1.first;
        std::string range12 = range1.second;
 
        auto range2 = identifyPair(value2, dash);
        std::string range21 = range2.first;
        std::string range22 = range2.second;

        int currentMax = findMax(std::stoi(range11), std::stoi(range12), std::stoi(range21), std::stoi(range22));
        
        if (maxVal < currentMax) {
            maxVal = currentMax;
        }

        allAssingmentsPairs.push_back(assignmentRanges(std::stoi(range11), std::stoi(range12), std::stoi(range21), std::stoi(range22)));
    }

    display(allAssingmentsPairs, maxVal);

}


std::pair<std::string, std::string> identifyPair(std::string assignmentPair, char c_) {

    char c = c_;
    std::string pair1, pair2 = "";

    auto it = std::find(assignmentPair.begin(), assignmentPair.end(), c);

    if (it != assignmentPair.end()) {
        size_t index = std::distance(assignmentPair.begin(), it);

        // index-1 and index+1, remove ,
        pair1 = assignmentPair.substr(0, index);
        //std::cout <<"Pair 1: " << pair1 << "\n";
        pair2 = assignmentPair.substr(index+1);
        //std::cout << "Pair 2: " << pair2 << "\n";
    }
    return std::make_pair(pair1, pair2);
}



int findMax(int a, int b, int c, int d) {
    int max = a;

    if (b > max) {
        max = b;
    }

    if (c > max) {
        max = c;
    }

    if (d > max) {
        max = d;
    }

    return max;
}


std::vector<int> assignmentRanges(int a, int b, int c, int d) {

    std::vector<int> v = {a, b, c, d};

    return v;
}


void display(std::vector<std::vector<int>> vec, int maxVal) {

    int rangeFullyContainOther = 0;

    for (std::size_t i = 0; i < vec.size(); ++i) {  
        for (int k = 1; k <= maxVal; ++k){           
            if (vec[i][0]<=k && k <= vec[i][1]) {
                std::cout << k;
            }
            else {
                std::cout << ".";
            }
        }

        std::cout <<std::format(" {}-{}\n", vec[i][0], vec[i][1]);

        for (int k = 1; k <= maxVal; ++k) {

            if (vec[i][2] <= k && k <= vec[i][3]) {
                std::cout << k;
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::format(" {}-{}\n\n", vec[i][2], vec[i][3]);


        if (vec[i][0] <= vec[i][2] && vec[i][1] >= vec[i][3]) {
            ++rangeFullyContainOther;
        }
        if (vec[i][2] >= vec[i][0] && vec[i][3] <= vec[i][1]) {
            ++rangeFullyContainOther;
        }
    }

    std::cout << std::format("In {} assignment pairs does one range fully contain the other range\n\n", rangeFullyContainOther);
}