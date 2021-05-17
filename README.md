# binarytree

## Descripción
Esta biblioteca (vichamasoft) y su binario permiten crear un árbol binario y almacenarlo en una base de datos sqlite3, para luego poder encontrar el ancestro común entre dos nodos del árbol binario.
Para crear el árbol  tenemos que invocar al programa con los siguientes parametros:


```
-t [nombre-arbol] -i [valores-separados-por-coma]

```

Por ejemplo 

```
-t ARBOL001 -i 10,8,15,16,7,9

```

Para encontrar el ancestro común entre dos nodos usamos la siguiente combinacion de parametros:

```
-t [nombre-arbol] -f [valores-separados-por-coma]

```

Por ejemplo:

```
-t ARBOL001 -f 7,9

```

## Compilación

Para compilar el programa se utiliza el estandar make.

make all : Para generar el binario.

make clean : Para borrar todos los archivos generados, incluso la base de datos.


## Requisitos

Es necesario instalar la biblioteca sqlite3.

Por ejemplo en Ubuntu:

```
sudo apt-get install sqlite3 libsqlite3-dev
```

## Todo:

Implementar CGI para soportar REST.

Implementar test cases usando Google C++ Testing Framework.
