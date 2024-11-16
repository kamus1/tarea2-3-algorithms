#include <bits/stdc++.h>
using namespace std;

//matrices de costos para remplazar y transponer una letra; matrices 26x26
vector<vector<int>> matriz_costos_replace(26, vector<int>(26));
vector<vector<int>> matriz_costos_transpose(26, vector<int>(26));

//tabla eliminar e insertar una letra (26 letras de la 'a' a la 'z' abcederario ingles)
vector<int> tabla_costos_delete(26);
vector<int> tabla_costos_insert(26);

//variable para usar las tablas o matrices, si es false usa costos default, si es true usa las tablas
bool usar_tablas = true;

// función para convertir un carácter a su índice en la matriz de costos
int indice_caracter(char c) {
    return c - 'a'; // asumimos que las letras son minúsculas 
}

//-----------------------Funciones de costos-------------------------//
int costo_sub(char a, char b) {
    int costo = 1;  // costo default
    if(!usar_tablas){
        if (a == b) return 0;
    }
    if(usar_tablas){
        costo = matriz_costos_replace[indice_caracter(a)][indice_caracter(b)];
    }
    return costo;
}

int costo_ins(char b) {
    int costo = 1;  // costo default
    if(usar_tablas){
        costo = tabla_costos_insert[indice_caracter(b)];
    }
    return costo;
}

int costo_del(char a) {
    int costo = 1;  // costo default
    if(usar_tablas){
        costo = tabla_costos_delete[indice_caracter(a)];
    }
    return costo;
}

int costo_trans(char a, char b) {
    int costo = 1; // costo default
    if(usar_tablas){
        costo = matriz_costos_transpose[indice_caracter(a)][indice_caracter(b)];
    }
    return costo;
}
//-------------------------------------------------------------------//

//-----------------------Algoritmo de Fuerza Bruta--------------------//
int distancia_fuerza_bruta(const string& string1, const string& string2, int index_s1, int index_s2) {
    if (index_s1 == 0) return index_s2 * costo_ins(string2[index_s2 - 1]);
    if (index_s2 == 0) return index_s1 * costo_del(string1[index_s1 - 1]);

    int costo_sustitucion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2 - 1) + costo_sub(string1[index_s1 - 1], string2[index_s2 - 1]);
    int costo_insercion = distancia_fuerza_bruta(string1, string2, index_s1, index_s2 - 1) + costo_ins(string2[index_s2 - 1]);
    int costo_eliminacion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2) + costo_del(string1[index_s1 - 1]);

    int costo_transposicion = INT_MAX;
    if (index_s1 > 1 && index_s2 > 1 && string1[index_s1 - 1] == string2[index_s2 - 2] && string1[index_s1 - 2] == string2[index_s2 - 1]) {
        costo_transposicion = distancia_fuerza_bruta(string1, string2, index_s1 - 2, index_s2 - 2) + costo_trans(string1[index_s1 - 2], string1[index_s1 - 1]);
    }

    return min({costo_sustitucion, costo_insercion, costo_eliminacion, costo_transposicion});
}

int calcular_distancia_fuerza_bruta(const string& string1, const string& string2) {
    return distancia_fuerza_bruta(string1, string2, string1.size(), string2.size());
}
//-------------------------------------------------------------------//

//---------------- Funciones para cargar los datos de los .txt en las matrices y tablas -----------------------//
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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <string1> <string2>" << endl;
        return 1;
    }

    string string1 = argv[1];
    string string2 = argv[2];

    // si es un "0" es decir un string vacio lo cambiamos
    if (string1 == "0") string1 = "";
    if (string2 == "0") string2 = "";

    cargar_cost_insert("cost_insert.txt");
    cargar_cost_delete("cost_delete.txt");
    cargar_cost_replace("cost_replace.txt");
    cargar_cost_transpose("cost_transpose.txt");

    int dis_min = calcular_distancia_fuerza_bruta(string1, string2);
    cout << "La distancia minima por fuerza bruta es: " << dis_min << endl;

    return 0;
}
