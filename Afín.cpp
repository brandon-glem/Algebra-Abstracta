#include <iostream>
#include <string>

using namespace std;

string alfabeto = "ABCDEFGHIJKLMNnOPQRSTUVWXYZ";

int euclides_ext(int a, int b, int* x, int* y){
	if (a == 0)
	{
		*x = 0, * y = 1;
		return b;
	}

	int x1, y1;
	int gcd = euclides_ext(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

int inversa(int a, int m){
	int x, y;
	int g = euclides_ext(a, m, &x, &y);
	if (g != 1)
		return false;

	else{
		int res = (x % m + m) % m;
		return res;
	}
}

string cifrado(string mensaje, int clav1, int clav2) {
	string cifrado;
	for (int i = 0; i < mensaje.size(); i++) {
		int pos = alfabeto.find(mensaje[i]);
		pos = ((clav1 * pos) + clav2) % alfabeto.size();
		cifrado += alfabeto[pos];
	}
	return cifrado;
}

string descifrado(string mensaje, int clav1, int clav2) {
	int tam = alfabeto.size();
	clav1 = inversa(clav1, tam);
	string descifrado;
	for (int i = 0; i < mensaje.size(); i++) {
		int pos = alfabeto.find(mensaje[i]);
		pos = (pos - clav2) * clav1;
		pos = pos % tam;
		if (pos < 0)
			pos += tam;
		descifrado += alfabeto[pos];
	}
	return descifrado;
}
void romperafin(string mensaje) {
	int tam = alfabeto.size();
	for (int a = 0; a < tam; a++) {
		if (inversa(a, tam) != 0) {
			for (int b = 0; b < tam; b++) {
				cout << "clave a: " << a << "  clave b: " << b << "  mensaje: " << endl;
				string des = descifrado(mensaje, a, b);
				cout << des << endl;
				cout << endl;
			}
		}
	}
}

int main()
{
	int a = 4, b = 7;

	string mensaje1 = "ELEMENTALMIQUERIDOWATSON";
	mensaje1 = cifrado(mensaje1, a, b);
	cout << mensaje1 << endl;

	string mensaje2 = "OKHFSNKFNWFCWJHSNCHQYWFSWF";
	mensaje2 = descifrado(mensaje2, a, b);
	cout << mensaje2 << endl;

	string romper="SLBCMVRBSHZBTnSRQVVMSZBVHnBVRQVLALHZBTnSRQVWQAXLZWnAQFQV";
	romperafin(romper);

	cout << "LA RESPUESTA A ROMPER EL CODIGO ES a = 23 Y b = 17" << endl;
	cout << descifrado(romper, 23, 17) << endl;
}

