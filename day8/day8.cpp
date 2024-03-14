// day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int treesOnEdge(std::vector<std::vector<int>> t );

int visibleTrees(std::vector<std::vector<int>> t);

int compareHeight(std::vector<std::vector<int>> t, int r, int c);


int main()
{
    std::string file = "day8.txt";

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

    std::vector<std::vector<int>> trees;
    std::string line;

    while (std::getline(inputFile, line)) {
        
        std::vector <int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }  
        trees.push_back(row);
    }

    inputFile.close();

    int tot = treesOnEdge(trees);

    tot += visibleTrees(trees);

    std::cout << "A total of " << tot << " trees are visible from outside the grid\n\n";

    std::cout << "Answer: " << tot <<"\n";

    return 0;
}



int treesOnEdge(std::vector<std::vector<int>> t) {

    // Calculate the number of rows and columns
    int numRows = t[0].size();
    int numCols = t.size();

    return (2*numRows + 2*numCols) - 4;
}


int compareHeight(std::vector<std::vector<int>> t, int r, int c){

    bool isVisible_r_left = false;
    bool isVisible_r_right = false;
    bool isVisible_c_top = false;
    bool isVisible_c_bottom = false;

    // rows
    for (int i = 0; i < r; ++i) {
        if (t[r][i] < t[r][c]) {
            isVisible_r_left = true;
        }
        else {
            isVisible_r_left = false;
        }
    }
 
    for (int i = t.size()-1; i > r; --i) {
        if (t[r][i] < t[r][c]) {
            isVisible_r_right < true;
        }
        else {
            isVisible_r_right = false;
        }
    }

    //cols
    for (int i = 0; i < c; ++i) {
        if (t[i][c] < t[r][c]) {
            isVisible_c_top = true;
        }
        else {
            isVisible_c_top = false;
        }
    }

    for (int i = t.size()-1; i > c; --i) {
        if (t[i][c] < t[r][c]) {
            isVisible_c_bottom = true;
        }
        else {
            isVisible_c_bottom = false;
        }
    }

    if (isVisible_r_left == true || isVisible_r_right == true || isVisible_c_top == true || isVisible_c_bottom == true) {
        return 1;
    }
    else {
        return 0;
    }

}


int visibleTrees(std::vector<std::vector<int>> t) {

    int count = 0;

    for (int i = 1; i < t.size()-1; ++i) {
        for (int j = 1; j < t.size()-1; ++j) {

            // iterate through trees that are not on the edges
            count += compareHeight(t,i,j);
        }
    }
    return count;
}