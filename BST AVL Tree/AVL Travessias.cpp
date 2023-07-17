#include <iostream>
#include <string>
#include <vector>
using namespace std;
int max(int a ,int b){
        return a > b ? a : b;
}
template <typename E>
class BSTNode{
    public:
    E data;
    int height;
    BSTNode* leftnode; // filho esquerdo
    BSTNode* rightnode;
     // filho direito
    BSTNode(E element){
        //Inicializando um nó na árvore
        data = element;
        leftnode = rightnode = nullptr;

    }
    BSTNode(BSTNode* ptr = nullptr){
        leftnode = rightnode = ptr;
    }
};
template <typename E>
class BST {

//Classe Abstrata que deriva da classe de dicionario
    public:
        BSTNode<E>* root;    //raiz de árvore
        int nodecount;    //número de nós da árvore   
        BST() {  //Construtor que inicializa a árvore                    
            root = nullptr;
            nodecount = 0;
        }

    public:

        ~BST() { clearhelp(root); } 
        int altura(BSTNode<E>* node){
            if(node == nullptr) return -1;
            else return node->height;
        }
        int getBalance(BSTNode<E>* node){
            if(node == nullptr) return 0;
            else return (altura(node->leftnode) - altura(node->rightnode));
        }
        bool find(int it)  {
                    return findhelp(root, it);
        }
        bool findhelp(BSTNode<E>* rt, int k){
            if(rt == nullptr) return false;
            else{
            if(rt->data > k) return findhelp(rt->leftnode,k);
            else if(rt->data == k) return true;
            else return findhelp(rt->rightnode,k);
            }
        }

        E remove(const E& k) {
            E temp = findhelp(root, k); //Vejo se esse nó existe. Se for diferente de null, existe um elemento associado a chave   
            if (temp != NULL) {
                root = removehelp(root, k); 
                //Atualizando sempre na raiz tanto no insert como no remove para os casos em que queira se mexer na raiz da árvore
                nodecount--; //Decrementa a quantidade de nós
            }
            return temp;
        }
        BSTNode< E>* deletemin(BSTNode< E>* rt) {
            if (rt->leftnode == nullptr)  
                return rt->rightnode;
            else {                     
                rt->leftnode = deletemin(rt->leftnode);
                return rt;
            }
        }
        BSTNode< E>* getmin(BSTNode< E>* rt){
                if (rt->leftnode == NULL) return rt;
                //Pega o menor elemento do filho do nó que quer ser removido para fazer a troca
                else return getmin(rt->leftnode);
        }
        BSTNode< E>* removehelp(BSTNode< E>* rt, const E& k){
            if (rt == NULL) return NULL; 
            else if (k < rt->data) rt->leftnode = removehelp(rt->leftnode, k);
            else if (k > rt->data) rt->rightnode = removehelp(rt->rightnode, k);
            else { 
                BSTNode< E>* temp = rt;
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
                    BSTNode< E>* temp = getmin(rt->rightnode); 
                    //O rt será uma cópia do temp
                    rt->data = temp->data;
                    rt->rightnode = deletemin(rt->rightnode);
                    delete temp;
                }
                }
                return rt;
        }
        }
        void insert (E it) {
            //Chaves repetidas sempre na subarvore direita
            root = inserthelp(root, it);
            nodecount++;
            
        }
        BSTNode<E>* rightRotate(BSTNode<E>* node){
            //l = left; lr = leftright; rt = node
            BSTNode<E>* left = node->leftnode;
            BSTNode<E>* leftright = left->rightnode;
            left->rightnode = node;
            node->leftnode = leftright;
            node->height = max(altura(node->leftnode),altura(node->rightnode)) + 1;
            left->height = max(altura(left->leftnode),altura(left->rightnode)) + 1;
            return left;
        }
        BSTNode<E>* leftRotate(BSTNode<E>* node){
            //r = right; rl = rightleft; rt = node
            BSTNode<E>* right = node->rightnode;
            BSTNode<E>* rightleft = right->leftnode;
            right->leftnode = node;
            node->rightnode = rightleft;
            node->height = max(altura(node->leftnode),altura(node->rightnode)) + 1;
            right->height = max(altura(right->leftnode),altura(right->rightnode)) + 1;
            return right;
        }
        BSTNode<E>* inserthelp(BSTNode<E>* root,E it) {
                if (root == nullptr) 
                    return new BSTNode<E> (it); //Se não tiver um nó, cria-se uma
                if (it < root->data)
                    root->leftnode = inserthelp(root->leftnode, it); //Chama recursivamente a funçao para o filho a esquerda até achar uma folha
                else root->rightnode = inserthelp(root->rightnode,it); //Chama recursivamente a funçao para o filho a direita até achar uma folha
                root->height =  1 + max(altura(root->leftnode),altura(root->rightnode));
                int balance = getBalance(root);
                if(balance < -1 && it >= root->rightnode->data) return leftRotate(root);
                if(balance > 1 && it < root->leftnode->data) return rightRotate(root);
                if(balance > 1 && it >= root->leftnode->data){
                    root->leftnode = leftRotate(root->leftnode);
                    return rightRotate(root);
                }
                if(balance < -1 && it < root->rightnode->data){
                root->rightnode = rightRotate(root->rightnode);
                return leftRotate(root);
                }
                return root;
            
        }
        int size() const {
            return nodecount;
        }
        void preorder(BSTNode<E>* rt){
            if (rt != NULL) {
                preorder(rt->leftnode);
                cout << rt->data << " ";
                preorder(rt->rightnode);
            }
            cout << endl;

        }
        void posorder(BSTNode<E>* rt){
            if (rt != NULL){
                posorder(rt->leftnode);
                posorder(rt->rightnode);
                cout << rt->data << " ";
            }
        }
        void inorder(BSTNode<E>* rt){
            if (rt != NULL) {
                inorder(rt->leftnode);
                cout << rt->data << " ";
                inorder(rt->rightnode);
            }

        }

};
int main(){ int index;
    long int aux;
    BST<long int>* tree = new BST<long int>;
    cin >> index;
    for(int i = 0; i < index;i++){
        cin >> aux;
        tree->insert(aux);
    }
    cout << "Pre order : ";
    tree->preorder(tree->root);
    cout << endl;
    cout << "In order  : ";
    tree->inorder(tree->root);
    cout << endl;
    cout << "Post order: ";
    tree->posorder(tree->root);
    return 0;
    }