//
// Created by chen on 2021/1/6.
//
#include "Node.h"

template<typename T>
Node<T>::Node(uint32_t prefix_length, size_t start_position, size_t end_position, Node<T> *parent)
        :prefix_length(prefix_length),start_position(start_position), end_position(end_position), parent(parent){}

template<typename T>
uint32_t Node<T>::get_bucket(T key, uint8_t partical_length) {
    //generate bitmask
    T bitmask = ((1 << partical_length) - 1) << (sizeof(key) * 8 - partical_length - prefix_length);
    return key & bitmask;
}