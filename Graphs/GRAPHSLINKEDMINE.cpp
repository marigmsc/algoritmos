#include <iostream>
using namespace std;
#define UNVISITED false
#define VISITED true
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
class Queue{
    public:
    Link<int> *rear;  //final
    Link<int> *front; //inicio
    int size;    //tamanho
    public:

    Queue(){
        front = rear = new Link<int>(nullptr);
        size = 0;
    }
    ~Queue(){
        Clear();

    }
    void Enqueue(int it){
        rear->next = new Link<int>(it,NULL); //cria um ponteiro depois do rear
        rear = rear->next; //avança um slot 
        size++; //aumenta o tamanho
    }
    int Dequeue(){
        if(size == 0) exit(1);
        else{ 
            Link<int> *temp = front->next; 
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
            Link<int> *temp = front->next;
            front->next = front->next->next;
            delete temp;
        }
        size = 0;
    }
    void Print(){
        Link<int> *temp = front->next;
        while(temp != nullptr){
            cout << temp->element << " ";
            temp = temp->next;
        }
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
    if (curr->next == NULL) abort(); //se a direita do cursor for nulo , não remove nada
    E it = curr->next->element; //declara uma variavel que é o elemento depois do cursor
    Link<E> *temp = curr->next; //criar um ponteiro auxilar que será igual ao ponteiro de depois do cursor
    if(tail == curr->next) tail = curr; //se o p
    curr->next = curr->next->next;
    cnt--;
    delete temp;
    return it;
}
E elementcursor(){
    if(curr->next == nullptr) abort();
    return curr->next->element;
}

};

class Edge{
    int vert;
    int weight;
    public:
    Edge(){vert = -1; weight = -1;}
    Edge(int v,int w){vert = v; weight = w;}
    inline int vertex(){return vert;}
    inline int wt(){return weight;}
};
class Graph{
    public:
    List<Edge>** vertex;
    int numVertex;
    int numEdge;
    bool *mark;
    public:
    Graph(int numVert){
        Init(numVert);
    }
    ~Graph(){
        delete mark;
        for(int i = 0; i < numVertex;i++) delete vertex[i];
        delete vertex;
    }
    void Init(int n){
        int i;
        numVertex = n;
        numEdge = 0;
        mark = new bool[n];
        vertex = (List<Edge>**) new List<Edge> * [numVertex];
        for(i = 0; i < numVertex;i++) mark[i] = UNVISITED;
        for(i = 0; i < numVertex;i++) vertex[i] = new List<Edge>;
    }
    inline int numOfVertex() const {return numVertex;} //Retorna o número de vértices
    inline int numOfArestas() const {return numEdge;} //Retorna o número de arestas
    inline int getMark(int v){return mark[v];}
    inline void setMark(int v,bool val){mark[v] = val;}
    int first(int v){
        if(vertex[v]->tamanho() == 0) return numVertex; //Se a lista daquele indice tiver vazia, retorna 0;
        vertex[v]->movetostart();
        Edge it = vertex[v]->elementcursor(); //Pega o primeiro elemento da lista que vai ser o primeiro vizinho do vertice
        return it.vertex(); //retorna o número de vertices desse elemento
    }
    int next(int v,int w){
        Edge it;
        if(isEdge(v,w)){
            if((vertex[v]->currposicion() + 1) < vertex[v]->tamanho()) {
                vertex[v]->next();
                it = vertex[v]->elementcursor();
                return it.vertex();
            }
        }
        return numVertex;

    }
    void setEdge(int i, int j, int weight){
    Edge currEdge(j,weight);
        if(isEdge(i,j)){
        vertex[i]->remove();
        vertex[i]->insert(currEdge);
        }
        else{
            numEdge++;
            for(vertex[i]->movetostart();vertex[i]->currposicion() < vertex[i]->tamanho();vertex[i]->next()){
                Edge temp = vertex[i]->elementcursor();
                if(temp.vertex() > j) break;
            }
            vertex[i]->insert(currEdge);
        }
    }
    void delEdge(int i,int j){
        if(isEdge(i,j)){
            vertex[i]->remove();
            numEdge--;
        }
    }
    bool isEdge(int i, int j){
        Edge it;
        for(vertex[i]->movetostart();vertex[i]->currposicion() < vertex[i]->tamanho();vertex[i]->next()){
            Edge temp = vertex[i]->elementcursor();
            if(temp.vertex() == j) return true;
        }
        return false;
    }
    int weight(int i, int j){
        Edge curr;
        if(isEdge(i,j)){
            curr = vertex[i]->elementcursor();
            return curr.wt();
        }
        else return 0;
    }
    void BFS(int start){
    int explored,explored_neighbour;
    Queue graph_queue; //Cria a fila
    graph_queue.Enqueue(start); // Coloca na fila o vértice que você escolheu para começar
    setMark(start,VISITED); // Marca ele como visitado
    while(graph_queue.Length() != 0){
        explored = graph_queue.Dequeue(); //Retira o primeiro elemento da fila 
        cout << explored + 1 << " ";
        for(explored_neighbour = first(explored);explored_neighbour < numVertex;explored_neighbour = next(explored,explored_neighbour)){
            if(getMark(explored_neighbour) == UNVISITED) {
                setMark(explored_neighbour,VISITED); //Se o vertice não for visitado ele irá adicionar todos a fila
                graph_queue.Enqueue(explored_neighbour);
            }
     } 
    //PostVisit     
    }
}
void DFS(int start){
        cout << start + 1 << " ";
        setMark(start,VISITED);
        for(int w = first(start);w < numVertex;w = next(start,w)){
           if(getMark(w) == UNVISITED) DFS(w);
        //cout << start << endl;
        }
}
void Graph_TraverseDFS(){
    int v;
    for(v = 0; v < numOfVertex();v++) setMark(v,UNVISITED);
    for(v = 0; v < numOfVertex();v++){
        if(getMark(v) == UNVISITED) DFS(v);
    }
}
void Graph_TraverseBFS(){
    int v;
    for(v = 0; v < numOfVertex();v++) setMark(v,UNVISITED);
    for(v = 0; v < numOfVertex();v++){
        if(getMark(v) == UNVISITED) BFS(v);
    }
}
};


int main() {
    int numbVertex,numChores;
    int before,next;
    cin >> numbVertex;
    cin >> numChores;
    Graph grafo = Graph(numbVertex);
    for(int i = 0; i < numChores;i++){
        cin >> before;
        cin >> next;
        grafo.setEdge(0,before - 1,next - 1);
    }
    cout << "BFS: " ;
    grafo.Graph_TraverseBFS();
    cout << endl;
    cout << "DFS: ";
    grafo.Graph_TraverseDFS();
    cout << endl;
    

    return 0;
}

