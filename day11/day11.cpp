// day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cmath>


struct Monkey {
    int id = -1;
    std::vector<int> items = {};
    std::string operation = "";
    std::string val = ""; // val used in operation for new items
    int testDivision = 0; // used as default since you cant divide by 0

    int ifTrue = -2;
    int ifFalse = -3;
    int slotNumber = -1;

    int inspectedItems = 0;

    // Constructor
    Monkey(int id_, std::vector<int> items_, std::string operation_, std::string val_, int testDivision_, int true_, int false_ ) :
    id(id_), items(items_), operation(operation_), val(val_), testDivision(testDivision_), ifTrue(true_), ifFalse(false_){
    
        this->displayMonkey();
    };

    void displayMonkey();
    void displayItems();

    std::vector<int> removeAfterThrown(int i);
};


/**************************************************
*   Functions belonging to struct Monkey
***************************************************/

std::vector<int> Monkey::removeAfterThrown(int remove) {

    auto it = std::find(this->items.begin(), this->items.end(), remove);

    // Erase the element at the specified position
    if (it != this->items.end()) {
        // Erase the element at the found position
        this->items.erase(it);
    }

    return this->items;
}

void Monkey::displayItems() {
    
    for (auto i : this->items) {
        std::cout << i << ",";
    }
}


void Monkey::displayMonkey() {

    std::cout << "Monkey " << this->id << ":\n";
    std::cout << "  Starting items: ";

    this->displayItems();

    std::cout << "\n  Operation: new = old " << this->operation << " " << this->val << "\n";
    std::cout << "  Test: divisible by " << this->testDivision << "\n";
    std::cout << "\tIf true: throw to monkey " << this->ifTrue;
    std::cout << "\n\tIf false: throw to monkey " << this->ifFalse << "\n\n";
}


/**************************************************
*   Functions
***************************************************/


void showInspectedItems(Monkey monkey) {
    std::cout << "Monkey " << monkey.id << " inspected items " << monkey.inspectedItems << " times.\n";
}


void displayRound(std::vector<Monkey> monkeyList) {

    std::cout << "\n";
    for (int i = 0; i < monkeyList.size(); ++i) {
        std::cout << "Monkey " << monkeyList[i].id << ": ";
        monkeyList[i].displayItems();
        std::cout << "\n";
    }
}

int calcOperation(int i, int valOperand, std::string operation) {
    
    const std::vector<std::string> ALL_OPERATIONS = { "+", "-", "*", "/" };
    int operationValue = 0;

    std::cout << "\tWorry level is ";

    if (operation == ALL_OPERATIONS[0]) {
        operationValue = i + valOperand;
        std::cout << "increased by " << valOperand << " to " << operationValue << "\n";
    }
    else if (operation == ALL_OPERATIONS[1]) {
        operationValue = i - valOperand;
        std::cout << "decreased by " << valOperand << " to " << operationValue << "\n";
    }
    else if (operation == ALL_OPERATIONS[2]) {
        operationValue = i * valOperand;
        std::cout << "multiplied by " << valOperand << " to " << operationValue << "\n";
    }
    else if (operation == ALL_OPERATIONS[3]) {
        operationValue = i / valOperand;
        std::cout << "divided by " << valOperand << " to " << operationValue << "\n";
    }
    // divided by 3
    operationValue = static_cast<int>(std::round(double(operationValue / 3)));
    std::cout << "\tMonkey gets bored with item. Worry level is divided by 3 to "<<operationValue <<"\n";

    return operationValue;
}


bool isDivisible(int i, int testDivision) {

    if (i % testDivision == 0) {
        std::cout << "\tCurrent worry level is not divisable by " << testDivision << std::endl;
        return true;
    }
    else {
        std::cout << "\tCurrent worry level not divisable by " << testDivision << std::endl;
        return false;
    }
}



std::vector<int> throwToMonkey(int slotNumber, int integer2throw, std::vector<Monkey> monkeyList) {

    monkeyList[slotNumber].items.push_back(integer2throw);
    
    return monkeyList[slotNumber].items;
}

int findSlotNumber(int integer2throw, int throwTo, std::vector<Monkey> monkeyList) {

    std::cout <<"\tItem with worry level " << integer2throw << " is thrown to monkey " << throwTo << "\n";
    
    for (int i = 0; i < monkeyList.size(); ++i) {
        if (throwTo == monkeyList[i].id) {
            return i;
        }
    }
    return 0;
}


std::vector<Monkey> activateOperation(Monkey m, std::vector<Monkey> monkeyList, int slotNumb) {

    int valOperand = -1;

    for (int i = 0; i < m.items.size(); ++i) {
        std::cout << "  Monkey inspects an item with a worry level of " << m.items[i] << "\n";
        m.inspectedItems++;

        // Determine if it's a word or number
        if (m.val == "old") {
            valOperand = m.items[i];
        }
        else {
            int result = 0;

            // Iterate through each character in the string
            for (char digit : m.val) {
                // Convert the character to its corresponding integer value
                int digitValue = digit - '0';

                // Update the result by multiplying it by 10 and adding the digit value
                result = result * 10 + digitValue;
            }
            valOperand = result;
        }

        m.items[i] = calcOperation(m.items[i], valOperand, m.operation);
        
        if (isDivisible(m.items[i], m.testDivision)) {
            m.slotNumber = findSlotNumber(m.items[i], m.ifTrue, monkeyList);
            monkeyList[m.slotNumber].items = throwToMonkey(m.slotNumber, m.items[i], monkeyList);
            m.items = m.removeAfterThrown(m.items[i]);
        }
        else{
            m.slotNumber = findSlotNumber(m.items[i], m.ifFalse, monkeyList);
            monkeyList[m.slotNumber].items = throwToMonkey(m.slotNumber, m.items[i], monkeyList);
            m.items = m.removeAfterThrown(m.items[i]);
        }
        monkeyList[slotNumb] = m;
        i--;
    }
    return monkeyList;
}

void calcMonkeyBusiness(std::vector<int>inspectItems) {

    for (int i = 0; i < inspectItems.size() - 1; ++i) {
        for (int j = i + 1; j < inspectItems.size(); ++j) {
            if (inspectItems[i] < inspectItems[j]) {
                std::swap(inspectItems[i], inspectItems[j]);
            }
        }
    }

    std::cout << "\n  Monkey businees: " << inspectItems[0] * inspectItems[1] <<"\n";
}


int main()
{
    std::vector<Monkey> monkeyList;
    const int ROUND = 20;

    monkeyList.emplace_back(Monkey(0, { 79,98 }, "*", "19", 23, 2, 3));
    monkeyList.emplace_back(Monkey(1, { 54,65,75,74 }, "+", "6", 19, 2, 0));
    monkeyList.emplace_back(Monkey(2, { 79,60,97 }, "*", "old", 13, 1, 3));
    monkeyList.emplace_back(Monkey(3, { 74 }, "+", "3", 17, 0, 1));

    int roundCounter = 0;

    while (roundCounter < ROUND) {

        for (int i = 0; i < monkeyList.size(); ++i) {
            std::cout << "Monkey " << monkeyList[i].id << ":\n";
            monkeyList = activateOperation(monkeyList[i], monkeyList, i);
        }
        std::cout << "\nAfter round " << roundCounter+1 << ", the monkey are holding items with these worry levels:"<<std::endl;
        displayRound(monkeyList);
        
        roundCounter++;
    }

    std::vector<int> inspectItems;

    for (int i = 0; i < monkeyList.size(); ++i) {
        if (i == 0) {
            std::cout << std::endl;
        }
        showInspectedItems(monkeyList[i]);
        inspectItems.push_back(monkeyList[i].inspectedItems);
    }


    calcMonkeyBusiness(inspectItems);


    return 0;
}
