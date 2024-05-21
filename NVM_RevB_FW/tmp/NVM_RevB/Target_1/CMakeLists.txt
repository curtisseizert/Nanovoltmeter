# CMSIS Build CMakeLists generated on 2024-05-20T14:54:54

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET NVM_RevB)
set(CPU Cortex-M33)
set(PRJ_DIR "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2")
set(OUT_DIR "C:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/out/NVM_RevB/Target_1")
set(INT_DIR "C:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/tmp/NVM_RevB/Target_1")
set(FPU SP_FPU)
set(DSP DSP)
set(TZ TZ)
set(SECURE TZ-disabled)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE speed)
set(DEBUG on)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=gnu11 -O2 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wall -Wpedantic -Werror -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=gnu++14 -O2 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Wall -Wpedantic -Werror -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/RTE/Device/STM32U575RITx/stm32u575xx_flash.sct")

set(DEFINES
  STM32U575xx
  _RTE_
)

set(INC_PATHS
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/include"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/RTE/_Target_1"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/Keil/STM32U5xx_DFP/2.2.0/Drivers/CMSIS/Device/ST/STM32U5xx/Include"
)

set(AS_ARM_SRC_FILES
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/RTE/Device/STM32U575RITx/startup_stm32u575xx.s"
)

set(CC_SRC_FILES
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/RTE/Device/STM32U575RITx/system_stm32u5xx.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/acq.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/ad403x.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/ad5686.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/adc.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/cmd_handler.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/dac.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/dma.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/fifo.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/gpio.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/i2c.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/lexer.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/main.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/nvmb.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/serial_io.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/sinc.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/spi.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/sys_cfg.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/tim.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/tmp117.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB_2/src/uart.c"
)

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/Curtis/.vcpkg/artifacts/fd3d78d7/compilers.arm.armclang/6.21.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.21.0")
set(TOOLCHAIN_VERSION_MIN "6.21.0")
include ("C:/Users/Curtis/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.1/etc/AC6.6.18.0.cmake")
include ("C:/Users/Curtis/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.1/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS} ${AS_FLAGS_GLOBAL}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_SECURE} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT}\" ${LD_SECURE} ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "NVM_RevB")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})
