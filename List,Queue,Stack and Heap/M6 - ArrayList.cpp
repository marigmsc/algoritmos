#include <iostream>
using namespace std;
class Lista{
    public:
    int maxsize;
    int listsize;
    int curr;
    int *array;
    public:
    void insert(int it){
        if (listsize >= maxsize) cout << "Erro"; //se o tamanho da lista exceder o máximo
        else{
        for (int i = listsize; i > curr; i--){ //loop que irá rodar nos elementos a direita do cursor
            array[i] = array[i - 1]; //desloca os elementos para direita
        }
        array[curr] = it; //insere o elemento onde está o cursor
        listsize++;
        }
    }
    void movetostart(){
        curr = 0;
    }
    void movetoend(){
        curr = listsize;
    }
    void prev(){
        if(curr != 0) curr--;
    }
    void next(){
        if(curr < listsize) curr++;
    }
    int remove(){
        if(curr < 0 || curr >= listsize) return 0;
        else{
            
            int it = array[curr]; //elemento onde está o cursor
            int i = curr;
            while(i < listsize - 1){ //enquanto i for menor que o tamanho da lista
                array[i ] = array[i + 1]; //desloca os elementos para esquerda
                i++;
            }
            listsize--;
            return it;
        }
    }
    void print(){
        for(int i = 0; i < listsize;i++) cout << *(array + i) << endl;
    }
};
Lista createlista(int size);
int main(){
    Lista list = createlista(5);
    list.insert(2);
    list.insert(10);
    list.insert(4);
    list.print();
    int removed = list.remove();

    cout << removed << endl;
    list.print();



    return 0;
}
Lista createlista(int size){
    Lista l;
    l.maxsize = size;
    l.listsize = l.curr = 0;
    l.array = new int[size];
    return l;
}