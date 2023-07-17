#include <iostream>
#define UNVISITED 0
#define VISITED 1
#define INFINITY 100000
using namespace std;
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

class Heap {
    private:
        KruskElem* heap;         
        int maxtam;     
        int tam;           
 
        void siftdown(int pos) {
            while (!isLeaf(pos)) {
                int j = leftchild(pos);
                int rc = rightchild(pos);
                if ((rc < tam) && heap[rc].distance < heap[j].distance)
                    j = rc;
                if (heap[pos].distance < heap[j].distance) return;
 
                swap<KruskElem>(heap, pos, j);
                pos = j;
            }
        }
 
        
    public:
 
        Heap(KruskElem* h, int num, int max) {
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
 
        void insert(KruskElem it) {
            int curr = tam++;
            heap[curr] = it;
 
            while ((curr != 0) && heap[curr].distance < heap[parent(curr)].distance) {
                swap<KruskElem>(heap, curr, parent(curr));
                curr = parent(curr);
            }
        }
 
        KruskElem removefirst() {
            swap<KruskElem>(heap, 0, --tam);
            if (tam != 0) siftdown(0);
            return heap[tam];
        }
        KruskElem topValue(){
            return heap[0];
        }
        void clear() {delete heap;}
        KruskElem remove(int pos) {
            if (pos == (tam - 1)) tam--;
            else {
                swap<KruskElem>(heap, pos, --tam);
                while ((pos != 0) && heap[pos].distance < heap[parent(pos)].distance) {
                    swap<KruskElem>(heap, pos, parent(pos));
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
    Heap H (HeapArray,edgecnt,edgecnt);
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

int main() {
    Graph *G = new Graph(4);
    G->SetEdge(0,2,4);
    G->SetEdge(0,1,2);
    G->SetEdge(1,3,3);
    G->SetEdge(1,2,1);
    G->SetEdge(2,3,5);
    cout << "Kruskel:" << endl;
    Kruskel(G);
   return 0;
}