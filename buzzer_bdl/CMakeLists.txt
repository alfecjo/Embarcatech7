add_executable(buzzer_bdl
        buzzer_bdl.c
        )

# pull in common dependencies and additional pwm hardware support
target_link_libraries(buzzer_bdl pico_stdlib hardware_pwm hardware_clocks)

# create map/bin/hex file etc.
pico_add_extra_outputs(buzzer_bdl)

# add url via pico_set_program_url
example_auto_set_url(buzzer_bdl)
