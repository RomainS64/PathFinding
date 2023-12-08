project(CoreEngine)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/Scene.h
    ${HEADER_DIR}/SceneObject.h
    ${HEADER_DIR}/Square.h
	${HEADER_DIR}/Event.h
    ${HEADER_DIR}/InputSystem.h
	${HEADER_DIR}/Button.h
)

set (SOURCES
    ${SOURCE_DIR}/Scene.cpp
    ${SOURCE_DIR}/SceneObject.cpp
    ${SOURCE_DIR}/Square.cpp
	${SOURCE_DIR}/Event.cpp
    ${SOURCE_DIR}/InputSystem.cpp
	 ${SOURCE_DIR}/Button.cpp
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