//
// Created by chen on 2020/12/21.
//
#include "../include/Column.h"
#include "../include/Node.h"
#include "../include/ResultStruct.h"


#define RADIX_BUCKET_COUNT 8
#define GET_BUCKET(VALUE, BITS) (VALUE >> BITS)

//Column C, query workload...

template <typename T>
ResultStruct<T> progress_radix_sort(Column<T>& c, T low, T high){
    ResultStruct<T> result;

    if(c.is_sorted()){
        // binary search and cracker index
    }

    //first query
    if(! c.final_data){
        //first traver the data, and get the count of every bucket
        std::vector<size_t> bucket_count;
        size_t partition_count = RADIX_BUCKET_COUNT * RADIX_BUCKET_COUNT;
        bucket_count.resize(partition_count, 0);
        //count every bucket
        for(auto elem : c.getdata()){
            ++bucket_count[GET_BUCKET(elem, 24)];
        }

        for(size_t i=1; i < partition_count; ++i){
            bucket_count[i]  += bucket_count[i-1];
        }
        c.set_Index(new Node<T>(0, c.getsize() - 1,bucket_count));
        //build Index node
        //now partition
        //allocate memory to final_data and final_offset
        size_t bucket_num = 0;
        c.allocate_final();
        for(auto elem : c.getdata()){
            bucket_num = GET_BUCKET(elem, 24);
            c.get_final_data()[bucket_count[bucket_num] - 1] = elem;
            c.get_final_offset()[bucket_count[bucket_num] -1] = elem;
            --bucket_count[bucket_num];
        }
    }

    //subsequence query
    return result;
}

template <typename T>
Node<T>& build_leafNode(int bucket_num, std::vector<size_t> bucket_count){

}


