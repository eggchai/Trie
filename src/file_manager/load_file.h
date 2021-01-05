//
// Created by chen on 2021/1/4.
//

#ifndef TRIE_LOAD_FILE_H
#define TRIE_LOAD_FILE_H

#include <iostream>
#include "../include/Column.h"
#include "../include/structs.h"
using namespace std;

template<typename T>
void load_queries(RangeQuery<T> &rangequeries, string QUERIES_FILE_PATH, size_t NUM_QUERIES);

template<typename T>
void load_column(Column<T> &c, string COLUMN_FILE_PATH, size_t COLUMN_SIZE);

void load_answers(vector<size_t> &answers, string QUERIES_ANSWERS_PATH, size_t NUM_QUERIES);

#endif//TRIE_LOAD_FILE_H
