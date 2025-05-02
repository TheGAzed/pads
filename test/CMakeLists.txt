add_library(functions helper/functions.c)
target_include_directories(functions PUBLIC helper)

add_subdirectory(sequential)
add_subdirectory(list)
#add_subdirectory(set)
#add_subdirectory(matrix_graph/tests)
