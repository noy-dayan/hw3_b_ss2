#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

#include "Fraction.hpp"

# define EPSILON 0.01

namespace ariel {
    // Fraction constructors
    Fraction::Fraction() : numerator(1), denominator(1) {}
    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0)
            throw std::invalid_argument("Denominator cannot be zero");
        minimizeFraction();

    }
    Fraction::Fraction(float n) {
        // check if input is already an integer value
        if (std::fabs(n - std::round(n)) < EPSILON) {
            this->numerator = std::round(n);
            this->denominator = 1;
            return;
        }

        // compute the integer and decimal parts separately
        int integerPart = static_cast<int>(n);
        float decimalPart = (n - integerPart) * 1000;
        decimalPart = round(decimalPart) / 1000;
        
        // compute the denominator as a power of 10 that is large enough to represent the decimal part
        this->denominator = 1;
        while (std::fabs(std::round(decimalPart * this->denominator) - decimalPart * this->denominator) >= EPSILON) {
            this->denominator *= 10;
        }

        // compute the numerator as the sum of the integer part and the adjusted decimal part
        this->numerator = integerPart * this->denominator + std::round(decimalPart * this->denominator);

        minimizeFraction();
    }    
    
    int Fraction::getNumerator(){
        return this->numerator;
    }

    int Fraction::getDenominator(){
        return this->denominator;
    }
    
    void Fraction::setNumerator(int numer){
        this->numerator = numer;
        minimizeFraction();
    }
    
    void Fraction::setDenominator(int denom){
        if (denom == 0)
            throw std::invalid_argument("Denominator cannot be zero");
        this->denominator = denom;
        minimizeFraction();
    }

    void Fraction::minimizeFraction() {
        int gcd = std::__gcd(this->numerator, this->denominator);
        this->numerator /= gcd;
        this->denominator /= gcd;

        if (this->denominator < 0 && this->numerator > 0){
            this->denominator = -this->denominator;
            this->numerator = -this->numerator;
        }
    }

    // + operator
    Fraction Fraction::operator+(const Fraction& other) const {
        int common_denom = this->denominator * other.denominator;
        int new_numer = this->numerator * other.denominator + other.numerator * this->denominator;
        int tmp;
        if (__builtin_add_overflow(this->numerator * other.denominator, other.numerator * this->denominator, &tmp))
            throw std::overflow_error("Add overflow");
        Fraction new_frac(new_numer, common_denom);
        new_frac.minimizeFraction();
        return (new_frac);
    }

    Fraction Fraction::operator+(const float& other) const {
        Fraction new_frac = Fraction{(int)(other * 1000), 1000};
        int tmp;
        if (__builtin_add_overflow(this->numerator * new_frac.denominator, new_frac.numerator * this->denominator, &tmp))
            throw std::overflow_error("Add overflow");

        new_frac = *this + Fraction{(int)(other * 1000), 1000};
        new_frac.minimizeFraction();
        return new_frac;
    }
    
    Fraction operator+(float float_num, const Fraction &frac_num){
        return Fraction(float_num) + frac_num;
    }

    // - operator
    Fraction Fraction::operator-(const Fraction& other) const {
        int common_denom = this->denominator * other.denominator;
        int new_numer = this->numerator * other.denominator - other.numerator * this->denominator;
        int tmp;
        if (__builtin_sub_overflow(this->numerator * other.denominator, other.numerator * this->denominator, &tmp))
            throw std::overflow_error("Sub overflow");
        Fraction new_frac(new_numer, common_denom);
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction Fraction::operator-(const float& other) const {
        Fraction new_frac = Fraction{(int)(other * 1000), 1000};
        int tmp;
        if (__builtin_sub_overflow(this->numerator * new_frac.denominator, new_frac.numerator * this->denominator, &tmp))
            throw std::overflow_error("Sub overflow");
            
        new_frac = *this - Fraction{(int)(other * 1000), 1000};
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction operator-(float float_num, const Fraction &frac_num){
        return Fraction(float_num) - frac_num;
    }

    // * operator
    Fraction Fraction::operator*(const Fraction& other) const {
        int tmp1, tmp2;

        if (__builtin_mul_overflow(this->numerator, other.numerator, &tmp1))
            throw std::overflow_error("Mul overflow");

        if(__builtin_mul_overflow(this->denominator, other.denominator, &tmp2))
            throw std::overflow_error("Mul overflow");

        int new_numer = this->numerator * other.numerator;
        int new_denom = this->denominator * other.denominator;
        
        Fraction new_frac(new_numer, new_denom);
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction Fraction::operator*(const float& other) const {
        int tmp1, tmp2;
        Fraction new_frac = Fraction{(int)(other * 1000), 1000};

        if (__builtin_mul_overflow(this->numerator, new_frac.numerator, &tmp1))
            throw std::overflow_error("Mul overflow");

        if(__builtin_mul_overflow(this->denominator, new_frac.denominator, &tmp2))
            throw std::overflow_error("Mul overflow");

        new_frac = *this * Fraction{(int)(other * 1000), 1000};
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction operator*(float float_num, const Fraction &frac_num){
        return Fraction(float_num) * frac_num;
    }

    // / operator
    Fraction Fraction::operator/(const Fraction& other) const {
        if (other.numerator == 0)
            throw std::runtime_error("Division by zero");

        int tmp1, tmp2;

        if (__builtin_mul_overflow(this->numerator, other.denominator, &tmp1))
            throw std::overflow_error("Div overflow");
        
        if (__builtin_mul_overflow(this->denominator, other.numerator, &tmp2))
            throw std::overflow_error("Div overflow");
        

        Fraction new_frac = *this * Fraction{other.denominator, other.numerator};
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction Fraction::operator/(const float& other) const {
        if (other == 0.0f)
            throw std::runtime_error("Division by zero");

        Fraction new_frac = Fraction{1000, (int)(other * 1000)};
        int tmp1, tmp2;

        if (__builtin_mul_overflow(this->numerator, new_frac.denominator, &tmp1))
            throw std::overflow_error("Div overflow");
        
        if (__builtin_mul_overflow(this->denominator, new_frac.numerator, &tmp2))
            throw std::overflow_error("Div overflow");

        new_frac = *this * Fraction{1000, (int)(other * 1000)};
        new_frac.minimizeFraction();
        return new_frac;
    }

    Fraction operator/(float float_num, const Fraction &frac_num){
        return Fraction(float_num) / frac_num;
    }

    // == operator
    bool Fraction::operator==(const Fraction& other) const {
        Fraction tmp_other = other;
        Fraction tmp_this = *this;

        tmp_other.minimizeFraction();
        tmp_this.minimizeFraction();

        return (tmp_this.numerator == tmp_other.numerator && tmp_this.denominator == tmp_other.denominator);
    }

    bool Fraction::operator==(const float& other) const {
        float fractionValue = (float) this->numerator / this->denominator;
        float diff = fractionValue - other;
        if (diff < 0)
            diff = -diff;
        return diff < EPSILON;
    }

    bool operator==(float float_num, const Fraction &frac_num){
        Fraction tmp_frac = frac_num;
        tmp_frac.minimizeFraction();

        float fractionValue = (float) tmp_frac.getNumerator() / tmp_frac.getDenominator();
        float diff = fractionValue - float_num;
        if (diff < 0)
            diff = -diff;
        return diff < EPSILON;
    }

    // != operator
    bool Fraction::operator!=(const Fraction& other) const {
        Fraction tmp_other = other;
        Fraction tmp_this = *this;

        tmp_other.minimizeFraction();
        tmp_this.minimizeFraction();

        return (tmp_this.numerator != tmp_other.numerator || tmp_this.denominator != tmp_other.denominator);

    }
    
    bool Fraction::operator!=(const float& other) const {
        float fractionValue = (float) this->numerator / this->denominator;
        float diff = fractionValue - other;
        if (diff < 0)
            diff = -diff;
        return diff >= EPSILON;    
    }

    bool operator!=(float float_num, const Fraction &frac_num){
        Fraction tmp_frac = frac_num;
        tmp_frac.minimizeFraction();

        float fractionValue = (float) tmp_frac.getNumerator() / tmp_frac.getDenominator();
        float diff = fractionValue - float_num;
        if (diff < 0)
            diff = -diff;
        return diff >= EPSILON;    
    }

    // > operator
    bool Fraction::operator>(const Fraction& other) const {
        int this_numer = this->numerator * other.denominator;
        int other_numer = other.numerator * this->denominator;
        return (this_numer > other_numer);  
    }

    bool Fraction::operator>(const float& other) const {
        return (*this > Fraction{(int)(other * 1000), 1000});
    }

    bool operator>(float float_num, const Fraction &frac_num){
        return (Fraction(float_num) > frac_num);
    }


    // < operator
    bool Fraction::operator<(const Fraction& other) const {
        int this_numer = this->numerator * other.denominator;
        int other_numer = other.numerator * this->denominator;
        return (this_numer < other_numer);
        
    }

    bool Fraction::operator<(const float& other) const {
        return (*this < Fraction{(int)(other * 1000), 1000});
    }

    bool operator<(float float_num, const Fraction &frac_num){
        return (Fraction(float_num) < frac_num);
    }

    // >= operator
    bool Fraction::operator>=(const Fraction& other) const {
        int this_numer = this->numerator * other.denominator;
        int other_numer = other.numerator * this->denominator;
        return (this_numer >= other_numer);
        
    }

    bool Fraction::operator>=(const float& other) const {
        return (*this >= Fraction{(int)(other * 1000), 1000});
    }

    bool operator>=(float float_num, const Fraction &frac_num){
        return (Fraction(float_num) >= frac_num);
    }


    // <= operator
    bool Fraction::operator<=(const Fraction& other) const {
        int this_numer = this->numerator * other.denominator;
        int other_numer = other.numerator * this->denominator;
        return (this_numer <= other_numer);
        
    }

    bool Fraction::operator<=(const float& other) const {
        return (*this <= Fraction{(int)(other * 1000), 1000});
    }

    bool operator<=(float float_num, const Fraction &frac_num){
        return (Fraction(float_num) <= frac_num);
    }

    // ++ operator
    Fraction Fraction::operator++() {
        this->numerator += this->denominator;
        minimizeFraction();
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction old_frac = *this;
        this->numerator += this->denominator;
        minimizeFraction();
        return old_frac;
    }

    // -- operator
    Fraction Fraction::operator--() {
        this->numerator -= this->denominator;
        minimizeFraction();
        return *this;    }

    Fraction Fraction::operator--(int) {
        Fraction old_frac = *this;
        this->numerator -= this->denominator;
        minimizeFraction();
        return old_frac;    }

    // output operator
    std::ostream& operator<<(std::ostream& os_, const Fraction& frac_num) {
        Fraction tmp_this = frac_num;
        tmp_this.minimizeFraction();
        
        os_ <<tmp_this.numerator << "/" << tmp_this.denominator;
        return os_;
    }  

    // input operaotr
    std::istream& operator>>(std::istream& is_, Fraction& frac_num){
        int numer, denom;
        char ch;
        is_ >> numer;

        char nextChar = is_.peek();
        if (!std::isspace(nextChar))
            is_ >> ch;
            if (ch == '.')
                throw std::runtime_error("Invalid input");

                

        if (!(is_ >> denom))
            throw std::runtime_error("Invalid input");

        if (denom == 0)
            throw std::runtime_error("Denominator cannot be zero");

        frac_num = Fraction(numer, denom);
        frac_num.minimizeFraction();
        return is_;
    }

}