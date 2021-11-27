#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tmxparser" for configuration "Debug"
set_property(TARGET tmxparser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(tmxparser PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libtmxparser.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libtmxparser.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS tmxparser )
list(APPEND _IMPORT_CHECK_FILES_FOR_tmxparser "${_IMPORT_PREFIX}/lib/libtmxparser.dll.a" "${_IMPORT_PREFIX}/bin/libtmxparser.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
