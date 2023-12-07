project(CoreEngine)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/Scene.h
    ${HEADER_DIR}/SceneObject.h
    ${HEADER_DIR}/Square.h
	${HEADER_DIR}/Observer.h
    ${HEADER_DIR}/GameState.h
)

set (SOURCES
    ${SOURCE_DIR}/Scene.cpp
    ${SOURCE_DIR}/SceneObject.cpp
    ${SOURCE_DIR}/Square.cpp
	${SOURCE_DIR}/Observer.cpp
    ${SOURCE_DIR}/GameState.cpp
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