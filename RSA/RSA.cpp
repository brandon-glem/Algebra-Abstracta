#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h>     
#include <time.h> 

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
T exponensiacion_mod(T base, T exponente, T mod) {
	T resultado = (T)1;
	while (exponente > 0) {
		if ((exponente & 1) > 0) {
			resultado = modulo(resultado * base, mod);
		}
		exponente >>= 1;
		base = modulo((base * base), mod);
	}
	return resultado;
}

template<class T>
T euclides_ext(T a, T b, T* x, T* y) {
	if (a == (T)0) {
		*x = (T)0;
		*y = (T)1;
		return b;
	}

	T x1, y1;
	T gcd = euclides_ext(modulo(b,a), a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

template<class T>
T inversa(T a, T m) {
	T x, y;
	T g = euclides_ext(a, m, &x, &y);
	if (g != (T)1)
		return (T)false;

	else {
		T res = modulo(modulo(x, m + m), m);
		return res;
	}
}

bool ES_COMPUESTO(ZZ a, ZZ n, ZZ t, ZZ u) {
	ZZ x = exponensiacion_mod<ZZ>(a, u, n);
	if ((x == 1) || (x == (n - 1))) {
		return false;
	}
	for (int i = 1; i <= t; i++) {
		x = exponensiacion_mod(x, (ZZ)2, n);
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
	ZZ n = modulo((ZZ)rand(), pote1);
	ZZ m = potencia((ZZ)2, b - 1) + 1;
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

void RSA_KEY(ZZ &k, ZZ &n, ZZ &e, ZZ &d) {
	k = k / 2;
	ZZ p, q;
	p = randongen_primos(k);
	q = randongen_primos(k);
	//cout << "p: " << p << endl << "q: " << q << endl;
	n = p * q;

	ZZ fi_n = (p - 1) * (q - 1);
	//cout << "fi_n: " << fi_n << endl;
	
	e = 2 + modulo((ZZ)rand(), n - 1);
	ZZ x, y;
	while (euclides_ext(e, fi_n, &x, &y) != (ZZ)1) {
		e = 2 + modulo((ZZ)rand(), n - 1);
	}

	d = inversa(e, fi_n);
}

int main(){
	srand(time(NULL));
	/*
	ZZ n, e, d;
	ZZ bits = to_ZZ("64");
	RSA_KEY(bits, n, e, d);
	cout << "n: " << n << endl << "e: " << e << endl << "d: " << d << endl;
	*/

	ZZ n = to_ZZ("4611788861944128493");
	ZZ e = to_ZZ("4985");
	ZZ d = to_ZZ("3064966195665298373");

	cout << "e: " << e << endl << "d: " << d << endl << "n: " << n << endl;
	cout << '\n';

	ZZ c, de;
	cout << "   m	|" << "	c		|" << "   m'" << endl;

	for (int i = 0; i < 10; i++) {
		ZZ m = 5 + modulo((ZZ)rand(), (ZZ)1000);
		c = exponensiacion_mod(m, e, n);
		de = exponensiacion_mod(c, d, n);

		cout << m << "	|" << c << "	|" << de << endl;
	}
}