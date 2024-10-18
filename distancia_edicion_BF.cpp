#include <bits/stdc++.h>
using namespace std;

//-----------------------Funciones de costos-------------------------//
// Calcula el costo de sustituir el carácter ‘a’ por ‘b’.
 // Parámetros:
 //−a: carácter original
 //−b: carácter con el que se sustituye
 // Return: costo de sustituir ’a’ por ’b’
 int costo_sub(char a, char b) {
 int costo = (a == b) ? 0 : 1;
 // Implementación
 return costo;
 }

// Calcula el costo de insertar el carácter ‘b’.
 // Parámetros:
 //−b: carácter a insertar
 // Return: costo de insertar ’b’
 int costo_ins(char b) {
 int costo = 1;
 // Implementación
 return costo;
 }


// Calcula el costo de eliminar el carácter ’a ’.
 // Parámetros:
 //−a: carácter a eliminar
 // Return: costo de eliminar ’a’
 int costo_del(char a) {
 int costo = 1;
 // Implementación
 return costo;
 }

 // Calcula el costo de transponer los caracteres ’a’ y ’b’.
 // Parámetros:
 //−a: primer carácter a transponer
 //−b: segundo carácter a transponer
 // Return: costo de transponer ’a’ y ’b’
 int costo_trans(char a, char b) {
 int costo = 1;
 // Implementación
 return costo;
 }

//-------------------------------------------------------------------//



//-----------------------Algoritmo de Fuerza Bruta--------------------//

int distancia_fuerza_bruta(const string& string1, const string& string2, int i, int j) {
    // caso base: si una cadena está vacía, el costo es insertar o eliminar el resto de la otra cadena
    if (i == 0) return j * costo_ins(string2[j - 1]);  // si string1 está vacío, insertar string2
    if (j == 0) return i * costo_del(string1[i - 1]);  // si string2 está vacío, eliminar string1

    // caso 1: realizar sustitución (o no, si son iguales)
    int costo_sustitucion = distancia_fuerza_bruta(string1, string2, i - 1, j - 1) + costo_sub(string1[i - 1], string2[j - 1]);

    // caso 2: realizar insercion
    int costo_insercion = distancia_fuerza_bruta(string1, string2, i, j - 1) + costo_ins(string2[j - 1]);

    // caso 3: realizar eliminacion
    int costo_eliminacion = distancia_fuerza_bruta(string1, string2, i - 1, j) + costo_del(string1[i - 1]);

    // caso 4: realizar transposición, solo si es posible (si hay al menos 2 caracteres en ambas cadenas y los pares de caracteres se pueden transponer)
    int costo_transposicion = INT_MAX;
    if (i > 1 && j > 1 && string1[i - 1] == string2[j - 2] && string1[i - 2] == string2[j - 1]) {
        costo_transposicion = distancia_fuerza_bruta(string1, string2, i - 2, j - 2) + costo_trans(string1[i - 1], string1[i - 2]);
    }
    
    // devolver el mínimo costo entre sustitución, inserción, eliminación y transposición (si aplica)
    return min({costo_sustitucion, costo_insercion, costo_eliminacion, costo_transposicion});
}

int calcular_distancia_fuerza_bruta(const string& string1, const string& string2) {
    return distancia_fuerza_bruta(string1, string2, string1.size(), string2.size());
}

//-------------------------------------------------------------------//

int main() {
    string string1, string2;
    cout << "string1: ";
    cin >> string1;
    cout << "string2: ";
    cin >> string2;

    int dis_min = calcular_distancia_fuerza_bruta(string1, string2);
    cout << "\nLa distancia minima por fuerza bruta es: " << dis_min << endl;

    return 0;
}
