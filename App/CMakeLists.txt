project(App)

set (SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME}
    ${SRC}
)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
        $<BUILD_INTERFACE:${MY_LIB_HEADER}>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CoreEngine
	PathFindingAStar
	Content
)