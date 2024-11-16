# variables
CC = g++
CFLAGS = -Wall -g

# lista de archivos fuente
SOURCES = distancia_edicion_BF.cpp \
          distancia_edicion_BF_memory.cpp \
          distancia_edicion_DP.cpp \
          distancia_edicion_dp_memory.cpp \
          medidor_memoria_BF.cpp \
          medidor_memoria_DP.cpp \
          datasets/gen_datasets.cpp \
          carpeta_pruebas_bf/calcular_promedios.cpp \
          carpeta_pruebas_dp/calcular_promedios.cpp

# generar ejecutables con nombres basados en los archivos fuente
EXECUTABLES = $(SOURCES:.cpp=)

# regla principal
all: $(EXECUTABLES)

# regla para compilar cada ejecutable
%: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# limpieza
clean:
	rm -f $(EXECUTABLES)
