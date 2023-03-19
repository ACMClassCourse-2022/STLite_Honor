#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        /**
         * add data members and constructors & destructor
         */

    };

protected:
    /**
     * add data members for linked list as protected members
     */

    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur) {}
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos) {}

public:
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */

    public:
        /**
         * iter++
         */
        iterator operator++(int) {}
        /**
         * ++iter
         */
        iterator & operator++() {}
        /**
         * iter--
         */
        iterator operator--(int) {}
        /**
         * --iter
         */
        iterator & operator--() {}
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const {}
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept {}
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {}
        bool operator==(const const_iterator &rhs) const {}
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {}
        bool operator!=(const const_iterator &rhs) const {}
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {

    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() {}
    list(const list &other) {}
    /**
     * TODO Destructor
     */
    virtual ~list() {}
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other) {}
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const {}
    const T & back() const {}
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {}
    const_iterator cbegin() const {}
    /**
     * returns an iterator to the end.
     */
    iterator end() {}
    const_iterator cend() const {}
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const {}
    /**
     * returns the number of elements
     */
    virtual size_t size() const {}

    /**
     * clears the contents
     */
    virtual void clear() {}
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value) {}
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos) {}
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {}
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() {}
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) {}
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() {}
    /**
     * sort the values in ascending order with operator< of T
     */
    void sort() {}
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void merge(list &other) {}
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() {}
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() {}
};

}

#endif //SJTU_LIST_HPP
