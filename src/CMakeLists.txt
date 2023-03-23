add_library(hashf SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/md5.c
)
target_link_libraries(hashf
    OpenSSL::Crypto
    OpenSSL::SSL
)
# build hash function dll