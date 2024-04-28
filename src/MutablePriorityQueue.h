//
// Created by Martim on 30/05/2023.
//

#ifndef DA___2ND_PROJECT_MUTABLEPRIORITYQUEUE_H
#define DA___2ND_PROJECT_MUTABLEPRIORITYQUEUE_H
#include <vector>



/**
 * @brief The MutablePriorityQueue class represents a mutable priority queue.
 *
 * @tparam T The type of elements stored in the queue.
 * @details The class T must have an accessible field `int queueIndex` and the `operator<` defined.
 */

template <class T>
class MutablePriorityQueue {
    std::vector<T *> H; /**< The heap storing the elements */

    /**
     * @brief Restores the heap property by moving an element up the heap.
     *
     * @param i The index of the element to heapify up.
     */

    void heapifyUp(unsigned i);

    /**
     * @brief Restores the heap property by moving an element down the heap.
     *
     * @param i The index of the element to heapify down.
     */

    void heapifyDown(unsigned i);

    /**
     * @brief Sets an element at a given index in the heap.
     *
     * @param i The index to set the element.
     * @param x The element to set.
     */

    inline void set(unsigned i, T * x);

public:

    /**
     * @brief Constructs an empty MutablePriorityQueue object.
     */

    MutablePriorityQueue();

    /**
     * @brief Inserts an element into the queue.
     *
     * @param x The element to insert.
     */

    void insert(T * x);

    /**
     * @brief Extracts the minimum element from the queue.
     *
     * @return The minimum element.
     */

    T * extractMin();

    /**
     * @brief Decreases the key of an element in the queue.
     *
     * @param x The element whose key should be decreased.
     */

    void decreaseKey(T * x);

    /**
     * @brief Checks if the queue is empty.
     *
     * @return True if the queue is empty, false otherwise.
     */

    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}
#endif //DA___2ND_PROJECT_MUTABLEPRIORITYQUEUE_H
