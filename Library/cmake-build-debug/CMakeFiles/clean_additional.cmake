# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Library_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Library_autogen.dir\\ParseCache.txt"
  "Library_autogen"
  )
endif()
