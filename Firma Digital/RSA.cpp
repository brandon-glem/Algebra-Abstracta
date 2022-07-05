#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h>     
#include <time.h> 
#include <string.h>
#include "sha1.h"


using namespace std;
using namespace NTL;

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

template<class t>
t potencia(t numero, t potencia) {
	t resultado = numero;
	while (potencia > (t)1) {
		resultado = resultado * numero;
		potencia--;
	}
	return resultado;
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

void RSA_KEY(ZZ& k, ZZ& n, ZZ& e, ZZ& d) {
	k = k / 2;
	ZZ p, q;
	p = randongen_primos(k);
	q = randongen_primos(k);
	n = p * q;

	ZZ fi_n = (p - 1) * (q - 1);

	e = 2 + modulo((ZZ)rand(), n - 1);
	ZZ x, y;
	while (euclides_ext(e, fi_n, &x, &y) != (ZZ)1) {
		e = 2 + modulo((ZZ)rand(), n - 1);
	}

	d = inversa(e, fi_n);
}

string ZZToString(ZZ num) {

	string var;
	stringstream y;

	y << num;
	y >> var;
	return var;

}

ZZ stringToZZ(string num) {
	ZZ var;
	stringstream y;

	y << num;
	y >> var;
	return var;

}

ZZ modulo_comun(ZZ cif1, ZZ cif2, ZZ exp1, ZZ exp2, ZZ mod) {
	ZZ u;
	ZZ v;
	euclides_ext(exp1, exp2, &u, &v);
	
	if (u < 0) {
		cif1 = inversa(cif1, mod);
		u = u * (ZZ)-1;
	}
	else {
		cif2 = inversa(cif2, mod);
		v = v * (ZZ)-1;
	}

	ZZ men;
	men = exponensiacion_mod(cif1, u, mod) * exponensiacion_mod(cif2, v, mod);
	return men;	
}

template <class T>
T factorizar(T &num, T factor) {
	factor = (ZZ)2;
	while (modulo(num,factor) != (ZZ)0) {
		factor++;
	}
	num = num / factor;
	return factor;
}

ZZ modulo_peque(ZZ mod, ZZ expo, ZZ cif) {
	ZZ factor = to_ZZ("2");
	ZZ num = mod;
	factor = factorizar(num, factor);

	ZZ fi_n = (num - 1) * (factor - 1);

	ZZ priv = inversa(expo, fi_n);
	ZZ men = exponensiacion_mod(cif, priv, mod);

	return men;
}

string dec_hex(ZZ dec) {
	string hex;
	ZZ residuo;

	while (dec > (ZZ)0) {
		residuo = modulo(dec, (ZZ)16);
		if (residuo == (ZZ)10) {
			hex += 'A';
		}
		else if (residuo == (ZZ)11) {
			hex += 'B';
		}
		else if (residuo == (ZZ)12) {
			hex += 'C';
		}
		else if (residuo == (ZZ)13) {
			hex += 'D';
		}
		else if (residuo == (ZZ)14) {
			hex += 'E';
		}
		else if (residuo == (ZZ)15) {
			hex += 'F';
		}
		else {
			hex += ZZToString(residuo);
		}
		dec /= (ZZ)16;
	}
	reverse(hex.begin(), hex.end());
	return hex;
}

ZZ hex_dec(string hex) {
	ZZ dec;
	ZZ base = (ZZ)1;
	for (int i = hex.size()-1; i >= 0; i--) {
		if (hex[i] >= '0' && hex[i] <= '9') {
			dec += (hex[i] - 48) * base;
			base = base * 16;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F') {
			dec += (hex[i] - 55) * base;
			base = base * 16;
		}
	}

	return dec;
}

string Firma_Digital(string M, ZZ priv, ZZ mod) {
	SHA1 checksum;
	checksum.update(M);
	string m = checksum.final();
	for (int i = 0; i < m.size(); i++) {
		if (m[i] == 'a') {
			m[i] = 'A';
		}
		else if (m[i] == 'b') {
			m[i] = 'B';
		}
		else if (m[i] == 'c') {
			m[i] = 'C';
		}
		else if (m[i] == 'd') {
			m[i] = 'D';
		}
		else if (m[i] == 'e') {
			m[i] = 'E';
		}
		else if (m[i] == 'f') {
			m[i] = 'F';
		}
	}
	cout << "The SHA-1 of \"" << M << "\" is: " << m << endl;

	ZZ mi = hex_dec(m);
	cout << "descimal del hash: " << mi << endl;
	mi = modulo(mi, mod);
	cout << "reduccion al modulo: " << mi << endl;
	mi = exponensiacion_mod(mi, priv, mod);
	cout << "cifrado: " << mi << endl;
	m = dec_hex(mi);

	return m;
}

void Validar_firma(string M, string phi, ZZ publi, ZZ mod) {
	SHA1 checksum;
	checksum.update(M);
	string m = checksum.final();
	for (int i = 0; i < m.size(); i++) {
		if (m[i] == 'a') {
			m[i] = 'A';
		}
		else if (m[i] == 'b') {
			m[i] = 'B';
		}
		else if (m[i] == 'c') {
			m[i] = 'C';
		}
		else if (m[i] == 'd') {
			m[i] = 'D';
		}
		else if (m[i] == 'e') {
			m[i] = 'E';
		}
		else if (m[i] == 'f') {
			m[i] = 'F';
		}
	}
	cout << "The SHA-1 of \"" << M << "\" is: " << m << endl;
	ZZ u = hex_dec(m);
	u = modulo(u, mod);

	ZZ mi = hex_dec(phi);
	cout << "decimal del phi: " << mi << endl;
	mi = exponensiacion_mod(mi, publi, mod);
	cout << "hash reducido al modulo: " << mi << endl;

	if (mi == u)
		cout << "LA FIRMA ES VALIDA" << endl;
	else
		cout << "LA FIRMA ES INVALIDA" << endl;
}

int main(){
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//PRIMER EJERCICIO

	ZZ mod = to_ZZ("999630013489");
	ZZ expo = to_ZZ("65537");
	ZZ cif = to_ZZ("747120213790");

	ZZ men;
	men = modulo_peque(mod, expo, cif);
	cout << "el mensaje es: " << men << endl;
	cout << '\n';

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SEGUNDO EJERCICIO

	ZZ men1 = to_ZZ("35794234179725868774991807832568455403003778024228226193532908190484670252364677411513516052471686245831933544");
	ZZ men2 = to_ZZ("35794234179725868774991807832568455403003778024228226193532908190484670252364665786748759822531352444533388184");
	ZZ e1 = to_ZZ("7");
	ZZ e2 = to_ZZ("11");
	ZZ modulo = to_ZZ("35794234179725868774991807832568455403003778024228226193532908190484670252364677411513516111204504060317568667");

	ZZ mensaje = modulo_comun(men1, men2, e1, e2, modulo);
	cout << "El mensaje es: " << mensaje << endl;
	cout << '\n';
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TERCER EJERCICIO
	srand(time(NULL));

	ZZ n, e, d;
	ZZ bits = to_ZZ("32");
	RSA_KEY(bits, n, e, d);
	cout << "n: " << n << endl << "e: " << e << endl << "d: " << d << endl;
	cout << '\n';

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//PRIMER MENSAJE

	string M = "Algebra Abstracta";
	string phi = Firma_Digital(M, d, n);
	cout << "phi: " << phi << endl;
	cout << '\n';
	string Mpri = "Algebra Abstracta";
	Validar_firma(Mpri, phi, e, n);
	cout << '\n';

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SEGUNDO MENSAJE
	M = "Hola Mundo";
	phi = Firma_Digital(M, d, n);
	cout << "phi: " << phi << endl;
	cout << '\n';
	Mpri = "Hola Mundo";
	Validar_firma(Mpri, phi, e, n);
	cout << '\n';

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TERCER MENSAJE
	M = "Esto si fue dificil";
	phi = Firma_Digital(M, d, n);
	cout << "phi: " << phi << endl;
	cout << '\n';
	Mpri = "Esto si fue dificil";
	Validar_firma(Mpri, phi, e, n);
	cout << '\n';
}