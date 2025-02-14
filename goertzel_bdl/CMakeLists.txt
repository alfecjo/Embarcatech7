# Add executable. Default name is the project name, version 0.1
add_executable(goertzel_bdl goertzel_bdl.c )

pico_set_program_name(goertzel_bdl "goertzel")
pico_set_program_version(goertzel_bdl "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(goertzel_bdl 0)
pico_enable_stdio_usb(goertzel_bdl 1)

# Add the standard library to the build
target_link_libraries(goertzel_bdl
        pico_stdlib hardware_adc)

# Add the standard include files to the build
target_include_directories(goertzel_bdl PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# create map/bin/hex file etc.
pico_add_extra_outputs(goertzel_bdl)

# add url via pico_set_program_url
example_auto_set_url(goertzel_bdl)