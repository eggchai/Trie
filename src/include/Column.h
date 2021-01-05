//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_COLUMN_H
#define TRIE_COLUMN_H

#include <vector>
#include "Node.h"


template<typename T>
class Column {
public:
    std::vector<T> data;
    std::vector<size_t> offset;
    T min;
    T max;
    size_t size;

    Node<T>* index;

    //is sorted?
    bool indexed;

    //final data and offset
    T* final_data;
    size_t* final_offset;
};


#endif//TRIE_COLUMN_H
