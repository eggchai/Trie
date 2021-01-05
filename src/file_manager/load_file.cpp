//
// Created by chen on 2021/1/4.
//
#include "load_file.h"

template<typename T>
void load_queries(RangeQuery<T> &rangequeries, string QUERIES_FILE_PATH, size_t NUM_QUERIES){
    //read file
    FILE *file = fopen(QUERIES_FILE_PATH.c_str(), "r");
    if(!file){
        std::cout<<"cannot open file"<<std::endl;
        return;
    }
    T* temp_data = (T*)malloc(sizeof(T) * NUM_QUERIES);
    fread(temp_data, sizeof(T), NUM_QUERIES, file);
    rangequeries.leftPredicate = std::vector<T>(NUM_QUERIES);
    for(size_t i=0; i < NUM_QUERIES; ++i){
        rangequeries.leftPredicate.push_back(temp_data[i]);
    }

    fread(temp_data, sizeof(T), NUM_QUERIES, file);
    rangequeries.rightPredicate = std::vector<T>(NUM_QUERIES);
    for(size_t i=0; i < NUM_QUERIES; ++i){
        rangequeries.rightPredicate.push_back(temp_data[i]);
    }
    fclose(file);
}

template<typename T>
void load_column(Column<T> &c, string COLUMN_FILE_PATH, size_t COLUMN_SIZE){
    FILE *file = fopen(COLUMN_FILE_PATH.c_str(), "r");
    if(!file){
        std::cout<<"cannot open Column file"<<endl;
        return;
    }
    T* temp_data = (T*)malloc(sizeof(T) * COLUMN_SIZE);
    fread(temp_data, sizeof(T), COLUMN_SIZE, file);
    c.data = std::vector<T>(COLUMN_SIZE);
    c.offset = std::vector<size_t>(COLUMN_SIZE);
    c.min = std::numeric_limits<T>::min();
    c.max = std::numeric_limits<T>::max();
    for(size_t i=0; i < COLUMN_SIZE; ++i){
        c.data.push_back(temp_data[i]);
        c.offset.push_back(i);
        if(temp_data[i] < c.min){
            c.min = temp_data[i];
        }
        if(temp_data[i] > c.max){
            c.max = temp_data[i];
        }
    }
}


void load_answers(vector<size_t> &answers, string QUERIES_ANSWERS_PATH, size_t NUM_QUERIES){
    FILE* file = fopen(QUERIES_ANSWERS_PATH.c_str(), "r");
    if(!file){
        std::cout<< "cannot open Answer file" <<std::endl;
        return;
    }
    size_t* temp_data = (size_t*)malloc(sizeof(size_t) * NUM_QUERIES);
    fread(temp_data, sizeof(size_t), NUM_QUERIES, file);
    for(size_t i=0; i < NUM_QUERIES; ++i){
        answers.push_back(temp_data[i]);
    }
    fclose(file);
}

