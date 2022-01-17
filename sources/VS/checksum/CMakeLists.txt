project (checksum)

file(GLOB SRC  *.*)

source_group(src                   FILES ${SRC})

add_executable(${PROJECT_NAME}
                        ${SRC}
                        )
