#include <iostream>
#define UNVISITED 0
#define VISITED 1
#define INFINITY 100000
using namespace std;
class DijkElem{
    public:
    int vertex, distance;
    DijkElem() {vertex = -1; distance = -1;}
    DijkElem(int v, int d){vertex = v; distance = d;}
};
class ParPtrTree{
    private:
    int* array;
    int size;
    public:
    ParPtrTree(){size = 0;}
    ParPtrTree(int s){
        size = s;
        array = new int[s];
    }
    ~ParPtrTree(){
        delete array;
    }
    int find (int curr) const{ 
        if(array[curr] == 0) return curr;
        array[curr] = find(array[curr]);
        return array[curr];
        }
    void UNION(int a, int b){
        int root1 = find(a);
        int root2 = find(b);
        if(root1 != root2) array[root2] = root1;

    }
    bool differ(int a,int b){
        if(find(a) != find(b)) return true;
        else return false;
    }
};
class KruskElem{
    public:
    int from,to,distance;
    KruskElem(){from = -1; to = -1; distance = -1;}
    KruskElem(int f,int t,int d){
        from = f; to = t; distance = d;
    }
};
template <typename E>
void swap(E *arr, int pos, int j) {
    E temp = arr[j];
    arr[j] = arr[pos];
    arr[pos] = temp;
}
template <typename E>
class Heap {
    private:
        E* heap;         
        int maxtam;     
        int tam;           
 
        void siftdown(int pos) {
            while (!isLeaf(pos)) {
                int j = leftchild(pos);
                int rc = rightchild(pos);
                if ((rc < tam) && heap[rc].distance < heap[j].distance)
                    j = rc;
                if (heap[pos].distance < heap[j].distance) return;
 
                swap<E>(heap, pos, j);
                pos = j;
            }
        }
 
        
    public:
 
        Heap<E>(E* h, int num, int max) {
            heap = h;
            tam = num;
            maxtam = max;
            buildHeap();
        }
        inline int length() const {return tam;}
        inline bool isLeaf(int pos) const{ return (pos >= tam/2) && (pos < tam);}
        inline int leftchild(int pos) const { return 2 * pos + 1; }
        inline int rightchild(int pos) const { return 2 * pos + 2;}
        inline int parent(int pos) const {return (pos - 1) / 2; }
        void buildHeap() {
            for (int i = tam / 2 - 1; i >= 0; i--) siftdown(i);
        }
 
        void insert(E it) {
            int curr = tam++;
            heap[curr] = it;
 
            while ((curr != 0) && heap[curr].distance < heap[parent(curr)].distance) {
                swap<E>(heap, curr, parent(curr));
                curr = parent(curr);
            }
        }
 
        E removefirst() {
            swap<E>(heap, 0, --tam);
            if (tam != 0) siftdown(0);
            return heap[tam];
        }
        E topValue(){
            return heap[0];
        }
        void clear() {delete heap;}
        E remove(int pos) {
            if (pos == (tam - 1)) tam--;
            else {
                swap<E>(heap, pos, --tam);
                while ((pos != 0) && heap[pos].distance < heap[parent(pos)].distance) {
                    swap<E>(heap, pos, parent(pos));
                    pos = parent(pos);
                }
 
                if (tam != 0) siftdown(pos);
            }
            
            return heap[tam];
        }
 
        
};

class Graph{
    public:
    int **matrix; // Matriz de adjacência
    int numArestas; // Número de arestas
    int numVertex; // Número de vértices
    int *mark; // Vetor que mostra se os vértices foram ou não visitados na travessia
    bool *inStack;
    public:
    Graph(const int& numVertices){
        numVertex = numVertices;
        inStack = new bool[numVertices];
        mark = new int[numVertices];
        matrix = new int*[numVertices];
        for(int i = 0;i < numVertices;i++) matrix[i] = new int[numVertices];
        for(int c = 0; c < numVertices;c++) mark[c] = UNVISITED;
        for(int c = 0; c < numVertices;c++) inStack[c] = false;
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
        void DFS(int v) {
        // previsit
        inStack[v] = true;
        SetMark(v, VISITED);
        for (int w = first(v); w < numOfVertex(); w = next(v, w)) 
            if (GetMark(w) == UNVISITED)
                DFS (w);
        // postvisit
        
    } 
    void graphTraverseDFS() {
        int v;
        for (v = 0; v < numOfVertex(); v++)
            SetMark(v, UNVISITED);
        for (v = 0; v < numOfVertex(); v++)
            if (GetMark(v) == UNVISITED)
                DFS(v);
    }
 
};
void Kruskel(Graph *G){
    ParPtrTree *A = new ParPtrTree(G->numOfVertex()); //Vetor de classes de equivalência
    KruskElem HeapArray[G->numOfArestas()];
    int edgecnt = 0;
    for(int i = 0; i < G->numOfVertex();i++){
        for(int w = G->first(i);w < G->numOfVertex();w = G->next(i,w)){ //Organizar as arestas da menor a maior na heap
            HeapArray[edgecnt].distance = G->weight(i,w);
            HeapArray[edgecnt].from = i;
            HeapArray[edgecnt].to = w;
            edgecnt++;
        }
    }
    Heap<KruskElem> H (HeapArray,edgecnt,edgecnt);
    int numMST = G->numOfVertex();
    while(numMST > 1){
        KruskElem temp;
        temp = H.removefirst();
        int v = temp.from;
        int u = temp.to;
        int weight = temp.distance;
        if(A->differ(v,u)){
            A->UNION(v,u);
            cout << v << " - " << u << "Distance: " << weight << endl;
            numMST--;
        }
    }
}
int minVertex(Graph* G, int* D) { // Acha o vértice de menor distância
    int i, v = -1;
    // Inicializa v para um vértice não visitado

    for (i = 0; i < G->numOfVertex(); i++)
        if (G->GetMark(i) == UNVISITED) {
            v = i;
            break;
        }

    for (i++; i < G->numOfVertex(); i++) // Achar o menor valor de D
        if ((G->GetMark(i) == UNVISITED) && (D[i] < D[v])) //Acha o vertice de menor distancia não visitado
            v = i;
        
    return v; 
}


void DijkstrawithoutHeap(Graph* G, int* D,int s) {
    int i, v, w;
    D[s] = 0;
    for (i = 0; i < G->numOfVertex(); i++) {       // Processa os vértices
        v = minVertex(G, D); 
        if (D[v] == INFINITY) return;    // Vértices inalcançáveis
        G->SetMark(v, VISITED);
        
        for (w = G->first(v); w < G->numOfVertex(); w = G->next(v, w))
            if (D[w] > (D[v] + G->weight(v, w)))
                D[w] = D[v] + G->weight(v, w);
    }
}
void Prim(Graph *G,int *D,int s){
    int V[G->numOfVertex()]; 
    int v,w;
    int mincost = 0;
    DijkElem temp;
    D[s] = 0;
    DijkElem HeapArray[G->numOfArestas()];
    temp.distance = 0;
    temp.vertex = s;
    HeapArray[0] = temp;
    Heap<DijkElem> H(HeapArray,1,G->numOfArestas());
    for(int i = 0; i < G->numOfVertex();i++){
        do{
            if(H.length() == 0) return;
            temp = H.removefirst();
            v = temp.vertex;
        }while(G->GetMark(v) == VISITED);
        G->SetMark(v,VISITED);
        if(v != s){
            int k = V[v]; //guarda o vertice previamente visitado mais proximo de v
            cout << "Edge " << k << " - " << v << endl;
            cout << "Weight: " << G->weight(k,v) << endl;
            mincost += G->weight(k,v);
        }
        if(D[v] == INFINITY) return;
        for(w = G->first(v); w < G->numOfVertex();w = G->next(v,w)){
            if(D[w] < G->weight(v,w)){
                D[w] = G->weight(v,w);
                V[w] = v; // guarda da onde o vertice w veio, ou seja onde ele tava conectado
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);
            }
        }
    }
    cout << mincost << endl;
}
void Dijkstra(Graph *G, int *D, int s){ //better on sparse graphs
    int v,w;
    DijkElem temp;
    DijkElem HeapArray[G->numOfArestas()];
    temp.distance = 0;
    D[s] = 0;
    temp.vertex = s;
    HeapArray[0] = temp;
    Heap<DijkElem> H(HeapArray,1,G->numOfArestas()); //Heap min para guardar o vértice de menor distância e a sua distância
    for(int i = 0; i < G->numOfVertex();i++){
        do{
            if(H.length() == 0) return;
            temp = H.removefirst(); //Pega o vértice de menor distância
            v = temp.vertex; // minVertex()
        }while(G->GetMark(v) == VISITED); //Roda até achar um vértice não visitado
        G->SetMark(v,VISITED);
        if(D[v] == INFINITY)return;
        for(w = G->first(v);w < G->numOfVertex();w = G->next(v,w)){ //Relaxation
            if(D[w] > (D[v] + G->weight(v,w))){
                D[w] = D[v] + G->weight(v,w);
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);
            }
        }
    }
}
void BellManFord(Graph *G,int s,int *D){
    for(int i = 0; i < G->numOfVertex();i++) D[i] = INFINITY;
    D[s] = 0;
    for(int k = 0; k < G->numOfVertex() - 1;k++){
        for(int i = 0;i < G->numOfVertex();i++){
            int j = G->first(i);
            while(j < G->numOfVertex()){
                if(D[j] > D[i] + G->weight(i,j)) D[j] = D[i] + G->weight(i,j);
                j = G->next(i,j);
            }
        }
    }
    for(int k = 0; k < G->numOfVertex();k++){
        int j = G->first(k);
        while(j < G->numOfVertex()){
            if(D[j] > D[k] + G->weight(k,j)) cout << "Negative cicle" << endl;
            j = G->next(k,j);
        }
    }
}

void Floyd(Graph *G,int D[4][4]){
    for(int i = 0; i < G->numOfVertex();i++){
        for(int j = 0; j < G->numOfVertex();j++){
            if(i == j) D[i][j] = 0; //se os vertices forem iguais
            else if(G->weight(i,j) != 0) D[i][j] = G->weight(i,j); //atualiza inicialmente a matriz com todos os pesos
            else D[i][j] = INFINITY; // se o peso for igual a zero ou seja não tem aresta disponivel
        }
    }
    for(int k = 0;k < G->numOfVertex();k++){
        for(int i = 0;i < G->numOfVertex();i++){
            for(int j = 0;j < G->numOfVertex();j++){
                if(D[i][k] != INFINITY && D[k][j] != INFINITY && D[i][j] > D[i][k] + D[k][j]){
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}
int main(){
    Graph *grafo = new Graph(4);
    int D[4];
    int K[4];
    int E[4][4];
    grafo->SetEdge(0,1,3);
    grafo->SetEdge(0,2,4);
    grafo->SetEdge(1,2,2);
    grafo->SetEdge(1,3,1);
    grafo->SetEdge(2,3,8);
    Floyd(grafo,E);
    for(int i = 0; i < 4;i++){
        cout << "BellManFord for Vertex " << i << ":" << endl;
        BellManFord(grafo,i,D);
        for(int j = 0; j < 4;j++) cout << D[j] << " ";
    cout << endl;
    }
    cout << "Floyd: " << endl;
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++) cout << E[i][j] << " ";
    cout << endl;
    }
    Dijkstra(grafo,K,0);
    cout << "Dijkstra: " << endl;
     for(int j = 0; j < 4;j++) cout << K[j] << " ";

    return 0;
}