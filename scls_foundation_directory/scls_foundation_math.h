//******************
//
// scls_foundation_math.h
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Foundation "Leonhard" part represents the foundation of SCLS.
// It is named after the "Father of modern mathematics", Leonhard Euler.
//
// This file contains some mathematical functions.
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_FOUNDATION_MATH
#define SCLS_FOUNDATION_MATH

#ifndef SCLS_PI
#define SCLS_PI 3.1415926535
#endif // SCLS_PI
#ifndef SCLS_HALP_PI
#define SCLS_HALF_PI 1.5707963267948966
#endif // SCLS_HALP_PI

// The namespace "scls" is used to simplify the all.
namespace scls
{
    //*********
	//
	// Mathematical functions
	//
	//*********

	// Partitions a number and return each numbers of the partition
	inline std::vector<long long> partition_number(long long number_to_partition, long long number_of_partitions) {
	    std::vector<long long> to_return = std::vector<long long>();

	    // Calculate the main value to add at each iteration
        long long round_partition_size = static_cast<long long>(static_cast<double>(number_to_partition) / static_cast<double>(number_of_partitions));
        long long rest = number_to_partition % number_of_partitions;

        // Calculate the rest to add at each iterations
        long long rest_to_add = static_cast<long long>(static_cast<double>(rest) / static_cast<double>(number_of_partitions));
        long long rest_of_rest = rest % number_of_partitions;

        // Calculate the rest of the rest to add at each iterations
        double rest_of_rest_to_add = 0;
        if(rest_of_rest != 0) rest_of_rest_to_add = static_cast<double>(number_of_partitions) / static_cast<double>(rest_of_rest);

        // Create the partition
        double current_rest_of_rest = static_cast<double>(rest_of_rest_to_add) / 2.0;
        unsigned int current_rest_added = 0;
        for(long long i = 0;i<number_of_partitions;i++) {
            long long to_add = 0;
            if(rest_of_rest_to_add != 0 && current_rest_of_rest >= rest_of_rest_to_add && current_rest_added < rest_of_rest) {
                to_add++;
                current_rest_added++;
                current_rest_of_rest -= rest_of_rest_to_add;
            }
            current_rest_of_rest++;
            to_return.push_back(round_partition_size + rest_to_add + to_add);
        }
        return to_return;
	};

	// Apply the Paeth function to a left, above and upper left values
	inline double paeth_function(double left, double above, double upper_left) {
		double p = left + above - upper_left;
		double pa = abs(p - left);
		double pb = abs(p - above);
		double pc = abs(p - upper_left);
		if (pa <= pb && pa <= pc) return left;
		else if (pb <= pc) return above;
		return upper_left;
	}

	//*********
	//
	// Get mathematicals datas
	//
	//*********

	// Normalize a value between "min" and "max" included
	inline double normalize_value(double number, double min, double max) { if(max == min) return 0; else if(max < min) std::swap(min, max); double t = (max - min) + 1; while (number < min) number += t; while (number > max) number -= t; return number; }

	// Return the size of a number
	inline int sign(double number) { return number < 0 ? -1 : (number == 0 ? 0 : 1); };

	//*********
	//
	// The Fraction class
	//
	//*********

	class Fraction {
	    // Class representating a fraction
    public:
        //*********
        //
        // Fraction simple methods
        //
        //*********

        // Most simple fraction constructor
        Fraction(long long numerator) : a_denominator(1), a_numerator(numerator) {};
        // Simple fraction constructor
        Fraction(long long numerator, long long denominator) : a_denominator(denominator), a_numerator(numerator) {normalize();};
        // Fraction copy constructor
        Fraction(const Fraction& to_copy) : a_denominator(to_copy.a_denominator), a_numerator(to_copy.a_numerator) {a_normalized = true;};

        // Returns a fraction from a double
        static Fraction from_double(double result) {
            long long result_in_long = static_cast<long long>(result);
            double after_decimal_point = static_cast<double>(result - static_cast<double>(result_in_long));
            if(after_decimal_point == 0) return Fraction(result_in_long, 1);
            long long after_decimal_point_in_long = static_cast<long long>(after_decimal_point * 100000);
            return Fraction(result_in_long, 1) + Fraction(after_decimal_point_in_long, 100000);
        };
        // Normalize the fraction
        void normalize() {
            if(a_normalized) return;

            const long long base_denominator = a_denominator; const long long base_numerator = a_numerator;
            if(a_denominator < 0) a_denominator = -a_denominator;
            if(a_numerator < 0) a_numerator = -a_numerator;

            // Apply the Euclid algorithm
            if(a_numerator != 0) {
                while(a_denominator != 0) {
                    long long t = a_denominator;
                    a_denominator = a_numerator % a_denominator;
                    a_numerator = t;
                }
                a_denominator = base_denominator / a_numerator;
                a_numerator = base_numerator / a_numerator;
            }
            else {
                a_denominator = 1;
            }
            if(a_denominator < 0) a_denominator = -a_denominator;
            if(a_numerator < 0) a_numerator = -a_numerator;

            // Apply the sign
            if((base_denominator < 0 && base_numerator > 0) || (base_denominator > 0 && base_numerator < 0)) a_numerator = -a_numerator;
            a_normalized = true;
        };
        // Sets this fraction as a double
        void set_from_double(double result) {
            Fraction new_value = from_double(result);
            a_denominator = new_value.a_denominator;
            a_numerator = new_value.a_numerator;
        };
        // Returns the fraction in double
        inline double to_double() const {if(a_denominator == 0) return 0; return static_cast<double>(a_numerator) / static_cast<double>(a_denominator);};

        // Getters and setter
        inline long long denominator() const {return a_denominator;};
        inline long long numerator() const {return a_numerator;};

        //*********
        //
        // Operator methods
        //
        //*********

        // Function to do operations with fractions
        // Adds an another Fraction to this fraction
        void _add(Fraction const& obj) {
            long long first_numerator = obj.a_numerator * a_denominator;
            long long second_numerator = a_numerator * obj.a_denominator;
            a_denominator = obj.a_denominator * a_denominator;
            a_numerator = first_numerator + second_numerator;
            a_normalized = false;
            normalize();
        };
        // Returns the adding of this fraction and another function
        Fraction _add_without_modification(Fraction const& obj) const {
            long long first_numerator = obj.a_numerator * a_denominator;
            long long second_numerator = a_numerator * obj.a_denominator;
            long long denominateur = obj.a_denominator * a_denominator;

            Fraction new_fraction = Fraction(first_numerator + second_numerator, denominateur);
            return new_fraction;
        };
        // Divides the fraction with an another fraction
        void _divide(Fraction const& obj) { _multiply(Fraction(obj.a_denominator, obj.a_numerator)); a_normalized = false; };
        // Divides the fraction with an another fraction
        Fraction _divide_without_modification(Fraction const& obj) const { return _multiply_without_modification(Fraction(obj.a_denominator, obj.a_numerator)); };
        // Returns if this fraction is equal to another
        bool _equal(Fraction const& obj) const {return obj.a_numerator * a_denominator == a_numerator * obj.a_denominator;};
         // Returns if this fraction is equal to an int
        bool _equal(int const& obj) const {return a_numerator == obj && a_denominator == 1;};
        // Multiplies the fraction with an another Fraction
        void _multiply(Fraction const& obj) { a_numerator *= obj.a_numerator; a_denominator *= obj.a_denominator; a_normalized = false; };
        // Multiplies the fraction with an another Fraction
        Fraction _multiply_without_modification(Fraction const& obj) const { return Fraction(a_numerator * obj.a_numerator, a_denominator * obj.a_denominator); };
        // Multiplies the fraction with a double
        Fraction _multiply_without_modification(double const& obj) const { return Fraction(a_numerator * obj, a_denominator); };
        // Multiplies the fraction with an unsigned int
        Fraction _multiply_without_modification(int const& obj) const { return Fraction(a_numerator * obj, a_denominator); };
        // Multiplies the fraction with an unsigned int
        Fraction _multiply_without_modification(unsigned int const& obj) const { return Fraction(a_numerator * obj, a_denominator); };
        // Substracts an another Fraction to this fraction
        void _substract(Fraction const& obj) {
            long long first_numerator = obj.a_numerator * a_denominator;
            long long second_numerator = a_numerator * obj.a_denominator;
            a_denominator = obj.a_denominator * a_denominator;
            a_numerator = second_numerator - first_numerator;
            a_normalized = false;
            normalize();
        };
        // Returns the substracting of this fraction and another function
        Fraction _substract_without_modification(Fraction const& obj) const {
            long long first_numerator = obj.a_numerator * a_denominator;
            long long second_numerator = a_numerator * obj.a_denominator;
            long long denominateur = obj.a_denominator * a_denominator;

            Fraction new_fraction = Fraction(second_numerator - first_numerator, denominateur);
            return new_fraction;
        };

        // Operator overloading with int
        // Greater operator
        bool operator>(const int& obj) { return to_double() > obj; }
        // Less operator
        bool operator<(const int& obj) { return to_double() < obj; }
        // Less or equal operator
        bool operator<=(const int& obj) { return to_double() < obj || _equal(obj); }
        // Equality operator
        bool operator==(const int& obj) { return _equal(obj); }
        // Multiplication operator
        Fraction operator*(int const& obj) const { return _multiply_without_modification(obj); }
        // Multiplication operator
        Fraction operator*(unsigned int const& obj) const { return _multiply_without_modification(obj); }

        // Operator overloading with double
        // Assignment operator assignment
        Fraction& operator=(double const& obj) { set_from_double(obj); return *this; }
        // Divisor operator
        Fraction operator/(double const& obj) { return _divide_without_modification(from_double(obj)); };
        // Greater than than operator
        bool operator>(const double& r) { return to_double() > r; }
        // Less than operator
        bool operator<(const double& r) { return to_double() < r; }
        // Minus operator
        Fraction operator-(double const& obj) { return _substract_without_modification(from_double(obj)); }
        // Minus operator assignment
        Fraction& operator-=(double const& obj) { _substract(from_double(obj)); return *this; }
        // Multiplication operator
        Fraction operator*(double const& obj) const { return _multiply_without_modification(obj); }
        // Plus operator
        Fraction operator+(double const& obj) { return _add_without_modification(from_double(obj)); };
        // Plus operator assignment
        Fraction& operator+=(double const& obj) { _add(from_double(obj)); return *this; }

        // Operator overloading with fractions
        // Decrement operator
        Fraction& operator--(int) { _substract(Fraction(1, 1)); return *this; }
        // Divisor operator
        Fraction operator/(Fraction const& obj) const { return _divide_without_modification(obj); };
        // Divisor operator assignment
        Fraction& operator/=(Fraction const& obj) { _divide(obj); return *this; };
        // Equality operator
        bool operator==(const Fraction& obj) const { return _equal(obj); }
        // Greater or equal than than operator
        bool operator>=(const Fraction& r) const { return _equal(r) || to_double() > r.to_double(); }
        // Greater than than operator
        bool operator>(const Fraction& r) const { return to_double() > r.to_double(); }
        // Increment operator
        Fraction& operator++(int) { _add(Fraction(1, 1)); return *this; }
        // Lesser than than operator
        bool operator<(const Fraction& r) const { return to_double() < r.to_double(); }
        // Minus operator
        Fraction operator-(Fraction const& obj) const { return _substract_without_modification(obj); };
        // Minus operator assignment
        Fraction& operator-=(const Fraction& obj) { _substract(obj); return *this; }
        // Multiplciation operator
        Fraction operator*(Fraction const& obj) const { return _multiply_without_modification(obj); };
        // Multiplication operator assignment
        Fraction& operator*=(Fraction const& obj) { _multiply(obj); return *this; };
        // Plus operator
        Fraction operator+(Fraction const& obj) const { return _add_without_modification(obj); };
        // Plus operator assignment
        Fraction& operator+=(const Fraction& obj) { _add(obj); return *this; }
    private:
        //*********
        //
        // Fraction simple attributes
        //
        //*********

        // Denominator of the fraction
        long long a_denominator = 1;
        // If the fraction has been normalized or not
        bool a_normalized = false;
        // Numerator of the fraction
        long long a_numerator = 0;

	};

	// Stream operator overloading
    static std::ostream& operator<<(std::ostream& os, const Fraction& obj) { os << "Fraction : " << obj.numerator() << " / " << obj.denominator() << " = " << obj.to_double(); return os; }
}

#endif // SCLS_FOUNDATION_MATH
