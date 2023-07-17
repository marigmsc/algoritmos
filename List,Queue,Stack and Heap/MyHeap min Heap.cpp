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
                if ((rc < tam) && heap[rc] < heap[j])
                    j = rc;
                if (heap[pos] < heap[j]) return;
 
                swap<E>(heap, pos, j);
                pos = j;
            }
        }
 
        
    public:
 
        Heap(E* h, int num, int max) {
            heap = h;
            tam = num;
            maxtam = max;
            buildHeap();
        }
        inline int length() const {return tam;}
        inline bool isLeaf(int post) const{ return (pos >= tam/2) && (pos < tam);}
        inline int leftchild(int pos) const { return 2 * pos + 1; }
        inline int rightchild(int pos) const { return 2 * pos + 2;}
        inline int parent(int pos) const {return (pos - 1) / 2; }
        void buildHeap() {
            for (int i = tam / 2 - 1; i >= 0; i--) siftdown(i);
        }
 
        void insert(const E& it) {
            int curr = tam++;
            heap[curr] = it;
 
            while ((curr != 0) && heap[curr] < heap[parent(curr)]) {
                swap<E>(heap, curr, parent(curr));
                curr = parent(curr);
            }
        }
 
        E removefirst() {
            swap(heap, 0, --tam);
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
                swap(heap, pos, --tam);
                while ((pos != 0) && heap[pos] < heap[parent(pos)]) {
                    swap(heap, pos, parent(pos));
                    pos = parent(pos);
                }
 
                if (tam != 0) siftdown(pos);
            }
            
            return heap[tam];
        }
 
        
};