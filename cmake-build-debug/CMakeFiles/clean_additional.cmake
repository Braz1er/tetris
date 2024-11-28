# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TTT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TTT_autogen.dir\\ParseCache.txt"
  "TTT_autogen"
  )
endif()
