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
void Prim(Graph *G, int* D,int s){
    int V[G->numOfVertex()];
    int w,mincost = 0;
    D[s] = 0;
    for(int i = 0;i < G->numOfVertex();i++){
        int v = minVertex(G,D);
        G->SetMark(v,VISITED);
        if(v != s) {
            int k = V[v];
            cout << "Edge " << k << " - " << v << endl;
            cout << "Weight: " << G->weight(k,v) << endl;
            mincost += G->weight(k,v);
        }
        if(D[v] == INFINITY) return;
        for(w = G->first(v); w < G->numOfVertex();w = G->next(v,w)){
            if(D[w] > G->weight(v,w)){
                D[w] = G->weight(v,w);
                V[w] = v;
            }
        }
    }
    //int minCost = 0;
    
        cout << mincost << endl;

    
    
}