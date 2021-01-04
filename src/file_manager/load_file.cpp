//
// Created by chen on 2021/1/4.
//
#include "load_file.h"

template<typename T>
void load_queries(RangeQuery<T> *rangequeries, string QUERIES_FILE_PATH, int64_t NUM_QUERIES){
    //read file
    FILE *file = fopen(QUERIES_FILE_PATH.c_str(), "r");
    if(!file){
        std::cout<<"cannot open file"<<std::endl;
        return;
    }
    d
}