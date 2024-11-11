#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/stat.h> // Para crear directorios en sistemas UNIX
#include <sys/types.h>
#include <vector>
#include <string>

using namespace std;

// Función para crear un directorio si no existe
bool crearDirectorio(const string &path) {
    #if defined(_WIN32)
        return _mkdir(path.c_str()) == 0 || errno == EEXIST;
    #else 
        return mkdir(path.c_str(), 0777) == 0 || errno == EEXIST;
    #endif
}

// Función para obtener la ruta de la carpeta de ejecución
string obtenerRutaEjecucion() {
    string ruta_base = "mediciones_memoria_bf";
    if (!crearDirectorio(ruta_base)) {
        cerr << "Error al crear la carpeta base." << endl;
        return "";
    }

    int numero_ejecucion = 1;
    string ruta_ejecucion;

    // Intentar crear una carpeta nueva con un número incremental hasta que funcione
    while (true) {
        ruta_ejecucion = ruta_base + "/ejecucion" + to_string(numero_ejecucion);
        
        // Si el directorio no existe, intentamos crearlo
        struct stat info;
        if (stat(ruta_ejecucion.c_str(), &info) != 0) {
            if (crearDirectorio(ruta_ejecucion)) {
                break;
            } else {
                cerr << "Error al crear la carpeta de ejecución: " << ruta_ejecucion << endl;
                return "";
            }
        } else {
            // Si el directorio ya existe, incrementamos el número de ejecución
            numero_ejecucion++;
        }
    }
    
    return ruta_ejecucion;
}

// Función para medir el uso de memoria de un par de palabras usando Valgrind
string medirMemoria(const string &string1, const string &string2) {
    string command = "valgrind --tool=memcheck --leak-check=full ./distancia_edicion_BF_memory " + string1 + " " + string2 +
                     " 2>&1 | grep 'total heap usage' | awk '{print $9}'";

    // Abrimos un proceso usando popen para capturar la salida del comando
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Error al ejecutar Valgrind." << endl;
        return "";
    }

    // Leer la salida del comando
    char buffer[128];
    string memoria_total;
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        memoria_total = buffer;
    }
    pclose(pipe);

    // Eliminar la coma si existe
    size_t comma_pos = memoria_total.find(',');
    if (comma_pos != string::npos) {
        memoria_total.erase(comma_pos, 1);
    }

    // Eliminar espacios en blanco adicionales
    memoria_total.erase(memoria_total.find_last_not_of(" \n\r\t") + 1);

    return memoria_total;
}

// Función para procesar cada archivo de dataset
void procesarDataset(const string &dataset, const string &ruta_ejecucion) {
    ifstream archivo(dataset);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo del dataset: " << dataset << endl;
        return;
    }

    string nombre_archivo_salida = dataset.substr(dataset.find_last_of("/") + 1);
    ofstream archivo_salida(ruta_ejecucion + "/" + nombre_archivo_salida);
    if (!archivo_salida.is_open()) {
        cerr << "No se pudo crear el archivo de salida para: " << dataset << endl;
        return;
    }

    string linea;
    bool primera_linea = true; // Para incluir encabezado solo una vez
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string string1, string2;
        iss >> string1 >> string2;

        if (string1 == "0") string1 = "";
        if (string2 == "0") string2 = "";

        int suma_tamaños = string1.size() + string2.size();
        string memoria_total = medirMemoria(string1, string2);

        if (primera_linea) {
            archivo_salida << "(tamaño S1+S2, memoria_total [bytes])" << endl;
            primera_linea = false;
        }
        
        archivo_salida << "(" << suma_tamaños << ", " << memoria_total << ")" << endl;
    }

    archivo.close();
    archivo_salida.close();
}

int main() {
    string ruta_ejecucion = obtenerRutaEjecucion();
    if (ruta_ejecucion.empty()) {
        cerr << "Error al crear la estructura de carpetas." << endl;
        return 1;
    }

    // Lista de archivos de dataset a procesar
    vector<string> datasets = {
        "datasets/dataset_cadena_vacia.txt",
        //"datasets/dataset_cadenas_aleatorias.txt",
        "datasets/dataset_palindromos.txt",
        "datasets/dataset_patrones_alternados.txt",
        "datasets/dataset_transposicion.txt",
        "datasets/dataset_repeticiones.txt",
        "datasets/dataset_con_gaps.txt"
    };

    // Procesar cada archivo de dataset y guardar los resultados en la carpeta de ejecución
    for (const auto &dataset : datasets) {
        procesarDataset(dataset, ruta_ejecucion);
    }

    cout << "Las mediciones de memoria se han completado y los resultados se han guardado en la carpeta " << ruta_ejecucion << "." << endl;

    return 0;
}
