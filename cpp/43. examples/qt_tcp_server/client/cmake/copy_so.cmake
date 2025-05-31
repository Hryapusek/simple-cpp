# copy_dlls.cmake
message(STATUS "Searching so in ${SEARCH_DIR}")
file(GLOB_RECURSE DLL_FILES "${SEARCH_DIR}/*.so*")

foreach(DLL ${DLL_FILES})
    message(STATUS "Copying ${DLL} to ${OUTPUT_DIR}")
    file(COPY "${DLL}" DESTINATION "${OUTPUT_DIR}")
endforeach()
