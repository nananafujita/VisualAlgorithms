# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appVisualAlgorithms_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appVisualAlgorithms_autogen.dir/ParseCache.txt"
  "appVisualAlgorithms_autogen"
  )
endif()
