cmake_minimum_required(VERSION 3.23.0)
project(GameTest)


file(GLOB_RECURSE GAME_TEST_SOURCES main.cpp)
set(EXEC_NAME snake)

add_executable(${EXEC_NAME} ${GAME_TEST_SOURCES})

target_link_libraries(${EXEC_NAME} game)

if(SANITIZERS)
	target_compile_options(${EXEC_NAME} PUBLIC -fsanitize=address -g)
	set_target_properties(${EXEC_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address")
endif()

add_custom_target(run_text_${EXEC_NAME}
	  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} text)

add_dependencies(run_text_${EXEC_NAME} ${EXEC_NAME})

add_custom_target(run_goi_${EXEC_NAME}
	  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME} goi)

add_dependencies(run_goi_${EXEC_NAME} ${EXEC_NAME})