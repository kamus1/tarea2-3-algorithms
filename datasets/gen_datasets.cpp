#include <bits/stdc++.h>
using namespace std;

string generarCadenaAleatoria(int longitud) {
    string cadena;
    for (int i = 0; i < longitud; ++i) {
        char letra = 'a' + rand() % 26;
        cadena += letra;
    }
    return cadena;
}

void generarCasosPruebaAleatorios(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string palabra1 = generarCadenaAleatoria(longitudActual);
        string palabra2 = generarCadenaAleatoria(longitudActual);
        archivo << palabra1 << " " << palabra2 << "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba de cadenas aleatorias.\n";
}

void generarCasosPruebaConStringVacio(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string palabraAleatoria = generarCadenaAleatoria(longitudActual);
        archivo << "0 " << palabraAleatoria << "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba con un string vacío.\n";
}

// función para aplicar transposiciones adyacentes sistemáticamente a una cadena
string aplicarTransposiciones(string cadena) {
    for (int i = 0; i < cadena.length() - 1; i += 2) {
        swap(cadena[i], cadena[i + 1]);
    }
    return cadena;
}

void generarCasosPruebaConTransposiciones(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string palabraOriginal = generarCadenaAleatoria(longitudActual);
        string palabraTranspuesta = aplicarTransposiciones(palabraOriginal);
        archivo <<  palabraTranspuesta << " " <<  palabraOriginal<< "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba de transposiciones adyacentes.\n";
}

// función para generar una cadena con caracteres repetidos ordenados
string generarCadenaConRepeticiones(int longitud) {
    string cadena;
    char letra = 'a' + rand() % 26;  // Caracter inicial

    for (int i = 0; i < longitud; ++i) {
        if (i > 0 && rand() % 2 == 0) {
            cadena += cadena[i - 1];
        } else {
            letra = 'a' + rand() % 26;
            cadena += letra;
        }
    }
    return cadena;
}

// función para generar casos de prueba donde una cadena tiene caracteres repetidos y la otra está desordenada
void generarCasosPruebaConRepeticiones(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        // Generar una cadena con caracteres repetidos
        string palabra2 = generarCadenaConRepeticiones(longitudActual);
        // Desordenar la cadena para generar la segunda palabra
        string palabra1 = palabra2;
        random_shuffle(palabra1.begin(), palabra1.end());
        archivo << palabra1 << " " << palabra2 << "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba con caracteres repetidos y desordenados.\n";
}

// función para generar una cadena palíndroma
string generarCadenaPalindroma(int longitud) {
    string mitad = generarCadenaAleatoria((longitud + 1) / 2);
    string palindromo = mitad;
    for (int i = longitud / 2 - 1; i >= 0; --i) {
        palindromo += mitad[i];
    }
    return palindromo;
}

// función para desordenar una cadena
string desordenarCadena(const string &cadena) {
    string desordenada = cadena;
    random_shuffle(desordenada.begin(), desordenada.end());
    return desordenada;
}

// función para generar casos de prueba con palíndromos y versiones desordenadas
void generarCasosPruebaPalindromos(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string palabraPalindromo = generarCadenaPalindroma(longitudActual);
        string palabraDesordenada = desordenarCadena(palabraPalindromo);
        archivo << palabraDesordenada << " " << palabraPalindromo<< "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba de palíndromos y versiones desordenadas.\n";
}

// función para generar una cadena con patrones alternados
string generarCadenaPatron(int longitud) {
    string patron = "xyz"; // se puede cambiar este patron a otro como "abc", "xyz", etc.
    string cadena;
    for (int i = 0; i < longitud; ++i) {
        cadena += patron[i % patron.length()];
    }
    return cadena;
}

// función para generar casos de prueba con caracteres alternados
void generarCasosPruebaConPatrones(int longitudMaxima, int incremento, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string palabra2 = generarCadenaPatron(longitudActual);
        string palabra1 = desordenarCadena(palabra2);
        archivo << palabra1 << " " << palabra2 << "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba de patrones alternados.\n";
}

// función para insertar gaps en posiciones aleatorias de una cadena
string insertarGaps(const string &cadena, int numGaps, int tamanoMaxGap) {
    string cadenaConGaps = cadena;
    for (int i = 0; i < numGaps; ++i) {
        if (cadenaConGaps.empty()) break;
        int posicionGap = rand() % cadenaConGaps.length();
        int tamanoGap = 1 + rand() % tamanoMaxGap;
        tamanoGap = min(tamanoGap, static_cast<int>(cadenaConGaps.length() - posicionGap));
        cadenaConGaps.erase(posicionGap, tamanoGap);
    }
    return cadenaConGaps;
}

// función para generar casos de prueba donde una cadena es la original y la otra tiene gaps de tamaño variable
void generarCasosPruebaConOriginalYGaps(int longitudMaxima, int incremento, int numGaps, int tamanoMaxGap, const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int longitudActual = incremento; longitudActual <= longitudMaxima; longitudActual += incremento) {
        string cadenaOriginal = generarCadenaAleatoria(longitudActual);
        string cadenaConGaps = insertarGaps(cadenaOriginal, numGaps, tamanoMaxGap);
        archivo << (cadenaConGaps.empty() ? "0" : cadenaConGaps) << " " << cadenaOriginal << "\n";
    }

    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado con los casos de prueba de original y cadena con gaps de tamaño variable.\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int longitudMaxima = 20;
    int incremento = 1;

    string archivoAleatorios = "dataset_cadenas_aleatorias.txt";
    string archivoConVacio = "dataset_cadena_vacia.txt";
    string archivoConTranposiciones = "dataset_transposicion.txt";
    string archivoConRepeticiones = "dataset_repeticiones.txt";
    string archivoPalindromos = "dataset_palindromos.txt";
    string archivoPatrones = "dataset_patrones_alternados.txt";
    string archivoConGaps = "dataset_con_gaps.txt";
    
    generarCasosPruebaAleatorios(longitudMaxima, incremento, archivoAleatorios);
    generarCasosPruebaConStringVacio(longitudMaxima, incremento, archivoConVacio);
    generarCasosPruebaConTransposiciones(longitudMaxima, incremento, archivoConTranposiciones);
    generarCasosPruebaConRepeticiones(longitudMaxima, incremento, archivoConRepeticiones);
    generarCasosPruebaPalindromos(longitudMaxima, incremento, archivoPalindromos);
    generarCasosPruebaConPatrones(longitudMaxima, incremento, archivoPatrones);

    int numGaps = 3;
    int tamanoMaxGap = 3;
    generarCasosPruebaConOriginalYGaps(longitudMaxima, incremento, numGaps, tamanoMaxGap, archivoConGaps);

    return 0;
}
