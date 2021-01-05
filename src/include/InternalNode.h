//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_INTERNALNODE_H
#define TRIE_INTERNALNODE_H

#include "Node.h"
#include "ResultStruct.h"
#include <vector>
#include "LeafNode.h"

template<typename T>
class InternalNode : public Node<T>{
private:
    uint8_t partical_key_length = 8;
    std::vector<Node<T>*> children;
public:
    //TODO
    InternalNode(LeafNode<T>& leaf, uint8_t count);
//    uint32_t get_bucket(T key);
    virtual ResultStruct& query(ResultStruct& result,T low, T high, Column<T> c);
    virtual ResultStruct& query(ResultStruct& result, T key, Column<T> c, bool direction);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T low, T high, Column<T> c);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T key, Column<T> c, bool direction);
    void transfer(LeafNode<T>& leaf, uint32_t count, Column<T>& c);
    void replace(InternalNode<T> *newNode, uint32_t bucket);
};



#endif//TRIE_INTERNALNODE_H
