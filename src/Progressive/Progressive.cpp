//
// Created by chen on 2020/12/21.
//

#ifndef TRIE_PROGRESSIVE_CPP
#define TTRIE_PROGRESSIVE_CPP
#include "../include/structs.h"
#include "../include/Column.h"
#include "../include/Node.h"
#include "Progressive_radix_index.cpp"
#include "../include/ResultStruct.h"

//get all data and query workload, and start to query
template<typename T>
void progressive(const RangeQuery<T>& query, const std::vector<size_t>& answers, Column<T>& c){
    size_t query_size = answers.size();
    for(size_t i=0; i<query_size; ++i){
        T low = query.leftPredicate[i];
        T high = query.rightPredicate[i];
        size_t ans = answers[i];
        if(progressive_radix_sort<T>(c, low, high).get_sum() == ans){
            //get time
            std::cout << "query correct" << std::endl;
        }else{
            std::cout << "something error in query" << std::endl;
        }
    }
}

#endif