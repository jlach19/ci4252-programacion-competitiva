/**
 * Nos piden armar n barriles utilizando k tablas por barril 
 * (m = n * k tablas en total) para maximizar la suma de sus
 * volumenes. El volumen de un barril está determinado 
 * por la longitud de su tabla mas corta. Ademas, tenemos la 
 * restriccion de que para cada par de barril x e y, entonce
 * |v_x - v_y| <= l
 * 
 * Si ordenamos el arreglo de tablas de menor a mayor, la tabla a_1
 * siempre formara parte de algún barril. Entonces, para que la 
 * diferencia de volumenes no exceda 'l', la tabla minima de 
 * cualquier barril debe pertenecer al rango [a_1, a_1 + l]
 * 
 * Debemos contar cuantas tablas cumplen a_i <= a_1 + l (llamemos a 
 * este conteo R). Si R < n, es imposible asignar una tabla valida 
 * como minimo a cada uno de los n barriles
 * 
 * Para maximizar la suma, seleccionamos progresivamente las tablas
 * válidas mas grandes posibles. Iteramos construyendo barriles 
 * asignando la tabla valida en la posicion 'i' actual como el 
 * minimo del barril y saltamos min(k, R - n_restantes) 
 * posiciones hacia la derecha para llenar los cupos de tablas
 * secundarias.
 * 
 * En el algoritmo se procede a leer n, k, l y el arreglo de tablas
 * de tamaño m = n * k, se ordenan las tablas de mannera ascendente, 
 * luego, eterminar la cantidad R de tablas que satisfacen 
 * a_i <= a_1 + l. En caso de que R sea menor a n, se retorna 0
 * Ademas, se usan punteros para seleccionar 
 * estrategicamente las n tablas minimas que componen los barriles y 
 * acumular el resultado en una variable long long.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, l;
    if (!(cin >> n >> k >> l)) return 0;

    long long m = n * k;
    vector<long long> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    // Ordenar las tablas de menor a mayor
    sort(a.begin(), a.end());

    // Encontrar el numero de tablas válidas R 
    int R = 0;
    while (R < m && a[R] <= a[0] + l) {
        R++;
    }

    // Si hay menos de n tablas válidas, es imposible armar n barriles que cumplan la regla
    if (R < n) {
        cout << 0 << "\n";
        return 0;
    }

    long long suma_volumenes = 0;
    int idx = 0; // Puntero para la tabla a seleccionar como mínimo del barril actual

    for (int barriles_restantes = n; barriles_restantes > 0; --barriles_restantes) {
        suma_volumenes += a[idx];

        long long salto = min(k, (long long)R - idx - (barriles_restantes - 1));
        idx += salto;
    }

    cout << suma_volumenes << "\n";

    return 0;
}