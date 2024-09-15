#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Define a class for the node representing a term in the polynomial
class Node {
public:
    int coeff; // Coefficient of the term
    int exp;   // Exponent of the term
    Node* next; // Pointer to the next node

    Node(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

// Polynomial class
class Polynomial {
private:
    Node* head; // Head of the linked list representing the polynomial
    Node* tail;

    // Add term manually
    void addTerm(int coeff, int exp) {
        if (coeff == 0) return; // Ignore zero coefficients
        Node* newNode = new Node(coeff, exp);
        Node* temp = head;
        while (temp != nullptr) {
            if (temp -> exp == exp) {
                temp -> coeff += coeff;
                return;
            }
            temp = temp -> next;
        }
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail -> next = newNode;
            tail = newNode;
        }
    }

public:
    // Constructor to initialize zero polynomial
    Polynomial() : head(nullptr), tail(nullptr){}
    Polynomial(istream& input)
    {
        int term;
        input >> term;
        for (int i = 0; i < term; ++i) {
            int coeff, exp;
            input >> coeff >> exp;
            addTerm(coeff, exp);
        }
    }

    // Print the polynomial
    void print() const {
        cout << "\n\nInside the print function \n\n";
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }
        Node* temp = head;
        bool first = true;

        while (temp != nullptr) {
            if (!first && temp->coeff > 0) cout << " + ";
            if (!first && temp->coeff < 0) cout << " ";
            if (first) first = false;
            cout << temp->coeff << "x^" << temp->exp;
            temp = temp->next;
        }
        cout << endl;
    }

    // Add two polynomials
    Polynomial operator+(const Polynomial& right_hand_side_poly) const {
        Polynomial result;
        Node* ptr1 = head;
        Node* ptr2 = right_hand_side_poly.head;

        while (!(ptr1 == nullptr || ptr2 == nullptr)) {
            int coeff = 0, exp = 0;
            if (ptr1 -> exp == ptr2 -> exp) {
                coeff = ptr1 -> coeff + ptr2 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
            else if (ptr1 -> exp > ptr2 -> exp) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            }
            else {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            }

            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                if (result.head == nullptr){
                    result.head = newNode;
                    result.tail = newNode;
                }
                else{
                    result.tail -> next = newNode;
                    result.tail = newNode;
                }
            }
        }
        if (ptr1 == nullptr && ptr2 == nullptr){
            return result;
        }
        else if (ptr1 == nullptr){
            result.tail -> next = ptr2;
        }
        else if (ptr2 == nullptr){
            result.tail -> next = ptr1;
        }

        return result;
    }



    Polynomial operator-(const Polynomial& right_hand_side_poly) const {
        Polynomial result;
        Node* ptr1 = head;
        Node* ptr2 = right_hand_side_poly.head;
        // Node* last = nullptr;

        while (!(ptr1 == nullptr || ptr2 == nullptr)) {
            int coeff = 0, exp = 0;
            if (ptr1 -> exp == ptr2 -> exp) {
                coeff = ptr1 -> coeff - ptr2 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            } 
            else if (ptr1 -> exp > ptr2 -> exp) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            } 
            else {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            }

            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                if (result.head == nullptr){
                    result.head = newNode;
                    result.tail = newNode;
                }
                else{
                    result.tail -> next = newNode;
                    result.tail = newNode;
                }
            }
        }

        if (ptr1 == nullptr && ptr2 == nullptr){
            return result;
        }
        else if (ptr1 == nullptr){
            result.tail -> next = ptr2;
        }
        else if (ptr2 == nullptr){
            result.tail -> next = ptr1;
        }

        return result;
    }


    
    Polynomial operator*(const Polynomial right_hand_poly) const{
        Polynomial result;
        Node* current_left_poly = head;
        Node* current_right_poly = right_hand_poly.head;

        while (current_left_poly != nullptr){
            if (current_right_poly == nullptr){
                current_left_poly = current_left_poly -> next;
                current_right_poly = right_hand_poly.head;
            }
            else{
                int coeff = 0, exp = 0;
                coeff = current_left_poly -> coeff * current_right_poly -> coeff;
                exp = current_left_poly -> exp + current_right_poly -> exp;
                result.addTerm(coeff, exp);
                current_right_poly = current_right_poly -> next;
            }
            
        }
     return result;
    }



    Polynomial operator^(int exp){
        Polynomial result;
        Polynomial base = *this;
        Node* current = head;


        if (exp == 0){
            result.addTerm(1, 0);
            return result;
        }
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


    Polynomial operator%(const Polynomial& divisor) const {
    
        if (divisor.head == nullptr) {
            throw invalid_argument("Division by zero polynomial.");
        }

        Polynomial dividend = *this;  // Copy of the dividend (the current polynomial)
        Polynomial remainder = divisor; // The remainder is initially the dividend


        while (remainder.head != nullptr && remainder.head->exp >= divisor.head->exp) {
            // Find the leading term of the quotient: (leading term of remainder) / (leading term of divisor)
            int leading_coeff = remainder.head->coeff / divisor.head->coeff;
            int leading_exp = remainder.head->exp - divisor.head->exp;

            // Create the leading term of the quotient
            Polynomial leading_term;
            leading_term.addTerm(leading_coeff, leading_exp);

            // Subtract the product of the leading term and divisor from the remainder
            Polynomial product = leading_term * divisor;  // Multiply leading term by divisor
            remainder = remainder - product;  // Subtract the result from the remainder

            // You could also add the leading_term to the quotient, but it's not necessary for remainder
        }

        // The remainder is returned, and it should have a degree less than the divisor
        return remainder;
    }



    // Parse polynomial from input
    void parseFromInput(int terms, istream& input) {
        for (int i = 0; i < terms; i++) {
            int coeff, exp;
            input >> coeff >> exp;
            addTerm(coeff, exp);
        }
    }
};

// CLI interface
void processCommands() {
    string command;
    
    while (getline(cin, command)) {
        istringstream iss(command);
        string operation;
        iss >> operation;
        if (operation == "ZERO" || operation == "zero") {
            Polynomial poly;
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
            int terms1, terms2;
            iss >> terms1;
            Polynomial poly;
            poly.parseFromInput(terms1, iss);
            iss >> terms2;
            poly.parseFromInput(terms2, iss);
            poly.print();
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
    processCommands();

    return 0;
}
