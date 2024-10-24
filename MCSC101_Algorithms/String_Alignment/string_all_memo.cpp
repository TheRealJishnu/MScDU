#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Function to compute the alignment cost of two strings using memoization with a DP vector
int alignStrings(const string& X, const string& Y, int gapCost, int i, int j, vector<vector<int>>& memo) {
    // Base case: If we reach the beginning of either string
    if (i == 0) return j * gapCost;  // All gaps in X
    if (j == 0) return i * gapCost;  // All gaps in Y

    // Check if the result is already computed
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // Mismatch cost
    int mismatchCost = (X[i - 1] == Y[j - 1]) ? 0 : 1;

    // Recursively calculate the minimum cost
    int cost = min({
        alignStrings(X, Y, gapCost, i - 1, j, memo) + gapCost,    // Gap in Y
        alignStrings(X, Y, gapCost, i, j - 1, memo) + gapCost,    // Gap in X
        alignStrings(X, Y, gapCost, i - 1, j - 1, memo) + mismatchCost  // Mismatch
    });

    // Memoize the result
    memo[i][j] = cost;
    return cost;
}

int main() {
    string X, Y;
    int gapCost;

    // Input the two strings and the gap cost
    cout << "Enter the first string (X): ";
    cin >> X;
    cout << "Enter the second string (Y): ";
    cin >> Y;
    cout << "Enter the gap cost: ";
    cin >> gapCost;

    // Create a memoization table initialized to -1
    vector<vector<int>> memo(X.size() + 1, vector<int>(Y.size() + 1, -1));

    // Compute the alignment cost
    int cost = alignStrings(X, Y, gapCost, X.size(), Y.size(), memo);
    cout << "Minimum alignment cost: " << cost << endl;

    return 0;
}
