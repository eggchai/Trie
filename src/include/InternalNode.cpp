//
// Created by chen on 2020/12/22.
//

#include "InternalNode.h"
#include "LeafNode.h"
#include "Column.h"
#include <algorithm>
#include <iostream>

template<typename T>
InternalNode<T>::InternalNode(LeafNode<T>& leaf, Column<T>& c,uint8_t count) {//initialation
    Node<T>(leaf.prefix_length, leaf.start_position, leaf.end_position, leaf.parent);
    //now it's time to optimization
    transfer(c,count);
}

//template<typename T>
//uint32_t InternalNode<T>::get_bucket(T key) {
//    //generate bitmask
//    T bitmask = ((1 << partical_key_length) - 1) << (sizeof(key) * 8 - partical_key_length - Node<T>::prefix_length);
//    std::cout<<prefix_length<<std::endl;
//    return key & bitmask;
//}
template<typename T>
ResultStruct &InternalNode<T>::query_without_optimize(ResultStruct& result,T low, T high, T* data, size_t* offset) {
    uint32_t low_bucket = get_bucket(low);
    uint32_t high_bucket = get_bucket(high);
    std::cout<<this->prefix_length<<std::endl;
    if(low_bucket == high_bucket){
        children[low_bucket]->query_without_optimize(result, low, high, data, offset);
    }else{
        //nodes between
        for(uint32_t i = low_bucket + 1; i < high_bucket; ++i){
            result.add_all_element(offset, children[i]->start_position, children[i]->end_position);
        }
        //the buckets low and high located
       children[low_bucket].query_without_optimize(result, low, data, offset, true);
       children[high_bucket].query_without_optimize(result, high, data, offset, false);
    }

    return result;
}
template<typename T>
ResultStruct &InternalNode<T>::query_without_optimize(ResultStruct& result,T key, T* data, size_t* offset, bool direction) {
    uint32_t position = get_bucket(key);
    //direction true - low, false - high
    if(direction){
        for(uint32_t i = position + 1; i < children.size(); ++i){
            result.add_all_element(children[i]);
        }
        query(result, key, data, result, direction);
    } else {
        for(uint32_t i = 0; i < position - 1; ++i){
            result.add_all_element(children[i]);
        }
        children[position].query_without_optimize(result, key, data, offset, direction);
    }
    return result;
}
// query and optimize
template<typename T>
ResultStruct &InternalNode<T>::query(ResultStruct &result, T low, T high, T* data, size_t* offset) {
    uint32_t low_bucket = get_bucket(low);
    uint32_t high_bucket = get_bucket(high);
    std::cout<<this->prefix_length<<std::endl;
    if(low_bucket == high_bucket){
        children[low_bucket]->query(result, low, high, data, result);
        std::sort(children.begin(),children.end());
    }else{
        //nodes between
        for(uint32_t i = low_bucket + 1; i < high_bucket; ++i){
            result.add_all_element(children[i]);
        }
        //the buckets low and high located
        children[low_bucket].query(result, low, data, offset, true);
        children[high_bucket].query(result, high, data, offset, false);
    }
    return result;
}
template<typename T>
ResultStruct &InternalNode<T>::query(ResultStruct &result, T key, T* data, size_t* offset, bool direction) {
    uint32_t position = get_bucket(key);
    //direction true - low, false - high
    if(direction){
        for(uint32_t i = position + 1; i < children.size(); ++i){
            result.add_all_element(children[i]);
        }
        query(result, key, data, offset, direction);
    } else {
        for(uint32_t i = 0; i < position - 1; ++i){
            result.add_all_element(children[i]);
        }
        children[position].query(result, key, data, offset, direction);
    }
    return result;
}
template<typename T>
void InternalNode<T>::transfer(Column<T>& c, uint8_t count) {
    //now transform a leafNode to a internalNode
    //why cannot use prefix_length which is a public member of parent class
    uint32_t prefix = Node<T>::prefix_length;
    uint8_t partical_key_length = count;
    T bitmask = ((1 << partical_key_length) - 1) << (sizeof(T) * 8 - partical_key_length);
    std::vector<size_t> bucket_count;
    uint32_t partition_count = partical_key_length * partical_key_length;
    bucket_count.resize(partition_count, 0);
    //count every bucket
    for(size_t i=0; i < COLUMN_SIZE; ++i){
        ++bucket_count[c.final_data[i] & bitmask];
    }
    for(size_t i=1; i < partition_count; ++i){
        bucket_count[i]  += bucket_count[i-1];
    }

    this->partical_key_length = partical_key_length;
    for(size_t i = 0; i < partition_count - 1; ++i){
        LeafNode<T> *leafNode = new LeafNode<T>(prefix + partical_key_length,
                                                this->start_position + bucket_count[i],
                                                this->start_position + bucket_count[i-1]);
        children.push_back(leafNode);
    }
    //the last leafnode
    LeafNode<T> *leafNode = new LeafNode<T>(prefix + partical_key_length,
                                            this->start_position + bucket_count[partical_key_length - 1],
                                            this->end_position);
    children.push_back(leafNode);
    Node<T> *parent = Node<T>::parent;
    //leaf is not root node, need to get the bucket of this leaf belong to
    if(!parent){
        T key = data[start_position];
        uint32_t parent_bucket = parent->get_bucket(key);
        parent->replace(this, parent_bucket);
    }
}

template<typename T>
void InternalNode<T>::replace(InternalNode<T> *newNode, uint32_t bucket) {
    children[bucket] = newNode;
}
