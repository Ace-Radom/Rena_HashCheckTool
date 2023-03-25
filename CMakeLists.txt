cmake_minimum_required(VERSION 3.10)
project(Rena_HashCheckTool VERSION 1.0)

# ============================================
#                search OpenSSL
# ============================================

find_package(OpenSSL REQUIRED)
if(NOT OPENSSL_FOUND)
    message(FATAL "Cannot found OpenSSL, please check environment")
endif()
include_directories(${OPENSSL_INCLUDE_DIR})
set(OPENSSL_DLL_DIR ${OPENSSL_INCLUDE_DIR}/../bin)
file(GLOB OPENSSL_DLL_FILE_LIST ${OPENSSL_DLL_DIR}/*.dll)
# catch all openssl dlls' path and save them in OPENSSL_DLL_FILE_LIST var

# ============================================
#                     main
# ============================================

set(LIBRARY_OUTPUT_PATH    ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_PREFIX   ${CMAKE_SOURCE_DIR}/install/Rena_HashCheckTool)

add_definitions(-DEXPORTING_APIS)
# add_definitions(-DUSING_PTHREAD)
add_definitions(-DENABLE_ERROUT)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(rhct
    main.c
)
target_link_libraries(rhct
    hashf
    dirop
    rhct_fstatic
)
# build Rena HashCheck Tool exe

# ============================================
#                 installation
# ============================================

install(
    FILES
        ${OPENSSL_DLL_FILE_LIST}
        ${LIBRARY_OUTPUT_PATH}/libhashf.dll
        ${LIBRARY_OUTPUT_PATH}/libcvector.dll
        ${EXECUTABLE_OUTPUT_PATH}/rhct.exe
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)