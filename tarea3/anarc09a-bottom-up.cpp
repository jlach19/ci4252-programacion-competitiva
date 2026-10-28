/*
 * El enfoque que usaremos para este ejercicio es el de bottom up
 *
 * Construimos la solucion de manera iterativa utilizando una tabla de estados 
 * dp[i][open], la cual representa el costo minimo de operaciones para procesar 
 * los primeros 'i' caracteres de la cadena terminando con exactamente 'open' 
 * llaves de apertura sin cerrar.
 * 
 * Los casos bases seran:
 *  - dp[0][0] = 0  
 *  - dp[0][j] = INF para j > 0 
 * 
 * Se consideraran las siguientes transiciones de estado de (i, open) a (i + 1, ...):
 *  - Para colocar '{': dp[i + 1][open + 1] = min(dp[i + 1][open + 1], dp[i][open] 
 *  + (S[i] != '{'))
 *  - Para colocar '}' (si open > 0): dp[i + 1][open - 1] = min(dp[i + 1][open - 1],
 *  dp[i][open] + (S[i] != '}'))
 * 
 * El algoritmo comienza inicializando la tabla dp[n + 1][n + 1] con valores INF.
 * Se establece el caso base dp[0][0] = 0.. Luego, se itera externamente sobre 'i'
 * de 0 a n - 1 (procesando cada carácter de la cadena)
 * 
 * Se itera sobre 'open' de 0 a 'i'. Si dp[i][open] != INF, propagar el costo
 * hacia dp[i + 1][open + 1] considerando el costo de colocar '{'. 
 * Pero, si open > 0, propagar el costo hacia dp[i + 1][open - 1] considerando
 * el costo de colocar '}'.
 *
 * Finalmente, se obtiene la respuesta final directamente de la celda dp[n][0].
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

void solve_bottom_up() {
    string s;
    int test_case = 1;

    while (cin >> s && s[0] != '-') {
        int n = s.length();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));

        dp[0][0] = 0; // 0 caracteres procesados, 0 llaves abiertas

        for (int i = 0; i < n; ++i) {
            for (int open = 0; open <= i; ++open) {
                if (dp[i][open] == INF) continue;

                // Colocar '{'
                int cost_open = (s[i] == '}') ? 1 : 0;
                if (open + 1 <= n) {
                    dp[i + 1][open + 1] = min(dp[i + 1][open + 1], dp[i][open] + cost_open);
                }

                // Colocar '}'
                if (open > 0) {
                    int cost_close = (s[i] == '{') ? 1 : 0;
                    dp[i + 1][open - 1] = min(dp[i + 1][open - 1], dp[i][open] + cost_close);
                }
            }
        }

        cout << test_case++ << ". " << dp[n][0] << "\n";
    }
}

int main() {
    cin.tie(NULL);
    solve_bottom_up();
    return 0;
}
