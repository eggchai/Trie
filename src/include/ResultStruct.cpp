//
// Created by chen on 2020/12/22.
//

#include "ResultStruct.h"

void ResultStruct::push_back(size_t position){
    sum += position;
}
void ResultStruct::push_back_maybe(size_t position, bool is_satisfied) {
    sum += position * is_satisfied;
}
void ResultStruct::add_all_element(size_t *offset, size_t start, size_t end) {
    for(size_t i = start; i <= end; i++){
        sum += offset[i];
    }
}
size_t ResultStruct::get_sum() {
    return sum;
}
