int stringAlignMUtil(string& x, string& y, vector<vector<int>>& dp, int i, int j) {
    if (i == 0) return j * 2;
    if (j == 0) return i * 2;
    if (dp[i][j] != -1) return dp[i][j];

    int delta = 2;
    vector<int> ifvow(26, 0);
    string vows = "aeiou";
    for (auto e : vows) {
        ifvow[e - 'a'] = 1;
    }

    vector<vector<int>> alph(26, vector<int>(26, 0));
    for (int a = 0; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            if (a == b) alph[a][b] = 0;
            else if (ifvow[a] == ifvow[b]) // same mismatch
                alph[a][b] = 1;
            else // different type mismatch
                alph[a][b] = 3;
        }
    }
