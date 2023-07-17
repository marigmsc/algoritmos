#include <iostream>
using namespace std;
template <typename E>
class Link{
    public:
    E element;
    Link<E> *next;
        Link<E>(const int& it,Link<E> *nextval){
            element = it;
            next = nextval;
        }
};
class Stack {
    public:
    Link<E> *top; // primeiro elemento
    int size; // número de elementos 
        void Push(E it){
            top = new Link<E>(it,top); //cria um nó em que o ponteiro next aponta p top, que inicialmente é NULL
            //depois igual ao top ou seja agora o top aponta p esse nó e o nó aponta p NULL como escrito acima
            size++; //aumenta o tamanho da pilha em 1
        }
        E Pop(){
            E it;
            Link<E> *temp = top;
            if(top == NULL) exit(1);
            else{
                it = top->element; //guarda o elemento a ser eliminado (o primeiro da fila)
                top = top->next; // faz o ponteiro top apontar pro elemento apos o primeiro
                size--; //diminui o tamanho da pilha
                delete temp; //desaloca o ponteiro antigo top
                return it;
            }
        }
        int Tamanho() {
            return size; //retorna o tamanho
        }
        E TopValue(){
            return top->element; //retorna o elemento no topo
        }
        void Clear(){
            while(top !=nullptr){
                Link<E> *temp = top; //iguala um temporario ao topo
                top = top->next; //avança um slot no ponteiro DO TOPO
                delete temp; //deleta temp e qnd temp se igualar a top de novo ja sera o proximo
            }
        size = 0;
        }
        void Print(){
            Link<E> *tmp = top; //ponteiro apontando pro topo
            while(tmp != nullptr){
                cout << tmp->element << endl; //imprime o elemento do top
                tmp = tmp->next; //avança um slot
            }
        }

        

            
        
};
Stack CreateStack();


int main(){
    Stack pilha = CreateStack();
    pilha.Push(2);
    pilha.Push(4);
    pilha.Push(6);
    pilha.Print();
    int removed = pilha.Pop();
    cout << "Removido:" << removed << endl;
    pilha.Print();
    int size = pilha.Tamanho();
    cout << size << endl;
    int topvalor = pilha.TopValue();
    cout << topvalor << endl;













    return 0;
}
Stack CreateStack(){
            Stack s;
            s.top = NULL; // colocando o ponteiro para NULL
            s.size = 0; // zerando o número de elementos
            return s;
        }