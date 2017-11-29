######## A simple cmakelists.txt file for OpenCV() #############  
cmake_minimum_required(VERSION 2.8)                          # 初始化Cmake版本检测  
PROJECT(cat_monitor)                                       # 工程名  

FIND_PACKAGE( OpenCV REQUIRED )                              # 环境变量中寻找OpenCV的库的位置  
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE(cat_monitor main.cpp)                         # 将文件加入工程，有多少.c或者cpp都加进去  
TARGET_LINK_LIBRARIES (cat_monitor ${OpenCV_LIBS})         # 这两行的次序也不能变!加入动态链接库  
########### end ####################################  