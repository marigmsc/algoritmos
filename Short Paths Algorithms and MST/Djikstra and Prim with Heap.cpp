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
void swap(DijkElem *arr, int pos, int j) {
    DijkElem temp = arr[j];
    arr[j] = arr[pos];
    arr[pos] = temp;
}
class Heap {
    private:
        DijkElem* heap;         
        int maxtam;     
        int tam;           
 
        void siftdown(int pos) {
            while (!isLeaf(pos)) {
                int j = leftchild(pos);
                int rc = rightchild(pos);
                if ((rc < tam) && heap[rc].distance < heap[j].distance)
                    j = rc;
                if (heap[pos].distance < heap[j].distance) return;
 
                swap(heap, pos, j);
                pos = j;
            }
        }
 
        
    public:
 
        Heap(DijkElem* h, int num, int max) {
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
 
        void insert(DijkElem it) {
            int curr = tam++;
            heap[curr] = it;
 
            while ((curr != 0) && heap[curr].distance < heap[parent(curr)].distance) {
                swap(heap, curr, parent(curr));
                curr = parent(curr);
            }
        }
 
        DijkElem removefirst() {
            swap(heap, 0, --tam);
            if (tam != 0) siftdown(0);
            return heap[tam];
        }
        DijkElem topValue(){
            return heap[0];
        }
        void clear() {delete heap;}
        DijkElem remove(int pos) {
            if (pos == (tam - 1)) tam--;
            else {
                swap(heap, pos, --tam);
                while ((pos != 0) && heap[pos].distance < heap[parent(pos)].distance) {
                    swap(heap, pos, parent(pos));
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
 
};
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
    Heap H(HeapArray,1,G->numOfArestas());
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


void Dijkstra(Graph* G, int* D,int s) {
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
// void Dijkstra(Graph *G, int *D, int s){ //better on sparse graphs
//     int v,w;
//     DijkElem temp;
//     DijkElem HeapArray[G->numOfArestas()];
//     temp.distance = 0;
//     D[s] = 0;
//     temp.vertex = s;
//     HeapArray[0] = temp;
//     Heap H(HeapArray,1,G->numOfArestas()); //Heap min para guardar o vértice de menor distância e a sua distância
//     for(int i = 0; i < G->numOfVertex();i++){
//         do{
//             if(H.length() == 0) return;
//             temp = H.removefirst(); //Pega o vértice de menor distância
//             v = temp.vertex; // minVertex()
//         }while(G->GetMark(v) == VISITED); //Roda até achar um vértice não visitado
//         G->SetMark(v,VISITED);
//         if(D[v] == INFINITY)return;
//         for(w = G->first(v);w < G->numOfVertex();w = G->next(v,w)){ //Relaxation
//             if(D[w] > (D[v] + G->weight(v,w))){
//                 D[w] = D[v] + G->weight(v,w);
//                 temp.distance = D[w];
//                 temp.vertex = w;
//                 H.insert(temp);
//             }
//         }
//     }
// }

int main() {
    Graph *G = new Graph(4);
    int D[4];
    for(int i = 0;i < 4;i++) D[i] = INFINITY;
    G->SetEdge(0,2,4);
    G->SetEdge(0,1,2);
    G->SetEdge(1,3,3);
    G->SetEdge(1,2,1);
    G->SetEdge(2,3,5);
    Prim(G,D,0);
    for(int i = 0;i <4;i++) cout << D[i] << " ";


    
    

   return 0;
}