set(TOOL_NAME tools_merge_pack_json)
add_executable(${TOOL_NAME} 
    merge_pack_json_main.cpp

    ${PROJECT_INCLUDE_DIR}/args/args.hpp
    ${PROJECT_INCLUDE_DIR}/nlohmann/json.hpp
)

target_include_directories(${TOOL_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

function(merge_pack_json out_var)
    set(flags)
    set(args OUTPUT_FILE)
    set(listArgs FILES)

    set(TOOL_NAME tools_merge_pack_json)
    
    cmake_parse_arguments(ARG "${flags}" "${args}" "${listArgs}" ${ARGN})
    if (NOT ARG_FILES)
        message(FATAL_ERROR "[merge_pack_json]: FILES is a required argument")
    endif()
    if (NOT ARG_OUTPUT_FILE)
        message(FATAL_ERROR "[merge_pack_json]: OUTPUT_FILE is a required argument")
    endif()
    
    file(REAL_PATH ${ARG_OUTPUT_FILE} out_f_path)

    get_filename_component(out_f_dir "${out_f_path}" DIRECTORY)
    list(JOIN ARG_FILES " " ARG_FILES)
    add_custom_command(OUTPUT ${out_f_path}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${out_f_dir}"
            COMMAND ${TOOL_NAME} -o ${ARG_OUTPUT_FILE} -- ${ARG_FILES} 
            DEPENDS ${ARG_FILES} ${TOOL_NAME}
            COMMENT "Merging ${ARG_FILES}"
            VERBATIM)
    set(${out_var} "${ARG_OUTPUT_FILE}" PARENT_SCOPE)
endfunction()