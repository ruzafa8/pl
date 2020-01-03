INTÉRPRETE DE PSEUDOCÓDIGO

Autores:
Alejandro José Ruzafa Casás
Brais Pardo Ramos


En esta práctica hemos desarrollado un intérprete 
de un pequeño pseudocódigo.

Contiene instrucciones básicas de declaración y 
asignación de variables:
	x : Entero
	y : Caracter = 'a'
	x = 3
	a :
sentencias iterativas:

	a = 0
	repite x veces a = a * 2 .
	mientras a >= 0 haz a = a - 1 .

sentencias selectivas:
	p : Proposicion
	se a < 18 daquela p = Falso se non p = Verdadero .

una __________:
	imprime p
	imprime a - x


Los ficheros que hay en el proyecto son:
	- lexer.l
	- parser.y
	- Makefile
	- bool.h / .c => Para gestionar la variable de tipo Proposicion
	- error.h => Para gestionar los errores a nivel semántico 
		    (Por ejemplo, poner un Caracter en la condición del if,
		     ya que, a nivel sintáctico no se distinguen tipos 
		     o intentar asignar un valor a una variable que no existe).
	- expression.h / .c => Para encapsular el tipo y el valor de una expresión
	- ExpressionStatement.h /.c => Encapsula las expresiones sin evaluarlas.
	- hash_table.c / .h => Para gestionar las variables del programa.
	- statement.c /.h => Para encapsular las sentencias y montar el arbol de ejecución.



A la hora de tratar errores, se ha creado en el fichero error.h un enumerado
que se utiliza como código de error y salida en aquellas operaciones que pueden tener errores,
por ejemplo, de tipado. Estos errores son indicados al usuario dependiendo de como hayan
ocurrido.
    Ej. 
	Var : Entero = 2
	Bar : Proposicion = Verdadero
	imprime ( Var / Bar)
    >$ Error linea, operación no definida para los tipos Entero y Proposicion


Se ha dado soporte parcial para arrays simples, pero debido a errores en la asignación de valores a
las posiciones del mismo, estos no funcionan en el programa final. El soporte en el parser
esta aún incluido en el fichero parser.y
