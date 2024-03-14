#include <iostream>
#include <vector>
#include <sstream>
#include <format>
#include <string>
#include <fstream>

int main() {

    std::string file = "list.txt";

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


    std::cout << "Elves, please write the number of calories per meal:\n";
    std::string line;

    int elfIndex = 1;
    int calMax = -1;

    int countElf = 1;
    int elfCal = 0;

    while (std::getline(inputFile, line)) {
        std::cout << line << "\n";
        
        if (elfCal > calMax) {
            calMax = elfCal;
            elfIndex = countElf;
        }
       
        if (line.empty()) {

            elfCal = 0;
            countElf++;
        }
        else {
            // Parse the line and add values to the current Elf's inventory
            std::istringstream iss(line);
            int value;
            if (iss >> value) {
                elfCal += value;
            }
        }
    }


    inputFile.close();


    // Display what elf is carrying the most calories
    // Display how many calories that elf is carrying
    std::cout << std::format("\nElf {} is carrying the most calories.\nThe elf is carrying {} calories\n", elfIndex, calMax);


    return 0;
}
