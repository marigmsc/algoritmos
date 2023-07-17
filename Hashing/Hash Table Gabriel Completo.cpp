#include <iostream>
#include <array>
#include <string>
 
template <typename Key, typename E>
class KVpair {
    private:
        Key k;
        E e;
    
    public:
        // Construtores
        KVpair() {}
        KVpair(Key kval, E eval) {
            k = kval;
            e = eval;
        } 
        // & -> referência a uma variável
        // const -> eficiencia/ não altera o conteudo variável mas ainda acessa
        // const antes da { -> nao altera nd da classe
        KVpair(const KVpair& o) {   // Construtor de cópia
            k = o.k;
            e = o.e;
        }
 
        void operator = (const KVpair& o) { // Operador de atribuição
            k = o.k;
            e = o.e;
        }
 
        // Funções de acesso à variáveis locais
        Key key() { return k ;}
        void setKey(Key ink) { k = ink;}
        E value() { return e; }
};
 
template <typename Key, typename E>
class Dictionary {
    private:
        void operator = (const Dictionary&) {}
        Dictionary(const Dictionary&) {}
 
    public:
        Dictionary() {}          // Construtor padrão
        virtual ~Dictionary() {} // Destrutor base
 
        // Reinicializa o dicionário
        virtual void clear() = 0;
 
        // Insere um registro
        // k: A chave do registro a ser inserido.
        // e: O registro a ser inserido.
        virtual void insert(const Key& k, const E& e) = 0;
 
        // Remove e retorna um registro
        // k: A chave do registro a ser removido.
        // Return: O registro encontrado. Se múltiplos
        // registros com a chave "k" forem encontrados,
        // remove um registro arbitrário. Retorna NULL
        // caso nenhum registro com a chave "k" exista.
        virtual E remove(const Key& k) = 0;
 
        // Remove e retorna um registro arbitrário do dicionário.
        // Return: O registro removido, ou NULL caso nenhum exista.
        virtual KVpair<Key, E> removeAny() = 0;
 
        // Return: Um registro correspondente a "k" (NULL se nenhum existe).
        // Se múltiplos registros coincidirem, retorna um arbitrário.
        // k: A chave do registro a ser procurado.
        virtual E find(const Key& k) const = 0;
 
        // Retorna o número de registros no dicionário
        virtual int size() const = 0;
};
 
 
template <typename T>
class List { 
    protected:
        int maxSize;     // Tamanho máximo da lista
        int listSize;    // Número atual de itens na lista
        int curr;        // Posição do elemento atual
        T* listArray;    // Vetor contendo os elementos da lista
 
    public:
 
        List(int size = 10) { // Construtor da classe, o valor 10 é o tamanho padrão dado a lista caso o usuário não forneça um valor
            maxSize = size;
            listSize = curr = 0;
            listArray = new T[maxSize];
        }
 
        ~List() { // Destrutor da classe
            delete [] listArray;
        }
 
        void clear() {  // Reinicializa a lista
            delete [] listArray; // Apaga o vetor da memória
            listSize = curr = 0; // Reseta o tamanho
            listArray = new T[maxSize]; // Cria o vetor novamente
        }
 
        // Insere "it" na posição atual
        void insert(const T& it) {
            for (int i = listSize; i > curr; i--) // Move os elmentos para dar espaço ao novo elemento
                listArray[i] = listArray[i - 1];
            
            listArray[curr] = it;
            listSize++; // Incrementa o tamanho da lista
        }
 
        void append(const T& it) { // Adiciona "it" no final da lista
            listArray[listSize++] = it;
        }
 
        // Remove e retorna o elemento atual.
        T remove() {
            T it = listArray[curr];                 // Copia o elemento a ser removido
            for (int i = curr; i < listSize - 1; i++) // Move os elementos, ocupando o espaço livre  
                listArray[i] = listArray[i + 1];
 
            listSize--; // Decrementa o  tamanho da lista
 
            return it;
        }
 
        void moveToStart() { curr = 0; } // Reseta a posição
        void moveToEnd() { curr = listSize; } // Move o cursor para o fim da lista
        void prev() { if (curr != 0) curr--; } // Move o cursor uma posição a menos
        void next() { if (curr < listSize) curr++; } // Move o cursor uma posição a mais
 
        // Retorna o tamanho da lista
        int length() const { return listSize; }
 
        // Retorna a posição atual
        int currPos() const { return curr; }
        
        // Define a posição atual da lista para "pos"
        void moveToPos(int pos) {
            curr = pos;
        }
 
        const T& getValue() const {
            return listArray[curr];
        }
 
        const int count(int x) const {
            int equalsIndex = 0;
 
            for (int i = 0; i < listSize; i++)
                if (listArray[i] == x) equalsIndex++;
 
            return equalsIndex;
        }
};
 
 
// Dicionário implementado como uma lista baseada em array não ordenada
// UAL = unsorted array-list
template <typename Key, typename E>
class UALdict : public Dictionary<Key, E> {
    private:
        List<KVpair<Key, E>>* list;
        
    public: 
        UALdict(int size = 10) {  // Construtor
            list = new List<KVpair<Key, E>> (size);
        }
 
        ~UALdict() {
            delete list;          // Destrutor
        }
 
        void clear() override {   // Reinicializa
            list->clear();
        }
 
        // Insere um elemento na lista
        void insert(const Key& k, const E& e) override {
            KVpair<Key, E> temp(k, e);
            list->append(temp);
        }
 
        // Usa busca sequencial para achar o elemento a ser removido
        E remove(const Key& k) override {
            E temp = find(k);    // "find" irá definir a posição da lista
            if (temp != NULL) list->remove();
            
            return temp;
        }
 
        // Remove o último elemento
        KVpair<Key, E> removeAny() override {
            list->moveToEnd();
            list->prev();
            KVpair<Key, E> e = list->remove();
 
            return e;
        }
 
        // Procura por "k" usando busca sequencial
        E find(const Key& k) const override {
            for (list->moveToStart(); list->currPos() < list->length(); list->next()) {
                KVpair<Key, E> temp = list->getValue();
                if (k == temp.key())
                    return temp.value();
            }
 
            return NULL;
        }
 
        int size() const override {
            return list->length();
        }
 
        void print() {
            UALdict<Key, E>* temp = this;
            KVpair<Key, E> kvtemp;
            while (temp->size() > 0) {
                kvtemp = this->removeAny();
                std::cout << "chave: " << kvtemp.key() << " | valor: " << kvtemp.value() << std::endl;
            }
        }
 
};
 
 
int main() {
 
    UALdict<int, int>* dict = new UALdict<int, int> (2);
 
    dict->insert(1, 2);
    dict->insert(3, 4);
    dict->print();
    
    return 0;
}