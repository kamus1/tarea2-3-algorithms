#include <bits/stdc++.h>
using namespace std;

//matrices de costos para remplazar y transponer una letra; matrices 26x26
vector<vector<int>> matriz_costos_replace(26, vector<int>(26));
vector<vector<int>> matriz_costos_transpose(26, vector<int>(26));

//tabla eliminar e insertar una letra (26 letras de la 'a' a la 'z' abcederario ingles)
vector<int> tabla_costos_delete(26);
vector<int> tabla_costos_insert(26);


// función para convertir un carácter a su índice en la matriz de costos
int indice_caracter(char c) {
    return c - 'a'; // asumimos que las letras son minúsculas 
}

//-----------------------Funciones de costos-------------------------//
// Calcula el costo de sustituir el carácter ‘a’ por ‘b’.
 // Parámetros:
 // − a: carácter original
 // − b: carácter con el que se sustituye
 // Return: costo de sustituir ’a’ por ’b’
 int costo_sub(char a, char b) {
    if (a == b) return 0;
    int costo = matriz_costos_replace[indice_caracter(a)][indice_caracter(b)];
    return costo;
 }

// Calcula el costo de insertar el carácter ‘b’.
 // Parámetros:
 // − b: carácter a insertar
 // Return: costo de insertar ’b’
 int costo_ins(char b) {
    int costo = tabla_costos_insert[indice_caracter(b)];
    return costo;
 }


// Calcula el costo de eliminar el carácter ’a ’.
 // Parámetros:
 // − a: carácter a eliminar
 // Return: costo de eliminar ’a’
 int costo_del(char a) {
    int costo = tabla_costos_delete[indice_caracter(a)];
    return costo;
 }

 // Calcula el costo de transponer los caracteres ’a’ y ’b’.
 // Parámetros:
 // − a: primer carácter a transponer
 // − b: segundo carácter a transponer
 // Return: costo de transponer ’a’ y ’b’
 int costo_trans(char a, char b) {
    int costo = matriz_costos_transpose[indice_caracter(a)][indice_caracter(b)]; //costo de transposición
    return costo;
 }

//-------------------------------------------------------------------//


//-----------------------Algoritmo de Fuerza Bruta--------------------//
// Calcula la distancia de edición utilizando fuerza bruta.
// Parámetros:
// - string1: primera cadena de caracteres a comparar
// - string2: segunda cadena de caracteres a comparar
// - index_s1: índice actual en string1 (número de caracteres restantes por procesar en string1)
// - index_s2: índice actual en string2 (número de caracteres restantes por procesar en string2)
// Return: el costo mínimo de convertir string1 en string2 considerando las operaciones de edición
int distancia_fuerza_bruta(const string& string1, const string& string2, int index_s1, int index_s2) {
    // caso base: si una cadena está vacía, el costo es insertar o eliminar el resto de la otra cadena
    if (index_s1 == 0) return index_s2 * costo_ins(string2[index_s2 - 1]);  // si string1 está vacío, insertar string2
    if (index_s2 == 0) return index_s1 * costo_del(string1[index_s1 - 1]);  // si string2 está vacío, eliminar string1

    // caso 1: realizar sustitución (o no, si son iguales)
    int costo_sustitucion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2 - 1) + costo_sub(string1[index_s1 - 1], string2[index_s2 - 1]);

    // caso 2: realizar insercion
    int costo_insercion = distancia_fuerza_bruta(string1, string2, index_s1, index_s2 - 1) + costo_ins(string2[index_s2 - 1]);

    // caso 3: realizar eliminacion
    int costo_eliminacion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2) + costo_del(string1[index_s1 - 1]);

    // caso 4: realizar transposición, solo si es posible (si hay al menos 2 caracteres en ambas cadenas y los pares de caracteres se pueden transponer)
    int costo_transposicion = INT_MAX;
    if (index_s1 > 1 && index_s2 > 1 && string1[index_s1 - 1] == string2[index_s2 - 2] && string1[index_s1 - 2] == string2[index_s2 - 1]) {
        costo_transposicion = distancia_fuerza_bruta(string1, string2, index_s1 - 2, index_s2 - 2) + costo_trans(string1[index_s1 - 2], string1[index_s1 - 1]); // costo_trans(string1[index_s1 - 2], string2[index_s1 - 2]);
    }
    
    // devolver el mínimo costo entre sustitución, inserción, eliminación y transposición (si aplica)
    return min({costo_sustitucion, costo_insercion, costo_eliminacion, costo_transposicion});
}

int calcular_distancia_fuerza_bruta(const string& string1, const string& string2) {
    return distancia_fuerza_bruta(string1, string2, string1.size(), string2.size());
}

//-------------------------------------------------------------------//



//---------------- Funciones para cargar los datos de los .txt en las matrices y tablas -----------------------//
//cargar los costos de inserción desde cost_insert.txt
 // Parámetros:
 // − filename: nombre del archivo 
 // Return: funcion void, carga tabla_cost_insert
void cargar_cost_insert(const string &filename) {
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir " << filename << endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        archivo >> tabla_costos_insert[i];
    }
    archivo.close();
}

//cargar los costos de eliminación desde cost_delete.txt
 // Parámetros:
 // − filename: nombre del archivo 
 // Return: funcion void, carga tabla_cost_delete
void cargar_cost_delete(const string &filename) {
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir " << filename << endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        archivo >> tabla_costos_delete[i];
    }
    archivo.close();
}

//cargar los costos de sustitución desde cost_replace.txt
 // Parámetros:
 // − filename: nombre del archivo 
 // Return: funcion void, carga matriz_costos_replace
void cargar_cost_replace(const string &filename) {
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir " << filename << endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> matriz_costos_replace[i][j];
        }
    }
    archivo.close();
}

//cargar los costos de transposición desde cost_transpose.txt
 // Parámetros:
 // − filename: nombre del archivo 
 // Return: funcion void, carga matriz_costos_transpose
void cargar_cost_transpose(const string &filename) {
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir " << filename << endl;
        return;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> matriz_costos_transpose[i][j];
        }
    }
    archivo.close();
}
//------------------------------------------------------------------------------------------------------------//


int main() {
    //cargar costos de las matrices y tablas;
    cargar_cost_insert("cost_insert.txt");
    cargar_cost_delete("cost_delete.txt");
    cargar_cost_replace("cost_replace.txt");
    cargar_cost_transpose("cost_transpose.txt");


    string string1, string2;
    cout << "string1: ";
    cin >> string1;
    cout << "string2: ";
    cin >> string2;

    int dis_min = calcular_distancia_fuerza_bruta(string1, string2);
    cout << "\nLa distancia minima por fuerza bruta es: " << dis_min << endl;

    return 0;
}
