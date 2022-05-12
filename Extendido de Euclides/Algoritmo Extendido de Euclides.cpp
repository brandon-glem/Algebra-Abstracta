#include <iostream>

using namespace std;

int euclides_ext(int a, int b, int* x, int* y) {
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

int main()
{
	//ecuaciones diofanticas
	int x, y;
	int a, b, c;

	cout << "ingrese valor de a: ";
	cin >> a;
	cout << endl << "ingrese valor de b: ";
	cin >> b;
	cout << endl << "ingrese valor de c: ";
	cin >> c;

	int mcd = euclides_ext(a, b, &x, &y);
	x = x * (c / mcd);
	y = y * (c / mcd);

	cout << "solucion: " << endl;
	cout << a << "(" << x << ") + " << b << "(" << y << ") = " << c << endl;

	cout << endl << "soluciones para los ejercicios" << endl;
	cout << "ec1: " << " x= " << 22 << "  y= " << -21 << endl;
	cout << "ec2: " << " x= " << -91 << "  y= " << 84 << endl;
	cout << "ec3: " << " x= " << -332 << "  y= " << 330 << endl;
}
