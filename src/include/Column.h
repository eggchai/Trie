//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_COLUMN_H
#define TRIE_COLUMN_H

#include "Node.h"
#include "Trie.h"
#include <vector>

template<typename T>
class Column {
public:
    std::vector<T> data;
    std::vector<size_t> offset;
    size_t size;

    Node<T>* index;

    //is sorted?
    bool indexed;

    //final data and offset
    T* final_data;
    size_t* final_offset{};
    // now update
        // and update
};


#endif//TRIE_COLUMN_H
