/*
 *  CPP_Percentage => A percentage datatype for C++
 *  Copyright (C) 2018  ZexZee
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CPP_SRC_PERCENTAGE
#define CPP_SRC_PERCENTAGE

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

#endif
