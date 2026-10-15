/**
 * Debemos minimizar la cantidad de caracteres distintos que 
 * permanecen en una cadena de tamaño n eliminando a lo sumo k 
 * caracteres.
 * Por lo tanto, vamos aplicar un enfoque codicioso (Greedy) basado 
 * en las frecuencias de los caracteres. Para eliminar un tipo de 
 * caracter distinto del resultado final, se deben borrar todas sus 
 * apariciones en la cadena. luego, para maximizar la cantidad de 
 * tipos de caracteres eliminados con un presupuesto maximo de k 
 * borrados, conviene eliminar primero aquellos caracteres que tengan
 * la menor frecuencia de aparicion.
 * 
 * Se procesan los caracteres en orden ascendente segun su 
 * frecuencia. Si k es suficiente para cubrir la frecuencia del 
 * caracter actual, se borra por completo y se descuenta su 
 * frecuencia de k.
 * 
 * El algoritmo entonces lee la cadena S y el numero k. Calcula 
 * la frecuencia de cada una de las 26 letras minusculas y crea una 
 * lista de letras presentes y se ordenan de menor a mayor frecuencia
 * Se itera sobre la lista organizadas y aqui vemos que si 
 * la frecuencia de la letra es <= k, se marca como eliminada
 * y se decrementa k, pero, en caso contrario, se detiene el proceso.
 * Finalmente, se imprime la cantidad de caracteres distintos que 
 * quedaron en la subsecuencia resultante, manteniendo el orden 
 * relativo original
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct CharFreq {
    char ch;
    int freq;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int k;
    if (!(cin >> s >> k)) return 0;

    // Contar las frecuencias de cada caracter en la cadena
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    // Almacenar solo las letras que aparecen al menos una vez
    vector<CharFreq> vec;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            vec.push_back({(char)('a' + i), freq[i]});
        }
    }

    // Ordenar las letras por frecuencia ascendente
    sort(vec.begin(), vec.end(), [](const CharFreq& a, const CharFreq& b) {
        return a.freq < b.freq;
    });

    // Registrar que letras seran eliminadas por completo
    vector<bool> removed(26, false);
    int distinct_remaining = vec.size();

    for (const auto& item : vec) {
        if (k >= item.freq) {
            k -= item.freq;
            removed[item.ch - 'a'] = true;
            distinct_remaining--;
        } else {
            // Si k ya no alcanza para borrar todas las instancias de esta letra, paramos
            break;
        }
    }

    // Imprimir el numero de caracteres distintos restantes
    cout << distinct_remaining << "\n";

    // Reconstruir la subsecuencia con los caracteres que no fueron eliminados
    string result = "";
    for (char c : s) {
        if (!removed[c - 'a']) {
            result += c;
        }
    }

    cout << result << "\n";

    return 0;
}