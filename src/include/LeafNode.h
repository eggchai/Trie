//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_LEAFNODE_H
#define TRIE_LEAFNODE_H

#include "Node.h"
#include "ResultStruct.h"
#include "Column.h"
#include "InternalNode.h"
#include <vector>
#define RADIX_BUCKET_COUNT 8

template<typename T>
class LeafNode : public Node<T>{
private:
    bool sorted;
public:
    // In leafNode, in the process of query optimize
    LeafNode(uint32_t prefix_length, size_t start_position, size_t end_position)
            :Node(prefix_length, start_position, end_position), sorted(false){};
    virtual ResultStruct& query(ResultStruct& result,T low, T high, std::vector<T> &data, std::vector<size_t> &offset);
    virtual ResultStruct& query(ResultStruct& result, T key, std::vector<T> &data, std::vector<size_t> &offset, bool direction);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T low, T high, std::vector<T> &data, std::vector<size_t> &offset);
    virtual ResultStruct& query_without_optimize(ResultStruct& result, T key, std::vector<T> &data, std::vector<size_t> &offset, bool direction);
    size_t binary_search(std::vector<T> &data, T key);
};



#endif//TRIE_LEAFNODE_H
