//
// Created by chen on 2020/12/22.
//

#include "InternalNode.h"
#include <algorithm>
#include <iostream>

template<typename T>
InternalNode<T>::InternalNode(LeafNode<T>& leaf, uint8_t count) {//initialation
    Node(leaf.prefix_length, leaf.start_position, leaf.end_position);
    //now it's time to optimization
    transfer(leaf, count);
}

//template<typename T>
//uint32_t InternalNode<T>::get_bucket(T key) {
//    //generate bitmask
//    T bitmask = ((1 << partical_key_length) - 1) << (sizeof(key) * 8 - partical_key_length - Node<T>::prefix_length);
//    std::cout<<prefix_length<<std::endl;
//    return key & bitmask;
//}
template<typename T>
ResultStruct<T> &InternalNode<T>::query_without_optimize(ResultStruct<T>& result,T low, T high, Column<T> c) {
    uint32_t low_bucket = get_bucket(low);
    uint32_t high_bucket = get_bucket(high);
    std::cout<<this->prefix_length<<std::endl;
    if(low_bucket == high_bucket){
        children[low_bucket]->query_without_optimize(result, low, high, c);
    }else{
        //nodes between
        for(uint32_t i = low_bucket + 1; i < high_bucket; ++i){
            result.add_all_element(children[i]);
        }
        //the buckets low and high located
       children[low_bucket].query_without_optimize(result, low, c, true);
       children[high_bucket].query_without_optimize(result, high, c, false);
    }

    return result;
}
template<typename T>
ResultStruct<T> &InternalNode<T>::query_without_optimize(ResultStruct<T>& result,T key, Column<T> c, bool direction) {
    uint32_t position = get_bucket(key);
    //direction true - low, false - high
    if(direction){
        for(uint32_t i = position + 1; i < children.size(); ++i){
            result.add_all_element(children[i]);
        }
        query(result, key, c, direction);
    } else {
        for(uint32_t i = 0; i < position - 1; ++i){
            result.add_all_element(children[i]);
        }
        children[position].query_without_optimize(result, key, c, direction);
    }
    return result;
}
// query and optimize
template<typename T>
ResultStruct<T> &InternalNode<T>::query(ResultStruct<T> &result, T low, T high, Column<T> c) {
    uint32_t low_bucket = get_bucket(low);
    uint32_t high_bucket = get_bucket(high);
    std::cout<<this->prefix_length<<std::endl;
    if(low_bucket == high_bucket){
        children[low_bucket]->query(result, low, high, c);
        std::sort(children.begin(),children.end());
    }else{
        //nodes between
        for(uint32_t i = low_bucket + 1; i < high_bucket; ++i){
            result.add_all_element(children[i]);
        }
        //the buckets low and high located
        children[low_bucket].query(result, low, c, true);
        children[high_bucket].query(result, high, c, false);
    }
    return result;
}
template<typename T>
ResultStruct<T> &InternalNode<T>::query(ResultStruct<T> &result, T key, Column<T> c, bool direction) {
    uint32_t position = get_bucket(key);
    //direction true - low, false - high
    if(direction){
        for(uint32_t i = position + 1; i < children.size(); ++i){
            result.add_all_element(children[i]);
        }
        query(result, key, c, direction);
    } else {
        for(uint32_t i = 0; i < position - 1; ++i){
            result.add_all_element(children[i]);
        }
        children[position].query(result, key, c, direction);
    }
    return result;
}
template<typename T>
void InternalNode<T>::transfer(LeafNode<T> &leaf, uint32_t count, Column<T>& c) {
    //now transform a leafNode to a internalNode
    uint32_t prefix = leaf.prefix_length;
    uint8_t partical_key_length = count;
    T bitmask = ((1 << partical_key_length) - 1) << (sizeof(T) * 8 - partical_key_length);
    std::vector<size_t> bucket_count;
    uint32_t partition_count = partical_key_length * partical_key_length;
    bucket_count.resize(partition_count, 0);
    //count every bucket
    for(auto elem : c.getdata()){
        ++bucket_count[elem & bitmask];
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
    Node<T> *parent = leaf.parent;
    //leaf is not root node, need to get the bucket of this leaf belong to
    if(!parent){
        T key = c.final_data[leaf.start_position];
        uint32_t parent_bucket = parent->get_bucket(key);
        parent->replace(this, parent_bucket);
    }
}

template<typename T>
void InternalNode<T>::replace(InternalNode<T> *newNode, uint32_t bucket) {
    children[bucket] = newNode;
}
