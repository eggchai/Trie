//
// Created by chen on 2020/12/22.
//

#ifndef TRIE_LEAFNODE_H
#define TRIE_LEAFNODE_H

#include "Node.h"
#include "ResultStruct.h"
#include "Column.h"
#include "InternalNode.h"
#define RADIX_BUCKET_COUNT 8

template<typename T>
class LeafNode : public Node<T>{
private:
    bool sorted;
public:
    // In leafNode, in the process of query optimize
    LeafNode(uint32_t prefix_length, size_t start_position, size_t end_position)
            :Node(prefix_length, start_position, end_position), sorted(false){};
    virtual ResultStruct<T>& query(ResultStruct<T>& result,T low, T high, Column<T> c);
    virtual ResultStruct<T>& query(ResultStruct<T>& result, T key, Column<T> c, bool direction);
    ResultStruct<T>& query_without_optimize(ResultStruct<T>& result, T low, T high, Column<T> c);
    ResultStruct<T>& query_without_optimize(ResultStruct<T>& result, T key, Column<T> c, bool direction);
    size_t binary_search(Column<T>& c,T key);
};



#endif//TRIE_LEAFNODE_H
