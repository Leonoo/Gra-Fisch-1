find_package(SFML 2 COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR})

# all source files
set(SRC
    main.cpp
	Character.cpp
	Character.h
)

# add the executable
add_executable(Gra-Fisch ${SRC})

target_link_libraries(Gra-Fisch ${SFML_LIBRARIES})