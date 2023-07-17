#include <iostream>
using namespace std;
class Link{
    public:
    int element;
    Link *next;
        Link(const int& it,Link *nextval = nullptr){
            element = it;
            next = nextval;
        }
        Link(Link* nextval = nullptr) {
            next = nextval;
        }
};
class Queue{
    public:
    Link *rear;  //final
    Link *front; //inicio
    int size;    //tamanho
    public:
    void Enqueue(int it){
        rear->next = new Link(it,NULL); //cria um ponteiro depois do rear
        rear = rear->next; //avança um slot 
        size++; //aumenta o tamanho
    }
    int Dequeue(){
        Link *temp = front->next; 
        if(size == 0) exit(1);
        else{ 
            Link *temp = front->next; 
            int it = temp->element; //pega o primeiro elemento apos o empty header
            front->next = temp->next; //avança um slot, agora apontando pro segundo elemento que sera o primeiro
            if(rear == temp) rear = front;
            size--; //diminui o tamanho
            delete temp;
            return it;
            
        }
    }
    int Length(){
        return size;
    }
    int FrontValue(){
        return front->next->element;
    }
    void Clear(){
        while(front->next != nullptr){
            Link *temp = front->next;
            front->next = front->next->next;
            delete temp;
        }
        size = 0;
    }
    void Print(){
        Link *temp = front->next;
        while(temp != nullptr){
            cout << temp->element << " ";
            temp = temp->next;
        }
    }
};
        

Queue CreateQueue();


int main(){
    Queue filinha = CreateQueue();
    filinha.Enqueue(4);
    filinha.Enqueue(7);
    filinha.Enqueue(12);
    //filinha.Print();
    int tamanho = filinha.Length();
    cout << tamanho << endl;
    //filinha.Clear();
    int removed = filinha.Dequeue();
    cout << removed << endl;
    filinha.Print();
    










    return 0;
}
Queue CreateQueue(){
    Queue f;
    f.front = f.rear = new Link(nullptr);
    f.size = 0;
    return f;
}
