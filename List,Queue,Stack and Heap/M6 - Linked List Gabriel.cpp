#include <iostream>
#include <string>

void assert(int condition, std::string msg) {
    if (condition) {
        std::cout << msg << std::endl;
        abort();
    }
}

class Link {
    public:
        int element; // Valor do nódulo
        Link *next;  // Ponteiro para o próximo nódulo na lista
    
    public:
        Link(const int& elemval, Link* nextval = nullptr) {
            element = elemval;
            next = nextval;
        }

        Link(Link* nextval = nullptr) {
            next = nextval;
        }
};

class List {
    protected:
        Link* head; // Ponteiro para a "cabeça" da lista
        Link* tail; // Ponteiro para o último elemento
        Link* curr; // Acesso ao elemento atual 
        int cnt;    // Tamanho da lista
    
        virtual void init() = 0;
        virtual void removeAll() = 0;

    public:

        virtual void print() = 0;
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

};

class LList : public List {
    private:
        void init() override { // Método auxiliar de inicialização
            curr = tail = head = new Link();
        }

        void removeAll() override { // Remove todos os nódulos da lista
            while (head != nullptr) {
                curr = head;
                head = head->next;
                delete curr;
            }
        }
    
    public:
        LList(int size = 10) { // Construtor
            init();
        }

        ~LList() {             // Destrutor
            removeAll();
        }

        void print() override {    // Imprime o conteúdo da lista
            while (head != nullptr) {
                Link* temp = curr;
                Link* tempHead = head;
                temp = tempHead;
                tempHead = tempHead->next;
                std::cout << temp->element << std::endl;
            }
        }

        // Insere "it" na posição atual 
        void insert(const int& it) override {
            curr->next = new Link(it, curr->next);
            if (tail == curr) tail = curr->next; // Nova "cauda"
            cnt++;
        }

        // Insere "it" ao final da lista
        void append(const int& it) override {
            tail = tail->next = new Link(it, nullptr);
            cnt++;
        }

        // Remove e retorna elemento atual
        int remove() override {
            assert(curr->next == nullptr, "Elemento inexistente.");
            int it = curr->next->element;        // Guarda o valor
            Link* ltemp = curr->next;            // Guarda o nódulo
            if (tail == curr->next) tail = curr; // Reseta a "cauda"
            curr->next = curr->next->next;       // Remove da lista
            delete ltemp;                        // Libera o espaço de memória previamente ocupado
            cnt--;                               // Decrementa o tamanho da lista
            
            return it;
        }

        void moveToStart() override { // Move o cursor para o início da lista
            curr = head;
        }

        void moveToEnd() override {   // Move o cursor para o fim da lista
            curr = tail;
        }

        // Move o cursor um passo atrás, sem mudanças caso já esteja no início
        void prev() override {
            if (curr == head) return;        // Elemento anterior indisponível
            Link* temp = head;
            // Percorre a lista até achar o elemento anterior
            while (temp->next != curr) temp = temp->next;
            curr = temp;
        }

        // Move o cursor um passo a frente, sem mudanças caso já esteja no final
        void next() override {
            if (curr != tail) curr = curr->next;
        }

        // Retorna o tamanho
        int length() const override {
            return cnt;
        }

        // Retorna a posição do elemento atual
        int currPos() const override {
            Link* temp = head;
            int i;
            for (i = 0; curr != temp; i++)
                temp = temp->next;
            
            return i;
        }

        // Move para posição "pos"
        void moveToPos(int pos) override {
            assert(!((pos >= 0) && (pos <= cnt)), "Posição fora de alcance.");
            curr = head;
            for (int i = 0; i < pos; i++) curr = curr->next;
        }

        // Retorna o elemento atual
        const int& getValue() const override {
            assert(curr->next == nullptr, "Sem valor.");
            return curr->next->element;
        }
};

int main() {

    return 0;
}