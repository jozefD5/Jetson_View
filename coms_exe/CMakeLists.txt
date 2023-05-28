project(coms_exe)                       # Create project
cmake_minimum_required(VERSION 3.22)    # CMake version check

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(../tools/test_lib)


# set(Boost_USE_STATIC_LIBS OFF)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)
# set(Boost_INCLUDE_DIR  "/boost_1_82_0")
# find_package(Boost  REQUIRED)

# if(Boost_FOUND)
#     message("CMake - Found Boost")
#     find_path(Boost_Asio_FOUND boost/asio.hpp PATHS ${Boost_INCLUDE_DIRS})
#     message("CMake - Found Asio")
#     if(Boost_Asio_FOUND)
# 	add_library(boost-asio INTERFACE)
# 	target_include_directories(boost-asio INTERFACE ${Boost_INCLUDE_DIRS})
# 	if(WIN32)
# 	    target_compile_definitions(boost-asio INTERFACE _WIN32_WINNT=0x0601)
# 	endif()
# 	add_library(Boost::asio ALIAS boost-asio)
#     endif()
# endif()

# find_package(OpenSSL REQUIRED)
find_package(Poco  REQUIRED  COMPONENTS Data DataSQLite Foundation Net NetSSL Util)
 

add_executable(coms_exe main.cpp)

target_link_libraries(coms_exe PUBLIC
        Poco::Data
        Poco::DataSQLite
        Poco::Foundation
        Poco::Net
        Poco::NetSSL
        Poco::Util
)

