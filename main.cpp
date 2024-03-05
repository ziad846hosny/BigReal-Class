#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class BigReal {
    string number, integer, fraction;
    char sign;
    bool after_dot = false;
public:
    BigReal() = default;

    BigReal(string unumber){
        number = unumber;

        // verifying that the entered value is a real number
        while(true) {
            bool check = false;
            int dots = 0;
            for (int i = 0; i < number.size(); i++) {
                // checking if a there is a sign before the number
                if(!(number[0] == '+' || number[0] == '-' || isdigit(number[0]))){
                    check = true;
                }

                // checking for prescence of any characters except '.'
                if(isalpha(number[i])){
                    if(number[0] != '.') {
                        check = true;
                    }
                }

                // checking if there is more than 1 dot '.'
                if(number[i] == '.'){
                    dots++;
                }
            }
            if(!(check || dots >= 2)){
                break;
            }else{
                cout << "enter a valid number: ";
                cin >> number;
            }
        }

        for(int i = 0; i < number.size(); i++){

            // reading the sign
            if(!isdigit(number[0])){
                sign = number[0];
            }else{
                sign = '+';
            }

            //checking if we passed the dot or not
            if(number[i] == '.'){
                after_dot = true;
                continue;
            }

            //copying the number into (integer, fraction)
            if(after_dot){
                fraction += number[i];
            }else{
                integer += number[i];
            }
        }

        // checking if the integer part is empty or not
        if(integer.empty()){
            integer = "0";
        }

        if(!isdigit(integer[0])){
            integer.erase(0,1);
        }

        // checking if the fraction part is empty or not
        if(fraction.empty()){
            fraction = "0";
        }
    }

    // Addition of two BigReal numbers
    BigReal operator+(const BigReal& other) const {
        BigReal result;
        double num1 = toDouble();
        double num2 = other.toDouble();
        result.fromDouble(num1 + num2);
        return result;
    }

    // Subtraction of two BigReal numbers
    BigReal operator-(const BigReal& other) const {
        BigReal result;
        double num1 = toDouble();
        double num2 = other.toDouble();
        result.fromDouble(num1 - num2);
        return result;
    }

    // Multiplication of two BigReal numbers
    BigReal operator*(const BigReal& other) const {
        BigReal result;
        double num1 = toDouble();
        double num2 = other.toDouble();
        result.fromDouble(num1 * num2);
        return result;
    }

    // Division of two BigReal numbers
    BigReal operator/(const BigReal& other) const {
        BigReal result;
        double num1 = toDouble();
        double num2 = other.toDouble();
        if (num2 != 0.0) {
            result.fromDouble(num1 / num2);
        } else {
            std::cerr << "Division by zero is not allowed." << std::endl;
        }
        return result;
    }

    // Convert BigReal to a double
    double toDouble() const {
        double result = std::stod(number);
        return (sign == '-') ? -result : result;
    }

    // Convert double to BigReal
    void fromDouble(double value) {
        sign = (value < 0) ? '-' : '+';
        value = std::abs(value);
        integer = std::to_string((int)value);
        fraction = std::to_string(value - floor(value));
        fraction.erase(0,2);
        for(int i = fraction.size() - 1; i >= 0; i--){
            if(fraction[i] == '0'){
                fraction.erase(i, i);
            }else{
                break;
            }
        }
    }

    // Print the BigReal number
    void print() const {
        std::cout << "Integer: " << sign << integer << "\n" << "Fraction: " << fraction;
    }

    // Override the << operator for convenient output
    friend std::ostream& operator<<(std::ostream& os, const BigReal& bigReal) {
        os << bigReal.sign << bigReal.integer << "." << bigReal.fraction;
        return os;
    }

    // Equal to operator
    bool operator== (BigReal& other){
        if (sign == other.sign && integer == other.integer && fraction == other.fraction){
            return true;
        }
        else{
            return false;
        }
    }

    // not Equal to operator
    bool operator!= (BigReal& other){
        if (sign == other.sign && integer == other.integer && fraction == other.fraction){
            return false;
        }
        else{
            return true;
        }
    }

    // Less than operator
    bool operator< (BigReal& other){
        if (sign=='+'&& other.sign=='-'){
            return false;
        }
        else if (sign=='-'&&other.sign=='+'){
            return true;
        }
        else{
            if (integer!=other.integer){
                return integer < other.integer;
            }
            else{
                return fraction < other.fraction;
            }
        }
    }

    // Greater than operator
    bool operator> (BigReal& other){
        if (sign=='+'&& other.sign=='-'){
            return true;
        }
        else if (sign=='-'&&other.sign=='+'){
            return false;
        }
        else{
            if (integer!=other.integer){
                return integer > other.integer;
            }
            else{
                return fraction > other.fraction;
            }
        }
    }

};

int main(){
    BigReal ob1("123.123"), ob2("456.456");
    cout << "Addition : " << ob1 + ob2
         << "\nSubtraction : " << ob1 - ob2
         <<"\nMultiplication : " << ob1 * ob2
         << "\nDivision : " << ob1/ob2;
}