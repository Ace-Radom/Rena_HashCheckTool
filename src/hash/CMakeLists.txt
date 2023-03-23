aux_source_directory(. HASH_SRC)
add_library(hashf SHARED
    ${HASH_SRC}
)
target_link_libraries(hashf
    OpenSSL::Crypto
    OpenSSL::SSL
)
# build hash function dll