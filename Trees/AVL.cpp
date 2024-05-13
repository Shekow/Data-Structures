#include <iostream>
using namespace std;

template<class T, class C = less<T>>
class AVL
{
    struct Node
    {
        T value;
        Node *leftChild, *rightChild;
        int bf, height;
        public:
            Node(T value): Node(value, NULL, NULL, 0, 1){}

            Node(T value, Node* leftChild, Node *rightChild, int bf, int height)
            : value(value), leftChild(leftChild), rightChild(leftChild), bf(bf), height(height){}
    };
    enum class ElementTD
    {
        Right, Value, Left
    };
    Node *root;
    C comp;
    int nodesCtr;
    int compare(T &firstValue, T &secondValue)
    {
        if (comp(firstValue, secondValue))
            return -1;
        if (comp(secondValue, firstValue))
            return 1;
        return 0;
    }
    bool contains(Node *node, T value)
    {
        if (node == NULL)
            return false;
        int com = compare(value, node->value);
        if (com == 0)
            return true;
        return (com > 0 ? contains(node->rightChild, value) : contains(node->leftChild, value));
    }
    Node *rightMost(Node *node)
    {
        while (node->rightChild != NULL)
            node = node->rightChild;
        return node;
    }
    Node *rotateRight(Node *node)
    {
        Node *other = node->leftChild;
        node->leftChild = other->rightChild;
        other->rightChild = node;
        update(node), update(other);
        return other;
    }
    Node *rotateLeft(Node *node)
    {
        Node *other = node->rightChild;
        node->rightChild = other->leftChild;
        other->leftChild = node;
        update(node), update(other);
        return other;
    }
    void update(Node *node)
    {
        if (node == NULL)
            return;
        int leftHeight = (node->leftChild == NULL ? 0 : node->leftChild->height);
        int rightHeight = (node->rightChild == NULL ? 0 : node->rightChild->height);
        node->height = max(leftHeight, rightHeight) + 1;
        node->bf = rightHeight - leftHeight;
    }
    Node *balance(Node *node)
    {
        if (node == NULL)
            return NULL;
        if (node->bf == -2)
        {
            if (node->leftChild->bf > 0)
                node->leftChild = rotateLeft(node->leftChild);
            node = rotateRight(node);
        }
        else if (node->bf == 2)
        {
            if (node->rightChild->bf < 0)
                node->rightChild = rotateRight(node->rightChild);
            node = rotateLeft(node);
        }
        return node;
    }
    Node *insert(Node *node, T value)
    {
        if (node == NULL)
            return new Node(value);
        if (compare(value, node->value) < 0)
            node->leftChild = insert(node->leftChild, value);
        else
            node->rightChild = insert(node->rightChild, value);
        update(node);
        node = balance(node);
        return node;
    }
    Node *remove(Node *node, T value)
    {
        int com = compare(value, node->value);
        if (com < 0)
            node->leftChild = remove(node->leftChild, value);
        else if (com > 0)
            node->rightChild = remove(node->rightChild, value);
        else
        {
            Node *tmp = node;
            if (node->leftChild == NULL)
            {
                node = node->rightChild;
                delete tmp;
            }
            else if (node->rightChild == NULL)
            {
                node = node->leftChild;
                delete tmp;
            }
            else
            {
                tmp = rightMost(node->leftChild);
                node->value = tmp->value;
                node->leftChild = remove(node->leftChild, tmp->value);
            }
        }
        update(node);
        node = balance(node);
        return node;
    }
    void displayElements(Node *node, ElementTD pattern[3])
    {
        if (node == NULL)
            return;
        for (int i{}; i < 3; i++)
        {
            switch (pattern[i])
            {
                case ElementTD::Left:
                    displayElements(node->leftChild, pattern);
                    break;
                case ElementTD::Right:
                    displayElements(node->rightChild, pattern);
                    break;
                default:
                    cout << node->value << " ";
            }
        }
    }
    void clear(Node *node)
    {
        if (node == NULL)
            return;
        clear(node->leftChild);
        clear(node->rightChild);
        delete node;
    }
    public:
    AVL(): root(NULL), nodesCtr(0){}
    void insert(T value)
    {
        if (!contains(root, value))
            root = insert(root, value), nodesCtr++;
    }
    void remove(T value)
    {
        if (contains(root, value))
            root = remove(root, value), nodesCtr--;
    }
    int size()
    {
        return nodesCtr;
    }
    bool isEmpty()
    {
        return size() == 0;
    }
    void displayInOrder()
    {
        ElementTD pat[] = {ElementTD::Left, ElementTD::Value, ElementTD::Right};
        displayElements(root, pat);
        cout << endl;
    }
    void displayInReverseOrder()
    {
        ElementTD pat[] = {ElementTD::Right, ElementTD::Value, ElementTD::Left};
        displayElements(root, pat);
        cout << endl;
    }
    void clear()
    {
        clear(root);
        root = NULL;
        nodesCtr = 0;
    }
    ~AVL()
    {
        clear();
    }
};