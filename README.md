# binarytree

Esta biblioteca (vichamasoft) y su binario permite crear un arbol binario y almacenarlo en una base de datos sqlite3, para luego poder encontrar el ancestro común entre dos nodos del arbol binario.
Para crear el arbol  tenemos que invocar al programa con los siguientes parametros:

-t [nombre-arbol] -i [valores-separados-por-coma]

Por ejemplo 
-t ARBOL001 -i 10,8,15,16,7,9

Para encontrar el ancestro común entre dos nodos usamos la siguiente combinacion de parametros:

-t [nombre-arbol] -f [valores-separados-por-coma]

Por ejemplo:
-t ARBOL001 -f 7,9


Compilar:
Para compilar el programa se utiliza el estandar make.

make all : Para generar el binario.

make clean : Para borrar todos los archivos generados, incluso la base de datos.


Requisitos:
Instalar la biblioteca sqlite3.

Todo:
Implementar CGI para soportar REST.
Implementar test cases usando Google C++ Testing Framework.
