# Adicione o código-fonte para o projeto
add_executable(dht22_bdl src/main.c
    src/dht22.c
    src/oled_setup.c
    src/ssd1306.c
    src/i2c_setup.c)

# Diretórios de inclusão
target_include_directories(dht22_bdl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)    

# Linkar as bibliotecas necessárias
target_link_libraries(dht22_bdl pico_stdlib
    hardware_gpio 
    hardware_i2c)

pico_add_extra_outputs(dht22_bdl)

# add url via pico_set_program_url
example_auto_set_url(dht22_bdl)