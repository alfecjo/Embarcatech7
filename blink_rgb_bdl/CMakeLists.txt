add_executable(blink_rgb_bdl
        blink_rgb_bdl.c
)

# pull in common dependencies
target_link_libraries(blink_rgb_bdl pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink_rgb_bdl)

# call pico_set_program_url to set path to example on github, so users can find the source for an example via picotool
example_auto_set_url(blink_rgb_bdl)
