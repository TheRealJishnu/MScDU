#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // Open the file in append mode (std::ios::app)
    ofstream outfile("dp_data.txt", ios::app);

    if (!outfile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    // Example data for memoization and tabulation (replace this with your actual data)
    vector<int> memoizationData = {10, 20, 30, 40, 50};  // Example memoization data
    vector<int> tabulationData = {15, 25, 35, 45, 55};   // Example tabulation data

    // Check if both vectors have the same size
    // if (memoizationData.size() != tabulationData.size()) {
    //     cerr << "Data sizes do not match!" << endl;
    //     return 1;
    // }

    // Append data into the file (no need to write headers each time)
    for (size_t i = 0; i < memoizationData.size(); ++i) {
        outfile << i << "\t\t\t" << memoizationData[i] << "\t\t\t" << tabulationData[i] << endl;
    }

    // Close the file after writing
    outfile.close();

    cout << "Data appended to dp_data.txt successfully!" << endl;

    return 0;
}
