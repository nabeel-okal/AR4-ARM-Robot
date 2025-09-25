# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AR4_PickAndPlace_autogen"
  "CMakeFiles/AR4_PickAndPlace_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/AR4_PickAndPlace_autogen.dir/ParseCache.txt"
  )
endif()
