/**
 * Tenemos que minimizar un numero entero de n dígitos cambiando 
 * como maximo k digitos. Para poder hacer que el numero de digitos
 * sea lo mas pequeño posible vamos aplicar una estrategia codiciosa 
 * de izquierda a  derecha, donde se va a priorizar las posiciones 
 * de mayor peso.
 * 
 * Tendremos dos casos, uno en donde el caso borde donde n = 1 y un 
 * caso general cuando n > 1.
 * 
 * En el algoritmo se leen n, k y la cadena S. Se manejan de forma 
 * independiente el caso especial n = 1. Luego se intera sobre la 
 * cadena de izquierda a derecha aplicando los cambios optimos y 
 * decrementando k con cada modificacion hasta agotar k o terminar
 * la cadena. Finalmente, se muestra la cadena resultante.
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    string s;
    cin >> s;

    // Caso de borde
    if (n == 1) {
        if (k >= 1) {
            s[0] = '0';
        }
        cout << s << "\n";
        return 0;
    }

    // Caso general
    for (int i = 0; i < n && k > 0; ++i) {
        if (i == 0) {
            // El primer digito debe ser como minimo '1' para evitar ceros a la izquierda
            if (s[i] != '1') {
                s[i] = '1';
                k--;
            }
        } else {
            // Los demas digitos pueden ser '0'
            if (s[i] != '0') {
                s[i] = '0';
                k--;
            }
        }
    }

    cout << s << "\n";

    return 0;
}