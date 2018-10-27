cmake_minimum_required(VERSION 3.3)

project(io)

find_package(VTKm REQUIRED
  COMPONENTS Rendering
  OPTIONAL_COMPONENTS TBB
  )

add_executable(io io.cxx)
target_include_directories(io PRIVATE ${VTKm_INCLUDE_DIRS})
target_link_libraries(io ${VTKm_LIBRARIES})
target_compile_options(io PRIVATE ${VTKm_COMPILE_OPTIONS})
