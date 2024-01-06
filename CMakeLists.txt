cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Flection VERSION 0.0.1
        LANGUAGES C CXX)

set(ExcutableName metaGen)

add_executable(${ExcutableName})

if(CMAKE_HOST_WIN32)
    set(LLVM_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/LLVM/lib/win_x64)
    set(LLVM_SHARED_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/LLVM/bin/win_x64)
    target_link_libraries(${ExcutableName} PUBLIC ${LLVM_LIBRARY_DIR}/libclang.lib)

    elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(LLVM_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/LLVM/bin/linux_x64)
    # TODO
else()
    message(FATAL_ERROR "Do not support current platform.\n")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set_target_properties(${ExcutableName} PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
src/*.cpp src/*.c include/*.hpp thirdparty/LLVM/include/*.h)
set(includes include thirdparty/LLVM/include thirdparty/CLI11)
target_include_directories(${ExcutableName} PUBLIC ${includes})
target_sources(${ExcutableName} PUBLIC ${sources})  

add_subdirectory(thirdparty/spdlog)

target_link_libraries(${ExcutableName} PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

add_subdirectory(thirdparty/inja)

target_link_libraries(${ExcutableName} PUBLIC inja)

add_custom_command(TARGET ${ExcutableName} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory  
		"${LLVM_SHARED_LIBRARY_DIR}"
		$<TARGET_FILE_DIR:${ExcutableName}>)


#setParserFlag(${ExcutableName} ${metaDir} )
