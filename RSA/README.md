El algoritmo RSA funciona de la siguiente manera:

1) Tenemos que generar 2 numeros primos distintos pero de igual tamaño ("p" y "q") y para ello usamos
	el generador de primos que utiliza los k-bits para generar un numero impar y que es sometido al test de Miller Rabin con un grado de confianza
	de 10 (s=10) ya que es el de mayor eficiencia demostrado en proyectos
	anteriores.

2) Ahora calculamos en "n" que nos servira como modulo de ambas claves tanto
	con la publica como la privada; y n resulta de multiplicar p y q.

3) Calculamos el phi_n que permitira generar la clave publica como privada,
	resulta de multiplicar (p-1) por (q-1); ya que nos vasamos en dos
	propiedades del teorema de Euler: 
		. Phi_p es igual a p - 1 siempre y cuando p sea primo.
		. Si p y q son primos entre si entonces phi_nm = phi_n * phi_m.

4) Teniendo el phi_n podemos calcular la clave publica que sera de
	conocimiento de todos("e"), y resulta de encontrar un numero aleatorio
	que sea mayor que 2 y menor que n-1; pero este numero aleatorio tiene que
	cumplir una condicion basica, que el maximo con un divisor de "e" y "phi_n"
	tiene que ser 1, es decir que deben de ser coprimos.

5) Para que ello se cumpla usamos el teorema extendido de Euclides con "e" y 
	"phi_n" y lo colocamos como condicional del bucle hasta que se cumpla.

6) Por ultimo para calcular la clave privada que sera solo de nuestro propio
	conocimiento usamos la inversa modular de la clave publica con modulo
	"phi_n" ya que asi podremos regresar al texto original del mensaje cifrado.



Con ello tendiamos la Clave Publica(e), la Clave Privada (d) y el modulo para ambas(n)

.Para poder cifrar usamos la exponenciacion modular:
	1) Tomamos un numero aleatorio cualquiera de preferencia distinto a 0 y 1
	2) Ese numero lo elevamos a la clave publica "e" y le sacamos el modulo "n".
	3) Con ello obtendremos el numero cifrado.

.Para poder descifrar el numero usaremos tambien la exponenciacion modular:
	1) Tomamos el numero cifrado.
	2) Lo elevamos esta vez a la clave privada "d" y le sacomos el modulo "n"
	3) Si es que encontramos bien la inversa de la clave publica, obtendremos
		como resultado el numero original antes de ser cifrado.



COMO EJEMPLO TENDRIAMOS ESTE CASO(usando 64 bits):

e: 4985
d: 3064966195665298373
n: 4611788861944128493

   m    |       c               |   m'
745     |2039321628932792406    |745
307     |1416670392868296858    |307
922     |2321976021843095846    |922
233     |3194628268882604072    |233
101     |3130805720757795435    |101
40      |306682214556398497     |40
703     |470242590856535917     |703
661     |3762674751224318582    |661
849     |3427263166431256161    |849
631     |44164471731254934      |631