set (HDR_FILES
    ${HDR_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/V4L2CaptureDecouple.h  
    ${CMAKE_CURRENT_LIST_DIR}/V4L2Capture.h 
    ${CMAKE_CURRENT_LIST_DIR}/V4L2.h
)


set (SRC_FILES
    ${SRC_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/V4L2CaptureDecouple.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/V4L2Capture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/V4L2.cpp
)

add_definitions(-DWITH_V4L2)
