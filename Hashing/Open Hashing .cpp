#include <iostream>
#include <list>
#include <math.h>
using namespace std;

class Dictionary{
    public:
    int size_hash_table;
    int num_elements;
    list<string> vector_list[];
    int Fold(string K){
        int tam = str.length(k);
        int sum = 0;
            for(int i = 0; i < tam;i++) sum += K[i];
        int key =  abs(sum) % size_hash_table;
        return key;
    } 
    public:
    Dictionary(int size,Fold(string K)){
        size_hash_table = size;
        num_elements = 0;
        vector_list = new list<string>[size];
        for(int i = 0; i < size;i++) vector_list[i] = new list<string>;

    }
    void Insert(Key k, string element){
//Insere sempre no final da lista e a lista não está ordenada
        if(Find(k) == NULL){
//Verifica se existe no dicionario alguém com a chave k
//Se existir, nada é feito.
        int position = Fold(k);
        
        }
    }


};
int main(){


 int
 















    return 0;
}
/* 
Hash Table é um array com m posições (indices de 0 a m - 1)
Para inteiros a função hash é h(k) = k mod m que entregará valores a 0 a m - 1
    Função hash para strings: (fold)
        int h(string K){
            int tam = str.length(k);
            int sum = 0;
            for(int i = 0; i < tam;i++) sum += K[i];
            return abs(sum) % m;
        }
    Colisões: entradas diferentes que sua função hash mapeia na mesma posição
Open Hashing: cada retorno da função hash para strings é associado a uma posição de uma linked list. Ao ocorrer a colisão insere os dois no mesmo slot?
Inserção/Remoção:
h(K) = j;
Insira K no j-th elementos
Ao manter a lista ordenada, MELHOR busca e PIOR inserção. Desordenada, é ao contrário
Busca:
h(K) = j;
If j-th is empty, false;
else, search;
*/