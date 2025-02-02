project("baas_backup_util")

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    "src/main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)