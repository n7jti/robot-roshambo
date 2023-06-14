# (C) Alan Ludwig All rights reserved

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
    main.cpp
    uart.cpp
    cmd_parser.cpp
    game.cpp
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
