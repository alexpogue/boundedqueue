// Copyright [2014] Alex pogue

class BoundedQueue {
    public:
        BoundedQueue(int size);
        BoundedQueue(const BoundedQueue& source);
        ~BoundedQueue();
        BoundedQueue& operator=(const BoundedQueue& rhs);
        void reinit();
        int getCapacity();
        int getSize();
        void enqueue(int elem);
        int dequeue();
    private:
        int* data;
        int capacity;
        int front;
        int numElements;
};
