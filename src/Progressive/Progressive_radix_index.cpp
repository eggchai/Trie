//
// Created by chen on 2020/12/21.
//
#include "../include/Column.h"
#include "../include/Node.h"
#include "../include/ResultStruct.h"
#include "../file_manager/load_file.h"
#include "../include/LeafNode.h"
#include "../include/InternalNode.h"

#define RADIX_BUCKET_COUNT 8
#define GET_BUCKET(VALUE, BITS) (VALUE >> BITS)

//Column C, query workload...

template <typename T>
ResultStruct progressive_radix_sort(Column<T>& c, T low, T high){
    ResultStruct result;

    if(c.indexed){
        // binary search and cracker index
        c.index->query_without_optimize(result, low, high, c);
    }else{
        //first query, initialize data pointer and index
        if(! c.final_data){
            //TODO: need to set c.data and c.offset
            //load in main function
            //COLUMN_SIZE
            c.final_data = (T*)malloc(sizeof(T) * COLUMN_SIZE);
            c.final_offset = (size_t*)malloc(sizeof(size_t) * COLUMN_SIZE);
            c.index = new LeafNode<T>(0,0,COLUMN_SIZE - 1);
        }
        //subsequence query
        c.index->query(result, low, high, c);
    }
    return result;
}



