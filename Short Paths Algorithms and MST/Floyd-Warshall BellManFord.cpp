#include <iostream>
#define UNVISITED 0
#define VISITED 1
#define INFINITY 100000
using namespace std;
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

void Floyd(Graph *G,int D[5][5]){
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

int main() {
    Graph *grafo = new Graph(5);
    int D[5];
    int E[5][5];
    grafo->SetEdge(0,1,-1);
    grafo->SetEdge(0,2,4);
    grafo->SetEdge(1,2,3);
    grafo->SetEdge(3,1,1);
    grafo->SetEdge(1,3,2);
    grafo->SetEdge(3,2,-5);
    grafo->SetEdge(1,4,2);
    grafo->SetEdge(4,3,-3);
    Floyd(grafo,E);
    for(int i = 0; i < 5;i++){
        cout << "BellManFord for Vertex " << i << ":" << endl;
        BellManFord(grafo,i,D);
        for(int j = 0; j < 5;j++) cout << D[j] << " ";
    cout << endl;
    }
    cout << "Floyd: " << endl;
    for(int i = 0;i < 5;i++){
        for(int j = 0;j < 5;j++) cout << E[i][j] << " ";
    cout << endl;
    }



    
    

   return 0;
}