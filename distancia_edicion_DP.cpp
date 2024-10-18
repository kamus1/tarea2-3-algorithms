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




int calcular_distancia(const string &string1, const string &string2){
    int tamano_palabra1 = string1.size(); 
    int tamano_palabra2 = string2.size();

    //inicializamos la matriz;
    vector<vector<int>> matriz(tamano_palabra1 + 1, vector<int>(tamano_palabra2 + 1)); // +1 para el 0 inicial de la matriz
    //palabra 1 -> fila
    //palabra 2 -> columna

    //primer valor igual a 0:
    matriz[0][0] =0;
    //rellenar fila, la razon de pq se usan los costos es pq la primera fila y columna de la matriz representan los costos acumulados de los casos base 
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
                                            matriz[fila_i - 2][col_j - 2] + costo_trans(string1[fila_i - 2], string2[col_j - 2])); // Transposición
            }
        }
    }

    //solo es print de la matriz
    for(int fila_i=0; fila_i <= tamano_palabra1; ++fila_i){
        for(int columna_j = 0; columna_j <=tamano_palabra2; ++columna_j){
            cout << matriz[fila_i][columna_j] << ' ';
        }
        cout << endl;
    }

    return matriz[tamano_palabra1][tamano_palabra2];
}


int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0);

    string string1, string2;
    cout << "Ingrese string1: ";
    cin >> string1;
    cout << "Ingrese String2: ";
    cin >> string2;

    int dis_min = calcular_distancia(string1, string2);
    cout << "\nLa distancia minima es: " << dis_min << endl;


    return 0;
}