cmake_minimum_required(VERSION 3.17)
project(Trie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Trie main.cpp src/include/structs.h src/Progressive/Progressive_radix_index.cpp src/Progressive/Progressive.cpp src/include/Node.h src/include/InternalNode.cpp src/include/InternalNode.h src/include/ResultStruct.cpp src/include/ResultStruct.h src/include/LeafNode.cpp src/include/LeafNode.h src/include/Column.cpp src/include/Column.h src/file_manager/load_file.h src/file_manager/load_file.cpp src/include/Node.cpp src/include/Global_parameters.h)