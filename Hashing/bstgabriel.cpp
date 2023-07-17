#include <iostream>
 
template <typename Key, typename E>
class Dictionary {
    private:
        void operator = (const Dictionary&) {}
        Dictionary(const Dictionary&) {}
 
    public:
        Dictionary() {}          // Construtor padrão
        virtual ~Dictionary() {} // Destrutor base
 
        // Reinicializa o dicionário
        virtual void clear() = 0;
 
        // Insere um registro
        // k: A chave do registro a ser inserido.
        // e: O registro a ser inserido.
        virtual void insert(const Key& k, const E& e) = 0;
 
        // Remove e retorna um registro
        // k: A chave do registro a ser removido.
        // Return: O registro encontrado. Se múltiplos
        // registros com a chave "k" forem encontrados,
        // remove um registro arbitrário. Retorna NULL
        // caso nenhum registro com a chave "k" exista.
        virtual E remove(const Key& k) = 0;
 
        // Remove e retorna um registro arbitrário do dicionário.
        // Return: O registro removido, ou NULL caso nenhum exista.
        virtual E removeAny() = 0;
 
        // Return: Um registro correspondente a "k" (NULL se nenhum existe).
        // Se múltiplos registros coincidirem, retorna um arbitrário.
        // k: A chave do registro a ser procurado.
        virtual E find(const Key& k) const = 0;
 
        // Retorna o número de registros no dicionário
        virtual int size() const = 0;
};
 
template <typename E>
class BinNode {
    public:
        virtual ~BinNode() {}
 
        virtual E& element() = 0;
 
        virtual void setElement(const E&) = 0;
 
        virtual BinNode* left() const = 0;
 
        virtual void setLeft(BinNode*) = 0;
 
        virtual BinNode* right() const = 0;
 
        virtual void setRight(BinNode*) = 0;
 
        virtual bool isLeaf() = 0;
};
 
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
    private:
        Key k;
        E it;
        BSTNode* lc;
        BSTNode* rc;
    
    public:
 
        BSTNode() { lc = rc = nullptr; }
        BSTNode(Key K, E e, BSTNode* l = nullptr, BSTNode* r = nullptr) {
            k = K;
            it = e;
            lc = l;
            rc = r;
        }
 
        ~BSTNode() {}
 
        E& element() { return it; }
        void setElement(const E& e) { it = e; }
        Key& key() { return k; }
        void setKey(const Key& K) { k = K; }
 
        inline BSTNode* left() const { return lc; }
        void setLeft(BinNode<E>* b) { lc = (BSTNode*) b; }
        inline BSTNode* right() const { return rc; }
        void setRight(BinNode<E>* b) { rc = (BSTNode*) b; }
 
        bool isLeaf() { return (lc == nullptr) && (rc == nullptr ); }
};
 
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
    private:
        BSTNode<Key, E>* root;
        int nodecount;
        void clearhelp(BSTNode<Key, E>* root) {
            if (root = nullptr) return;
            clearhelp(root->left());
            clearhelp(root->right());
            delete root;
        }
 
        BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
            if (root == nullptr)
                return new BSTNode<Key, E>(k, it, nullptr, nullptr);
            if (k < root->key())
                root->setLeft(inserthelp(root->left(), k, it));
            else root->setRight(inserthelp(root->right(), k, it));
            return root;
        }
 
        BSTNode<Key, E>* deletemin(BSTNode<Key, E>* rt) {
            if (rt->left() == nullptr)
                return rt->right();
            else {
                rt->setLeft(deletemin(rt->left()));
                return rt;
            }
        }
 
        BSTNode<Key, E>* getmin(BSTNode<Key, E>* rt) {
            if (rt->left() == nullptr)
                return rt;
            else
                return getmin(rt->left());
        }
 
        BSTNode<Key, E>* removehelp(BSTNode<Key, E>* rt, const Key& k) {
            if (rt == nullptr) return nullptr;
            else if (k < rt->key())
                rt->setLeft(removehelp(rt->left(), k));
            else if (k > rt->key())
                rt->setRight(removehelp(rt->right(), k));
            else {
                BSTNode<Key, E>* temp = rt;
                if (rt->left() == nullptr) {
                    rt = rt->right();
                    delete temp;
                } else if (rt->right() == nullptr) {
                    rt = rt->left();
                    delete temp;
                } else {
                    BSTNode<Key, E>* temp = getmin(rt->right());
                    rt->setElement(temp->element());
                    rt->setKey(temp->key());
                    rt->setRight(deletemin(rt->right()));
                    delete temp;
                }
            }
 
            return rt;
        }
 
        E findhelp(BSTNode<Key, E>* root, const Key& k) const {
            if (root == nullptr) return NULL;
            if (k < root->key())
                return findhelp(root->left(), k);
            else if (k > root->key())
                return findhelp(root->right(), k);
            else 
                return root->element();
        }
 
        void printhelp(BSTNode<Key, E>* root, int level) const {
            if (root == nullptr) return;
            printhelp(root->left(), level + 1);
            for (int i = 0; i < level; i++)
                std::cout << " ";
            std::cout << root->key() << std::endl;
            printhelp(root->right(), level + 1);
        }
 
    public:
 
        BST() {
            root = nullptr;
            nodecount = 0;
        }
 
        ~BST() { clearhelp(root); }
 
        void clear() {
            clearhelp(root);
            root = nullptr;
            nodecount = 0;
        }
 
        void insert (const Key& k, const E& e) {
            root = inserthelp(root, k, e);
            nodecount++;
        }
 
        E remove(const Key& k) {
            E temp = findhelp(root, k);
            if (temp != NULL) {
                root = removehelp(root, k);
                nodecount--;
            }
 
            return temp;
        }
 
        E removeAny() {
            if (root != nullptr) {
                E temp = root->element();
                root = removehelp(root, root->key());
                nodecount--;
 
                return temp;
            } else return NULL;
        }
 
        E find(const Key& k) const {
            return findhelp(root, k);
        }
 
        int size() const {
            return nodecount;
        }
 
        void print() const {
            if (root == nullptr) std::cout << "Lista vazia." << std::endl;
            else printhelp(root, 0);
        }
};
 
 
template <typename E>
void preorder(BinNode<E>* root) {
    if (root == nullptr) return;   // Subárvore vazia
    visit(root);                   // Executar ação desejada
    preorder(root->left());
    preorder(root->right());
}
 
template <typename E>
int count(BinNode<E>* root) {
    if (root == nullptr) return 0;   // Nada para contar
    return 1 + count(root->left()) + count(root->right());
}
 
int main() {
 
    BST<int, int>* bst = new BST<int, int>;
 
    bst->insert(2, 9);
    bst->insert(3, 8);
    bst->remove(3);
    bst->insert(5, 3);
    bst->print();
 
    return 0;
}