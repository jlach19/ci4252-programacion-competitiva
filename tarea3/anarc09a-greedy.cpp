/*
 * En este codigo, aplicaremos la estrategia greedy.
 * 
 * Cuando vamos a procesar la cadena de izquierda a derecha, cualquier pareja adyacente 
 * del tipo "{}" se considera válida y no requiere operaciones. Entonces si eliminamos
 * todas las parejas validas de forma iterativa, la cadena restante siempre se 
 * reducirá a un patrón del tipo "}}}...{{{"  
 * Debido a esto, entonces cada par de llaves de cierre "}}" se corrige cambiando 
 * la primera a '{' -> ceil(C / 2) ops. Ademas, cada par de llaves de apertura "{{" 
 * se corrige cambiando la segunda a '}' -> ceil(O / 2) ops. Pero, si C y O son impares,
 * las llaves sobrantes forman el par "}{", el cual requiere 2 modificaciones 
 * para convertirse en "{}".
 * 
 * El algoritmo comienza leyendo la cadena de entrada por cada caso de prueba 
 * hasta encontrar '-'.Luego, recorre la cadena caracter por caracter utilizando 
 * un contador las llaves de apertura no emparejadas:
 *    - Si encontramos '{', incrementamos el contador de aperturas.
 *    - Si encontramos '}' y tenemos aperturas pendientes, decrementamos el contador 
 *      (se emparejan con éxito).
 *    - Si encontramos '}' y no hay aperturas pendientes, incrementamos un contador 
 *      independiente para cierres huérfanos.
 * Luego, se calcula la cantidad de operaciones.
 * Finalmente, se imprime el numero de caso de prueba y el resultado.
 * 
 */

#include <iostream>
#include <string>

using namespace std;

void solve_greedy() {
    string s;
    int test_case = 1;

    // Procesar casos de prueba hasta que el primer caracter sea '-'
    while (cin >> s && s[0] != '-') {
        int open_count = 0;  // Cuenta las llaves '{' actualmente abiertas
        int close_count = 0; // Cuenta las llaves '}' que no tienen un '{' que las anteceda

        for (char c : s) {
            if (c == '{') {
                open_count++;
            } else { 
                if (open_count > 0) {
                    // La llave de cierre actual se empareja correctamente con un '{' previo
                    open_count--;
                } else {
                    // No hay '{' disponible para emparejar esta llave '}'
                    close_count++;
                }
            }
        }

        int ans = (close_count + 1) / 2 + (open_count + 1) / 2;

        cout << test_case++ << ". " << ans << "\n";
    }
}

int main() {
    cin.tie(NULL);

    solve_greedy();

    return 0;
}
