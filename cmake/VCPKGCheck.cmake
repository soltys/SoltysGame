if(NOT DEFINED ENV{VCPKG_ROOT})
    message(FATAL_ERROR "Enviroment var: VCPKG_ROOT is not defined")
endif(NOT DEFINED ENV{VCPKG_ROOT})

if(NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
    message(FATAL_ERROR "Enviroment var: VCPKG_DEFAULT_TRIPLET is not defined")
endif()

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()