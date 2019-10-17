file(GLOB CUR_SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB CUR_HDR_FILES ${CMAKE_CURRENT_LIST_DIR}/*.h)
list(REMOVE_ITEM CUR_SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/defaultSetterOld.cpp")
list(REMOVE_ITEM CUR_HDR_FILES "${CMAKE_CURRENT_LIST_DIR}/defaultSetterOld.h")

set(SRC_FILES ${SRC_FILES} ${CUR_SRC_FILES})
set(HDR_FILES ${HDR_FILES} ${CUR_HDR_FILES})