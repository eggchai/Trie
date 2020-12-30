//
// Created by chen on 2020/12/22.
//

#include "ResultStruct.h"

template<typename T>
void ResultStruct<T>::push_back(T key){
    sum += key;
}
template<typename T>
void ResultStruct<T>::push_back_maybe(T key, bool is_satisfied) {
    sum += key * is_satisfied;
}
template<typename T>
void ResultStruct<T>::add_all_element(Column<T>& c, Node<T>* node) {
    size_t start = node->start_position;
    size_t end = node->end_position;
    for(size_t i = start; i <= end; i++){
        sum += c.final_data[i];
    }
}
