//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

//FIXME: header files contains each other(Node and Column).
//In fact, Column should be replaced by array in most cases
#include "ResultStruct.h"

template<typename T>
class Column;

template <typename T>
class Node {
public:
    uint32_t prefix_length = 0;
    size_t start_position = 0;
    size_t end_position = 0;
    Node<T> *parent;

    Node(uint32_t prefix_length, size_t start_position, size_t end_position, Node<T> *parent);
    virtual ResultStruct& query(ResultStruct& result,T low, T high, Column<T>& c) = 0;
    virtual ResultStruct& query(ResultStruct& result, T key, Column<T>& c, bool direction) = 0;
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T low, T high, Column<T>& c) = 0;
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T key, Column<T>& c, bool direction) = 0;
    uint32_t get_bucket(T key,uint8_t partical_length);
};


#endif//TRIE_NODE_H
