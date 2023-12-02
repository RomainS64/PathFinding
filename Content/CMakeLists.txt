project(Content)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/AStarBoard.h
)

set (SOURCES
    ${SOURCE_DIR}/AStarBoard.cpp
)

add_library(${PROJECT_NAME}
    STATIC
        ${HEADERS}
        ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${HEADER_DIR}>
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CoreEngine
	PathFindingAStar
)