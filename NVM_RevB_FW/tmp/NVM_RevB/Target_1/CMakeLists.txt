# CMSIS Build CMakeLists generated on 2024-01-30T23:17:09

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET NVM_RevB)
set(CPU Cortex-M33)
set(PRJ_DIR "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB")
set(OUT_DIR "C:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/out/NVM_RevB/Target_1")
set(INT_DIR "C:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/tmp/NVM_RevB/Target_1")
set(FPU SP_FPU)
set(DSP DSP)
set(TZ TZ)
set(SECURE Non-secure)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE speed)
set(DEBUG on)
set(AS_FLAGS_GLOBAL "-masm=auto")
set(CC_FLAGS_GLOBAL "-std=gnu11 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Weverything -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=gnu++14 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Weverything -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/RTE/Device/STM32U575RITxQ/stm32u575xx_flash_ns.sct")

set(DEFINES
  STM32U575xx
  _RTE_
)

set(INC_PATHS
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/include"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/RTE/_Target_1"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Include"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/PrivateInclude"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Driver/Include"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/Keil/STM32U5xx_DFP/2.2.0/Drivers/CMSIS/Device/ST/STM32U5xx/Include"
)

set(AS_ARM_SRC_FILES
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/RTE/Device/STM32U575RITxQ/startup_stm32u575xx.s"
)

set(CC_SRC_FILES
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/BasicMathFunctions/BasicMathFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/BayesFunctions/BayesFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/CommonTables/CommonTables.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/CommonTables/CommonTablesF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/ComplexMathFunctions/ComplexMathFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/ControllerFunctions/ControllerFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/DistanceFunctions/DistanceFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/DistanceFunctions/DistanceFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/FastMathFunctions/FastMathFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/FilteringFunctions/FilteringFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/FilteringFunctions/FilteringFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/MatrixFunctions/MatrixFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/MatrixFunctions/MatrixFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/SVMFunctions/SVMFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/SVMFunctions/SVMFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/SupportFunctions/SupportFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/SupportFunctions/SupportFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/TransformFunctions/TransformFunctions.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/DSP/Source/TransformFunctions/TransformFunctionsF16.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/Keil/STM32U5xx_DFP/2.2.0/CMSIS/Driver/I2C_STM32U5xx.c"
  "C:/Users/Curtis/AppData/Local/Arm/Packs/Keil/STM32U5xx_DFP/2.2.0/CMSIS/Driver/SPI_STM32U5xx.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/RTE/Device/STM32U575RITxQ/system_stm32u5xx_ns.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/ad403x.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/ad5686.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/adc.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/delay.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/gpio.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/it.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/main.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/ospi.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/spi.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/sys_cfg.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/tim.c"
  "c:/Users/Curtis/Documents/Electronics/Projects/NVM_RevB/src/uart.c"
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
