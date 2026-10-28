/*
 * En este ejercicio vamos a usar el manera Top-Down. 
 * 
 * El problema dse puede implentar como una toma de decisiones secuenciales para cada 
 * caracter de la cadena, donde en la posicion 'i' podemos decidir si colocar '{'
 *
 * Para asegurar que la cadena sea valida, en todo momento la cantidad de llaves
 * de apertura 'open' debe cumplir que es mayor o igual a 0 y al finaliazr la cadena
 * se debe cumplir que open == 0
 *
 * Definimos dp(i, open) como el costo minimo de corregir el sufijo desde 'i' 
 * dado que hay 'open' llaves de apertura pendientes de cerrar, donde i va 
 * ser el indice actual de la cadena entre 0 y N y open la cantidad actual
 * de llaves { abiertas que aun no han sido cerradas 

 * 
 * Transicion en la posicion 'i':
 *  - Se asigna '{' a costo = (S[i] != '{') + dp(i + 1, open + 1)  
 *  - Poner '}' (si open > 0) costo =  (S[i] != '}') + dp(i + 1, open - 1)
 * 
 * El algoritmo inicializa la tabla de memoizacion memo[2005][2005] con el valor
 * -1, invoca la funcion recursiva desde la posicion inicial dp(0,0)
 * En la funcion recursiva:
 *    1. Verificar si open > posiciones_restantes (n - i). Si es asi, 
 *    retornar INF porque no habra suficientes caracteres para cerrar las llaves.
 *    2. Retornar el caso base si i == n: 0 si open == 0, de lo contrario INF.
 *    3. Consultar la tabla de memoizacion. Si ya se calculo el estado (i, open), 
 *    devolverlo.
 *    4. Calcular el costo minimo de cambiar o mantener el carácter actual como 
 *    '{' o '}' y guardar el resultado en la tabla.
 * Finalmente, se imprime la respuesta devuelta por la llamada recursiva
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int memo[2005][2005];
string s;
int n;

int dp(int i, int open) {
    // Si hay mas llaves abiertas que posiciones restantes, es imposible balancear
    if (open > n - i) return INF;
    if (i == n) return (open == 0) ? 0 : INF;

    if (memo[i][open] != -1) return memo[i][open];

    int ans = INF;

    // Dejar/Cambiar a '{'
    int cost_open = (s[i] == '}') ? 1 : 0;
    ans = min(ans, cost_open + dp(i + 1, open + 1));

    // Dejar/Cambiar a '}' (solo si hay llaves abiertas pendientes)
    if (open > 0) {
        int cost_close = (s[i] == '{') ? 1 : 0;
        ans = min(ans, cost_close + dp(i + 1, open - 1));
    }

    return memo[i][open] = ans;
}

void solve_top_down() {
    int test_case = 1;
    while (cin >> s && s[0] != '-') {
        n = s.length();
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                memo[i][j] = -1;
            }
        }
        cout << test_case++ << ". " << dp(0, 0) << "\n";
    }
}

int main() {
    cin.tie(NULL);
    solve_top_down();
    return 0;
}
