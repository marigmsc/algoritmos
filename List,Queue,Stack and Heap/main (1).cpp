#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
class Link{
    public:
    int element;
    Link *next;
        Link(const int& it,Link *nextval){
            element = it;
            next = nextval;
        }
        Link(Link *nextval){
            
            next = nextval;
        }
};
class Stack {
    public:
    Link *top; // primeiro elemento
    int size; // número de elementos 
        void Push(int it){
            top = new Link(it,top); //cria um nó em que o ponteiro next aponta p top, que inicialmente é NULL
            //depois igual ao top ou seja agora o top aponta p esse nó e o nó aponta p NULL como escrito acima
            size++; //aumenta o tamanho da pilha em 1
        }
        int Pop(){
            int it;
            Link *temp = top;
            if(top == NULL) exit(1);
            else{
                it = top->element; //guarda o elemento a ser eliminado (o primeiro da fila)
                top = top->next; // faz o ponteiro top apontar pro elemento apos o primeiro
                size--; //diminui o tamanho da pilha
                delete temp; //desaloca o ponteiro antigo top
                return it;
            }
        }
        int TopValue(){
            return top->element; //retorna o elemento no topo
        }
        void Clear(){
            while(top !=nullptr){
                Link *temp = top; //iguala um temporario ao topo
                top = top->next; //avança um slot no ponteiro DO TOPO
                delete temp; //deleta temp e qnd temp se igualar a top de novo ja sera o proximo
            }
        size = 0;
        }

        

            
        
};
Stack CreateStack();



int main(){
        char entrada[500];
        
        Stack Pilha = CreateStack();
        while(!cin.eof()){
            
            cin >> entrada;
            
            int v1 = atoi(entrada);
             
            
                if(v1 != 0){
                   
                    Pilha.Push(v1);
                }
                else{
                    if(!strcmp(entrada,"+")) {
                        int v2 = Pilha.Pop();
                       int v3 = Pilha.Pop();
                        Pilha.Push(v2 + v3);
                    }
                    else if(!strcmp(entrada,"-")){
                            int v2 = Pilha.Pop();
                            int v3 = Pilha.Pop();
                            Pilha.Push(v3 - v2);
                    }
                    else if(!strcmp(entrada,"*")) {
                            int v2 = Pilha.Pop();
                            int v3 = Pilha.Pop();
                            Pilha.Push(v2 * v3);
                    }
                    else if(!strcmp(entrada,"END")){
                        int resultado = Pilha.TopValue();
                        cout << resultado << endl;
                        
                        Pilha.Clear();
                         
                }
                

        }
       
       
        

        }
        
 

        






    return 0;
}
Stack CreateStack(){
            Stack s;
            s.top = new Link(NULL); // colocando o ponteiro para NULL
            s.size = 0; // zerando o número de elementos
            return s;
        }
