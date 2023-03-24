aux_source_directory(. DIROP_SRC)
add_library(dirop STATIC
    ${DIROP_SRC}
)
target_link_libraries(dirop
    cvector
)