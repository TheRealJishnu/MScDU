#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll mainMemoi(vector<vector<ll>>& memo, const string& x, const string& y, const vector<vector<int>>& alph, ll delta, int i, int j) {
    if (i == 0) return delta * j; // Deleting all characters from y
    if (j == 0) return delta * i; // Deleting all characters from x

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    ll c1 = (x[i - 1] == y[j - 1]) ? mainMemoi(memo, x, y, alph, delta, i - 1, j - 1) : 
        alph[x[i - 1] - 'a'][y[j - 1] - 'a'] + mainMemoi(memo, x, y, alph, delta, i - 1, j - 1);
    
    ll c2 = delta + mainMemoi(memo, x, y, alph, delta, i - 1, j); // Deletion from x
    ll c3 = delta + mainMemoi(memo, x, y, alph, delta, i, j - 1); // Insertion into x

    memo[i][j] = min(c1, min(c2, c3));
    return memo[i][j];
}

ll mainTabulation(vector<vector<int>>& dp, string x, string y, vector<vector<int>> alph, int delta){
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
    return dp[x.size()][y.size()];
}
ll stringAlign(string x, string y){
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
    vector<vector<int>> dp(x.size()+1, vector<int>(y.size()+1, -1));
    vector<vector<ll>> memo(x.size()+1, vector<ll>(y.size()+1, -1));

    // Time for Memoization
    auto start = std::chrono::steady_clock::now();
    mainMemoi(memo, x, y, alph, delta, x.size(), y.size());
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Memoization Judgement of Chronos : ";
    std::cout << std::chrono::duration<double, std::nano>(diff).count() << " nano-second" << std::endl;

    // Time for Tabulation
    start = std::chrono::steady_clock::now();
    mainTabulation(dp, x, y, alph, delta);
    end = std::chrono::steady_clock::now();

    diff = end - start;
    cout << "Tabulation Judgement of Chronos : ";
    std::cout << std::chrono::duration<double, std::nano>(diff).count() << " nano-second" << std::endl;

    /*Printing dp and memoi table
    cout << "Memoization " << endl;
    for(int i = 0; i <= x.size(); i++){
        for (int j = 0; j <= y.size(); j++)
        {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Tabulation " << endl;
    for(int i = 0; i <= x.size(); i++){
        for (int j = 0; j <= y.size(); j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    */
    return 0;
}

string gibberish()
{
    static std::ranlux48 rng( std::chrono::system_clock::now().time_since_epoch().count() );
    static std::uniform_int_distribution<int> rnd57( 100, 110 );
    static std::uniform_int_distribution<char> rndAZ( 'a', 'z' );
    std::string s( rnd57( rng ), 0 );
    for (char& c : s) c = rndAZ( rng );
    // for(int i=0; i<s.size(); i++){
    //     s[i] -= 'A';
    //     s[i] += 'a';
    // }
    // cout << s << endl;
    return s;
}

int main() {
    string a = gibberish();
    string b = gibberish();
    cout << a << " " << b << endl;
    // string a;
    // string b;
    // cin >> a >> b;
    vector<vector<int>> dp(a.size()+1, vector<int>(b.size()+1, 0));
    stringAlign(a, b);

}
