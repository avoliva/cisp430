//19 Code
#include <cmath>        
class Complex 
{
  public:
    Complex(int real, int imaginary)
    {
      this->real = real;
      this->imaginary = imaginary;
    }
    int getReal() const{ return this->real; }
    int getImaginary() const { return this->imaginary; }
    void setReal(int real) { this->real = real; }
    void setImaginary(int imaginary) { this->imaginary = imaginary; }
    int absolute();
    int norm()
    {
      return pow(this->real, 2) + pow(this->imaginary, 2);
    }
    
  private:
    int real;
    int imaginary;
  
};

/*
Getters and setters are must for the class, so the user can easily get and set the member variables.
You might want to implement operator overloading, depending on how far you want to take this class.
You can make it so the user can easily add, subtract, 
*/
#include <iostream>
class RationalNumber
{
public:
    RationalNumber(int numerator, int denominator)
    {
        try 
        {
            if (denominator == 0)
                throw 0;
            this->numerator = numerator;
            this->denominator = denominator;
            this->reduce(*this); 
            this->normalize(*this);
        }
        catch (int)
        {
            std::cout << "Denominator must not be zero." << std::endl;  
        }
    }
    friend std::ostream& operator<< (std::ostream& out, RationalNumber& rn);
    friend std::istream& operator>> (std::istream& in, RationalNumber& rn);
    friend RationalNumber operator+ (const RationalNumber& rn1, const RationalNumber& rn2);
    friend RationalNumber operator- (const RationalNumber& rn1, const RationalNumber& rn2);
    friend RationalNumber operator* (RationalNumber& rn1, RationalNumber& rn2);
    friend RationalNumber operator/ (RationalNumber& rn1, RationalNumber& rn2);
    friend bool operator> (RationalNumber& rn1, RationalNumber& rn2);
    friend bool operator< (RationalNumber& rn1, RationalNumber& rn2);
    friend bool operator>= (RationalNumber& rn1, RationalNumber& rn2);
    friend bool operator<= (RationalNumber& rn1, RationalNumber& rn2);
    friend bool operator== (RationalNumber& rn1, RationalNumber& rn2);
    int getNumerator() { return this->numerator; }
    int getDenominator() { return this->denominator; }
    void setNumerator(int numerator) { this->numerator = numerator; }
    void setDenominator(int denominator) { this->denominator = denominator; }
    RationalNumber& normalize(RationalNumber& rn)
    {
        int num = rn.getNumerator();
        int denom = rn.getDenominator();
        if (num < 0 && denom < 0)
        {
            rn.setNumerator(std::abs(num));
            rn.setDenominator(std::abs(denom));
        }
        else if (num > 0 && denom < 0)
        {
            rn.setNumerator(-std::abs(num));
            rn.setDenominator(std::abs(denom));
        }
        return rn;
    }
    RationalNumber& reduce(RationalNumber& rn)
    {
        int num = rn.getNumerator();
        int denom = rn.getDenominator();
    
        for (int i = denom * num; i > 1; i--) {  
            if ((denom % i == 0) && (num % i == 0)) {  
                denom /= i;  
                num /= i;  
            }          
        }
        rn.setDenominator(denom);
        rn.setNumerator(num);
        return rn;
    }
private:
    int numerator;
    int denominator;
};

std::ostream& operator<< (std::ostream& out, RationalNumber& rn)
{
    out << rn.getNumerator() << "/" << rn.getDenominator();
    return out;
}

std::istream& operator>> (std::istream& in, RationalNumber& rn)
{
    char slash;
    int num;
    int denom;
    in >> num >> slash >> denom;
    try
    {
        if (slash != '/')
            throw 0;
        rn.setNumerator(num);
        rn.setDenominator(denom);
        rn.normalize(rn);
        rn.reduce(rn);
    }
    catch (int)
    {
        std::cout << "Must be entered in fraction form." << std::endl;
    }
    return in;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else return gcd(b, a%b);
}
int lcm(int a, int b)
{
    return std::abs(a * b) / gcd(a, b);
}

RationalNumber operator+ (RationalNumber& rn1, RationalNumber& rn2)
{
    int LCM = lcm(rn1.getDenominator(), rn2.getDenominator());
    int a = rn1.getNumerator() * (LCM / rn1.getDenominator());
    int b = rn2.getNumerator() * (LCM / rn2.getDenominator());
    RationalNumber obj(a+b, LCM);
    obj.normalize(obj);
    obj.reduce(obj);
    return obj;
}

RationalNumber operator- (RationalNumber& rn1, RationalNumber& rn2)
{
    int LCM = lcm(rn1.getDenominator(), rn2.getDenominator());
    int a = rn1.getNumerator() * (LCM / rn1.getDenominator());
    int b = rn2.getNumerator() * (LCM / rn2.getDenominator());
    RationalNumber obj(a-b, LCM);
    obj.normalize(obj);
    obj.reduce(obj);
    return obj;
}

RationalNumber operator* (RationalNumber& rn1, RationalNumber& rn2)
{
    RationalNumber obj(rn1.getNumerator() * rn2.getNumerator(), rn1.getDenominator() * rn2.getDenominator());
    return obj;
}

RationalNumber operator/ (RationalNumber& rn1, RationalNumber& rn2)
{
    RationalNumber obj(rn1.getNumerator() * rn2.getDenominator(), rn1.getDenominator() * rn2.getNumerator());
    return obj;
}

bool operator> (RationalNumber& rn1, RationalNumber& rn2)
{
    if (rn1.getNumerator() > 0 && rn2.getNumerator() > 0)
        return ((rn1.getNumerator() * rn2.getDenominator()) < (rn2.getNumerator() * rn1.getDenominator()));
    else
        return ((rn1.getNumerator() * rn2.getDenominator()) > (rn2.getNumerator() * rn1.getDenominator()));
}

bool operator>= (RationalNumber& rn1, RationalNumber& rn2)
{
    if (rn1.getNumerator() > 0 && rn2.getNumerator() > 0)
        return ((rn1.getNumerator() * rn2.getDenominator()) >= (rn2.getNumerator() * rn1.getDenominator()));
    else
        return ((rn1.getNumerator() * rn2.getDenominator()) <= (rn2.getNumerator() * rn1.getDenominator()));

}

bool operator< (RationalNumber& rn1, RationalNumber& rn2)
{
    if (rn1.getNumerator() > 0 && rn2.getNumerator() > 0)
        return ((rn1.getNumerator() * rn2.getDenominator()) > (rn2.getNumerator() * rn1.getDenominator()));
    else
        return ((rn1.getNumerator() * rn2.getDenominator()) < (rn2.getNumerator() * rn1.getDenominator()));

}

bool operator<= (RationalNumber& rn1, RationalNumber& rn2)
{
    if (rn1.getNumerator() > 0 && rn2.getNumerator() > 0)
        return ((rn1.getNumerator() * rn2.getDenominator()) >= (rn2.getNumerator() * rn1.getDenominator()));;
    else
        return ((rn1.getNumerator() * rn2.getDenominator()) >= (rn2.getNumerator() * rn1.getDenominator()));
}

bool operator== (RationalNumber& rn1, RationalNumber& rn2)
{
    return ((rn1.getNumerator() * rn2.getDenominator()) == (rn2.getNumerator() * rn1.getDenominator()));
}




int main()
{
    RationalNumber rn(2,5);
    RationalNumber rn2(1,25);
    // std::cin >> rn;
    RationalNumber rn3 = rn / rn2;
    std::cout << rn3 << std::endl;
    return 0;
}











