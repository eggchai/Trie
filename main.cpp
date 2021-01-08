#include <iostream>
#include "src/file_manager/load_file.h"

int QUERY_SIZE;
size_t COLUMN_SIZE;
string COLUMN_PATH, QUERY_PATH, ANSWER_PATH;

int main() {
    // load data
    std::vector<size_t> answers;
    RangeQuery<int> rangeQueries;
    Column<int> c;

    load_answers(answers,ANSWER_PATH,QUERY_SIZE);

    //undefined reference to
    load_queries<int>(rangeQueries, QUERY_PATH, QUERY_SIZE);
    load_column<int>(c,COLUMN_PATH, COLUMN_SIZE);
    //progressive(rangeQueries, answers, c);
    // update from my pc
    return 0;
}
