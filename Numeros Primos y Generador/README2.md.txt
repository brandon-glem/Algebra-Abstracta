Para poder generar un primo de n cantidad de bits utilice 2 funciones:
1. la primera permite generar un numero de n bits, utilizando un numero
aleatorio desde 0 hasta la potencia de 2 elevado a la cantidad de bits
menos uno y usando otro número igual de grande y usando la operación or
binaria y retornando el número que es impar.

2. la segunda usa el numero generado en la parte anterior y lo somete al test
de Miller Rabin, si el número es compuesto se suma dos ya que el número es impar
y hacer más fácil el hallar un primo; una vez el número supere el test
tendremos un numero de n bits que es primo.
Y utilizamos para esta parte la misma variable s que utilizamos para el caso
anterior cuando generamos números primos de 3, 4 y 5 cifras ya que tenemos una
eficiencia significativa.
