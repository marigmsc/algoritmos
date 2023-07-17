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