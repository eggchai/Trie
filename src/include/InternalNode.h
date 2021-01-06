//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_INTERNALNODE_H
#define TRIE_INTERNALNODE_H

#include "Node.h"
#include "ResultStruct.h"
#include <vector>

template<typename T>
class LeafNode;

template<typename T>
class Column;

template<typename T>
class InternalNode : public Node<T>{
private:
    uint8_t partical_key_length = 8;
    std::vector<Node<T>*> children;
public:
    InternalNode(LeafNode<T>& leaf, Column<T>& c,uint8_t count);
    virtual ResultStruct& query(ResultStruct& result,T low, T high, T* data, size_t* offset);
    virtual ResultStruct& query(ResultStruct& result, T key, T* data, size_t* offset, bool direction);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T low, T high, T* data, size_t* offset);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T key, T* data, size_t* offset, bool direction);
    void transfer(T* data, size_t* offset, uint8_t count);
//    void replace(InternalNode<T> *newNode, uint32_t bucket);
};



#endif//TRIE_INTERNALNODE_H
