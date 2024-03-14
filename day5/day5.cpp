// day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<char>> performMove(std::vector<int> commandRow, std::vector<std::vector<char>> cratesClean_);

void displayInitial(std::vector<std::vector<char>> cc);
void displayMove(std::vector<std::vector<char>> cc);

int main()
{
    std::string file = "day5.txt";

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

    std::vector<std::vector<char>> crates;
    std::vector<std::vector<char>> moves;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        //crates.push_back(row);
        if (!row.empty() && row[0] != 'm') {
            crates.push_back(row);
        }
        else if (!row.empty() && row[0] == 'm') {
            moves.push_back(row);
        }
    }


    displayInitial(crates);


    auto cRow = crates.size();
    std::vector<char> cCol = crates[cRow-1];

    std::vector<int> slots;
    
    // count how many stacks
    int stacks = 0;
    for (int i = 0; i < cCol.size(); ++i) {
       if (isdigit(cCol[i])) {
            stacks++;
            slots.push_back(i);
       }
    }

    std::vector<std::vector<char>> cratesClean;
    
    for (const auto& row : crates) {
        std::vector<char>cratesRow(stacks);
        fill(cratesRow.begin(), cratesRow.end(), ' ');

        int i = 0;
        for (auto& s : slots) {
            if (row[s] != ' ' && row[s] != '[' && row[s] != ']') {
                cratesRow[i] = row[s];
            }
            ++i;
        }
        cratesClean.push_back(cratesRow);
    }

    // save moves
    std::vector<std::vector<int>> commandMove;

    for (const auto& row : moves) {
        std::vector<int> howmany_from_to;
        for (auto col : row) {
            if (isdigit(col)) {
                //std::cout << col << " ";
                int c = int(col - '0');
                howmany_from_to.push_back(c);
            }
        }
        commandMove.push_back(howmany_from_to);
        //std::cout << std::endl;
    }

    for (int i = 0; i < commandMove.size(); i++) {    

        std::vector<int> desiredRow = commandMove[i];
        cratesClean = performMove(desiredRow,cratesClean);
        displayMove(cratesClean);
    }

}


void displayInitial(std::vector<std::vector<char>> cc) {

    std::cout << "\nInitial state\n";

    for (const auto& row:cc) {
        for (const auto& col: row) {
            std::cout << col;
        }
        std::cout << "\n";
    }
}




void displayMove(std::vector<std::vector<char>> cc) {

    std::cout << "\nMove\n";
    
    for (const auto& row : cc) {
        for (const auto& col : row) {
            if (isdigit(col)) {
                std::cout << " " << col << " ";
            }
            else if(col != ' ' && !isdigit(col)) {
               std::cout << "[" << col << "]";
            }
            else {
                std::cout << "   ";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


std::vector<std::vector<char>> performMove(std::vector<int> commandRow, std::vector<std::vector<char>> cratesClean_) {

    const int howmany = commandRow[0];
    const int from = commandRow[1];
    const int to = commandRow[2];

    auto cRow = cratesClean_.size();
    auto cCol = cratesClean_[cRow - 1].size();

    for (int i = 0; i < cCol; ++i) {
        
        std::vector<char> move;

        if (int(cratesClean_[cRow - 1][i] - '0') == from) {

            int counter = 0;

            for (int j = 0; j < cRow; ++j) {
                if (cratesClean_[j][i] != ' ' && counter < howmany) {
                    move.push_back(cratesClean_[j][i]);
                    cratesClean_[j][i] = ' ';
                    counter++;
                }
            }

            for (int k = 0; k < cCol; ++k) {
                if (int(cratesClean_[cRow - 1][k] - '0') == to) {
                    int counter2 = 0;
                    for (int m = cRow-1; m >= 0; --m) {
                        if (cratesClean_[m][k] == ' ' && counter2 < howmany) {
                            cratesClean_[m][k] = move[counter2];
                            counter2++;
                        }
                    }

                    while(counter2 < howmany){
                        std::vector<char> extraRow(cRow);
                        fill(extraRow.begin(), extraRow.end(), ' ');
                        cratesClean_.insert(cratesClean_.begin(), extraRow);
                        cratesClean_[0][k] = move[counter2];
                        counter2++; 
                    }

                }
            }
        }
    }
    return cratesClean_;
}




