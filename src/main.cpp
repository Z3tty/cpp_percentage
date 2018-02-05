#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <string>

// Class for defining percentages (0-100)
// Although this can trivially be done with unsigned ints
// this class gives more or less full support for it as a type
class percentage {
public:

	// Conversion functions
	// Semi-trivial, they do however make conversions slightly faster to do, with less syntax
	// Essentially replaces the following:
	// (type)p.retrieve()
	// std::to_string(p.retrieve())
	// (type)p->retrieve()
	// std::to_string(p->retrieve())
	int toInt(void);
	float toFloat(void);
	double toDouble(void);
	std::string toString(void);

	// Since the value itself is protected, we need a wrapper
	unsigned int retrieve(void) { return this->value; }
	percentage(unsigned int p); 	// Constructor
	void realloc(unsigned int v);	// Set the value, essentially re-constructing the object

	// Exponentiation does not have its own sign, so it gets its own function
	void expp(unsigned int e);

	// Operator overloading, nothing too fancy; quite simply wrappers for operations
	friend std::ostream& operator<<(std::ostream& os, const percentage& p);
	percentage operator+(const percentage& p)   { percentage r(this->value + p.value); return r; }
	percentage operator-(const percentage& p)   { percentage r(this->value - p.value); return r; }
	percentage operator/(const percentage& p)   { percentage r(this->value / p.value); return r; }
	percentage operator*(const percentage& p)   { percentage r(this->value * p.value); return r; }
	percentage operator%(const percentage& p)   { percentage r(this->value % p.value); return r; }
	percentage operator+=(const percentage& p)  { this->addp(p); percentage r(this->value); return r; }
	percentage operator-=(const percentage& p)  { this->subp(p); percentage r(this->value); return r; }
	percentage operator/=(const percentage& p)  { this->divp(p); percentage r(this->value); return r; }
	percentage operator*=(const percentage& p)  { this->mulp(p); percentage r(this->value); return r; }
	percentage operator%=(const percentage& p)  { this->modp(p); percentage r(this->value); return r; }
	percentage operator+(const unsigned int i)  { percentage r(this->value + i); return r; }
	percentage operator-(const unsigned int i)  { percentage r(this->value - i); return r; }
	percentage operator/(const unsigned int i)  { percentage r(this->value / i); return r; }
	percentage operator*(const unsigned int i)  { percentage r(this->value * i); return r; }
	percentage operator%(const unsigned int i)  { percentage r(this->value % i); return r; }
	percentage operator+=(const unsigned int i) { percentage p(i); this->addp(p); percentage r(this->value); return r; }
	percentage operator-=(const unsigned int i) { percentage p(i); this->subp(p); percentage r(this->value); return r; }
	percentage operator/=(const unsigned int i) { percentage p(i); this->divp(p); percentage r(this->value); return r; }
	percentage operator*=(const unsigned int i) { percentage p(i); this->mulp(p); percentage r(this->value); return r; }
	percentage operator%=(const unsigned int i) { percentage p(i); this->modp(p); percentage r(this->value); return r; }
	percentage operator++()			    { this->realloc(this->value+1); percentage r(this->value); return r; }
	percentage operator++(int)		    { percentage p(this->value); this->realloc(this->value+1); return p; }
	percentage operator--()			    { this->realloc(this->value-1); percentage r(this->value); return r; }
	percentage operator--(int) 		    { percentage p(this->value); this->realloc(this->value-1); return p; }

private:
	// Math functions for operators
	void addp(percentage p);
	void subp(percentage p);
	void divp(percentage p);
	void mulp(percentage p);
	void modp(percentage p);

protected:
	// The value itself
	unsigned int value;
};

// The actual cout overloading, makes sure that printing -> (VALUE)%
std::ostream& operator<<(std::ostream& os, const percentage& p) { os << p.value << "%"; return os; }

// Constructor: Verify bounds and report any assignment/value errors
percentage::percentage(unsigned int p) 
{
	if(p <0 || p >100) {
		std::cout << "ValueError :: Percentage allocated with more than 100 or less than 0" << std::endl;
		exit(EXIT_FAILURE);
		return;
	} percentage::value = p;
}

// Virtually identical to the constructor, but for reallocating the percentage
void percentage::realloc(unsigned int v) 
{
	if(v <0 || v >100) {
		std::cout << "ValueError :: Percentage allocated with more than 100 or less than 0" << std::endl;
		exit(EXIT_FAILURE);
		return;
	} this->value = v;
}

// Simple math - Uses realloc to catch value errors
void percentage::addp(percentage p) { this->realloc(this->value + p.value); }
void percentage::subp(percentage p) { this->realloc(this->value - p.value); }
void percentage::mulp(percentage p) { this->realloc(this->value * p.value); }

// Simple math, yet with potential for /0 bugs
void percentage::divp(percentage p) 
{ 
	if(p.value != 0) { this->realloc(this->value / p.value); return; }
	std::cout << "Divide by zero in percentage::divp()" << std::endl;
	exit(EXIT_FAILURE);
}
void percentage::modp(percentage p) 
{ 
	if(p.value != 0) { this->realloc(this->value % p.value); return; }
	std::cout << "Divide by zero in percentage::modp()" << std::endl;
	exit(EXIT_FAILURE);
}

// Actual code for conversions - Evidently they serve as wrappers
int 		percentage::toInt(void) 	{ return (int)value; 				}
float 		percentage::toFloat(void) 	{ return (float)value; 				}
double 		percentage::toDouble(void) 	{ return (double)value; 			}
std::string percentage::toString(void) 	{ return std::to_string(value); 	}

// Exponentiation using a multiplication-loop
void percentage::expp(unsigned int e) { 
	percentage *p = this; unsigned int tmp = 1;
	while(e >0) {
		tmp *= p->value;
		--e;
	} this->realloc(tmp);
}

int main(int argc, char **argv)
{
	// Testing of every function
	// If any of these return an error, a recent change created a bug
	percentage prc(54);
	percentage qrt(46);
	percentage xyz(2);
	percentage vtc(3);
	std::cout << "1 " << prc << std::endl;
	std::cout << "2 " << qrt << std::endl;
	std::cout << "3 " << xyz << std::endl;
	std::cout << "4 " << vtc << std::endl;
	std::cout << "54 + 46 =\t" << prc + qrt << std::endl;
	std::cout << "54 - 46 =\t" << prc - qrt << std::endl;
	std::cout << "2 * 3   =\t" << xyz * vtc << std::endl;
	std::cout << "46 / 2  =\t" << qrt / xyz << std::endl;
	std::cout << "46 % 3  =\t" << qrt % vtc << std::endl;
	vtc.expp(2);
	std::cout << "3 ** 2  =\t" << vtc << std::endl;

	percentage p(10);
	percentage q(5);
	std::cout << "Origin-values: P:10 Q:5" << std::endl;
	p += q;
	std::cout << "(P += Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p -= q;
	std::cout << "(P -= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p /= q;
	std::cout << "(P /= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	p *= q;
	std::cout << "(P *= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;
	q.realloc(3);
	p %= q;
	std::cout << "(P %= Q) P: " << p << std::endl;
	std::cout << "Q: " << q << std::endl;

	p.realloc(50);
	std::cout << "P set to 50" << std::endl;
	std::cout << "P + 1 " << p + 1 << std::endl;
	std::cout << "P - 1 " << p - 1 << std::endl;
	std::cout << "P / 2 " << p / 2 << std::endl;
	std::cout << "P * 2 " << p * 2 << std::endl;
	std::cout << "P % 3 " << p % 3 << std::endl;
	std::cout << "P +=1, -=1, *=2, /=2, %=8" << std::endl;
	p += 1;
	std::cout << p << std::endl;
	p -= 1;
	std::cout << p << std::endl;
	p *= 2;
	std::cout << p << std::endl;
	p /= 2;
	std::cout << p << std::endl;
	p %= 8;
	std::cout << p << std::endl;
	std::cout << "P++ " << p++ << std::endl;
	std::cout << "++P " << ++p << std::endl;
	std::cout << "P-- " << p-- << std::endl;
	std::cout << "--P " << --p << std::endl;

	p.realloc(74);
	std::cout << "P is now 74" << std::endl;
	std::cout << "P.toInt() +1 =>\t\t\t\t " 		<< p.toInt()+1 			<< std::endl;
	std::cout << "P.toFloat() +0.5 =>\t\t\t " 		<< p.toFloat()+0.5 		<< std::endl;
	std::cout << "P.toDouble() -0.43253234523 =>\t\t " 	<< p.toDouble()-0.43253234523 	<< std::endl;
	std::cout << "P.toString().append(\"str\") =>\t\t " 	<< p.toString().append("str") 	<< std::endl;
	return 0;
}
