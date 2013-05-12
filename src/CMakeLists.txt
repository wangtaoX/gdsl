#the source code name
SET(LIB_SRC list.c hash.c string.c bitmap.c rw_lock.c xor.c)

#set header file directory
SET(HEADER_FILE_DIR "../include")
#where to find the header file
INCLUDE_DIRECTORIES(${HEADER_FILE_DIR})

FIND_PACKAGE(Threads)
#make a shared library
ADD_LIBRARY(gdsl SHARED ${LIB_SRC})
TARGET_LINK_LIBRARIES(gdsl ${CMAKE_THREAD_LIBS_INIT})

#install the gdsl in ${CMAKE_INSTALL_PREFIX}/lib
INSTALL(TARGETS gdsl
    LIBRARY DESTINATION lib
    )
