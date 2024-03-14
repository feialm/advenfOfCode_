// day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <format>


int findPriority(char item);


/*
Lowercase item types a through z have priorities 1 through 26.
Uppercase item types A through Z have priorities 27 through 52.
*/


const std::vector<char> charPriorityScore = {'a','b','c','d','e','f','g','h',
'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
'R','S','T','U','V','W','X','Y','Z'};

char findSharedItem(std::string rucksack);


int main()
{

    std::vector<std::string>rucksacks;
    std::vector<int> priorityValue; // priority value for each rucksack
    std::vector<char> sharedItem; // shared item in each rucksack

    std::string file = "rucksacks.txt";

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
        std::cout << line << "\n";

        std::istringstream iss(line);
        std::string input;
        if (iss >> input) {
            rucksacks.push_back(input);
        }
        else {
            std::cout << "Wrong type if input\n";
        }
    }

    int sumPriorities = 0;

    // loopa igenom rucksacks, printa ut priority score för en sådan rucksack
    for (int i = 0; i < rucksacks.size(); ++i) {
        
        char item = findSharedItem(rucksacks[i]);
        int priority = findPriority(item);

        std::cout << std::format("Rutsack {} has shared item {} and priority {}\n",i+1, item, priority);
        sumPriorities += priority;

    }

    std::cout << std::format("Total priority: {}", sumPriorities);

}


char findSharedItem(std::string rucksack) {

    std::string comparment1 = rucksack.substr(0, rucksack.length()/2);
    std::string comparment2 = rucksack.substr(rucksack.length()/ 2);

    //std::cout << "--------------------------------------\n" << comparment1 << "\n" << comparment2 << "\n";

    char sharedItem = '1'; //store a number as a default char since the the items are letters 

    for(auto& comparment1_:comparment1){

        // Print current character 
        //std::cout << comparment1[i] << " ";

        for (auto& comparment2_ : comparment2){
            
            if (comparment1_ == comparment2_) {
                sharedItem = comparment1_;
            }
        }
    }
    return sharedItem;
}



int findPriority(char item){
 
    int k = 0; //default 0
    for (int j = 0; j < charPriorityScore.size(); ++j) {
        if (item == charPriorityScore[j]) {
            k = j;
            break;
        }
    }

    return k+1;// slot number is the priority score, +1 since slotnumber starts at 0
}