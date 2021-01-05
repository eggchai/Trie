#include <iostream>
#include "src/file_manager/load_file.h"
#include "src/include/structs.h"
#include "src/Progressive/Progressive.cpp"
int main() {
    // load data
    std::vector<size_t> answers;
    RangeQuery<int> rangeQueries;
    Column<int> c;
    load_answers(answers,"/home/chen/CLionProjects/Trie/a1",QUERY_SIZE);
    load_queries(rangeQueries, "/home/chen/CLionProjects/Trie/q1", QUERY_SIZE);
    load_column(c,"col1", COLUMN_SIZE);
    //progressive(rangeQueries, answers, c);
    // update from my pc
    return 0;
}
