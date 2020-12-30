//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_RESULTSTRUCT_H
#define TRIE_RESULTSTRUCT_H

#include "Node.h"
#include "Column.h"

template<typename T>
class ResultStruct {
private:
    long long int sum;
public:
    void push_back(T key);
    void push_back_maybe(T key, bool is_satisfied);
    void add_all_element(Column<T>& c, Node<T>* node);
};


#endif//TRIE_RESULTSTRUCT_H
