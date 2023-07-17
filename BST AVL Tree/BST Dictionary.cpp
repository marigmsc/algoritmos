#include <iostream>
using namespace std;
template <typename Key, typename E>
class Dictionary {
    private:
        void operator = (const Dictionary&) {}
        Dictionary(const Dictionary&) {}
 
    public:
        Dictionary() {}          
        virtual ~Dictionary() {} 
        virtual void clear() = 0;
        virtual void insert(const Key& k, const E& e) = 0;
        virtual E remove(const Key& k) = 0;
        virtual E find(const Key& k) const = 0;
        virtual int size() const = 0;
};
template <typename Key, typename E>
class BSTNode{
    public:
    Key key; 
    E data;
    BSTNode* leftnode; // filho esquerdo
    BSTNode* rightnode; // filho direito
    BSTNode(Key k, E element){
        //Inicializando um nó na árvore
        key = k;
        data = element;
        leftnode = rightnode = new BSTNode(nullptr);

    }
    BSTNode(BSTNode* ptr = nullptr){
        leftnode = rightnode = ptr;
    }
};
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
//Classe Abstrata que deriva da classe de dicionario
    private:
        BSTNode<Key, E>* root;    //raiz de árvore
        int nodecount;    //número de nós da árvore
        public:      
        BST() {  //Construtor que inicializa a árvore                    
            root = nullptr;
            nodecount = 0;
        }

        ~BST() { clearhelp(root); } 

        void insert (const Key& k, const E& e) {
            //Chaves repetidas sempre na subarvore direita
            root = inserthelp(root, k, e);
            nodecount++;
        }
        BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
                if (root == nullptr) 
                    return new BSTNode<Key, E>(k, it); //Se não tiver um nó, cria-se uma
                if (k < root->key())
                    root->leftnode = inserthelp(root->leftnode, k, it); //Chama recursivamente a funçao para o filho a esquerda até achar uma folha
                else root->rightnode = inserthelp(root->rightnode, k, it); //Chama recursivamente a funçao para o filho a direita até achar uma folha
                return root;         
        }
        E removeAny() {
            if (root != nullptr) {
                E temp = root->data;
                root = removehelp(root, root->key);
                nodecount--;

                return temp;
            } else return NULL;
        }
        int size() const {
            return nodecount;
        }

        void print() const {
                    if (root == nullptr) cout << "Lista vazia." << endl;
                    else printhelp(root, 0);
        }
        E find(const Key& k) const {
                    return findhelp(root, k);
        }
        E findhelp(BSTNode<Key, E>* root, const Key& k) const { //funciona recursivamente
                    if (root == nullptr) return NULL;      
                    if (k < root->key)
                        return findhelp(root->left, k);  //realizará uma recursão para o lado esquerdo da árvore
                    else if (k > root->key)
                        return findhelp(root->right, k); //realizará uma recursão para o lado direito da árvore
                    else 
                        return root->data;      //Se a k = root->key retorna o elemento associado a chave   
                }
        E remove(const Key& k) {
            E temp = findhelp(root, k); //Vejo se esse nó existe. Se for diferente de null, existe um elemento associado a chave   
            if (temp != NULL) {
                root = removehelp(root, k); 
                //Atualizando sempre na raiz tanto no insert como no remove para os casos em que queira se mexer na raiz da árvore
                nodecount--; //Decrementa a quantidade de nós
            }
            return temp;
        }
        BSTNode<Key, E>* deletemin(BSTNode<Key, E>* rt) {
            if (rt->leftnode == nullptr)  
                return rt->rightnode;
            else {                     
                rt->leftnode = deletemin(rt->leftnode);
                return rt;
            }
        }
        BSTNode<Key, E>* getmin(BSTNode<Key, E>* rt){
                if (rt->leftnode == NULL) return rt;
                //Pega o menor elemento do filho do nó que quer ser removido para fazer a troca
                else return getmin(rt->leftnode);
        }
        BSTNode<Key, E>* removehelp(BSTNode<Key, E>* rt, const Key& k){
            if (rt == NULL) return NULL; 
            else if (k < rt->key) rt->leftnode = removehelp(rt->leftnode, k);
            else if (k > rt->key) rt->rightnode = removehelp(rt->rightnode, k);
            else { 
                BSTNode<Key, E>* temp = rt;
                //São realizados recursões até achar o nó que se deseja remover a qual procede a remoção no ultimo else
                if (rt->leftnode == nullptr) { 
                    rt = rt->rightnode; 
                    delete temp;
                }
                else if (rt->rightnode == nullptr) { 
                    rt = rt->leftnode; 
                    delete temp;
                }
                else { 
                    if(rt->leftnode == nullptr)
                        return rt->rightnode; //Se não existir um filho a esquerda é so fazer com que o nó anterior aponte para o filho da direita para remover determinado nó
                    else if(rt->rightnode == nullptr) return rt->leftnode;
                    else{
                    BSTNode<Key, E>* temp = getmin(rt->rightnode); 
                    //O rt será uma cópia do temp
                    rt->data = temp->data;
                    rt->key = temp->key;
                    rt->rightnode = deletemin(rt->rightnode);
                    delete temp;
                }
                }
                return rt;
        }

};
int main(){














    return 0;
}