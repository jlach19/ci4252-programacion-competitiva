/**
 * El problema solicita encontrar la casa de uno de los amigos que minimice la 
 * suma total de las distancias recorridas por todos para reunirse. La métrica 
 * de distancia utilizada es la distancia de Manhattan: |x1 - x2| + |y1 - y2|.
 * 
 * Al descomponer la distancia de Manhattan en sus dos componentes independientes 
 * (eje X y eje Y), podemos reducir la complejidad computacional. Esto es asi ya que
 * La distancia Manhattan permite calcular los costos horizontales y verticales por 
 * separado sin interferencia, tambien evaluar todas las parejas tomaria O(N^2) y 
 * es ineficiente para N <= 10000. Asimismo, al ordenar las coordenadas de forma independiente
 * y aplicar sumas acumuladas, podemos calcular la suma de distancias de cualquier casa 
 * hacia todas las demás en tiempo O(1) por dimensión.
 * 
 * Dado que el punto de encuentro está restringido a la ubicación de alguno de los 
 * amigos, el costo total para la casa 'i' sera la suma de sus distancias 1D 
 * en X e Y. La respuesta optima es el mínimo de estas sumas.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para representar a un amigo en el plano
struct Point {
    int id;
    long long x, y;
};

// Estructura para almacenar información ordenada de una sola dimensión
struct Coord {
    long long val;
    int id;
};

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<Point> pts(n);
    vector<Coord> X(n), Y(n);

    // Lectura de la entrada y preservación de indices
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
        X[i] = {pts[i].x, i};
        Y[i] = {pts[i].y, i};
    }

    // Ordenar coordenadas X e Y
    sort(X.begin(), X.end(), [](const Coord& a, const Coord& b) {
        return a.val < b.val;
    });
    sort(Y.begin(), Y.end(), [](const Coord& a, const Coord& b) {
        return a.val < b.val;
    });

    // Sumas acumuladas para X e Y
    vector<long long> prefX(n + 1, 0), prefY(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefX[i + 1] = prefX[i] + X[i].val;
        prefY[i + 1] = prefY[i] + Y[i].val;
    }

    // Arreglos para guardar la distancia total en X e Y para cada amigo por su ID
    vector<long long> distX(n, 0), distY(n, 0);

    // Calculo del costo 1D en O(1) para cada punto de la lista ordenada
    for (int i = 0; i < n; ++i) {
        // Para X[i] (1-based index pos = i + 1)
        long long pos = i + 1;
        long long val = X[i].val;
        long long sum_left = pos * val - prefX[pos];
        long long sum_right = (prefX[n] - prefX[pos]) - (n - pos) * val;
        distX[X[i].id] = sum_left + sum_right;

        // Para Y[i]
        val = Y[i].val;
        sum_left = pos * val - prefY[pos];
        sum_right = (prefY[n] - prefY[pos]) - (n - pos) * val;
        distY[Y[i].id] = sum_left + sum_right;
    }

    // Encontrar la casa que minimiza la distancia total
    long long min_total_dist = -1;
    for (int i = 0; i < n; ++i) {
        long long total = distX[i] + distY[i];
        if (min_total_dist == -1 || total < min_total_dist) {
            min_total_dist = total;
        }
    }

    cout << min_total_dist << "\n";
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}