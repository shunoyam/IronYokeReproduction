
cmake_minimum_required(VERSION 3.12)
project(run)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH  $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)

set(CMAKE_CXX_FLAGS "-Ofast -Dcxx=17")

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories($ENV{ROOTSYS})

include_directories(../src/eigen3)

set(HEADER_FILES
  ../function/LoadConfigurationFile.hpp

  ../function/UsefulFunctions.hpp
  ../function/cpp17.hpp

  ../src/class/coil/coil.hpp
  ../src/class/Bfield/Bfield.hpp
  ../src/class/svd/svd.hpp
  ../src/class/info_SVD/info_SVD.hpp
  ../function/solution_inverse_TSVD.hpp
  ../src/class/Legendre/Legendre.hpp
  ../src/class/coils/coils.hpp
  ../src/class/CoilBlocks/CoilBlocks.hpp  
  ../src/class/Bs/Bs.hpp

  ../function/Axisymmetrize3dOperaMap.hpp
  ../function/CreateIronYokeGeometry.hpp
  ../function/DrawMagneticField_TsukubaSolenoid.hpp
  ../function/ReproduceIronYoke.hpp
  )

set(SOURCE_FILES
  ../function/LoadConfigurationFile.cpp

  ../function/UsefulFunctions.cpp
  ../function/cpp17.cpp

  ../src/class/coil/coil.cpp
  ../src/class/Bfield/Bfield.cpp
  ../src/class/svd/svd.cpp
  ../src/class/info_SVD/info_SVD.cpp
  ../function/solution_inverse_TSVD.cpp
  ../src/class/Legendre/Legendre.cpp
  ../src/class/coils/coils.cpp
  ../src/class/CoilBlocks/CoilBlocks.cpp
  ../src/class/Bs/Bs.cpp

  ../function/Axisymmetrize3dOperaMap.cpp
  ../function/CreateIronYokeGeometry.cpp
  ../function/DrawMagneticField_TsukubaSolenoid.cpp
  ../function/ReproduceIronYoke.cpp

  ../main/main.cpp
  )

add_executable(run ${HEADER_FILE} ${SOURCE_FILES})
target_link_libraries(run ${ROOT_LIBRARIES} ${Boost_LIBRARIES})












