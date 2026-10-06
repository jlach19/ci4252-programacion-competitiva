/**
 * Lo que necesitamos es maximizar la funcion f(m) = sum(m mod a_i) para i desde 1 hasta n.
 * 
 * Es conocido que el residuo maximo posible al dividir cualquier numero m entre a_i es (a_i - 1).
 * 
 * Si elegimos m = MCM(a_1, a_2, ..., a_n) - 1, se cumple que m mod a_i = a_i - 1 
 * para todo 1 <= i <= N de manera simultanea.
 * 
 * Por lo tanto, el valor maximo alcanzable de la funcion es simplemente la suma 
 * de (a_i - 1) para cada uno de los N enteros dados. No es necesario calcular 
 * el MCM ni encontrar la m explicitamente.
 */
#include <iostream>

using namespace std;

int main() {
    // Optimizacion de lectura/escritura
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    long long suma_maxima = 0;

    // Iterar "n" veces para procesar cada elemento de entrada de forma continua
    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;
        suma_maxima += (a - 1);
    }
    // Imprimir el valor maximo resultante de la función f(m)
    cout << suma_maxima << "\n";

    return 0;
}