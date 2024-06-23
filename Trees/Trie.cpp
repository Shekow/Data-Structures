#include <iostream>
#include <string>
using namespace std;

template<size_t Alpha = 26, char Start = 'a'>
class Trie
{
    class Node
    {
        public:
        Node *children[Alpha];
        bool endWord;
        Node()
        {
            endWord = false;
            for (size_t i{}; i < Alpha; i++)
                children[i] = NULL;
        }
        bool hasChildren()
        {
            for (size_t i{}; i < Alpha; i++)
                if (children[i] != NULL)
                    return true;
            return false;
        }
        ~Node()
        {
            for (size_t i{}; i < Alpha; i++)
                if (children[i] != NULL)
                    delete children[i];
        }
    };
    Node* remove(Node *node, string &s, size_t index)
    {
        if (node == NULL)
            return NULL;
        if (index == s.size())
        {
            node->endWord = false;
            if (!node->hasChildren())
            {
                delete node;
                node = NULL;
            }
            return node;
        }
        size_t nextChild = s[index] - Start;
        node->children[nextChild] = remove(node->children[nextChild], s, index + 1);
        if (!node->hasChildren() and !node->endWord)
        {
            delete node;
            node = NULL;
        }
        return node;
    }
    Node *root;
    size_t nodeCount;

    public:
    Trie()
    {
        root = new Node();
        nodeCount = 0;
    }
    void insert(string s)
    {
        if (search(s))
            return;
        Node *node = root;
        for (char c: s)
        {
            if (node->children[c - Start] == NULL)
                node->children[c - Start] = new Node;
            node = node->children[c - Start];
        }
        node->endWord = true;
        nodeCount++;
    }
    bool search(string s)
    {
        Node *node = root;
        for (char c: s)
        {
            if (node->children[c - Start] == NULL)
                return false;
            node = node->children[c - Start];
        }
        return node->endWord;
    }
    void remove(string s)
    {
        if (!search(s))
            return;
        remove(root, s, 0);
        nodeCount--;
    }
    size_t size()
    {
        return nodeCount;
    }
    ~Trie()
    {
        delete root;
    }
};