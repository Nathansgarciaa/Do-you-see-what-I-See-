#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MonoStack.h" // Assuming MonoStack.h contains the definition of MonoStack class
using namespace std;

class SpeakerView { // Changed class name from Speakerview to SpeakerView
public:
    SpeakerView() = default;

    // Constants for maximum rows and columns
    static const int MAX_ROWS = 1000; // just to set the 2d array, need amounts to declare it
    static const int MAX_COLS = 100;  

    void ProcessFile(string file) {
        ifstream f(file);
    
        if (!f.is_open()) {
            cerr << "Could not open file: " << file << endl;
            return;
        }

        double data[MAX_ROWS][MAX_COLS]; // create 2d array to be read in
        int colsInRow[MAX_ROWS] = {0}; // Initialize all elements to 0
        int totalRows = 0;

        string line; // line to take in the rows

        // Read data from the file line by line
        while (getline(f, line) && totalRows < MAX_ROWS) {
            istringstream iss(line); // parses the lines

            double value;
            int colIndex = 0;

            // Read values from the current line and store them in data array
            while (iss >> value && colIndex < MAX_COLS) {
                data[totalRows][colIndex++] = value;
            }

            colsInRow[totalRows] = colIndex;

            if (colIndex > 0) {
               totalRows++;
            }
        }

        f.close(); // Close the file after reading

        // Process each column
        for (int i = 0; i < colsInRow[0]; i++) { // Assuming we're interested in the columns of the first row
            MonoStack<double> stack(totalRows, 'd'); // Assuming 'd' is a valid argument for the MonoStack constructor
            
            // Iterate through each row and push values onto the stack if they are greater than the previous ones
            for (int j = 0; j < totalRows; j++) {
                if (i < colsInRow[j]) { // Checks if the column exists in the row
                    if(data[j][i] > stack.peek()){
                        stack.push(data[j][i]);
                    }
                }
            }

            // Output the stack content for each column
            cout << "There are " << stack.getSize() << " people who can see in column " << i << ". Their heights are: ";
            while (!stack.isEmpty()) {
                cout << stack.pop() << " ";
            }
            cout << endl;
        }
    }
};
