/**
 * Sabemos que Vanya tiene n examenes, para obtener la beca, el 
 * promedio de sus notas debe ser al menos avg. Esto es equivalente 
 * a decir que la suma total de sus notas debe ser al menos:
 * target_sum = n * avg
 * 
 * Para minimizar el total de ensayos escritos, aplicamos un enfoque 
 * codicioso (Greedy). Calculamos la suma total actual de las notas. 
 * Si es mayor o igual a (n * avg), no se requieren ensayos 
 * adicionales. En caso contrario, ordenamos los examenes de 
 * menor a mayor costo de ensayo (b_i). Incrementamos la nota de
 * los examenes en este orden optimo hasta alcanzar la suma 
 * requerida. Para cada examen i, podemos sumar como máximo 
 * (r - a_i) puntos
 * 
 * El algoritmo lee n, r, avg y los n pares (a_i, b_i), luego se 
 * calcula target_sum = n * avg y la suma_actual de todas las
 * a_i. Posterior se ordena el vector de exámenes basándonos en b_i 
 * de manera ascendente. Se itera sobre los examenes ordenados,
 * agregando la cantidad necesaria de puntos 
 * min(puntos_faltantes, r - a_i) y acumulando el costo en ensayos.
 * Finalmente, se imprime la cantidad total minima de ensayos.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para almacenar la nota actual y el costo por punto de un examen
struct Exam {
    long long a; // nota actual
    long long b; // costo en ensayos por punto
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long r, avg;
    if (!(cin >> n >> r >> avg)) return 0;

    vector<Exam> exams(n);
    long long current_sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> exams[i].a >> exams[i].b;
        current_sum += exams[i].a;
    }

    // Suma objetivo necesaria para alcanzar el promedio deseado
    long long target_sum = (long long)n * avg;

    // Si ya se alcanza o supera el objetivo, no se necesitan ensayos
    if (current_sum >= target_sum) {
        cout << 0 << "\n";
        return 0;
    }

    // Ordenar los examenes de menor a mayor costo por punto (b)
    sort(exams.begin(), exams.end(), [](const Exam& x, const Exam& y) {
        return x.b < y.b;
    });

    long long points_needed = target_sum - current_sum;
    long long total_essays = 0;

    // Iterar de forma codiciosa incrementando notas al menor costo posible
    for (int i = 0; i < n && points_needed > 0; ++i) {
        long long max_add = r - exams[i].a; // Puntos maximos que se pueden sumar a este examen
        if (max_add <= 0) continue;

        // Tomar el minimo entre los puntos permitidos y los puntos que aun faltan
        long long add = min(points_needed, max_add);

        total_essays += add * exams[i].b;
        points_needed -= add;
    }

    cout << total_essays << "\n";

    return 0;
}