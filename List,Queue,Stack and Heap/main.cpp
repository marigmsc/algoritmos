#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

class Link {
    public:
        Link* next;
        int element;

        Link(int& elemval, Link* nextval = nullptr) {
            next = nextval;
            element = elemval;
        }

        Link(Link* nextval = nullptr) {
            next = nextval;
        }
};

class Stack {
    public:
        Link* top;
        int size;

    Stack() {
        top = nullptr;
        size = 0;
    }

    void clear() {
        while (top != nullptr) {
            Link* tmp = top;
            top = top->next;
            delete tmp;
        }

        size = 0;
    }

    void print() {
        Link* tmp = top;
        while (tmp != nullptr) {
            std::cout << tmp->element << std::endl;
            tmp =  tmp->next;
        }
    }

    void push(int& it) {
        top = new Link(it, top);
        size++;
    }

    int pop() {
        Link* tmp = top;
        int returnStr = tmp->element;
        top = top->next;
        delete tmp;
        size--;

        return returnStr;
    }

    int topValue() const {
        return top->element;
    }

};

int main() {

    Stack* pilha = new Stack();
    std::string input;
    std::string insideInput;

    while (input != "EOF") {

        std::cin >> insideInput;
        int valor = atoi(insideInput.data());
        pilha->push(valor);
        while (insideInput != "END") {
            std::cin >> insideInput;

            if (insideInput == "*") {
                int v2 = pilha->pop();
                int v1 = pilha->pop();
                int res = v1*v2;
                pilha->push(res);
            }

            if (insideInput == "+") {
                int v2 = pilha->pop();
                int v1 = pilha->pop();
                int res = v1+v2;
                pilha->push(res);
            }

            if (insideInput == "-") {
                int v2 = pilha->pop();
                int v1 = pilha->pop();
                int res = v1-v2;
                pilha->push(res);
            }
            
            int valor2 = atoi(insideInput.data());
            if (insideInput != "END" && insideInput != "*" && insideInput != "+" && insideInput != "-") pilha->push(valor2);
            
        }

        pilha->print();
        pilha->clear();
        std::cin >> input;
        int valor3 = atoi(input.data());
        if (input != "END" && input != "EOF") pilha->push(valor3);
        

    }

    

    return 0;
}