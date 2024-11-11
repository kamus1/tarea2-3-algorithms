# tarea2-3-algorithms
Benjamin Camus

202173072-9

## Requerimientos: 

Para realizar mediciones de memoria se necesita tener instalado valgrind:

sudo apt-get update
sudo apt-get install valgrind

## Descripcion de los archivos .cpp

### distancia_edicion_DP.cpp

### ditancia_edicion_BF.cpp

### medidor_memoria_dp.cpp

### medidor_memoria_bf.cpp

### distancia_edicion_dp_memory.cpp

### distancia_edicion_bf_memory.cpp


### edicion_mod.cpp

Solo es la estructura básica del algoritmo de la distancia de edición utilizando dp, este archivo fue usado solamente para hacer pruebas

### datasets/gen_datasets.cpp

## Descripcion de los datasets y archivos .txt

Dentro de la carpeta /datasets se encuentran 7 archivos .txt con los casos de prueba generados por el código gen_datasets.cpp:

- datasets_cadena_vacia.txt
- dataset_cadenas_aleatorias
- dataset_con_gaps
- dataset_palindromos
- dataset_patrones_alternados
- dataset_repeticiones
- dataset_transposicion

### Archivos .txt con los costos para realizar operaciones
 - cost_delete.txt: Se considera como una fila con los costos para eliminar cada una de las 26 letras del alfabeto inglés.
 
 - cost_insert.txt: Se considera como una fila con los costos para insertar cada una de las 26 letras del alfabeto inglés.

 - cost_replace.txt: Una matriz de 26*26 con los costos para remplazar una letra "a" por una letra "b".

 -cost_transpose.txt: Una matriz de 26*26 con los costos para realizar una transposicón de una letra "a" por una letra "b".


## Carpetas y archivos de pruebas

### carpeta_pruebas_bf
Aqui por cada ejecucion del archivo distancia_edicion_BF.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt

### carpeta_pruebas_bf
Aqui por cada ejecucion del archivo distancia_edicion_DP.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt

### mediciones_memoria_bf

### mediciones_memoria_dp