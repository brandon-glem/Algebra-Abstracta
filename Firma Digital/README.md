Ejercicio 1:
Para poder romper el algoritmo RSA en este ejercicio usaremos la factorización del módulo, ya que si podemos factorizar el modulo podemos hallar el phi-n y con ello podemos hallar con facilidad la inversa de la clave publica con phi-n, como resultado obtendremos la clave privada.
Entonces:
1. Creamos la función para poder romper el algoritmo RSA que tendrá como argumentos el mensaje cifrado, la clave publica y el módulo.
2. Creamos una variable que almacenara uno de los dos números que al multiplicarse dan como resultado el módulo.
3. Usamos la función factorizar que va dividiendo el numero hasta encontrar “p” y “q” que dan como resultado el módulo.
4. Teniendo “p” y “q” obtenemos phi-n = (p-1) * (q-1).
5. Para hallar la clave privada calculamos la inversa de la clave publica con modulo phi-n.
6. Por último, para hallar el mensaje, realizamos la exponenciación modular con el mensaje cifrado elevado a la clave privada que hallamos en el paso anterior con modulo n.
7. Finalizamos obteniendo el mensaje.
Ejercicio 2:
Para obtener un mensaje cifrado con RSA sabiendo que la persona que cifro el mismo mensaje con el mismo modulo, pero diferente clave publica para 2 personas podemos utilizar el ataque por modulo común que consiste en:
1. Creamos una función “modulo_comun” que tiene como parámetros las 2 claves públicas, los dos mensajes cifrados y el módulo común.
2. Como tenemos dos claves publicas diferentes podemos hallar un “u” y un “v” ya que las claves publicas son primos entre sí; para ello usamos el algoritmo extendido de Euclides.
3. Con ello nos daremos cuenta que uno tiene valor positivo y el otro tiene valor negativo; por lo tanto, al que tiene el valor negativo lo volvemos positivo y le calculamos la inversa a su correspondiente mensaje cifrado.
4. Por último, calculamos 𝑐𝑐1𝑢𝑢 × 𝑐𝑐2′𝑣𝑣 𝑚𝑚𝑚𝑚𝑚𝑚 𝑛𝑛
5. Con ello obtendremos el mensaje enviado a los dos destinatarios.