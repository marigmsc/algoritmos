#include <iostream>
using namespace std;
 
template <typename E>
void swap(E* arr, int pos, int j) {
    E temp = arr[j];
    arr[j] = arr[pos];
    arr[pos] = temp;
}
 
template <typename E>
class Heap {
    private:
        E* heap;         // Ponteiro para o vetor heap
        int maxsize;     // Tamanho máximo da heap
        int n;           // Número de elementos atualmente na heap
 
        void siftdown(int pos) {
            while (!isLeaf(pos)) {
                int j = leftchild(pos);
                int rc = rightchild(pos);
                if ((rc < n) && heap[rc] > heap[j])
                    j = rc;
                if (heap[pos] > heap[j]) return;
 
                swap<E>(heap, pos, j);
                pos = j;
            }
        }
 
        
    public:
 
        Heap(E* h, int num, int max) {
            heap = h;
            n = num;
            maxsize = max;
            buildHeap();
        }
 
        int size() const {
            return n;
        }
 
        bool isLeaf(int pos) const {
            return (pos >= n/2) && (pos < n);
        }
 
        int leftchild(int pos) const {
            return 2 * pos + 1;
        }
 
        int rightchild(int pos) const {
            return 2 * pos + 2;
        }
 
        int parent(int pos) const {
            return (pos - 1) / 2;
        }
 
        void buildHeap() {
            for (int i = n / 2 - 1; i >= 0; i--) siftdown(i);
        }
 
        void insert(const E& it) {
            int curr = n++;
            heap[curr] = it;
 
            while ((curr != 0) && heap[curr] > heap[parent(curr)]) {
                swap<E>(heap, curr, parent(curr));
                curr = parent(curr);
            }
        }
 
        E removefirst() {
            swap(heap, 0, --n);
            if (n != 0) siftdown(0);
            return heap[n];
        }
        E topValue(){
            return heap[0];
        }
 
        E remove(int pos) {
            if (pos == (n - 1)) n--;
            else {
                swap(heap, pos, --n);
                while ((pos != 0) && heap[pos] > heap[parent(pos)]) {
                    swap(heap, pos, parent(pos));
                    pos = parent(pos);
                }
 
                if (n != 0) siftdown(pos);
            }
            
            return heap[n];
        }
 
        
};
 
int main() {

 
    return 0;
}