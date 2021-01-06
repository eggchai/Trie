//
// Created by chen on 2020/12/18.
//

#ifndef TRIE_STRUCTS_H
#define TRIE_STRUCTS_H
#include "Global_parameters.h"
#include <vector>



template<typename T>
class RangeQuery{
public:
    std::vector<T> leftPredicate;
    std::vector<T> rightPredicate;
};

template<typename T>
class IndexEntry{
public:
        T m_key;
        //m_rowId is the offset of Column
        size_t m_rowId;
};


//#include <algorithm>
//#include <cstring>
//#include <vector>
//#include "structs.h"
//typedef unsigned char uint8_t;
//typedef unsigned int unit32_t;
//
//
////class Column;
//class Node;
//
//class ResultStruct{
//    long long int sum = 0;
//public:
//    ResultStruct() : sum(0){
//
//    }
//    void reverse(size_t capacity){
//        (void)capacity;
//    }
//    void push_back(int key){
//        sum += key;
//    }
//    void push_back(int key, int maybe){
//        sum += key * maybe;
//    }
//    void add_all_element(Column& c,Node* node){
//        size_t start = node->get_start_position();
//        size_t end = node->get_end_position();
//        for(size_t i = start; i < end; ++i){
//            sum += c.get_final_data()[i];
//        }
//    }
//};
//
////定义node
////template<typename T>
////class Node{
////public:
////    unit32_t prefix_length;
////    uint8_t partical_key_length;
////    Node* parent;
////    std::vector<T> partical_keys;
////
////    //纯虚函数
////    virtual size_t get_bucket(int key) = 0;
////};
//
//union ptr_location{
//    size_t position;
//    Node* ptr;
//};
//
//template <typename T>
//class Node{
//private:
//    unit32_t prefix_length;
//    uint8_t partical_key_length;
//    Node* parent;
//    size_t size;
//    std::vector<T> partical_keys;
//    std::vector<size_t> children;
//    //false represent data, true represent node
//    std::vector<bool> child_type;
//    std::vector<bool> child_sorted;
//
//    // this node is sorted or not;
//    bool sorted;
//
//    size_t start_position, end_position;
//    //the leafNode's first key
//public:
//    Node(size_t start, size_t end, std::vector<size_t> bucket_count)
//        : start_position(start), end_position(end){
//        for(auto elem : bucket_count){
//            positions.push_back(elem);
//        }
//    }
//
//    virtual uint16_t get_bucket(T key){
//        size_t bitmask = 255 << (sizeof(key) * 8 - prefix_length - partical_key_length);
//        return key & bitmask;
//    }
//
//    //traverse
//    ResultStruct& traverse_Node(Column c, ResultStruct result, T low, T high, bool compare){
//        int low_bucket = get_bucket(low);
//        int high_bucket = get_bucket(high);
//        if(low_bucket == high_bucket){
//
//        }else {
//           for(int i = low_bucket+1; i < high_bucket; ++i){
//               if(child_type[i]) {
//                   //start position is the children[i], and the end position is next ptr
//               } else {
//                   result.add_all_element(children[i].ptr);
//               }
//           }
//           //
//        }
//        return result;
//    }
//
//    //if Node is sorted
//    size_t get_position(T key, std::vector<T>& data){
//        //if sorted, binary search; else, continue to partition
//        size_t left = start_position;
//        size_t right = end_position;
//        size_t mid;
//        if(sorted){
//            while(left <= right){
//                mid = start_position + (end_position - start_position) / 2;
//                if(data[mid] == key){
//                    return mid;
//                }else if(data[mid] > key){
//                    right = mid -1;
//                }else {
//                    left = mid + 1;
//                }
//            }
//        }
//        return -1;
//    }
//
//    //对这个桶进行遍历，找到结果
//    void search_in_node(ResultStruct& result, std::vector<T>& data, T low, T high){
//        for(size_t i = start_position; i < end_position; i++){
//            int is_satisfied = data[i] >= low && data[i] <= high;
//            result.push_back(data[i], is_satified);
//        }
//    }
//};
//
//
//template<typename T>
//class InternalNode: public Node<T>{
//private:
//    std::vector<Node<T>*> children;
//public:
//    virtual size_t get_bucket(int key){
//        //binary search
//        size_t count = children.size();
//    }
//};

//template <typename T>
//class DataNode : public Node<T>{
//    //prefix_length is the length of key;
//    //partical_key_length = 0 represents this node is a data node
//    size_t position;
//};


//column
//template <typename T>
//class Column{
//private:
//    std::vector<T> data;
//    std::vector<size_t> offset;
//    size_t size;
//
//    //index root
//    Node<T>* index_root;
//
//    //is sorted?
//    bool sorted;
//
//    //final data and offset
//    T* final_data;
//    size_t* final_offset;
//public:
//    std::vector<T>& getdata(){
//        return data;
//    }
//    std::vector<size_t>& getoffset(){
//        return offset;
//    }
//    T* get_final_data(){
//        return final_data;
//    }
//    size_t* get_final_offset(){
//        return final_offset;
//    }
//    bool is_sorted(){
//        return sorted;
//    }
//    void set_sorted(bool flag){
//        sorted = flag;
//    }
//    void allocate_final(){
//        posix_memalign((void**)final_data, 64, size * sizeof(data));
//        memset(final_data,0,size * sizeof(data));
//        posix_memalign((void**)final_offset, 64, size * sizeof(offset));
//        memset(final_offset,0,size * sizeof(offset));
//    }
//    void set_Index(Node<T> *root){
//        index = root;
//    }
//    size_t get_size() const{
//        return size;
//    }
//};
#endif //TRIE_STRUCTS_H
