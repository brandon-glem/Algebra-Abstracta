La función Miller Rabin permite verificar si un número es primo o no;
de esta manera utilizando el psudo código visto en el laboratorio
pude generar el código para ello.

Para no tener conflictos por el rango de las variables utilice la
librería NTL que permite utilizar números demasiado grandes y también
para no generar conflicto en las operaciones genere mis funciones "modulo",
"exponenciación modular" y "potencia".

La primera parte del algoritmo de Miller Rabin verifica si un número es
compuesto o no a base de exponenciaciones modulares; la segunda parte
prueba "s" cantidades de veces si el numero "n" es compuesto para así poder
determinar si un número es primo o no;

Para determinar qué valor debería tomar "s" en mi código hice pruebas con 
s=2, s=5 y así subiendo de forma secuencial dando como resultado que el
tiempo de respuesta rondaba los 30,31 o 32 segundos dependiendo del uso del
procesador en esos momentos; cuando use s=10, el tiempo de generación disminuyo
considerablemente a 28,27 segundos, de igual manera probe con números
superiores dando tiempos mayores a 30 segundos, en conclusión "s" para mi algoritmo
tomaría el valor de 10.