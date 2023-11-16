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
   // Skip the first two lines
   getline(file, line);
   getline(file, line);
   while (getline(file, line)) {
       istringstream iss(line);
       Element element;
       // Use '\t' to separate the columns
       if (!(iss >> element.atomicNumber >> element.name)) {
           cerr << "Error reading line: " << line << endl;
           break;
       }
       // Read the rest of the line for the atomic weight
       char openParen;
       iss >> openParen;
       if (openParen == '(') {
           iss >> element.atomicMass;
           char closeParen;
           iss >> closeParen;
       } else {
           iss.putback(openParen);
           iss >> element.atomicMass;
       }
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
   cout << (it != periodicTable.end() ? "Element: " + it->second.name + "\nAtomic Mass: " + to_string(it->second.atomicMass) + " u" : "Element with atomic number " + to_string(atomicNumber) + " not found in the periodic table.") << endl;
}

int main() {
  // Load periodic table data from a file
  map<int, Element> periodicTable = loadPeriodicTable("periodic_table.txt");

  int atomicNumber;
  char choice;

  do {
      // Get user input for atomic number
      cout << "Enter the atomic number: ";
      cin >> atomicNumber;

      // Display element information
      displayElementInfo(periodicTable, atomicNumber);

      cout << "Do you want to continue? (y/n): ";
      cin >> choice;
  } while (choice == 'y' || choice == 'Y');

  return 0;
}
