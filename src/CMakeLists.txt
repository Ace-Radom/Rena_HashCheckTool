add_subdirectory(cvector)
# build cvector subproject
add_subdirectory(hash)
# build hash functions
add_subdirectory(dirop)
# build dir operation functions

add_library(rhct_fstatic STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/rhct.c
)
target_link_libraries(rhct_fstatic
    hashf
    dirop
    pthread
)