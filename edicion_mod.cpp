#include <bits/stdc++.h>
using namespace std;

//para calcular la distancia de Damerau-Levenshtein
int damerauLevenshteinDistance(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();

    //crear tabla para almacenar los resultados parciales
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    //inicializar la tabla
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            dp[i][j] = min({dp[i - 1][j] + 1,       // Eliminación
                            dp[i][j - 1] + 1,       // Inserción
                            dp[i - 1][j - 1] + cost // Sustitución
                           });

            //verificar si es posible hacer una transposición
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost); // transposición
            }
        }
    }

    //distancia de damerau-levenshtein
    for(auto a :dp){
        for (auto b : a){
            cout << b << ' ';
        }
        cout << endl;
    }
    return dp[m][n];
}

int main() {
    string str1, str2;

    cout << "primera cadena: ";
    cin >> str1;
    cout << "segunda cadena: ";
    cin >> str2;

    int distance = damerauLevenshteinDistance(str1, str2);

    cout << "La distancia de Damerau-Levenshtein es: " << distance << endl;

    return 0;
}
