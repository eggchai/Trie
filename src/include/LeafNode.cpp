//
// Created by chen on 2020/12/22.
//

#include "LeafNode.h"
#include "Column.h"
#include "InternalNode.h"
#include <iostream>


// query and optimized
template<typename T>
ResultStruct &LeafNode<T>::query_without_optimize(ResultStruct &result, T low, T high, Column<T>& c) {
    if(sorted){
        size_t start = binary_search(c, low, true);
        size_t end = binary_search(c, high, false);
        for(size_t i = start; i <= end; ++i){
            result.push_back(c.final_data[i]);
        }
    }else{
        // unsorted, and optimize
        for(size_t i = Node<T>::start_position; i < Node<T>::end_position; ++i){
            int flag = c.final_data[i] >= low && c.final_data[i] <= high;
            result.push_back_maybe(c.final_data[i], flag);
        }
    }
    return result;
}

template<typename T>
size_t LeafNode<T>::binary_search(std::vector<T> &data, T key, bool direction) {
    //binary search
    size_t left = Node<T>::start_position;
    size_t right = Node<T>::end_position;
    size_t mid;
    size_t result = right + 1;
    while(left <= right){
        mid = left + (right - left)/2;
        if(data[mid] > key){
            if(direction)
                result = mid;
            right = mid - 1;
        }else if(data[mid] < key){
            if(!direction)
                result = mid;
            left = mid + 1;
        }else{
            return mid;
        }
    }
    return result;
}


template<typename T>
ResultStruct &LeafNode<T>::query_without_optimize(ResultStruct &result, T key, Column<T>& c, bool direction) {
    if(sorted){
        size_t location = binary_search(c, key);
        // direction true-low, false-high
        size_t start, end;
        if(direction){
            start = location;
            end = Node<T>::end_position;
        }else {
            start = Node<T>::start_position;
            end = location;
        }
        while(start <= end){
            result.push_back(c.final_data[start]);
            ++ start;
        }
    } else {
        size_t start = Node<T>::start_position;
        size_t end = Node<T>::end_position;
        while(start <= end) {
            bool is_satisfied = (direction && c.final_data[start] >= key) || (!direction && c.final_data[start] <= key);
            result.push_back_maybe(c.final_data[start], is_satisfied);
            start++;
        }
    }
    return result;
}

template<typename T>
ResultStruct& LeafNode<T>::query(ResultStruct &result, T low, T high, Column<T>& c) {
    if(Node<T>::size < 1024){
        sort(c.final_data, Node<T>::start_position, Node<T>::end_position);
        sorted = true;
        query_without_optimize(result, low, high, c);
    }else{
        //this leafNode transforms to a internalNode+leafNodes, and call query_without_optimize
//        std::vector<size_t> bucket_count;
//        size_t partition_count = RADIX_BUCKET_COUNT * RADIX_BUCKET_COUNT;
//        bucket_count.resize(partition_count, 0);
//        size_t bucket;
//        for(size_t i = Node<T>::start_position; i < Node<T>::end_position; ++i){
//            //get_bucket
//            bucket = Node<T>::get_bucket(c.final_data[i]);
//        }
//        for(uint32_t i = 1; i < partition_count; i++){
//            bucket_count[i] +=bucket_count[i-1];
//        }
        //now construct node
        //InternalNode* internal = new InternalNode();
        //TODO: bucket count relates to the number of this node and the query result
        new InternalNode<T>(this, 8);
        //after optimizing, query_without_optimize. but how to release this leaf?
    }
    return result;
}
template<typename T>
ResultStruct& LeafNode<T>::query(ResultStruct& result, T key, Column<T>& c, bool direction) {
    if(Node<T>::size < 1024){
        sort(c.final_data, Node<T>::start_position, Node<T>::end_position);
    }else{
        //this leafNode transforms to a internalNode+leafNodes, and call query_without_optimize
        //TODO: optimize here
        new InternalNode<T>(this, 8);
    }
    return result;
}
