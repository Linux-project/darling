project(keymgr)

cmake_minimum_required(VERSION 2.4.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdinc")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -nostdlib")

include_directories(${CMAKE_SOURCE_DIR}/libc/fbsdcompat)
include_directories(${CMAKE_SOURCE_DIR}/kernel/libsyscall/wrappers)
include_directories(${CMAKE_SOURCE_DIR}/src/libc/darwin)

add_definitions(-DHAVE_STDINT_H=1)

set(keymgr_sources
	keymgr.c
)

set(DYLIB_INSTALL_NAME "/usr/lib/system/libkeymgr.dylib")
add_circular(keymgr FAT
	SOURCES
		 ${keymgr_sources}
	SIBLINGS
		system_c
		system_dyld
		system_malloc
		system_pthread
		platform
		system_kernel
)
#target_link_libraries(keymgr PRIVATE system_c system_dyld system_malloc system_pthread)
#make_fat(keymgr)

add_darling_static_library(keymgr_static SOURCES ${keymgr_sources})
make_fat(keymgr_static)

install(TARGETS keymgr DESTINATION libexec/darling/usr/lib/system)
