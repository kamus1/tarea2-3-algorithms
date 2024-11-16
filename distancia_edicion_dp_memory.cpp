#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

//matrices de costos para remplazar y transponer una letra; matrices 26x26
vector<vector<int>> matriz_costos_replace(26, vector<int>(26));
vector<vector<int>> matriz_costos_transpose(26, vector<int>(26));

//tabla eliminar e insertar una letra (26 letras de la 'a' a la 'z' abcederario ingles)
vector<int> tabla_costos_delete(26);
vector<int> tabla_costos_insert(26);

//variable para usar las tablas o matrices, si es false usa costos default, si es true usa las tablas
bool usar_tablas = true;


// función para convertir un carácter a su índice en la matriz de costos
//IMPORTANTE: solo funciona asumiendo que los caracteres son las 26 letras del alfabeto ingles y solo minusculas, si hay alguna mayuscula se va a salir del rango
int indice_caracter(char c) {
    return c - 'a'; // asumimos que las letras son minúsculas // a=97 en ascii, b=98 b-a = 1
}

//-----------------------Funciones de costos-------------------------//
// Calcula el costo de sustituir el carácter ‘a’ por ‘b’.
 // Parámetros:
 //−a: carácter original
 //−b: carácter con el que se sustituye
 // Return: costo de sustituir ’a’ por ’b’
 int costo_sub(char a, char b) {
    int costo = 1;  // costo default
    if(!usar_tablas){
        if (a == b) return 0; // si son iguales 0, esto es default si no se usan las tablas
    }
    if(usar_tablas){
        costo = matriz_costos_replace[indice_caracter(a)][indice_caracter(b)];
    }

    return costo;
 }

// Calcula el costo de insertar el carácter ‘b’.
 // Parámetros:
 //−b: carácter a insertar
 // Return: costo de insertar ’b’
 int costo_ins(char b) {
    int costo = 1;  // costo default
    if(usar_tablas){
        costo = tabla_costos_insert[indice_caracter(b)];
    }

    return costo;
 }


// Calcula el costo de eliminar el carácter ’a ’.
 // Parámetros:
 //−a: carácter a eliminar
 // Return: costo de eliminar ’a’
 int costo_del(char a) {
    int costo = 1;  // costo default
    if(usar_tablas){
        costo = tabla_costos_delete[indice_caracter(a)];
    }
    return costo;
 }

 // Calcula el costo de transponer los caracteres ’a’ y ’b’.
 // Parámetros:
 //−a: primer carácter a transponer
 //−b: segundo carácter a transponer
 // Return: costo de transponer ’a’ y ’b’
 int costo_trans(char a, char b) {
    int costo = 1; // costo default
    if(usar_tablas){
        costo = matriz_costos_transpose[indice_caracter(a)][indice_caracter(b)]; //costo de transposición
    }
    return costo;
 }

//-------------------------------------------------------------------//

// Calcula la distancia de edicion utilizando programacion dinamica
 // Parámetros:
 //−string1: primera palabra
 //−string2: segunda palabra
 // Return: la distancia de edicion 
int calcular_distancia_dp(const string &string1, const string &string2){
    int tamano_palabra1 = string1.size(); 
    int tamano_palabra2 = string2.size();

    //inicializamos la matriz;
    vector<vector<int>> matriz(tamano_palabra1 + 1, vector<int>(tamano_palabra2 + 1)); // +1 para el 0 inicial de la matriz
    //palabra 1 -> fila
    //palabra 2 -> columna

    //primer valor igual a 0:
    matriz[0][0] =0;
    //rellenar fila, la razon de por qué se usan los costos es pq la primera fila y columna de la matriz representan los costos acumulados de los casos base 
    for(int fila_i=1; fila_i <= tamano_palabra1; ++fila_i){
        matriz[fila_i][0] = matriz[fila_i - 1][0] + costo_del(string1[fila_i - 1]); // costo de eliminar caracteres
    }
    //rellenar columna
    for(int col_j=1; col_j <= tamano_palabra2; ++col_j){
        matriz[0][col_j] = matriz[0][col_j - 1] + costo_ins(string2[col_j - 1]); // costo de insertar caracteres
    }


    //recorremos la matriz por cada valor de una columan en fila //de izq a derecha
    //vamos calculando la distancia de edicion, que es el valor minimo entre las operaciones sustitucion, insercion y eliminacion 
    for(int fila_i=1; fila_i <= tamano_palabra1; ++fila_i){
        for(int col_j = 1; col_j <=tamano_palabra2; ++col_j){
            char letra_p1 = string1[fila_i - 1];
            char letra_p2 = string2[col_j - 1];
            
            //valores de la matriz necesarios para los calculos
            int val_diagonal_sup = matriz[fila_i-1][col_j-1];
            int val_superior = matriz[fila_i-1][col_j];
            int val_izq = matriz[fila_i][col_j-1];

            //calculo de los costos de las operaciones
            int val_sustitucion = val_diagonal_sup + costo_sub(letra_p1, letra_p2);
            int val_insertion = val_superior + costo_ins(letra_p2);
            int val_eliminacion = val_izq + costo_del(letra_p1);

            int distancia_min = min({val_sustitucion,val_insertion,val_eliminacion});
            //ajustamos el valor del bloque de la matriz actual:
            matriz[fila_i][col_j] = distancia_min;

            //ahora consideramos la transposicion de 2 caracteres adyacentes,
            //solo se realiza si se cumple la condicion de que 2 caracteres adyacentes se pueden transponer
            if (fila_i > 1 && col_j > 1 
                && string1[fila_i - 1] == string2[col_j - 2] 
                && string1[fila_i - 2] == string2[col_j - 1]){                                  //+ costo
                matriz[fila_i][col_j] = min(matriz[fila_i][col_j],
                                            matriz[fila_i - 2][col_j - 2] + costo_trans(string1[fila_i - 2], string1[fila_i - 1])); // Transposición string1[fila_i - 2], string2[col_j - 2]
            }
        }
    }

    //solo es print de la matriz
    
    //for(int fila_i=0; fila_i <= tamano_palabra1; ++fila_i){
    //    for(int columna_j = 0; columna_j <=tamano_palabra2; ++columna_j){
    //        cout << matriz[fila_i][columna_j] << ' ';
    //    }
    //    cout << endl;
    //}
    

    return matriz[tamano_palabra1][tamano_palabra2];
}


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






int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Por favor, proporciona dos strings como argumentos." << endl;
        return 1;
    }

    // Los strings son tomados desde los argumentos de línea de comandos
    string s1 = argv[1];
    string s2 = argv[2];

    // si es un "0" es decir un string vacio lo cambiamos
    if (s1 == "0") s1 = ""; 
    if (s2 == "0") s2 = "";

    // Cargar las tablas y matrices como antes
    cargar_cost_insert("cost_insert.txt");
    cargar_cost_delete("cost_delete.txt");
    cargar_cost_replace("cost_replace.txt");
    cargar_cost_transpose("cost_transpose.txt");

    // Calcular distancia y mostrar el resultado
    int distancia = calcular_distancia_dp(s1, s2);
    cout << distancia << endl;

    return 0;
}