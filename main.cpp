#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct Element {
    string name;
    int atomicNumber;
    double atomicMass;
};

// Function to load periodic table data from a file
map<int, Element> loadPeriodicTable(const string& filename) {
    ifstream file(filename);
    map<int, Element> periodicTable;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            Element element;
            iss >> element.atomicNumber >> element.name >> element.atomicMass;
            periodicTable[element.atomicNumber] = element;
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return periodicTable;
}

// Function to display element information
void displayElementInfo(const map<int, Element>& periodicTable, int atomicNumber) {
    auto it = periodicTable.find(atomicNumber);

    if (it != periodicTable.end()) {
        cout << "Element: " << it->second.name << endl;
        cout << "Atomic Mass: " << it->second.atomicMass << " u" << endl;
    } else {
        cout << "Element with atomic number " << atomicNumber << " not found in the periodic table." << endl;
    }
}

int main() {
    // Load periodic table data from a file
    map<int, Element> periodicTable = loadPeriodicTable("periodic_table.txt");

    // Get user input for atomic number
    int atomicNumber;
    cout << "Enter the atomic number: ";
    cin >> atomicNumber;

    // Display element information
    displayElementInfo(periodicTable, atomicNumber);


    return 0;
}
