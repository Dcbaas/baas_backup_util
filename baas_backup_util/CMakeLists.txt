project("baas_backup_util")

set(CMAKE_CXX_STANDARD 20)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
    "src/main.cpp"
    "src/config.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json spdlog::spdlog)
