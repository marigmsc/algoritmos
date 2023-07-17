#include <iostream>
#include <string>
using namespace std;
template <typename E>
class Link{ //Criando a classe dos nós
    public:
    E element; //Valor do nó
    Link<E> *next; // Ponteiro para o próximo nó da lista
    public:
    Link(E elemval, Link<E>* nextval = nullptr) {
            element = elemval;
            next = nextval;
        }

        Link(Link<E>* nextval = nullptr) {
            next = nextval;
        }
};
template <typename E>
class List{
    public:
    Link<E> *head; //Aponta para o primeiro elemento
    Link<E> *tail; //Aponta para o último elemento
    Link<E> *curr; //Cursor
    int cnt; //Tamanho da lista
    public:
    List(){
        head = tail = curr = new Link<E>(nullptr);
        cnt  = 0;
    }
    ~List(){}
void print() {    // Imprime o conteúdo da lista
            while (head != nullptr) {
                Link<E>* temp = curr;
                Link<E>* tempHead = head;
                temp = tempHead;
                tempHead = tempHead->next;
                cout << temp->element << endl;
            }
}
void append(E it) {
            tail = tail->next = new Link<E>(it, nullptr); //cria uma nova cauda, com o elemento adicionado e um ponteiro apontando pra null por ser a nova última posição
            cnt++; // aumenta o size da lista
}
void insert(E it){
        curr->next = new Link<E>(it,curr->next); //criar um nó a direita do cursor, e fazer com o que o slot do cursor aponte para ele
        if(tail == curr) tail = curr->next; // determina nova cauda
        cnt++; //aumenta o número de elementos
}
int tamanho(){
        return cnt; // returna o size da lista
}
void movetostart(){
        curr = head; // leva o cursor para o nó inicial (head)
}
void movetoend(){
        curr = tail; // leva o cursor para o nó final(tail)
}
void next(){
        if(curr != tail) curr = curr->next; // avança o cursor em 1 unidade
}
int currposicion(){
     Link<E> *temp = head; // ponteiro auxiliar que será igual a head
            int i;
            for (i = 0; curr != temp; i++) //enquanto o cursor for diferente de temp
                temp = temp->next; //avança uma posição até achar e parar
            
            return i;
}
void prev(){
    if(curr == head) return; //se o cursor for igual a cabeça, retorna nada
    Link<E> *temp = head; // ponteiro auxiliar que será igual a head
    while(temp->next != curr) temp = temp->next; //vai avançando uma posição até estar a uma posição do cursor
    curr = temp; //iguala
}

E remove(){
    if (curr->next == NULL) return 0; //se a direita do cursor for nulo , não remove nada
    E it = curr->next->element; //declara uma variavel que é o elemento depois do cursor
    Link<E> *temp = curr->next; //criar um ponteiro auxilar que será igual ao ponteiro de depois do cursor
    if(tail == curr->next) tail = curr; //se o p
    curr->next = curr->next->next;
    cnt--;
    delete temp;
    return it;
}

};

int main(){
    int curr;
   



    return 0;
}

