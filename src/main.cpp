#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>


using namespace std;


void parseFile(const string& filename, const char& separator = '\t') {
    ifstream file(filename);
    if (!file.is_open()) {
        throw ios_base::failure("Error: Unable to open file.");
    }

    string line;    
    vector<string> headers;
    vector<vector<double>> data;

    // Читаем заголовки
    if (getline(file, line)) {
        istringstream headerStream(line);
        string header;
        while (getline(headerStream, header, separator)) {
            headers.push_back(header);
        }
    } else {
        throw runtime_error("Error: File is empty.");
    }
    
    // Читаем данные
    while (getline(file, line)) {
        istringstream dataStream(line);
        vector<double> row;
        string value;
        while (getline(dataStream, value, separator)) {
            try {
                row.push_back(stod(value));
            } catch (const exception& ex) {
                throw runtime_error("Error: Invalid value " + value +
                 " at " + to_string(data.size()) + " row and " +
                 to_string(row.size()) + "column." );
            }
        }
        if (row.size() != headers.size()) {
            throw runtime_error("Error: Mismatch between number of elements and headers at row " + to_string(data.size()) + ".");
        }
        data.push_back(row);
    }

    // Вывод содержимого
    cout << "Headers:" << endl;
    for (string& header : headers) {
        cout << header << separator;
    }
    cout << "\nData:\n";
    for (vector<double>& row : data) {
        for (double value : row) {
            cout << value << separator;
        }
        cout << endl;
    }
}

int main() {
    try {
        const string filename = "src/data.csv"; 
        parseFile(filename, ',');
    } catch (const exception& ex) {
        cerr << ex.what() << endl;
    }
    return 0;
}
