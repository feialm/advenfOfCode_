// day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>


// Structure to represent a file or directory
struct FileSystemItem {
    std::string name = NULL;
    int size = -1;
    std::vector<FileSystemItem> vec = {};

    // constuctor
    FileSystemItem(std::string n, int s, std::vector<FileSystemItem> v) : name(n), size(s), vec(v) {}
};


int main()
{
    std::string file = "day7.txt";

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

    const std::string COMMAND = "$";
    const std::string DIR = "dir";
    const std::string LS = "ls";
    const std::string CD = "cd";
    const std::string OUT = "..";
    const std::string OUTERMOST = "/";
    const std::string EMPTY = "";


    std::vector<FileSystemItem> fileSystem;

    while (std::getline(inputFile, line)) {

        std::istringstream iss(line);
        std::string arg1, arg2, arg3;
        
        iss >> arg1 >> arg2 >> arg3;

        
    }

    inputFile.close();



    return 0;

}


