cmake_minimum_required(VERSION 3.3)

project(unstructured_mesh)

find_package(VTKm REQUIRED
  COMPONENTS Rendering
  OPTIONAL_COMPONENTS TBB
  )

add_executable(unstructured_mesh unstructured_mesh.cxx)
target_include_directories(unstructured_mesh PRIVATE ${VTKm_INCLUDE_DIRS})
target_link_libraries(unstructured_mesh ${VTKm_LIBRARIES})
target_compile_options(unstructured_mesh PRIVATE ${VTKm_COMPILE_OPTIONS})
