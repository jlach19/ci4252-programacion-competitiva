/**
 * Analizando la naturaleza de los datos, se puede observar que el
 * arreglo no cambia, es decir, es estatico y que la funcion min()
 * es idempotente (min(x, x) = x)
 * 
 * Por lo tanto se considera que la estructura de datos ideal es la 
 * tabla esparcida. Lo que permite responder cada consulta [l,r] en
 * tiempo constante O(1) tras una precomputación de O(N log N)
 * 
 * En este codigo lo que se hara es precomputar los valores de log2 
 * para acelerar la determinación del tamaño de bloque en cada consulta.
 * Se contruye la tabla esparcida calculando dinámicamente los mínimos 
 * para todos los subintervalos con longitudes potencias de 2. Y Para
 * cada consulta [l, r], calcular en O(1) la superposición de dos bloques
 * de tamaño 2^k e imprimir el mínimo obtenido.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 100005;
const int LOGN = 18;

int st[MAXN][LOGN];
int log_table[MAXN];

// Contruccion de la tabla esparcida
void build(const vector<int>& A, int n) {
    // Inicializar logaritmos para O(1) en las consultas
    log_table[1] = 0;
    for (int i = 2; i <= n; ++i) {
        log_table[i] = log_table[i / 2] + 1;
    }

    // Casos base: Subarreglos de longitud 2^0 = 1
    for (int i = 0; i < n; ++i) {
        st[i][0] = A[i];
    }

    // Llenado de tabla
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

// Consulta del minimo en el rango [l, r]
int query(int l, int r) {
    int len = r - l + 1;
    int k = log_table[len];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
    // Optimizacion de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    // Construir la estructura de datos
    build(A, n);

    int Q;
    cin >> Q;
    while (Q--) {
        int i, j;
        cin >> i >> j;
        // Garantizamos que l <= r
        if (i > j) swap(i, j);
        cout << query(i, j) << "\n";
    }

    return 0;
}