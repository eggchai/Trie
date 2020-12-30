//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include "ResultStruct.h"
#include "Column.h"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long size_t;


template <typename T>
class Node {
public:
    uint32_t prefix_length = 0;
    size_t start_position = 0;
    size_t end_position = 0;
    Node<T> *parent;

    Node(uint32_t prefix_length, size_t start_position, size_t end_position)
            :prefix_length(prefix_length),start_position(start_position), end_position(end_position){}
    virtual ResultStruct<T>& query(ResultStruct<T>& result,T low, T high, Column<T> c) = 0;
    virtual ResultStruct<T>& query(ResultStruct<T>& result, T key, Column<T> c, bool direction) = 0;
    virtual ResultStruct<T>& query_without_optimize(ResultStruct<T>& result, T low, T high, Column<T> c) = 0;
    virtual ResultStruct<T>& query_without_optimize(ResultStruct<T>& result, T key, Column<T> c, bool direction) = 0;
    uint32_t get_bucket(T key) {
        //generate bitmask
        T bitmask = ((1 << partical_key_length) - 1) << (sizeof(key) * 8 - partical_key_length - prefix_length);
        return key & bitmask;
    }
};


#endif//TRIE_NODE_H
