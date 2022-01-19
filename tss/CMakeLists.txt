include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(TrainStationSim main.cpp 
				"INIReader.h" 
				"passenger.h" 
				"train.h" 
				"train.cpp" 
				"passengerSpawner.h" 
				"clock.h" 
				"activity.h" 
				"passenger.cpp" 
				"event.h" 
				"event.cpp" 
				"boardingChecklist.h" 
				"boardingChecklist.cpp" 
				"station.h" 
				"trainPassengerSpawner.h" 
				"trainPassengerSpawner.cpp" 
				"passengerManager.h" 
				"passengerManager.cpp" 
				"id.h" 
				"trainManager.h" 
				"trainManager.cpp" 
				"space.h" 
				"spaceLayout.cpp" 
				"space.cpp" 
				"spaceLayout.h" 
				"activity.cpp" 
				"passengerState.h" 
				"id.cpp" 
				"platform.h" 
				"platform.cpp" 
				"clock.cpp")

target_link_libraries(TrainStationSim ${CONAN_LIBS})

add_custom_command(TARGET TrainStationSim POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					"${CMAKE_CURRENT_SOURCE_DIR}/data/default.ini"
					"${CMAKE_CURRENT_SOURCE_DIR}/data/default_schedule.json"
					"${CMAKE_CURRENT_BINARY_DIR}/bin/")
