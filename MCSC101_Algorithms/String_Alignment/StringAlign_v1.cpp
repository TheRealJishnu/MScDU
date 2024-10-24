#include <bits/stdc++.h>
using namespace std;

void stringAlign(vector<vector<int>>& dp, string x, string y){
    int delta = 2;

    vector<int> ifvow(26, 0);
    string vows = "aeiou";
    for(auto e : vows){
        ifvow[e - 'a'] = 1;
    }

    vector<vector<int>> alph(26, vector<int>(26, 0));
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if(i == j) alph[i][j] = 0;
            else if(ifvow[i] == ifvow[j]) // same mismatch
                alph[i][j] = 1;
            else // different type ismatch
                alph[i][j] = 3;
        }
    }
    
    // Initial Base Cases
    for(int i = 0; i <= x.size(); i++){
        dp[i][0] = i * delta;
    }
    for(int j = 0; j <= y.size(); j++){
        dp[0][j] = j * delta;
    }
    
    for(int i = 1; i <= x.size(); i++){
        for (int j = 1; j <= y.size(); j++) {
            int c1 = dp[i-1][j-1] + alph[x[i-1]-'a'][y[j-1]-'a']; 
            int c2 = dp[i-1][j] + delta;
            int c3 = dp[i][j-1] + delta;
            dp[i][j] = min(c1, min(c2, c3));
        }
    }
}

int main() {
    string a = "name";
    string b = "naem";
    vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
    stringAlign(dp, a, b);
    cout << "HI after function call" << endl;
    for(int i = 0; i <= a.size(); i++){
        for (int j = 0; j <= b.size(); j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}
