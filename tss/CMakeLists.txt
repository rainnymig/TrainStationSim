include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(TrainStationSim main.cpp 
				"INIReader.h" 
				"passenger.h" 
				"stage.h" 
				"manageSystem.h" 
				"train.h" 
				"manageSystem.cpp" 
				"train.cpp" 
				"passengerSpawner.h" 
				"clock.h" 
				"activity.h" "passenger.cpp" "event.h" "event.cpp" "boardingChecklist.h" "boardingChecklist.cpp")

target_link_libraries(TrainStationSim ${CONAN_LIBS})

add_custom_command(TARGET TrainStationSim POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					"${CMAKE_CURRENT_SOURCE_DIR}/data/default.ini"
					"${CMAKE_CURRENT_SOURCE_DIR}/data/default_schedule.json"
					"${CMAKE_CURRENT_BINARY_DIR}/bin/")
