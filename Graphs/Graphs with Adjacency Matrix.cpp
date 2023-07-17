#include <iostream>
#include <stack>
#define UNVISITED 0
#define VISITED 1
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

    Queue(){
        front = rear = new Link(nullptr);
        size = 0;
    }
    ~Queue(){
        Clear();

    }
    void Enqueue(int it){
        rear->next = new Link(it,NULL); //cria um ponteiro depois do rear
        rear = rear->next; //avança um slot 
        size++; //aumenta o tamanho
    }
    int Dequeue(){
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

class Graph{
    public:
    int **matrix; // Matriz de adjacência
    int numArestas; // Número de arestas
    int numVertex; // Número de vértices
    int *mark; // Vetor que mostra se os vértices foram ou não visitados na travessia
    public:
    Graph(const int& numVertices){
        numVertex = numVertices;
        mark = new int[numVertices];
        matrix = new int*[numVertices];
        for(int i = 0;i < numVertices;i++) matrix[i] = new int[numVertices];
        for(int c = 0; c < numVertices;c++) mark[c] = UNVISITED;
        for(int i = 0; i < numVertices;i++){
            for(int j = 0; j  < numVertices;j++){
                matrix[i][j] = 0;
            }
        }
        numArestas = 0;
    }
    ~Graph(){
    }
    inline int numOfVertex() const {return numVertex;} //Retorna o número de vértices
    inline int numOfArestas() const {return numArestas;} //Retorna o número de arestas
    inline int isEdge (const int& i, const int& j) const {return matrix[i][j] != 0;} //Retorna se determinada aresta existe
    inline int weight  (const int& v1,const int& v2) const {return matrix[v1][v2];} //Retorna o valor que determinado vértice tem
    inline int GetMark  (const int& i) const{return mark[i];} //Retorna se é visitado ou não o vértice
    inline void SetMark (const int& v, const int& val){ mark[v] = val;} //Atribui um valor ao vetor de visitação
    int first(const int& it){ //Retorna o primeiro vizinho do vértice it;
        for(int i = 0; i < numVertex;i++){
            if(matrix[it][i] != 0) return i; 
        }
        return numVertex; // retorna número de vértices se não tiver nenhum
    }
    int next(const int& it, const int& ito){ //Retorna o vizinho de it depois de ito
        for(int i = ito + 1;i < numVertex;i++){
            if(matrix[it][i] != 0) return i;
        }
        return numVertex; // retorna número de vértices se não houver vizinho
    }
    void SetEdge(const int& v1, const int& v2, const int& wt){ //Adiciona uma aresta ao grafo
        if(matrix[v1][v2] == 0) { //Verifica se tem algo naquela aresta
            numArestas++; //Aumenta o número de arestas
            matrix[v1][v2] = wt; //Adiciona o elemento
        }
    }
    void DelEdge(const int& v1, const int& v2 ){
        if(matrix[v1][v2] != 0){ //Verifica se tem algo na aresta
            numArestas--;
            matrix[v1][v2] = 0; //Deleta
        }
    }
    void printMatrix(){
        for(int i = 0;i < numVertex;i++){
            for(int j = 0; j < numVertex;j++) cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
        void BFS(int start) {
        int explored,explored_neighbour;
        Queue graph_queue; //Cria a fila
        graph_queue.Enqueue(start); // Coloca na fila o vértice que você escolheu para começar
        setMark(start,VISITED); // Marca ele como visitado
        while(graph_queue.Length() != 0){
            explored = graph_queue.Dequeue(); //Retira o primeiro elemento da fila 
            cout << explored + 1 << " ";
            for(explored_neighbour = first(explored);explored_neighbour < numOfVertex();explored_neighbour = next(explored,explored_neighbour)){
                if(getMark(explored_neighbour) == UNVISITED) {
                    setMark(explored_neighbour,VISITED); //Se o vertice não for visitado ele irá adicionar todos a fila
                    graph_queue.Enqueue(explored_neighbour);
                }
            } 
        }
    }
    void graphTraverseBFS() {
        int v;
        for (v = 0; v < numOfVertex(); v++)
            setMark(v, UNVISITED);
        for (v = 0; v < numOfVertex(); v++)
            if (getMark(v) == UNVISITED)
                BFS(v);
    }
    void DFS(int v) {
        // previsit
        cout << v + 1 << " ";
        setMark(v, VISITED);
        for (int w = first(v); w < numOfVertex(); w = next(v, w)) 
            if (getMark(w) == UNVISITED)
                DFS (w);
        // postvisit
        
    } 
    void graphTraverseDFS() {
        int v;
        for (v = 0; v < numOfVertex(); v++)
            setMark(v, UNVISITED);
        for (v = 0; v < numOfVertex(); v++)
            if (getMark(v) == UNVISITED)
                DFS(v);
    }
    void tophelp(int v){
        setMark(v,VISITED);
        for(int w = first(v); w < numOfVertex();w = next(v,w)){
            if(getMark(w) == UNVISITED) tophelp(w);                
        }
        cout << v + 1 << " "; 
    }
    void topsort(){
        int i;
        for(i = 0; i < numOfVertex();i++) setMark(i,UNVISITED);
        for(i = 0;i < numOfVertex();i++){
            if(getMark(i) == UNVISITED) tophelp(i);
        }   
    }
};

int main() {
    Graph grafo = Graph(6);

    grafo.SetEdge(0, 1, 1);
    grafo.SetEdge(0, 2, 1);
    grafo.SetEdge(0, 3, 1);
    grafo.SetEdge(3, 5, 1);
    grafo.SetEdge(3, 4, 1);
    //grafo.printMatrix();
    grafo.Graph_Traverse();

    return 0;
}

