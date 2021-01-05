//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_RESULTSTRUCT_H
#define TRIE_RESULTSTRUCT_H

#include "structs.h"
//Now this class does not contain Node and Column

class ResultStruct {
private:
    size_t sum;
public:
    void push_back(size_t position);
    void push_back_maybe(size_t position, bool is_satisfied);
    void add_all_element(size_t* offset, size_t start, size_t end);
    size_t get_sum();
};


#endif//TRIE_RESULTSTRUCT_H
