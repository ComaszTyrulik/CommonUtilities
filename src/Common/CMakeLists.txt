include("${PROJECT_CONFIG_PATH}/Lib/config.cmake")

set(
	LIB_HEADERS_LIST
	"Exceptions.h"
	"Exceptions/FilesystemException.h"
	"Factories.h"
	"Filesystem/Filesystem.h"
	"Filesystem/IFilesystem.h"
	"Filesystem/Types.h"
	"Helpers.h"
	"IdGenerators/IUuIdGenerator.h"
	"IdGenerators/UuId4Generator.h"
	"Types.h"
	"Utils/EnumUtils.h"
	"Utils/GeneralUtils.h"
	"Utils/Hasher.h"
	"Utils/PointersUtils.h"
	"Utils/ThreadUtils/AsyncTaskExecutor.h"
	"Utils/Time.h"
)
set(
	LIB_SRC_LIST
	"Exceptions/FilesystemException.cpp"
	"Filesystem/Filesystem.cpp"
	"IdGenerators/UuId4Generator.cpp"
	"Utils/Time.cpp"
)

list(TRANSFORM LIB_HEADERS_LIST PREPEND ${LIB_HEADERS_PREFIX})
list(TRANSFORM LIB_SRC_LIST PREPEND ${LIB_SRC_PREFIX})

add_library(${LIB_TARGET_NAME} STATIC "${LIB_SRC_LIST}" "${LIB_HEADERS_LIST}")
target_include_directories(${LIB_TARGET_NAME} PUBLIC "${LIB_INCLUDE_DIR}")
target_compile_features(${LIB_TARGET_NAME} PUBLIC cxx_std_17)

target_link_libraries(
	${LIB_TARGET_NAME}
    PUBLIC
        ${CT_VENDOR_XXHASH}
		CONAN_PKG::fmt
	PRIVATE
        CONAN_PKG::stduuid
)

set_compiler_options(${LIB_TARGET_NAME})

target_precompile_headers(
	${LIB_TARGET_NAME}
	PRIVATE
        <memory>
        <string_view>
        <filesystem>
        <cstdint>
        <string>
        <map>
        <unordered_map>
        <chrono>
        <map>
        <string>
        <vector>
        <fmt/format.h>
        <xxHash/xxhash.h>
)

if(DEFINED CT_COMMON_ENABLE_DEBUG)
    target_compile_definitions(${LIB_TARGET_NAME} PUBLIC CT_DEBUG)
endif()

# Group files into proper folders - for IDE
group_files("${LIB_HEADERS_LIST}" "${LIB_INCLUDE_DIR}")
group_files("${LIB_SRC_LIST}" "${LIB_SRC_DIR}")

configure_file("${LIB_HEADERS_PREFIX}/Resources.h.in" "${LIB_HEADERS_PREFIX}/Resources.h")

add_library(CT::common_utils ALIAS ${LIB_TARGET_NAME})
