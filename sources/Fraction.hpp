#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

namespace ariel {

    class Fraction {
        private:
            int numerator, denominator;
            
        public:
            Fraction();
            Fraction(int n, int float_num);
            Fraction(float n);

            int getNumerator();
            int getDenominator();

            void setNumerator(int numerator);
            void setDenominator(int denominator);

            void minimizeFraction();

            Fraction operator+(const Fraction& other) const;
            Fraction operator+(const float& other) const;

            Fraction operator-(const Fraction& other) const;
            Fraction operator-(const float& other) const;

            Fraction operator*(const Fraction& other) const;
            Fraction operator*(const float& other) const;

            Fraction operator/(const Fraction& other) const;
            Fraction operator/(const float& other) const;

            bool operator==(const Fraction& other) const;
            bool operator==(const float& other) const;
    
            bool operator!=(const Fraction& other) const;
            bool operator!=(const float& other) const;

            bool operator>(const Fraction& other) const;
            bool operator>(const float& other) const;

            bool operator<(const Fraction& other) const;
            bool operator<(const float& other) const;

            bool operator>=(const Fraction& other) const;
            bool operator>=(const float& other) const;

            bool operator<=(const Fraction& other) const;
            bool operator<=(const float& other) const;

            Fraction operator++(); // pre-increment
            Fraction operator++(int); // post-increment
            Fraction operator--(); // pre-decrement
            Fraction operator--(int); // post-decrement
            friend std::ostream& operator<<(std::ostream& os_, const Fraction& frac_num);
            friend std::istream& operator>>(std::istream& is_, Fraction& frac_num);
    };

    Fraction operator+(float float_num, const Fraction &frac_num);
    Fraction operator-(float float_num, const Fraction &frac_num);
    Fraction operator*(float float_num, const Fraction &frac_num);
    Fraction operator/(float float_num, const Fraction &frac_num);

    bool operator==(float float_num, const Fraction &frac_num);
    bool operator!=(float float_num, const Fraction &frac_num);
    bool operator>(float float_num, const Fraction &frac_num);
    bool operator<(float float_num, const Fraction &frac_num);
    bool operator>=(float float_num, const Fraction &frac_num);
    bool operator<=(float float_num, const Fraction &frac_num);

}

#endif // FRACTION_H
