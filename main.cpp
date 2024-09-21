#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
    * Polynomial class
    * This class represents a polynomial as a linked list of terms.
    * Each term is represented by a Node object.
    * The class provides methods to add, subtract, multiply, and divide polynomials.
    * The class also provides a method to evaluate the polynomial for a given value of x.
    * The class also provides a method to print the polynomial.
    * The class also provides a method to parse the polynomial from input.
*/


class Node {
public:
    double coeff; // Coefficient of the term
    int exp;   // Exponent of the term
    Node* next; // Pointer to the next node

    Node(double c, int e) : coeff(c), exp(e), next(nullptr) {}
};

// Polynomial class
class Polynomial {
private:
    Node* head; // Head of the linked list representing the polynomial
    Node* tail;

    // Add term manually
    /**
     * This function adds a term to the polynomial. If the term already exists, it
     * updates the coefficient of the existing term. If the coefficient is zero, it
     * ignores the term. Otherwise, it adds the term to the end of the linked list.
     * 
     * The time complexity of this function is O(n) in the worst case, where n is the
     * number of terms in the polynomial.
     * 
     * The while loop is responsible for checking if the term already exists in the polynomial.
     */
    void addTerm(double coeff, int exp) {
        if (coeff == 0) return; // Ignore zero coefficients
        Node* newNode = new Node(coeff, exp);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else{
            Node* temp = head;
            while (temp != nullptr) {
                if (temp -> exp == exp) {
                    temp -> coeff += coeff;
                    return;
                }
                temp = temp -> next;
            }
            tail -> next = newNode;
            tail = newNode;
        }
    }

public:
    // We have two constructors: one default constructor and one constructor that takes an 
    // input stream as an argument. The second constructor is used to parse the polynomial from
    // input.
    Polynomial() : head(nullptr), tail(nullptr){}
    Polynomial(istream& input)
    {
        int number_of_term;
        input >> number_of_term;
        for (int i = 0; i < number_of_term; ++i) {
            double coeff;
            int exp;
            input >> coeff >> exp;
            addTerm(coeff, exp);
        }
    }




    // The time complexity of this function is O(n), where n is the number of terms in the poly. 
    void print() const {
        // If the polynomial is empty, print 0
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }
        Node* temp = head;
        bool first = true;
        // The bool first varaiable is used to check if the term is the first term in the polynomial. 
        // If it is the first term, we don't print the sign. Otherwise, we print the sign.
        while (temp != nullptr) {
            if (!first && temp -> coeff > 0) cout << " + ";
            if (!first && temp -> coeff < 0) cout << " ";

            // If it is the first iteration, it means that it is the first term in the polynomial. 
            // So, we don't print the sign. 
            // Once the first term is printed, we set the first variable to false. 
            if (first) first = false;
            cout << temp -> coeff << "x^" << temp -> exp;
            temp = temp -> next;
        }
        cout << endl;
    }






    /*
    * This is the addition operator overload. It adds two polynomials and returns the result. 
    * The time complexity of this function is O(n + m), where n is the number of terms in the 
    * first polynomial
    * 
    * The time complexity of this function is O(n + m), where n is the number of terms in the
    * first polynomial and m is the number of terms in the second polynomial.
    */
    Polynomial operator+(const Polynomial& right_hand_side_poly) const {
        Polynomial result;
        Node* left_poly = head;
        Node* right_poly = right_hand_side_poly.head;

        // The while loop iterates over the two polynomials until one of them reaches the end.
        while (left_poly != nullptr || right_poly != nullptr) {
            double coeff = 0;
            int exp = 0;

            // If the left poly is null, we add the right poly to the result. 
            if (left_poly == nullptr) 
            {
                coeff = right_poly -> coeff;
                exp = right_poly -> exp;
                right_poly = right_poly -> next;
            }

            // If the right poly is null, we add the left poly to the result. 
            else if (right_poly == nullptr)
            {
                coeff = left_poly -> coeff;
                exp = left_poly -> exp;
                left_poly = left_poly -> next;
            }

            // If the exponents of the two terms are equal, we add the coefficients.
            else if (left_poly -> exp == right_poly -> exp) 
            {
                coeff = left_poly -> coeff + right_poly -> coeff;
                exp = left_poly -> exp;
                left_poly = left_poly -> next;
                right_poly = right_poly -> next;
            }

            // If the exponent of the left term is greater than the exponent of the right term,
            // we add the left term to the result.
            else if (left_poly -> exp > right_poly -> exp)
            {
                coeff = left_poly -> coeff;
                exp = left_poly -> exp;
                left_poly = left_poly -> next;
            }

            // If the exponent of the left is not greater than the exponent of the right, 
            // we add the right term to the result. 
            else 
            {
                coeff = right_poly -> coeff;
                exp = right_poly -> exp;
                right_poly = right_poly -> next;
            }

            // If the coefficient is zero, we ignore the term. Otherwise, we add the term to the
            // result. 
            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                // If the head pointer of the result is pointing to null, it means that the, 
                // new term is the first term in the resul. So, we set the head and tail pointers
                // to the new term.
                if (result.head == nullptr){
                    result.head = newNode;
                    result.tail = newNode;
                }
                // If the head pointer of the result is not null, it means that the new term is not
                // the first term in the result. So, we add the term to the end of the linked list.
                else{
                    result.tail -> next = newNode;
                    result.tail = newNode;
                }
            }
        }

        return result;
    }






    /*
    * This is the subtraction operator overload. It subtracts two polynomials and returns
    * the result.
    * 
    * The time complexity of this function is O(n + m), where n is the number of terms
    * in the first polynomial and m is the number of terms in the second polynomial.
    * 
    */
    Polynomial operator-(const Polynomial& right_hand_side_poly) const {
        Polynomial result;
        Node* right_poly = head;
        Node* left_poly = right_hand_side_poly.head;


        while (right_poly != nullptr || left_poly != nullptr) {
            double coeff = 0;
            int exp = 0;

            // Id the left poly is null, we add the right poly to the result.
            if (right_poly == nullptr)
            {
                coeff = -left_poly -> coeff;
                exp = left_poly -> exp;
                left_poly = left_poly -> next;
            }

            // If the right poly is null, we add the left poly to the result.
            else if (left_poly == nullptr)
            {
                coeff = right_poly -> coeff;
                exp = right_poly -> exp;
                right_poly = right_poly -> next;
            }

            // If the exponents of the two terms are equal, we subtract the coefficients.
            else if (right_poly -> exp == left_poly-> exp) 
            {
                coeff = right_poly -> coeff - left_poly -> coeff;
                exp = right_poly -> exp;
                right_poly = right_poly -> next;
                left_poly = left_poly -> next;
            }

            // If the exponent of the right term is greater than the exponent of the left term, 
            // we add the right term to the result.
            else if (right_poly -> exp > left_poly -> exp) {
                coeff = right_poly -> coeff;
                exp = right_poly -> exp;
                right_poly = right_poly -> next;
            } 

            // If the exponent of the right term is not greater than the exponent of the left term,
            // we add the left term to the result.
            else {
                coeff = - left_poly -> coeff;
                exp = left_poly -> exp;
                left_poly = left_poly -> next;
            }

            // If the coefficient is zero, we ignore the term. Othersie, we add the term to the result.
            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                // If the head pointer of the result is pointing to null, it means that the 
                // new term is the first term in the result. So, we set the head and tail pointers
                // to the new term. 
                if (result.head == nullptr){
                    result.head = newNode;
                    result.tail = newNode;
                }
                // If the head pointer of the result is not null, it means that the new term is not
                // the first term in the result. So, we add the term to the end of the linked list. 
                else{
                    result.tail -> next = newNode;
                    result.tail = newNode;
                }
            }
        }

        return result;
    }



    /*
    * This is the multiplication operator overload. It multiplies two polynomials and returns
    * the result.
    * 
    * The time complexity of this function is O(n^2), where n is the number of terms in the
    * first polynomial.
    */
    Polynomial operator*(const Polynomial& right_hand_poly) const{
        Polynomial result;
        Node* left_poly = head;
        Node* right_poly = right_hand_poly.head;

        /*
        This while loop iterates over the left polynomial and the right polynomial.
        The loop will terminate when the left polynomial reaches the end or point to null.
        The left polynomial will be updated to the next term only when the right poly 
        reaches the end or points to null. 
        The second loop is in the addTerm function. It iterates over the terms in the
        result polynomial and checkes if there is any term with the same exponent, 
        if there is, it updates the coefficient of the term, otherwise it adds the term
        to the end of the linked list. 
        */
        while (left_poly != nullptr){

            // If the right poly is null, we update the left poly to the next term.
            if (right_poly == nullptr){
                left_poly = left_poly -> next;
                right_poly = right_hand_poly.head;
            }

            // If the right poly is not null, we multiply the left term with the right term.
            // Then we add the new term to the result.
            else{
                double coeff = 0;
                int exp = 0;
                coeff = left_poly -> coeff * right_poly -> coeff;
                exp = left_poly -> exp + right_poly -> exp;
                result.addTerm(coeff, exp);
                right_poly = right_poly -> next;
            }
            
        }
     return result;
    }





    /*
    * This is the exponentiation operator overload. It raises the polynomial to the power of n
    * and returns the result.
    * 
    * The function uses the binary exponentiation algorithm to calculate the result.
    * The function first checks if the exponent is zero. If it is, it returns 1.
    * Then it initializes the result to 1 and the base to the polynomial.
    * The function then iterates over the bits of the exponent from right to left.
    * If the current bit is 1, it multiplies the result by the base.
    * Then it squares the base.
    * Finally, it returns the result.
    * 
    * The time complexity of this function is O(n^2 * log m), where n is the exponent.
    * 
    */
    Polynomial operator^(int exp){
        Polynomial result;
        Polynomial base = *this;
        Node* current = head;


        if (exp == 0){
            result.addTerm(1, 0);
            return result;
        }
        // This addTerm will take O(1) time for this case because
        // this is the first term in the result polynomial. 
        result.addTerm(1, 0);
        while(exp > 0){
            if (exp % 2 == 1){
                result = result * base;
            }
            base = base * base;
            exp /= 2;
        }
        return result;
    }




    /*
    * This is the division operator overload. It divides the polynomial by the denominator
    * and returns the remainder.
    * 
    * The function uses the polynomial long division algorithm to calculate the remainder.
    * The function first checks if the denominator is zero. If it is, it throws an exception.
    * Then it initializes the dividend and the remainder to the polynomial.
    * The function then iterates over the terms of the dividend until the degree of the remainder
    * is less than the degree of the denominator.
    * In each iteration, it finds the leading term of the quotient and subtracts the product of the
    * leading term and the denominator from the remainder.
    * Finally, it returns the remainder.
    * 
    * The time complexity of this function is O(n^2), where n is the number of terms in the
    * polynomial.
    */

    Polynomial operator%(const Polynomial& denominator) const {

        if (denominator.head == nullptr) {
            throw invalid_argument("Division by zero polynomial.");
        }

        Polynomial dividend = *this;  // Copy of the dividend (the current polynomial)
        Polynomial remainder = *this; // The remainder is initially the dividend

        while (remainder.head -> exp >= denominator.head -> exp) {
            
            // Find the leading term of the quotient: 
            // (leading term of remainder) / (leading term of divisor)
            double leading_coeff = remainder.head -> coeff / denominator.head -> coeff;
            int leading_exp = remainder.head -> exp - denominator.head -> exp;

            // Create the leading term of the quotient
            Polynomial leading_term;
            leading_term.head = new Node(leading_coeff, leading_exp);
            leading_term.tail = leading_term.head;

            // Multiply the leading term by the divisor and subtract the result from the remainder
            Polynomial product;
            product = leading_term * denominator;  // Multiply leading term by divisor
            remainder = remainder - product;  // Subtract the result from the remainder
        }

        // The remainder is returned, and it should have a degree less than the divisor
        return remainder;
    }



    /*
    * This function evaluates the polynomial for a given value of x and returns the result.
    *
    * The time complexity of this function is O(n), where n is the number of terms in the
    * polynomial. 
    */
    double evaluate(const Polynomial& poly, double x) const 
    {
        double final_result = 0;
        double result = 1;
        double base = x;
        Node* current = poly.head;
        int n = 0;
        if (current != nullptr) {n = current -> exp;}
        if (current == nullptr) {return 0;}
        
        while (current != nullptr) {
            if (n == 0)
            {
                result = result * current -> coeff;
                current = current -> next;
                final_result += result;
                if (current != nullptr)
                {
                    n = current -> exp;
                    result = 1;
                    base = x;
                }
            }
            else 
            {
                if (n % 2 == 1)
                {
                    result = result * base;
                }
                    base = base * base;
                    n = n / 2;
            }
        }
        return final_result;
    }


    /*
    * This function parses the polynomial from the input stream.
    * The function first reads the number of terms in the polynomial.
    * Then it reads each term from the input stream and adds it to the polynomial.
    * 
    * The time complexity of this function is O(n), where n is the number of terms in
    * the polynomial.
    */
    void parseFromInput(int terms, istream& input) {
        for (int i = 0; i < terms; i++) {
            double coeff = 0;
            int exp = 0;
            input >> coeff >> exp;
            addTerm(coeff, exp);
        }
    }


    Polynomial zero() const {
        Polynomial poly;
        return poly;
    }

};




/*
* This function processes the commands from the input stream.
* The function reads each command from the input stream and processes it.
* The function supports the following commands:
* - ZERO: Prints the zero polynomial.
* - ARBITRARY n: Parses an arbitrary polynomial with n terms from the input stream and prints it.
* - PRINT n: Parses a polynomial with n terms from the input stream and prints it.
* - EVAL n m: Parses two polynomials with n and m terms from the input stream and prints them.
* - ADD n m: Parses two polynomials with n and m terms from the input stream, adds them, and
* prints the result.
* - SUB n m: Parses two polynomials with n and m terms from the input stream, subtracts them,
* and prints the result.
* - MUL n m: Parses two polynomials with n and m terms from the input stream, multiplies them,
* and prints the result.
* - EXP n m: Parses a polynomial with n terms from the input stream and raises it to the power of m.
* - MOD n m: Parses two polynomials with n and m terms from the input stream, divides the first
* polynomial by the second polynomial, and prints the remainder.
* - QUIT: Exits the command processor.
* - Invalid command: Prints "Invalid command".
*
*/
void processCommands() {
    string command;
    
    while (getline(cin, command)) {
        istringstream iss(command);
        string operation;
        iss >> operation;
        if (operation == "ZERO" || operation == "zero") {
            Polynomial poly;
            poly = poly.zero();
            poly.print();
        }
        else if (operation == "ARBITRARY" || operation == "arbitrary") {
            int terms;
            iss >> terms;
            Polynomial poly;
            poly.parseFromInput(terms, iss);
            poly.print();
        }
        else if (operation == "PRINT" || operation == "print") {
            int terms;
            iss >> terms;
            Polynomial poly;
            poly.parseFromInput(terms, iss);
            poly.print();
        } 
        else if (operation == "EVAL" || operation == "eval") {
            int terms1;
            double value;
            iss >> terms1;
            Polynomial poly;
            poly.parseFromInput(terms1, iss);
            iss >> value;
            double result = poly.evaluate(poly, value);
            cout << result << endl;
        }
        else if (operation == "ADD" || operation == "add") {
            int terms1, terms2;
            iss >> terms1;
            Polynomial poly1;
            poly1.parseFromInput(terms1, iss);

            iss >> terms2;
            Polynomial poly2;
            poly2.parseFromInput(terms2, iss);

            Polynomial result = poly1 + poly2;
            result.print();
        } 
        else if (operation == "SUB" || operation == "sub") {
            int terms1, terms2;
            iss >> terms1;
            Polynomial poly1;
            poly1.parseFromInput(terms1, iss);

            iss >> terms2;
            Polynomial poly2;
            poly2.parseFromInput(terms2, iss);

            Polynomial result = poly1 - poly2;
            result.print();
        }
        else if (operation == "MUL" || operation == "mul") {
            int terms1, terms2;
            iss >> terms1;
            Polynomial poly1;
            poly1.parseFromInput(terms1, iss);

            iss >> terms2;
            Polynomial poly2;
            poly2.parseFromInput(terms2, iss);
            Polynomial result = poly1 * poly2;
            result.print();
        }
        else if (operation == "EXP" || operation == "exp") {
            int terms = 0, n = -1;
            iss >> terms;
            Polynomial poly;
            poly.parseFromInput(terms, iss);
            iss >> n;
            if (n < 0){
                cout << "Invalid exponent" << endl;
                continue;
            }
            Polynomial result = poly ^ n;
            result.print();
        } 
        else if (operation == "MOD" || operation == "mod") {
            int terms1, terms2;
            iss >> terms1;
            Polynomial poly1;
            poly1.parseFromInput(terms1, iss);

            iss >> terms2;
            Polynomial poly2;
            poly2.parseFromInput(terms2, iss);

            Polynomial result = poly1 % poly2;
            result.print();

        } 
        else if (operation == "QUIT" || operation == "quit") {
            break; // Exit the loop
        } else {
            cout << "Invalid command" << endl;
        }
    }
}












int main() {
    // Run the command processor
    cout << "Please enter any of the following commands:" << endl;
    cout << "ZERO" << endl;
    cout << "ARBITRARY  <int> ( <int>  <int> )* " << endl;
    cout << "PRINT <int> ( <int>  <int> )* " << endl;
    cout << "EVAL   <int> ( <int>  <int> )*  <int>" << endl;
    cout << "ADD   <int> ( <int>  <int> )*  <int> ( <int>  <int> )* " << endl;
    cout << "SUB    <int> ( <int>  <int> )*  <int> ( <int>  <int> )* " << endl;
    cout << "MUL    <int> ( <int>  <int> )*  <int> ( <int>  <int> )* " << endl;
    cout << "EXP    <int> ( <int>  <int> )*  <int>" << endl;
    cout << "MOD    <int> ( <int>  <int> )*  <int> ( <int>  <int> )* " << endl;
    cout << "QUIT" << endl;
    cout << "Please enter the command: " << endl;
    processCommands();

    return 0;
}
