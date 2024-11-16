#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <iomanip>
#include <regex>

namespace fs = std::filesystem;

// Función para leer los valores de un archivo y almacenar los datos en un map
void leerArchivo(const std::string& archivo, std::map<int, std::vector<double>>& tiempos) {
    std::ifstream inFile(archivo);
    if (!inFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return;
    }

    int longitud;
    double tiempo;
    std::string line;
    while (std::getline(inFile, line)) {
        // Buscar las líneas con el formato "( longitud, tiempo )"
        if (line[0] == '(') {
            size_t commaPos = line.find(',');
            size_t endPos = line.find(')');

            if (commaPos != std::string::npos && endPos != std::string::npos) {
                longitud = std::stoi(line.substr(2, commaPos - 2));
                tiempo = std::stod(line.substr(commaPos + 1, endPos - commaPos - 1));

                tiempos[longitud].push_back(tiempo);
            }
        }
    }
}

// Función para procesar los archivos de cada carpeta de ejecución y acumular sus tiempos
void procesarCarpetas(const std::string& carpeta, std::map<std::string, std::map<int, std::vector<double>>>& resultadosPorArchivo) {
    std::regex ejecucionPattern("^ejecucion_\\d+$"); // Patrón para "ejecucion" seguido de un número

    for (const auto& entry : fs::directory_iterator(carpeta)) {
        if (fs::is_directory(entry)) {
            std::string nombre_carpeta = entry.path().filename().string();
            if (std::regex_match(nombre_carpeta, ejecucionPattern)) { // Solo procesa carpetas que coincidan con el patrón

                // Procesa cada archivo en la carpeta de ejecución
                for (const auto& file : fs::directory_iterator(entry.path())) {
                    if (fs::is_regular_file(file) && file.path().extension() == ".txt") {
                        std::string nombre_archivo = file.path().filename().string();
                        std::map<int, std::vector<double>>& tiempos = resultadosPorArchivo[nombre_archivo];
                        leerArchivo(file.path().string(), tiempos);
                    }
                }
            }
        }
    }
}

// Función para calcular los promedios y escribir el archivo de salida
void calcularPromedios(const std::string& archivoSalida, const std::map<std::string, std::map<int, std::vector<double>>>& resultadosPorArchivo) {
    std::ofstream outFile(archivoSalida);
    if (!outFile.is_open()) {
        std::cerr << "No se pudo crear el archivo de salida: " << archivoSalida << std::endl;
        return;
    }

    for (const auto& [nombre_archivo, tiemposPorLongitud] : resultadosPorArchivo) {
        outFile << "promedio " << nombre_archivo << ":\n";
        for (const auto& [longitud, tiempos] : tiemposPorLongitud) {
            double suma = 0.0;
            for (double tiempo : tiempos) {
                suma += tiempo;
            }
            double promedio = suma / tiempos.size();  // Calcula el promedio

            // Formato de salida: notación científica para números menores a 0.001, fijo para el resto
            outFile << "( " << longitud << ", ";
            if (promedio < 0.001) {
                outFile << std::scientific << std::setprecision(6) << promedio;
            } else {
                outFile << std::fixed << std::setprecision(6) << promedio;
            }
            outFile << " )\n";
        }
        outFile << "--------------------------------------\n";
    }
}

int main() {
    std::string carpetaBase = ".";  // Usa el directorio actual como base
    std::string archivoSalida = "promedios.txt";

    std::map<std::string, std::map<int, std::vector<double>>> resultadosPorArchivo;
    procesarCarpetas(carpetaBase, resultadosPorArchivo);
    calcularPromedios(archivoSalida, resultadosPorArchivo);

    std::cout << "Cálculo de promedios completado y guardado en " << archivoSalida << std::endl;
    return 0;
}
