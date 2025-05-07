SET(BUILD_EXE_NAME "TEST_BIO")

file(GLOB_RECURSE ALL_SRCS 
    *.cpp
) 

# 创建测试程序
add_executable(${BUILD_EXE_NAME} ${ALL_SRCS})

# 强制使用静态库
# set(Boost_USE_STATIC_LIBS ON)

target_link_libraries(${BUILD_EXE_NAME}
    ssl 
    crypto
    )

# IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#     target_link_libraries(${BUILD_EXE_NAME}
#         ws2_32 mswsock)
# ENDIF(CMAKE_SYSTEM_NAME MATCHES "Windows")

# 设置包含目录
target_include_directories(${BUILD_EXE_NAME} PUBLIC ../src)

