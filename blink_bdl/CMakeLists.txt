add_executable(blink_bdl
    blink_bdl.c
    )

# pull in common dependencies
target_link_libraries(blink_bdl pico_stdlib)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink_bdl pico_cyw43_arch_none)
endif()

# create map/bin/hex file etc.
pico_add_extra_outputs(blink_bdl)

# add url via pico_set_program_url
example_auto_set_url(blink_bdl)
