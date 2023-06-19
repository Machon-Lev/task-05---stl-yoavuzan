# CMakeList.txt : CMake project for Task06_Yoav_Uzan, include source and define
# project specific logic here.
#

# Add source to this project's executable.

#add_executable (Task06_Yoav_Uzan "Task06_Yoav_Uzan.cpp" "Task06_Yoav_Uzan.h")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
 # set_property(TARGET Task06_Yoav_Uzan PROPERTY CXX_STANDARD 20)
#endif()

# TODO: Add tests and install targets if needed.


add_executable (Task06_Yoav_Uzan "src/main.cpp" "src/Location.cpp")

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)
