#include <iostream>
using namespace std;

template<class T, class C = greater<T>>
class Heap
{
    public:
    T *data;
    int curSize, capacity;
    class EmptyHeap: public out_of_range 
    {
        public:
        EmptyHeap(const char *msg): out_of_range(msg){}
    };
    static int inBounds(int index, int n)
    {
        return index >= 0 && index < n; 
    }
    static int firstChildIndex(int index)
    {
        return index * 2 + 1;
    }
    static int secondChildIndex(int index)
    {
        return index * 2 + 2;
    }
    static int parentIndex(int index)
    {
        return (index - 1) / 2;
    }
    static void heapifyDown(T *data, int n, int index)
    {
        C compare;
        while (inBounds(firstChildIndex(index), n))
        {
            int minChildIndex = firstChildIndex(index);
            if (inBounds(secondChildIndex(index), n) && compare(data[minChildIndex], data[secondChildIndex(index)]))
                minChildIndex = secondChildIndex(index);
            if (compare(data[index], data[minChildIndex]))
                swap(data[minChildIndex], data[index]), index = minChildIndex;
            else
                break;
        }
    }
    static void heapifyUp(T *data, int n, int index)
    {
        C compare;
        while (inBounds(parentIndex(index), n) && compare(data[parentIndex(index)], data[index]))
            swap(data[index], data[parentIndex(index)]), index = parentIndex(index);
    }
    static void buildHeap(T *data, int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyDown(data, n, i);
    }
    static void heapSort(T *data, int n)
    {
        buildHeap(data, n);
        for (int i{n - 1}; i > 0; i--)
            swap(data[0], data[i]), heapifyDown(data, i, 0);
    }

    void makeRoom()
    {
        if (curSize < capacity)
            return;
        T *tmp = data;
        data = new T[capacity * 2];
        for (int i{}; i < curSize; i++)
            data[i] = tmp[i];
        capacity *= 2;
        delete [] tmp;
    }
    bool inBounds(int index)
    {
        return inBounds(index, curSize);
    }
    void heapifyDown(int index = 0)
    {
        heapifyDown(data, curSize, index);
    }
    void heapifyUp()
    {
        heapifyUp(data, curSize, curSize - 1);
    }
    void buildHeap()
    {
        buildHeap(data, curSize);
    }
    void ensurePopulated()
    {
        if (isEmpty())
            throw EmptyHeap("Heap is empty");
    }
    
    public:
    Heap(): curSize(0)
    {
        capacity = 2;
        data = new T[capacity];
    }
    Heap(T *array, int n)
    {
        if (n == 0)
            Heap();
        else
        {
            capacity = curSize = n;
            data = new T[capacity];
            for (int i{}; i < curSize; i++)
                data[i] = array[i];
            buildHeap();
        }
    }
    T top()
    {
        ensurePopulated();
        return data[0];
    }
    void push(T element)
    {
        makeRoom();
        data[curSize++] = element;
        heapifyUp();
    }
    T pop()
    {
        ensurePopulated();
        T tmp = data[0];
        data[0] = data[--curSize];
        heapifyDown();
        return tmp;
    }
    int size()
    {
        return curSize;
    }
    bool isEmpty()
    {
        return size() == 0;
    }
    void displayElements()
    {
        heapSort(data, curSize);
        for (int i{curSize - 1}; i >= 0; i--)
            cout << data[i] << " ";
        buildHeap();
    }
    ~Heap()
    {
        delete [] data;
    }
};