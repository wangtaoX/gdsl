#the source code name
SET(LIB_SRC "list.c")

#set header file directory
SET(HEADER_FILE_DIR "../include")
#where to find the header file
INCLUDE_DIRECTORIES(${HEADER_FILE_DIR})

#make a shared library
ADD_LIBRARY(gdsl SHARED ${LIB_SRC})

#install the gdsl in ${CMAKE_INSTALL_PREFIX}/lib
INSTALL(TARGETS gdsl
    LIBRARY DESTINATION lib
    )
