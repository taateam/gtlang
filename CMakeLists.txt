cmake_minimum_required(VERSION 3.16)
project(gtlang)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(CMAKE_CXX_FLAGS "/utf-8")
set(CMAKE_C_FLAGS "/utf-8")
set(CMAKE_TOOLCHAIN_FILE "C:/v/vcpkg/scripts/buildsystems/vcpkg.cmake")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(KEEP_OUTPUT)
endif()

# Boost
find_package(Boost REQUIRED COMPONENTS algorithm interprocess filesystem system regex)
# ICU
find_package(ICU REQUIRED COMPONENTS uc i18n data)
# cURL
find_package(CURL REQUIRED)
# MySQL C API
find_path(MYSQL_INCLUDE_DIR mysql.h PATH_SUFFIXES include)
find_library(MYSQL_LIB NAMES mysqlclient)

# Include source files
file(GLOB SOURCES "./*.cpp")

# Define executable
add_executable(gtlang ${SOURCES})


# Include directories
target_include_directories(gtlang PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS}
)
target_include_directories(gtlang PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(gtlang PRIVATE "C:/v/installed/x64-windows/include")
target_include_directories(gtlang PRIVATE "C:/x/mysql-connector-c++-9.1.0-winx64/include/jdbc")

# Link libraries
target_link_libraries(gtlang
    Boost::algorithm
    Boost::interprocess
    Boost::interprocess
    Boost::system
    Boost::regex
    ICU::uc
    ICU::i18n
	ICU::data
    CURL::libcurl
    Threads::Threads 
)
target_link_libraries(gtlang
    "C:/x/mysql-connector-c++-9.1.0-winx64/lib64/vs14/mysqlcppconn.lib"
)

target_include_directories(gtlang PRIVATE "C:/x/mysql")
target_include_directories(gtlang PRIVATE "C:/x/mysql-connector-c++-9.1.0-winx64/include/jdbc")
