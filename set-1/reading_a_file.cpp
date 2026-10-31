#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // Open the file (relative path = same folder as the executable)
    ifstream file("input_breaking_repeating_xor.txt");   // change to your actual filename

    if (!file.is_open()) {
        cerr << "Error: Could not open the file!\n";
        return 1;
    }

    // Method 1: Read the entire file into a single string
    string content((istreambuf_iterator<char>(file)),
                         istreambuf_iterator<char>());

    cout << "File content:\n" << content << endl;

    // Method 2: Read line by line (useful for large files)
    /*
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    */

    file.close();   // optional – destructor does it automatically
    return 0;
}