## A simple CMake file to compile an Arduino project.
## Adjust the settings according to your board.
## The settings here work for the Arduino Uno, Rev. 3.

# Project name
project(blink)

# CMake version
cmake_minimum_required(VERSION 2.6)

# Options 
# Adjust to your board
set(MCU "atmega328p" CACHE STRING "Processor Type")
set(CPU_SPEED "16000000" CACHE STRING "Speed of the CPU")
set(PORT "/dev/ttyACM0" CACHE STRING "USB Port")
set(PORT_SPEED "115200" CACHE STRING "Serial Port Speed")
set(PIN_VARIANT "standard" CACHE STRING "Pin Selection Variant. Either standard, mega, leonardo, eightanaloginputs")
set(ARDUINO_PATH "$ENV{HOME}/programs/arduino/" CACHE PATH "Path to arduino installation")
set(ARDUINO_CORE_PATH "${ARDUINO_PATH}/hardware/arduino" CACHE PATH "Path to arduino core files")
set(PROGRAMMER "stk500v1" CACHE STRING "Programmer Type")
set(COMPILE_FLAGS "" CACHE STRING "Additional Compiler Flags")

# Set own source files
# Simply list all your C / C++ source (not header!) files here
set(SRC_FILES ${PROJECT_NAME}.cpp)

# Include directories
include_directories(
	${ARDUINO_CORE_PATH}/cores/arduino
	${ARDUINO_CORE_PATH}/variants/${PIN_VARIANT}
	/usr/lib/gcc/avr/4.3.5/include/
	/usr/lib/avr/include/
	)

# Find Arduino source files.
file(GLOB_RECURSE ARDUINO_CORE_SRC 
	${ARDUINO_CORE_PATH}/cores/arduino/*.c
	${ARDUINO_CORE_PATH}/cores/arduino/*.cpp
	)

set(CMAKE_SYSTEM_NAME Arduino)

# Compiler suite specification
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_OBJDUMP avr-objdump)
set(CMAKE_RANLIB avr-ranlib)
set(CMAKE_LINKER avr-ld)

# Compiler flags
add_definitions(-mmcu=${MCU} -DF_CPU=${CPU_SPEED})
add_definitions(-c -g -Os -Wall)
add_definitions(-fno-exceptions -ffunction-sections -fdata-sections)

# Linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")   # remove -rdynamic for C
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # remove -rdynamic for CXX
set(CMAKE_EXE_LINKER_FLAGS "-Os -Wl,--gc-sections -mmcu=${MCU}")

add_executable(${PROJECT_NAME} ${ARDUINO_CORE_SRC} ${SRC_FILES})

add_custom_target(download 
	COMMAND ${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
	COMMAND avrdude -F -p${MCU} -c${PROGRAMMER} -P${PORT} -b${PORT_SPEED} -D -Uflash:w:${PROJECT_NAME}.hex:i
	DEPENDS ${PROJECT_NAME}
	)
