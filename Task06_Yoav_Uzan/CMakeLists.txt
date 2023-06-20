# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)
project ("Task06_Yoav_Uzan")
# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
 # cmake_policy(SET CMP0141 NEW)
  #set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()
 

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_C_EXTENSIONS OFF)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
   add_compile_options (/W3 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Task06_Yoav_Uzan "src/main.cpp" "src/Location.cpp")

# Include sub-projects.
add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)
