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
                delete newNode;
            }
            temp = temp -> next;
        }
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
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
        Node* last = result.head;

        while (ptr1 != nullptr || ptr2 != nullptr) {
            int coeff = 0, exp = 0;
            if (ptr1 -> exp == ptr2 -> exp) {
                coeff = ptr1 -> coeff + ptr2->coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
            else if (ptr1 -> exp > ptr2 -> exp) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            }
            else if (ptr1 == nullptr) {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            } else if (ptr2 == nullptr) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            } else {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            }

            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                if (last == nullptr){
                    result.head = newNode;
                }
                else{
                    last -> next = newNode;
                    last = last -> next;
                }
            }
        }
        if (ptr1 == nullptr && ptr2 == nullptr){
            return result;
        }
        else if (ptr1 == nullptr){
            last -> next = ptr2;
        }
        else if (ptr2 == nullptr){
            last -> next = ptr1;
        }

        return result;
    }



    Polynomial operator-(const Polynomial& right_hand_side_poly) const {
        Polynomial result;
        Node* ptr1 = head;
        Node* ptr2 = right_hand_side_poly.head;
        Node* last = nullptr;

        while (ptr1 != nullptr || ptr2 != nullptr) {
            int coeff = 0, exp = 0;
            if (ptr1 == nullptr) {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            } else if (ptr2 == nullptr) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            } else if (ptr1 -> exp == ptr2 -> exp) {
                coeff = ptr1 -> coeff - ptr2->coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            } else if (ptr1 -> exp > ptr2 -> exp) {
                coeff = ptr1 -> coeff;
                exp = ptr1 -> exp;
                ptr1 = ptr1 -> next;
            } else {
                coeff = ptr2 -> coeff;
                exp = ptr2 -> exp;
                ptr2 = ptr2 -> next;
            }

            if (coeff != 0){
                Node* newNode = new Node(coeff, exp);
                if (last == nullptr){
                    result.head = newNode;
                }
                else{
                    last -> next = newNode;
                }
                last = newNode;
            }
        }

        return result;
    }



    int raise_to(int coeff, int exp){
        int result = 1;
        while (exp > 0){
            if (exp % 2 == 1){
                result = result * coeff;
            }
            coeff = coeff * coeff;
            exp = exp / 2;
        }
        return result;
    }

    Polynomial operator^(int exp){
        Polynomial result;
        Node* current = head;

        if (exp == 0){
            Node* newNode = new Node(1, 0);
            result.head = newNode;
            return result;
        }
        
        while(current != nullptr){
            int coeff = current -> coeff;
            coeff = raise_to(coeff, exp);
            current -> coeff = coeff;
            current -> exp = current -> exp * exp;
            current = current -> next;
        }
        return *this;
    }


    
    // Polynomial operator*(const Polynomial right_hand_poly) const{
    //     Polynomial result;
    //     Node* current_left_poly = head;
    //     Node* current_right_poly = right_hand_poly.head;
    // }


    // Parse polynomial from input
    void parseFromInput(int terms, istream& input) {
        for (int i = 0; i < terms; ++i) {
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
        // else if (operation == "MUL" || operation == "mul") {
        //     int terms1, terms2;
        //     iss >> terms1;
        //     Polynomial poly1;
        //     poly1.parseFromInput(terms1, iss);

        //     iss >> terms2;
        //     Polynomial poly2;
        //     poly2.parseFromInput(terms2, iss);
        //     if (terms1 > terms2){
        //         Polynomial result = poly1 * poly2;
        //     }
        //     else if (terms1 < terms2){
        //         Polynomial result = poly2 * poly1;          
        //     }
        //    else{ 
        //         Polynomial result = poly1 * poly2;
        //     } 
        //     result.print();
        // }
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
