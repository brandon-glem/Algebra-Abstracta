#include <iostream>
#include <string>
#include <vector>

using namespace std;

string alfabeto = "ABCDEFGHIJKLMNnOPQRSTUVWXYZ";

vector<int> euclides_ext(int a, int b) {
	int x, y, d;
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
		vector<int> gcd = { d, x, y };
		return gcd;
	}
	int x1 = 0, x2 = 1, y1 = 1, y2 = 0;
	while (b > 0) {
		int q = a / b;
		int r = a - (q * b);
		x = x2 - (q * x1);
		y = y2 - (q * y1);
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}
	d = a;
	x = x2;
	y = y2;
	vector<int> gcd = { d,x,y };
	return gcd;
}

int inversa(int a, int b) {
	vector<int> x;
	x = euclides_ext(a, b);
	int inverso;
	inverso = ((x[1] % b) + b) % b;
	return inverso;
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

int main()
{
	int a = 4, b = 7;

	string mensaje1 = "ELEMENTALMIQUERIDOWATSON";
	mensaje1 = cifrado(mensaje1, a, b);
	cout << mensaje1 << endl;

	string mensaje2 = "OKHFSNKFNWFCWJHSNCHQYWFSWF";
	mensaje2 = descifrado(mensaje2, a, b);
	cout << mensaje2 << endl;
}
