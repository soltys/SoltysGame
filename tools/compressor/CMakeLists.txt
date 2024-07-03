set(TOOL_NAME tools_compressor)
add_executable(${TOOL_NAME} 
    compressor_main.cpp

    ${PROJECT_INCLUDE_DIR}/miniz/miniz.hpp
    ${PROJECT_VENDOR_DIR}/miniz/miniz.cpp
)

target_include_directories(${TOOL_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})


function(compress_file out_var)
    set(flags FORCE)
    set(args INPUT_FILE OUTPUT_FILE)
    set(listArgs)

    set(TOOL_NAME tools_compressor)
    
    cmake_parse_arguments(ARG "${flags}" "${args}" "${listArgs}" ${ARGN})
    if (NOT ARG_INPUT_FILE)
        message(FATAL_ERROR "[compress_file]: INPUT_FILE is a required argument")
    endif()
    if(NOT ARG_OUTPUT_FILE)
        message(FATAL_ERROR "[compress_file]: OUTPUT_FILE is a required argument")
    endif()

    file(REAL_PATH ${ARG_INPUT_FILE} input_f_path)
    file(REAL_PATH ${ARG_OUTPUT_FILE} out_f_path)

    get_filename_component(out_f_dir "${out_f_path}" DIRECTORY)

    add_custom_command(OUTPUT ${out_f_path}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
            COMMAND ${TOOL_NAME} ${input_f_path} ${out_f_path}
            DEPENDS "${input_f_path}" ${TOOL_NAME}
            COMMENT "Compressing file from ${input_f_path} into ${out_f_path}"
            VERBATIM)
    set(${out_var} "${ARG_OUTPUT_FILE}" PARENT_SCOPE)
endfunction()