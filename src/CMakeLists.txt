find_package(SFML 2 COMPONENTS system window graphics)
include_directories(${SFML_INCLUDE_DIR})

add_definitions( -D_USE_MATH_DEFINES )

# all source files
set(SRC
    main.cpp
	Character.cpp
	Character.h
	Piranha.cpp
	Piranha.h
	BlasenAttacke.cpp
	BlasenAttacke.h
	Collision.cpp
)

# add the executable
add_executable(Gra-Fisch ${SRC})

target_link_libraries(Gra-Fisch ${SFML_LIBRARIES})

