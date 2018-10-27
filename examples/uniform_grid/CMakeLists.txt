cmake_minimum_required(VERSION 3.3)

project(uniform_grid)

find_package(VTKm REQUIRED
  COMPONENTS Rendering
  OPTIONAL_COMPONENTS TBB
  )

add_executable(uniform_grid uniform_grid.cxx)
target_include_directories(uniform_grid PRIVATE ${VTKm_INCLUDE_DIRS})
target_link_libraries(uniform_grid ${VTKm_LIBRARIES})
target_compile_options(uniform_grid PRIVATE ${VTKm_COMPILE_OPTIONS})
