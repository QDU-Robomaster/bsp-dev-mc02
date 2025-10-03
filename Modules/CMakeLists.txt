# Automatically include all Modules/*/CMakeLists.txt

message(STATUS "[XRobot] Scanning module directory: Modules/")

file(GLOB MODULE_DIRS RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)

foreach(MOD ${MODULE_DIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${MOD}")
        if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${MOD}/CMakeLists.txt")
            message(STATUS "[XRobot] Including module: ${MOD}")
            include("${CMAKE_CURRENT_LIST_DIR}/${MOD}/CMakeLists.txt")
        endif()
    endif()
endforeach()
