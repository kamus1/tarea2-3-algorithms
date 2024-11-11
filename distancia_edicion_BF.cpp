#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
using namespace chrono;

// Matrices de costos para reemplazar y transponer letras (26x26)
vector<vector<int>> matriz_costos_replace(26, vector<int>(26));
vector<vector<int>> matriz_costos_transpose(26, vector<int>(26));

// Tablas para eliminar e insertar letras (26 letras del alfabeto inglés)
vector<int> tabla_costos_delete(26);
vector<int> tabla_costos_insert(26);

// Variable para usar las tablas o matrices; si es false, usa costos por defecto
bool usar_tablas = true;

// Variable global para almacenar las operaciones
vector<string> operaciones_globales;

// Funciones para cargar los datos de los .txt en las matrices y tablas
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

int indice_caracter(char c) {
    return c - 'a';
}

// Funciones de costos
int costo_sub(char a, char b) {
    int costo = 1; // Costo default
    if (!usar_tablas) {
        if (a == b) return 0;
    }
    if (usar_tablas) {
        costo = matriz_costos_replace[indice_caracter(a)][indice_caracter(b)];
    }
    return costo;
}

int costo_ins(char b) {
    int costo = 1; // Costo default
    if (usar_tablas) {
        costo = tabla_costos_insert[indice_caracter(b)];
    }
    return costo;
}

int costo_del(char a) {
    int costo = 1; // Costo default
    if (usar_tablas) {
        costo = tabla_costos_delete[indice_caracter(a)];
    }
    return costo;
}

int costo_trans(char a, char b) {
    int costo = 1; // Costo default
    if (usar_tablas) {
        costo = matriz_costos_transpose[indice_caracter(a)][indice_caracter(b)];
    }
    return costo;
}

// Función recursiva para calcular la distancia de edición y registrar las operaciones
int distancia_fuerza_bruta(const string& string1, const string& string2, int index_s1, int index_s2, vector<string>& operaciones) {
    if (index_s1 == 0) {
        int costo_total = 0;
        for (int k = index_s2 - 1; k >= 0; --k) {
            char c = string2[k];
            int costo = costo_ins(c);
            costo_total += costo;
            operaciones.push_back("Inserción: " + string(1, c) + " | Costo: " + to_string(costo));
        }
        return costo_total;
    }
    if (index_s2 == 0) {
        int costo_total = 0;
        for (int k = index_s1 - 1; k >= 0; --k) {
            char c = string1[k];
            int costo = costo_del(c);
            costo_total += costo;
            operaciones.push_back("Eliminación: " + string(1, c) + " | Costo: " + to_string(costo));
        }
        return costo_total;
    }

    vector<string> operaciones_sub, operaciones_ins, operaciones_del, operaciones_trans;

    // Sustitución
    int costo_sustitucion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2 - 1, operaciones_sub);
    int costo_op_sub = costo_sub(string1[index_s1 - 1], string2[index_s2 - 1]);
    costo_sustitucion += costo_op_sub;
    if (costo_op_sub > 0) {
        operaciones_sub.push_back("Sustitución: " + string(1, string1[index_s1 - 1]) + " -> " + string(1, string2[index_s2 - 1]) + " | Costo: " + to_string(costo_op_sub));
    }

    // Inserción
    int costo_insercion = distancia_fuerza_bruta(string1, string2, index_s1, index_s2 - 1, operaciones_ins);
    int costo_op_ins = costo_ins(string2[index_s2 - 1]);
    costo_insercion += costo_op_ins;
    operaciones_ins.push_back("Inserción: " + string(1, string2[index_s2 - 1]) + " | Costo: " + to_string(costo_op_ins));

    // Eliminación
    int costo_eliminacion = distancia_fuerza_bruta(string1, string2, index_s1 - 1, index_s2, operaciones_del);
    int costo_op_del = costo_del(string1[index_s1 - 1]);
    costo_eliminacion += costo_op_del;
    operaciones_del.push_back("Eliminación: " + string(1, string1[index_s1 - 1]) + " | Costo: " + to_string(costo_op_del));

    // Transposición
    int costo_transposicion = INT_MAX;
    if (index_s1 > 1 && index_s2 > 1 && string1[index_s1 - 1] == string2[index_s2 - 2] && string1[index_s1 - 2] == string2[index_s2 - 1]) {
        costo_transposicion = distancia_fuerza_bruta(string1, string2, index_s1 - 2, index_s2 - 2, operaciones_trans);
        int costo_op_trans = costo_trans(string1[index_s1 - 2], string1[index_s1 - 1]);
        costo_transposicion += costo_op_trans;
        operaciones_trans.push_back("Transposición: " + string(1, string1[index_s1 - 2]) + " <-> " + string(1, string1[index_s1 - 1]) + " | Costo: " + to_string(costo_op_trans));
    }

    // Seleccionar la operación con el menor costo
    int min_cost = costo_sustitucion;
    vector<string>* min_operaciones = &operaciones_sub;

    if (costo_insercion < min_cost) {
        min_cost = costo_insercion;
        min_operaciones = &operaciones_ins;
    }
    if (costo_eliminacion < min_cost) {
        min_cost = costo_eliminacion;
        min_operaciones = &operaciones_del;
    }
    if (costo_transposicion < min_cost) {
        min_cost = costo_transposicion;
        min_operaciones = &operaciones_trans;
    }

    operaciones = *min_operaciones;
    return min_cost;
}

int calcular_distancia_fuerza_bruta(const string& string1, const string& string2) {
    operaciones_globales.clear(); // Limpiar las operaciones previas
    vector<string> operaciones_temp;
    int distancia = distancia_fuerza_bruta(string1, string2, string1.size(), string2.size(), operaciones_temp);
    // Las operaciones se almacenan en orden inverso, las invertimos
    reverse(operaciones_temp.begin(), operaciones_temp.end());
    operaciones_globales = operaciones_temp;
    return distancia;
}

// Función para crear un directorio si no existe
bool crearDirectorio(const string &path) {
    #if defined(_WIN32)
        return _mkdir(path.c_str()) == 0 || errno == EEXIST;
    #else 
        return mkdir(path.c_str(), 0777) == 0 || errno == EEXIST;
    #endif
}

string obtenerRutaEjecucion() {
    string ruta_base = "carpeta_pruebas_bf";
    if (!crearDirectorio(ruta_base)) {
        cerr << "Error al crear la carpeta base." << endl;
        return "";
    }

    int numero_ejecucion = 1;
    string ruta_ejecucion;
    while (true) {
        ruta_ejecucion = ruta_base + "/ejecucion_" + to_string(numero_ejecucion);
        struct stat info;
        if (stat(ruta_ejecucion.c_str(), &info) != 0) {
            if (crearDirectorio(ruta_ejecucion)) {
                break;
            } else {
                cerr << "Error al crear la carpeta de ejecución: " << ruta_ejecucion << endl;
                return "";
            }
        } else {
            numero_ejecucion++;
        }
    }
    return ruta_ejecucion;
}

void procesarArchivo(const string &archivoEntrada, const string &rutaEjecucion, const string &nombreArchivoSalida) {
    ifstream archivo(archivoEntrada);
    string archivoSalida = rutaEjecucion + "/" + nombreArchivoSalida;
    ofstream archivoResultado(archivoSalida);
    if (!archivo) {
        cerr << "Error al abrir el archivo de entrada: " << archivoEntrada << endl;
        return;
    }
    if (!archivoResultado) {
        cerr << "Error al abrir el archivo de salida: " << archivoSalida << endl;
        return;
    }

    string linea;
    vector<tuple<int, int, double>> resumenResultados;

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string string1, string2;
        iss >> string1 >> string2;

        if (string1 == "0") string1 = "";
        if (string2 == "0") string2 = "";

        int longitudS1 = string1.size();
        int longitudS2 = string2.size();

        auto inicio = chrono::high_resolution_clock::now();
        int distancia = calcular_distancia_fuerza_bruta(string1, string2);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration<double>(fin - inicio);
        double tiempo_ejecucion = duracion.count();

        archivoResultado << "Palabras: " << string1 << ", " << string2 << endl;
        archivoResultado << "Longitudes: S1=" << longitudS1 << " S2=" << longitudS2 << " S1+S2=" << longitudS1 + longitudS2 << endl;
        archivoResultado << "Distancia mínima de edición: " << distancia << endl;
        archivoResultado << "Tiempo de ejecución (segundos): " << tiempo_ejecucion << endl;

        archivoResultado << "Operaciones necesarias para la distancia mínima de edición:\n";
        for (const auto &operacion : operaciones_globales) {
            archivoResultado << operacion << endl;
        }

        archivoResultado << "--------------------------------------" << endl << endl;
        resumenResultados.push_back(make_tuple(longitudS1, longitudS2, tiempo_ejecucion));
    }

    archivoResultado << "Resumen de Longitudes y Tiempos de Ejecución:\n";
    archivoResultado << "longitud_S1 + longitudS2, tiempo_ejecucion[seg]" << endl;
    for (const auto &resumen : resumenResultados) {
        archivoResultado << "( " << get<0>(resumen) + get<1>(resumen) << ", " << get<2>(resumen) << " )" << endl;
    }

    archivo.close();
    archivoResultado.close();
}

int main() {
    // Cargar los costos desde los archivos .txt
    cargar_cost_insert("cost_insert.txt");
    cargar_cost_delete("cost_delete.txt");
    cargar_cost_replace("cost_replace.txt");
    cargar_cost_transpose("cost_transpose.txt");

    // Variable para alternar entre salida estándar y procesamiento de archivos
    bool usar_salida_estandar = false;

    if (usar_salida_estandar) {
        // Ejemplo de cálculo con salida estándar
        string S1 = "hola";
        string S2 = "joale";

        cout << "Ingrese S1: ";
        cin >> S1;
        cout << "Ingrese S2: ";
        cin >> S2;

        auto inicio = chrono::high_resolution_clock::now();
        int distancia = calcular_distancia_fuerza_bruta(S1, S2);
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration<double>(fin - inicio);
        double tiempo_ejecucion = duracion.count();

        cout << "Distancia mínima de edición: " << distancia << endl;
        cout << "Tiempo de ejecución (segundos): " << tiempo_ejecucion << endl;

        cout << "Operaciones necesarias para la distancia mínima de edición:\n";
        for (const auto &operacion : operaciones_globales) {
            cout << operacion << endl;
        }
    } else {
        // Crear la carpeta para la ejecución actual
        string rutaEjecucion = obtenerRutaEjecucion();
        if (rutaEjecucion.empty()) {
            cerr << "Error al crear la estructura de carpetas." << endl;
            return 1;
        }

        // Procesamiento de archivos y guardado de resultados en archivos
        vector<pair<string, string>> archivos = {
            //{"datasets/dataset_cadena_vacia.txt", "res_cadena_vacia.txt"},
            //{"datasets/dataset_cadenas_aleatorias.txt", "res_cadena_aleatorias.txt"},
            //{"datasets/dataset_palindromos.txt", "res_cadenas_palindromos.txt"},
            {"datasets/dataset_patrones_alternados.txt", "res_patrones_alternados.txt"},
            //{"datasets/dataset_transposicion.txt", "res_transposicion.txt"},
            //{"datasets/dataset_repeticiones.txt", "res_cadenas_con_repeticiones.txt"},
            //{"datasets/dataset_con_gaps.txt", "res_cadenas_con_gaps.txt"}
        };

        for (const auto &par : archivos) {
            procesarArchivo(par.first, rutaEjecucion, par.second);
        }

        cout << "El procesamiento ha finalizado y los resultados se han guardado en la carpeta " << rutaEjecucion << "." << endl;
    }

    return 0;
}
