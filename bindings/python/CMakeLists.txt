add_library(cloudphxx SHARED lib.cpp)
set_target_properties(cloudphxx PROPERTIES SUFFIX ".so") # e.g. Mac defaults to .dylib which is not looked for by Python

# informing the Python bindings where to find Python
find_package(PythonLibs)
if (NOT PYTHON_LIBRARIES)
  message(FATAL_ERROR "
    Python libraries not found. 
    Please install them (e.g. sudo apt-get install python-dev).
  ")
endif()
target_include_directories(cloudphxx PUBLIC ${PYTHON_INCLUDE_DIRS})
target_link_libraries(cloudphxx ${PYTHON_LIBRARIES})

# informing the Python bindings where to find Boost.Python 
find_package(Boost COMPONENTS python QUIET)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "
    Boost.Python not found. 
    Please install it (e.g. sudo apt-get install libboost-python-dev).
  ")
endif()
target_link_libraries(cloudphxx ${Boost_LIBRARIES})

# requireing Blitz++
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
    #include <blitz/array.h>
    int main() {}
  " BLITZ_FOUND)
if (NOT BLITZ_FOUND)
  message(FATAL_ERROR "
    Blitz++ library not found. 
    Please install it (e.g. sudo apt-get install libblitz0-dev).
  ")
endif()

# ... where to find libclouph++
target_link_libraries(cloudphxx cloudphxx_lgrngn)

# installation (see http://www.cmake.org/pipermail/cmake/2013-March/054138.html)
execute_process (
   COMMAND ${PYTHON_EXECUTABLE} -c
   	"import site, sys; sys.stdout.write(site.PREFIXES[-1])"
   OUTPUT_VARIABLE PYTHON_PREFIX
)
file ( TO_CMAKE_PATH "${PYTHON_PREFIX}" PYTHON_PREFIX )
execute_process (
   COMMAND ${PYTHON_EXECUTABLE} -c
   	"import site, sys; sys.stdout.write(site.getsitepackages()[-1])"
   OUTPUT_VARIABLE PYTHON_SITE_DIR
)
file ( TO_CMAKE_PATH "${PYTHON_SITE_DIR}" PYTHON_SITE_DIR )
string ( REGEX REPLACE "^${PYTHON_PREFIX}/" ""
   PYTHON_SITE_DIR "${PYTHON_SITE_DIR}"
)

install ( TARGETS cloudphxx
   LIBRARY
     DESTINATION ${PYTHON_SITE_DIR}
     COMPONENT library
)
