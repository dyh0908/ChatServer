cmake_minimum_required(VERSION 3.0)  # 要求的最低版本号
project(main)   # 工程文件的名字

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)   # 有了这个编译文件就可以进行调试了 可以是-g -O2 等

# 设置可执行文件生成后的存储位置 
# PROJECT_SOURCE_DIR 是工程的根目录，是cmake预定义的变量，可直接拿来使用
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

add_executable(server ./src/server.cpp)  # 生成可执行文件server ： 通过源文件 TCPserver.cpp 源文件编译而来
add_executable(client ./src/client.cpp) # 生成可执行文件client ： 通过源文件 client.cpp 源文件编译而来