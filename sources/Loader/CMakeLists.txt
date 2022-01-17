# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Loader)

include_directories(../common/_VS_KEIL/CMSIS
                    ../common/_VS_KEIL/FatFS
                    ../common/_VS_KEIL/HAL
                    ../common/_VS_KEIL/USBH
                    ../common/_VS_KEIL/std_includes
                             src
                             src/Hardware/FatFS
                             src/Hardware/HAL
                             src/Hardware/USBH
                    ../Panel/src
                    )
                    
add_definitions(-DSTM32F401xE -DLOADER)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(/wd4159)    # #pragma pack(pop,...): has popped previously pushed identifier xxx
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4820)    # 'xxx': '4' bytes padding added after data member 'yyy'
add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C function under -EHc.
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
add_compile_options(/wd5219)    # implicit conversion from 'xxx' to 'float', possible loss of data
add_compile_options(/wd5220)    # a non-static data member with a volatile qualified type no longer implies
add_compile_options(/wd26812)   # The enum type %type% is unscoped. Prefer 'enum class' over 'enum' (Enum.3)


file(GLOB SRC            ../Panel/src/defines.h
                                  src/*.*)
file(GLOB HAL            ../common/_VS_KEIL/HAL/stm32f4xx_hal.*
                         ../common/_VS_KEIL/HAL/stm32f4xx_hal_cortex.*
                         ../common/_VS_KEIL/HAL/stm32f4xx_hal_rcc.*
                         ../common/_VS_KEIL/HAL/stm32f4xx_hal_gpio.*)
# file(GLOB HARDWARE                src/Hardware/*.*)
# file(GLOB HARDWARE_FATFS          src/Hardware/FatFS/*.*)
# file(GLOB HARDWARE_HAL   ../Panel/src/Hardware/HAL/HAL.h
#                                   src/Hardware/HAL/*.*)
# file(GLOB HARDWARE_USBH           src/Hardware/USBH/*.*)

source_group(src            FILES ${SRC})
source_group(HAL            FILES ${HAL})
# source_group(Hardware       FILES ${HARDWARE})
# source_group(Hardware/FatFS FILES ${HARDWARE_FATFS})
# source_group(Hardware/HAL   FILES ${HARDWARE_HAL})
# source_group(Hardware/USBH  FILES ${HARDWARE_USBH})

add_library(${PROJECT_NAME}
                    ${SRC}
                    ${HAL}
#                    ${HARDWARE}
#                    ${HARDWARE_FATFS}
#                    ${HARDWARE_HAL}
#                    ${HARDWARE_USBH}
                    )
