#This library implements some general data structures,
#you can use it in your own program, please see README
PROJECT(gdsl)

SET(CMAKE_C_FLAGS "-g -Wall")
#the source code directory
ADD_SUBDIRECTORY(src)

#the example directory
ADD_SUBDIRECTORY(example)

#header file directory
ADD_SUBDIRECTORY(include)
