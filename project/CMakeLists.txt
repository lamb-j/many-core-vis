cmake_minimum_required(VERSION 3.6)

set(VTKm_DIR "/home/users/jlambert/my_build/lib")

#Find the VTK-m package
find_package(VTKm REQUIRED QUIET
  OPTIONAL_COMPONENTS Serial CUDA TBB
  )

if(VTKm_CUDA_FOUND)
  set(old_nvcc_flags ${CUDA_NVCC_FLAGS})
  set(old_cxx_flags ${CMAKE_CXX_FLAGS})
  vtkm_setup_nvcc_flags( old_nvcc_flags old_cxx_flags)
  vtkm_disable_troublesome_thrust_warnings()

  # Cuda compiles do not respect target_include_directories
  cuda_include_directories(${VTKm_INCLUDE_DIRS})
  cuda_add_executable(sobel sobel.cu)

  set(CUDA_NVCC_FLAGS ${old_nvcc_flags})
  set(CMAKE_CXX_FLAGS ${old_cxx_flags})
else()
  add_executable(sobel sobel.cxx sobel_funcs.cxx)
endif()

target_include_directories(sobel PRIVATE ${VTKm_INCLUDE_DIRS})
target_link_libraries(sobel PRIVATE ${VTKm_LIBRARIES})
target_compile_options(sobel PRIVATE ${VTKm_COMPILE_OPTIONS})
