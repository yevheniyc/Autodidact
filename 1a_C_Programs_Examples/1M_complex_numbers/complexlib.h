/*
	complexlib.h - Yevheniy Chuba - 01/26/2016
	library for working with complex numbers
*/

typedef struct {
	double real;
	double imag;
} complex; // name of the struct type

// define function prototypes that will return complex type
complex add(complex addend, complex augend);
complex subtract(complex minuend, complex subtrahend);
complex multiply(complex multiplier, complex multiplicand);
complex power(complex base, int degree);
// return pointer to char type
char *print_complex(complex value);

complex add(complex addend, complex augend) {
	complex result;

	result.real = addend.real + augend.real;
	result.imag = addend.imag + augend.imag;

	return result;
}

complex subtract(complex minuend, complex subtrahend) {
	complex result;

	result.real = minuend.real - subtrahend.real;
	result.imag = minuend.imag - subtrahend.imag;

	return result;
}

complex multiply(complex multiplier, complex multiplicand) {
	complex result;

	result.real = multiplier.real * multiplicand.real 
				  - multiplier.imag * multiplicand.imag;

	result.imag = multiplier.real * multiplicand.imag
				  - multiplier.imag * multiplicand.real;

	return result;
}

complex power(complex base, int degree) {
	complex result;
	int i;

	result.real = 1.0;
	result.imag = 0.0;

	for (i = 1; i <= degree; i++)
		result = multiply(result, base);

	return result;
}

char *print_complex(complex value) {
	// sprintf writes into provided buffer (a string array)
	static char buffer[133];

	if (value.imag < 0.0)
		sprintf(buffer, "%f-%fi\0", value.real, -value.imag);
	else
		sprintf(buffer, "%f+%fi\0", value.real, value.imag);

	return buffer;
}