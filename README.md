# Distancia de Damerau-Levenshtein
Benjamin Andrés Camus Valdés

202173072-9

## Uso
Se puede utilizar Makefile para compilar todos los archivos para luego poder ser ejecutados, usar make clean para limpiar los archivos compilados.

## Requerimientos: 

Para realizar mediciones de memoria se necesita tener instalado valgrind:

```
sudo apt-get update
sudo apt-get install valgrind
```

## Descripcion de los archivos .cpp

### distancia_edicion_DP.cpp
Este código calcula la distancia de edicion extendida utilizando el enfoque de programación dinámica, considerando las operaciones: inserción, eliminación, sustitución y transposición. Este codigo utiliza costos variables para las 4 operaciones mencionadas, para cada una de las operaciones se leen los costos de archivos .txt explicados más abajo. Para utilizar los costos de los archivos .txt la variable global **usar_tablas=true** debe estar en true, de lo contrario se utilizaran los costos default. Este código tiene implementado la automatización de las realización de las pruebas de tiempo utilizando **chrono**, para realizar las pruebas se leen archivos .txt de distintos casos que contienen pares de 2 cadenas, para leer estos archivos y hacer las mediciones de tiempo la variable ( ubicada en main() ) **usar_salida_estandar = false** debe estar en false, de lo contrario se pedirán 2 cadenas por la terminal para realizar el calculo de la distancia de edición de manera indivudal. A su vez dentro de main existe el siguiente vector:
```
  // Archivos de entrada y nombres de archivos de salida
  vector<pair<string, string>> archivos = {
      {"datasets/dataset_cadena_vacia.txt", "res_cadena_vacia.txt"},
      {"datasets/dataset_cadenas_aleatorias.txt", "res_cadena_aleatorias.txt"},
      {"datasets/dataset_palindromos.txt", "res_cadenas_palindromos.txt"},
      {"datasets/dataset_patrones_alternados.txt", "res_patrones_alternados.txt"},
      {"datasets/dataset_transposicion.txt", "res_transposicion.txt"},
      {"datasets/dataset_repeticiones.txt", "res_cadenas_con_repeticiones.txt"},
      {"datasets/dataset_con_gaps.txt", "res_cadenas_con_gaps.txt"}
  };
```
En este vector se pueden agregar o eliminar para que casos de prueba se quieren realizar las pruebas (esto solo si la variable usar_salida_estandar=false).

Este código tambien guarda la ruta o la secuencia de operaciones que se realiza del calculo de la distancia de edicion, la secuencia para transformar un S1 en un S2. los resultados se guardan dentro de la carpeta **carpeta_pruebas_dp**, y cada vez que se ejecuta el código se guardan los resultados dentro de una carpeta *ejecucion_n* donde n es el número de la ejecucion del codigo, los resultados son guardados en archivos .txt con el formato res_nombre_del_caso.txt, como se puede ver en el vector de arriba.

Si usar_salida_estandar = true, se piden 2 cadenas por la entrada estandar y se calcula la distancia de edicion, dando el resultado por la salida estándar.

### ditancia_edicion_BF.cpp
Este código también calcula la distancia de edición pero utilizando el enfoque de fuerza bruta, en donde mediante recursión prueba las 4 operaciones, es por ello que tiene una complejidad de O(m*n), donde m es la longitud de S1 y n la lognitud de S2. Este código implementa las mismas funcionalidades que el anterior como para usar los costos variables o no, usar la salida estandar o no. Los resultados de este codigo son guardados en la carpeta **carpeta_pruebas_bf**.

### distancia_edicion_dp_memory.cpp
Debido a que los codigos anterioires calculan la secuencia de las operaciones realizando operaciones y estructuras adicionales utilizan más memoria de la cual no debe ser medida, es por eso que existe este codigo, el cual es una simplificacion por así decirlo del codigo anterior para el calculo de la distancia de edición mediante el algoritmo de programación dinámica. Este código tanbién utiliza los costos variables al leerlos de archivos .txt, solamente no calcula la secuencia de las operaciones.

### distancia_edicion_BF_memory.cpp
Al igual que el código anterior, este no calcula la secuencia de operaciones realizados en el calculo de la distandia de edicion. Este código implementa el enfoque de fuerza bruta.

### medidor_memoria_BF.cpp
Este código se encarga de automatizar el proceso de la medición de memoria para el código **distancia_edicion_BF_memory.cpp**, para ello utiliza valgrind, leyendo el consumo de memoria total del programa. Este código lee los pares de strings de los .txt con los casos de prueba y se los pasa como parámtros al código de **distancia_edicion_BF_memory.cpp**, luego guarda los resultados de las mediciones de memoria en la carpeta **mediciones_memoria_bf**, dentro con una carpeta de nombre *ejecucion_n* donde n es el número de la ejecucion del codigo.


### medidor_memoria_DP.cpp
Realiza lo mismo que el código anterior pero para el código de **distancia_edicion_dp_memory.cpp** y exporta los resultados de las mediciones de memoria en la carpeta **mediciones_memoria_dp**

###calcular_promedios.cpp
Este codigo se encuentra dentro de las carpetas **carpeta_pruebas_bf** y **carpeta_pruebas_bf**, lo que hace es calcular el promedio de los resultados obtenidos para cada carpeta de nombre *ejecucion_n*, luego exporta los resultados en el archivo promedios.txt.

Ejemplo:
```
 promedio res_cadena_aleatorias.txt:
( 2, 5.893000e-06 )
( 4, 1.415240e-05 )
( 6, 6.164160e-05 )

--------------------------------------
promedio res_cadena_vacia.txt:
( 1, 5.063400e-06 )
( 2, 3.731000e-06 )
( 3, 1.933400e-06 )

--------------------------------------
promedio res_cadenas_con_gaps.txt:
( 1, 4.689000e-06 )
( 2, 3.248200e-06 )
( 3, 2.669200e-06 )

--------------------------------------
promedio res_cadenas_con_repeticiones.txt:
( 2, 7.205400e-06 )
( 4, 1.502040e-05 )
( 6, 8.188300e-05 )

--------------------------------------
```
### datasets/gen_datasets.cpp
Este código es el encargado de generar los casos de prueba, segun los siguientes parámetros:

    int longitudMaxima = 10;
    int incremento = 1;
    ...
    int numGaps = 3;
    int tamanoMaxGap = 2;

Estos parámetros están ubicados en main(), longitudMaxima define cual es el máximo de la longitud que una cadena puede tener en los casos de prueba, incremento dice en cuanto se va a ir incrementado la cadena, en este caso se va a ir incrementando de a un caracter. 
numGaps es utilizado para el caso donde hay una cadena que tiene gaps o espacios vacios entre medio, esta variable nos indica cuantos gaps va a tener la cadena S1, y el tamanoMaxGap dice cual va a ser el tamaño máximo que puede tener ese gap.

## Descripcion de los datasets y archivos .txt

Dentro de la carpeta /datasets se encuentran 7 archivos .txt con los casos de prueba generados por el código gen_datasets.cpp:

- dataset_cadena_vacia.txt
- dataset_cadenas_aleatorias.txt
- dataset_con_gaps.txt
- dataset_palindromos.txt
- dataset_patrones_alternados.txt
- dataset_repeticiones.txt
- dataset_transposicion.txt

### Archivos .txt con los costos para realizar operaciones
 - cost_delete.txt: Se considera como una fila con los costos para eliminar cada una de las 26 letras del alfabeto inglés.
 
 - cost_insert.txt: Se considera como una fila con los costos para insertar cada una de las 26 letras del alfabeto inglés.

 - cost_replace.txt: Una matriz de 26*26 con los costos para remplazar una letra "a" por una letra "b".

 -cost_transpose.txt: Una matriz de 26*26 con los costos para realizar una transposicón de una letra "a" por una letra "b".

## Carpetas y archivos de pruebas

### carpeta_pruebas_bf
Aqui por cada ejecucion del archivo distancia_edicion_BF.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt
Las pruebas se guardan con nombre *ejecucion_n* donde n es el número de la ejecucion del codigo.

### carpeta_pruebas_bf
Aqui por cada ejecucion del archivo distancia_edicion_DP.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt
Las pruebas se guardan con nombre *ejecucion_n* donde n es el número de la ejecucion del codigo.

### mediciones_memoria_bf
Aqui por cada ejecucion del archivo medidor_memoria_BF.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt
Las pruebas se guardan con nombre *ejecucion_n* donde n es el número de la ejecucion del codigo.

### mediciones_memoria_dp
Aqui por cada ejecucion del archivo medidor_memoria_DP.cpp se guardan las pruebas realizadas para caso de prueba en archivos .txt
Las pruebas se guardan con nombre *ejecucion_n* donde n es el número de la ejecucion del codigo.


Dentro de una carpeta *ejecucion_n* se puede encontrar algo como lo siguiente:

```
res_cadena_aleatorias.txt
res_cadena_vacia.txt
res_cadenas_con_gaps.txt
res_cadenas_con_repeticiones.txt
res_cadenas_palindromos.txt
res_patrones_alternados.txt
res_transposicion.txt
```

Un ejemplo de estos archivos:

```
Palabras: s, o
Longitudes: S1=1 S2=1 S1+S2=2
Distancia mínima de edición: 1
Tiempo de ejecución (segundos): 4.498e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: s -> o | Costo: 1
--------------------------------------

Palabras: vq, tm
Longitudes: S1=2 S2=2 S1+S2=4
Distancia mínima de edición: 2
Tiempo de ejecución (segundos): 3.476e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: v -> t | Costo: 1
Sustitución en posición 1: q -> m | Costo: 1
--------------------------------------

Palabras: hbm, dqu
Longitudes: S1=3 S2=3 S1+S2=6
Distancia mínima de edición: 3
Tiempo de ejecución (segundos): 2.795e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: h -> d | Costo: 1
Sustitución en posición 1: b -> q | Costo: 1
Sustitución en posición 2: m -> u | Costo: 1
--------------------------------------

Palabras: lcsz, alnx
Longitudes: S1=4 S2=4 S1+S2=8
Distancia mínima de edición: 4
Tiempo de ejecución (segundos): 2.945e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: l -> a | Costo: 1
Sustitución en posición 1: c -> l | Costo: 1
Sustitución en posición 2: s -> n | Costo: 1
Sustitución en posición 3: z -> x | Costo: 1
--------------------------------------

Palabras: xyzif, vdcwj
Longitudes: S1=5 S2=5 S1+S2=10
Distancia mínima de edición: 5
Tiempo de ejecución (segundos): 3.436e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: x -> v | Costo: 1
Sustitución en posición 1: y -> d | Costo: 1
Sustitución en posición 2: z -> c | Costo: 1
Sustitución en posición 3: i -> w | Costo: 1
Sustitución en posición 4: f -> j | Costo: 1
--------------------------------------

Palabras: irxejs, sqtevl
Longitudes: S1=6 S2=6 S1+S2=12
Distancia mínima de edición: 5
Tiempo de ejecución (segundos): 4.108e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: i -> s | Costo: 1
Sustitución en posición 1: r -> q | Costo: 1
Sustitución en posición 2: x -> t | Costo: 1
Sustitución en posición 4: j -> v | Costo: 1
Sustitución en posición 5: s -> l | Costo: 1
--------------------------------------

Palabras: zgotiqe, vqdtpnb
Longitudes: S1=7 S2=7 S1+S2=14
Distancia mínima de edición: 6
Tiempo de ejecución (segundos): 5.18e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: z -> v | Costo: 1
Sustitución en posición 1: g -> q | Costo: 1
Sustitución en posición 2: o -> d | Costo: 1
Sustitución en posición 4: i -> p | Costo: 1
Sustitución en posición 5: q -> n | Costo: 1
Sustitución en posición 6: e -> b | Costo: 1
--------------------------------------

Palabras: lrdjamaz, sjrmbmrx
Longitudes: S1=8 S2=8 S1+S2=16
Distancia mínima de edición: 7
Tiempo de ejecución (segundos): 5.931e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: l -> s | Costo: 1
Sustitución en posición 1: r -> j | Costo: 1
Sustitución en posición 2: d -> r | Costo: 1
Sustitución en posición 3: j -> m | Costo: 1
Sustitución en posición 4: a -> b | Costo: 1
Sustitución en posición 6: a -> r | Costo: 1
Sustitución en posición 7: z -> x | Costo: 1
--------------------------------------

Palabras: xsdnnleti, uxejmfwdi
Longitudes: S1=9 S2=9 S1+S2=18
Distancia mínima de edición: 8
Tiempo de ejecución (segundos): 7.033e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: x -> u | Costo: 1
Sustitución en posición 1: s -> x | Costo: 1
Sustitución en posición 2: d -> e | Costo: 1
Sustitución en posición 3: n -> j | Costo: 1
Sustitución en posición 4: n -> m | Costo: 1
Sustitución en posición 5: l -> f | Costo: 1
Sustitución en posición 6: e -> w | Costo: 1
Sustitución en posición 7: t -> d | Costo: 1
--------------------------------------

Palabras: gfwgeqqvdr, jwohquufha
Longitudes: S1=10 S2=10 S1+S2=20
Distancia mínima de edición: 9
Tiempo de ejecución (segundos): 7.895e-06
Operaciones necesarias para la distancia mínima de edición:
Eliminación en posición 0 de g | Costo: 1
Sustitución en posición 1: f -> j | Costo: 1
Sustitución en posición 3: g -> o | Costo: 1
Sustitución en posición 4: e -> h | Costo: 1
Inserción en posición 5 de u | Costo: 1
Sustitución en posición 6: q -> u | Costo: 1
Sustitución en posición 7: v -> f | Costo: 1
Sustitución en posición 8: d -> h | Costo: 1
Sustitución en posición 9: r -> a | Costo: 1
--------------------------------------

Palabras: yquxugkbcnj, ktitzalvdeg
Longitudes: S1=11 S2=11 S1+S2=22
Distancia mínima de edición: 11
Tiempo de ejecución (segundos): 8.927e-06
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: y -> k | Costo: 1
Sustitución en posición 1: q -> t | Costo: 1
Sustitución en posición 2: u -> i | Costo: 1
Sustitución en posición 3: x -> t | Costo: 1
Sustitución en posición 4: u -> z | Costo: 1
Sustitución en posición 5: g -> a | Costo: 1
Sustitución en posición 6: k -> l | Costo: 1
Sustitución en posición 7: b -> v | Costo: 1
Sustitución en posición 8: c -> d | Costo: 1
Sustitución en posición 9: n -> e | Costo: 1
Sustitución en posición 10: j -> g | Costo: 1
--------------------------------------

Palabras: bvnrpkyykxoh, ukngnrwzerhx
Longitudes: S1=12 S2=12 S1+S2=24
Distancia mínima de edición: 11
Tiempo de ejecución (segundos): 1.0179e-05
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: b -> u | Costo: 1
Sustitución en posición 1: v -> k | Costo: 1
Sustitución en posición 3: r -> g | Costo: 1
Sustitución en posición 4: p -> n | Costo: 1
Sustitución en posición 5: k -> r | Costo: 1
Sustitución en posición 6: y -> w | Costo: 1
Sustitución en posición 7: y -> z | Costo: 1
Sustitución en posición 8: k -> e | Costo: 1
Sustitución en posición 9: x -> r | Costo: 1
Sustitución en posición 10: o -> h | Costo: 1
Sustitución en posición 11: h -> x | Costo: 1
--------------------------------------

Palabras: qhinnmuohjiyt, gxgfnncacinvg
Longitudes: S1=13 S2=13 S1+S2=26
Distancia mínima de edición: 12
Tiempo de ejecución (segundos): 1.1993e-05
Operaciones necesarias para la distancia mínima de edición:
Sustitución en posición 0: q -> g | Costo: 1
Sustitución en posición 1: h -> x | Costo: 1
Sustitución en posición 2: i -> g | Costo: 1
Sustitución en posición 3: n -> f | Costo: 1
Sustitución en posición 5: m -> n | Costo: 1
Sustitución en posición 6: u -> c | Costo: 1
Sustitución en posición 7: o -> a | Costo: 1
Sustitución en posición 8: h -> c | Costo: 1
Sustitución en posición 9: j -> i | Costo: 1
Sustitución en posición 10: i -> n | Costo: 1
Sustitución en posición 11: y -> v | Costo: 1
Sustitución en posición 12: t -> g | Costo: 1
--------------------------------------

Resumen de Longitudes y Tiempos de Ejecucion:
longitud_S1 + longitudS2, tiempo_ejecucion[seg]
( 2, 4.498e-06 )
( 4, 3.476e-06 )
( 6, 2.795e-06 )
( 8, 2.945e-06 )
( 10, 3.436e-06 )
( 12, 4.108e-06 )
( 14, 5.18e-06 )
( 16, 5.931e-06 )
( 18, 7.033e-06 )
( 20, 7.895e-06 )
( 22, 8.927e-06 )
( 24, 1.0179e-05 )
( 26, 1.1993e-05 )

```


