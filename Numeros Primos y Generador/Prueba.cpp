#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h>     
#include <time.h> 
#include <math.h>

using namespace std;
using namespace NTL;

template<class t>
t potencia(t numero, t potencia) {
	t resultado = numero;
	while (potencia > (t)1) {
		resultado = resultado * numero;
		potencia--;
	}
	return resultado;
}

template<class T>
T modulo(T dividendo, T divisor) {
	T cociente = dividendo / divisor;
	T residuo = dividendo - cociente * divisor;

	if (dividendo < 0) {
		residuo = divisor + residuo;
		return residuo;
	}
	return residuo;
}

template <class T>
T exponensiacion(T base, T exponente, T mod) {
	T resultado = (T)1;
	while (exponente > 0) {
		if ((exponente & 1) > 0) {
			resultado = modulo(resultado * base, mod);
		}
		exponente >>= 1;
		base = (base * base) % mod;
	}
	return resultado;
}

bool ES_COMPUESTO(ZZ a, ZZ n, ZZ t, ZZ u) {
	ZZ x = exponensiacion<ZZ>(a, u, n);
	if ((x == 1) || (x == (n - 1))) {
		return false;
	}
	for (int i = 1; i <= t; i++) {
		x = exponensiacion(x, (ZZ) 2, n);
		if (x == (n - 1)) {
			return false;
		}
	}
	return true;
}

bool MILLER_RABIN(ZZ n, ZZ s) {
	ZZ t = to_ZZ("0");
	ZZ u = n - 1;
	while (modulo(u, (ZZ)2) == 0) {
		u = u / 2;
		t = t + 1;
	}
	for (int i = 1; i <= s; i++) {
		ZZ a = 2 + modulo((ZZ)rand(), n - 1);
		if (ES_COMPUESTO(a, n, t, u)) {
			return false;
		}
	}
	return true;
}

ZZ randon_bits(ZZ b) {
	ZZ pote1 = potencia((ZZ)2, b) - 1;
	ZZ n = modulo((ZZ)rand(),pote1);
	ZZ m = potencia((ZZ)2, b-1) + 1;
	n = n | m;
	return n;
}

ZZ randongen_primos(ZZ b) {
	ZZ s = to_ZZ("10");
	ZZ n = randon_bits(b);
	while (MILLER_RABIN(n, s) == false) {
		n = n + 2;
	}
	return n;
}

int main()
{
	srand(time(NULL));
	ZZ a = to_ZZ("100");
	for (; a < 100000; a++) {
		if (MILLER_RABIN(a, (ZZ)10)) {
			cout << a << "  ";
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << endl << "GENERADOR DE NUMEROS PRIMOS:" << endl;
	ZZ bits = to_ZZ("16");
	for (int i = 0; i < 3; i++) {
		cout << "numeros de " << bits << " bits: ";
		for (int j = 0; j < 3; j++) {
			cout << randongen_primos(bits)<<"   ";
		}
		bits *= 2;
		cout << endl;
	}
}