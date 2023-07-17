#include <iostream>
#include <string>

void assert(int condition, std::string msg) {
    if (condition) {
        std::cout << msg << std::endl;
        abort();
    }
}

class AList {            // Classe abstrata contendo a assinatura das funções e variáveis que serão usadas na classe List
    protected:
        int maxSize;     // Tamanho máximo da lista
        int listSize;    // Número atual de itens na lista
        int curr;        // Posição do elemento atual
        int* listArray;  // Vetor contendo os elementos da lista
    
    public:

        virtual void clear() = 0;
        virtual void insert(const int& it) = 0;
        virtual void append(const int& it) = 0;
        virtual int remove() = 0;
        virtual void moveToStart() = 0;
        virtual void moveToEnd() = 0;
        virtual void prev() = 0;
        virtual void next() = 0;
        virtual int length() const = 0;
        virtual int currPos() const = 0;
        virtual void moveToPos(int pos) = 0;
        virtual const int& getValue() const = 0;
        virtual const int count(int x) const = 0;

};

class List : public AList { // Classe lista, a qual herda da classe abstrata AList
    public:

        List(int size = 10) { // Construtor da classe, o valor 10 é o tamanho padrão dado a lista caso o usuário não forneça um valor
            maxSize = size;
            listSize = curr = 0;
            listArray = new int[maxSize];
        }

        ~List() { // Destrutor da classe
            delete [] listArray;
        }

        void clear() override {  // Reinicializa a lista
            delete [] listArray; // Apaga o vetor da memória
            listSize = curr = 0; // Reseta o tamanho
            listArray = new int[maxSize]; // Cria o vetor novamente
        }

        // Insere "it" na posição atual
        void insert(const int& it) override {
            assert(listSize >= maxSize, "Tamanho máximo da lista atingido.");
            for (int i = listSize; i > curr; i--) // Move os elmentos para dar espaço ao novo elemento
                listArray[i] = listArray[i - 1];
            
            listArray[curr] = it;
            listSize++; // Incrementa o tamanho da lista
        }

        void append(const int& it) override { // Adiciona "it" no final da lista
            assert(listSize >= maxSize, "Tamanho máximo da lista atingido.");
            listArray[listSize++] = it;
        }

        // Remove e retorna o elemento atual.
        int remove() override {
            assert(!((curr >= 0) && (curr < listSize)), "Não há elementos.");
            int it = listArray[curr];                 // Copia o elemento a ser removido
            for (int i = curr; i < listSize - 1; i++) // Move os elementos, ocupando o espaço livre  
                listArray[i] = listArray[i + 1];

            listSize--; // Decrementa o  tamanho da lista

            return it;
        }

        void moveToStart() override { curr = 0; } // Reseta a posição
        void moveToEnd() override { curr = listSize; } // Move o cursor para o fim da lista
        void prev() { if (curr != 0) curr--; } // Move o cursor uma posição a menos
        void next() { if (curr < listSize) curr++; } // Move o cursor uma posição a mais

        // Retorna o tamanho da lista
        int length() const override { return listSize; }

        // Retorna a posição atual
        int currPos() const override { return curr; }
        
        // Define a posição atual da lista para "pos"
        void moveToPos(int pos) override {
            assert(!((pos >= 0) && (pos <= listSize)), "Posição fora de alcance.");
            curr = pos;
        }

        const int& getValue() const override {
            assert(!((curr >= 0) && (curr <= listSize)), "Elemento atual indisponível.");
            return listArray[curr];
        }

        const int count(int x) const override {
            int equalsIndex = 0;

            for (int i = 0; i < listSize; i++)
                if (listArray[i] == x) equalsIndex++;

            return equalsIndex;
        }
};

int main() {

    List* list = new List(1);

    std::cout << list->length() << std::endl;

    // list->append(3);
    // list->append(24);
    // list->append(1);

    // std::cout << list->getValue() << std::endl;
    list->next();
    list->next();
    // std::cout << list->getValue() << std::endl;

    return 0;
}