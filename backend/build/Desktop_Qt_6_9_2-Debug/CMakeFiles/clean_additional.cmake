# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/TrainSimulationApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/TrainSimulationApp_autogen.dir/ParseCache.txt"
  "TrainSimulationApp_autogen"
  )
endif()
