##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.4.0-B60] date: [Wed Dec 18 10:12:22 CST 2024] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = F7_DDS


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/gpio.c \
Core/Src/freertos.c \
Core/Src/rtc.c \
Core/Src/usart.c \
Core/Src/stm32f7xx_it.c \
Core/Src/stm32f7xx_hal_msp.c \
Core/Src/stm32f7xx_hal_timebase_tim.c \
Core/Src/HelloWorld.c \
Core/Src/uxr_transport_uart_it.c \
Core/Src/uxr_transport_usb.c \
Core/Src/serialtransport.c \
USB_DEVICE/App/usb_device.c \
USB_DEVICE/App/usbd_desc.c \
USB_DEVICE/App/usbd_cdc_if.c \
USB_DEVICE/Target/usbd_conf.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pcd_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_ll_usb.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_flash_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_dma_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_i2c_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_exti.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rtc_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart_ex.c \
Core/Src/system_stm32f7xx.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/port.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c \
microcdr/src/c/common.c \
microcdr/src/c/types/array.c \
microcdr/src/c/types/basic.c \
microcdr/src/c/types/sequence.c \
microcdr/src/c/types/string.c \
microdds/src/c/util/ping.c \
microdds/src/c/util/time.c \
microdds/src/c/profile/matching/matching.c \
microdds/src/c/profile/multithread/multithread.c \
microdds/src/c/profile/shared_memory/shared_memory.c \
microdds/src/c/profile/transport/custom/custom_transport.c \
microdds/src/c/profile/transport/stream_framing/stream_framing_protocol.c \
microdds/src/c/profile/transport/ip/ip_posix.c \
microdds/src/c/profile/transport/ip/tcp/tcp_transport_posix_nopoll.c \
microdds/src/c/profile/transport/ip/tcp/tcp_transport.c \
microdds/src/c/profile/transport/ip/udp/udp_transport_posix_nopoll.c \
microdds/src/c/profile/transport/ip/udp/udp_transport.c \
microdds/src/c/core/log/log.c \
microdds/src/c/core/serialization/xrce_header.c \
microdds/src/c/core/serialization/xrce_subheader.c \
microdds/src/c/core/serialization/xrce_types.c \
microdds/src/c/core/session/common_create_entities.c \
microdds/src/c/core/session/create_entities_bin.c \
microdds/src/c/core/session/create_entities_xml.c \
microdds/src/c/core/session/create_entities_ref.c \
microdds/src/c/core/session/object_id.c \
microdds/src/c/core/session/read_access.c \
microdds/src/c/core/session/session_info.c \
microdds/src/c/core/session/session.c \
microdds/src/c/core/session/submessage.c \
microdds/src/c/core/session/write_access.c \
microdds/src/c/core/session/stream/input_best_effort_stream.c \
microdds/src/c/core/session/stream/input_reliable_stream.c \
microdds/src/c/core/session/stream/output_best_effort_stream.c \
microdds/src/c/core/session/stream/output_reliable_stream.c \
microdds/src/c/core/session/stream/seq_num.c \
microdds/src/c/core/session/stream/stream_id.c \
microdds/src/c/core/session/stream/stream_storage.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
LWIP/App/lwip.c \
LWIP/Target/ethernetif.c \
Drivers/BSP/Components/lan8742/lan8742.c \
Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_eth.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/auth.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ccp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap_ms.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-md5.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-new.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/demand.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eui64.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipv6cp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/magic.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/mppe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/multilink.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppapi.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppcrypt.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppoe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppol2tp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppos.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/upap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/utils.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/vj.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.c \
Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.c \
Middlewares/Third_Party/LwIP/src/netif/slipif.c \
Middlewares/Third_Party/LwIP/src/netif/zepif.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ecp.c \
Middlewares/Third_Party/LwIP/src/api/err.c \
Middlewares/Third_Party/LwIP/src/api/if_api.c \
Middlewares/Third_Party/LwIP/src/api/netbuf.c \
Middlewares/Third_Party/LwIP/src/api/sockets.c \
Middlewares/Third_Party/LwIP/src/api/netdb.c \
Middlewares/Third_Party/LwIP/src/api/tcpip.c \
Middlewares/Third_Party/LwIP/src/api/api_lib.c \
Middlewares/Third_Party/LwIP/src/api/api_msg.c \
Middlewares/Third_Party/LwIP/src/api/netifapi.c \
Middlewares/Third_Party/LwIP/src/core/def.c \
Middlewares/Third_Party/LwIP/src/core/ip.c \
Middlewares/Third_Party/LwIP/src/core/pbuf.c \
Middlewares/Third_Party/LwIP/src/core/timeouts.c \
Middlewares/Third_Party/LwIP/src/core/tcp_in.c \
Middlewares/Third_Party/LwIP/src/core/altcp.c \
Middlewares/Third_Party/LwIP/src/core/inet_chksum.c \
Middlewares/Third_Party/LwIP/src/core/init.c \
Middlewares/Third_Party/LwIP/src/core/raw.c \
Middlewares/Third_Party/LwIP/src/core/tcp.c \
Middlewares/Third_Party/LwIP/src/core/memp.c \
Middlewares/Third_Party/LwIP/src/core/altcp_tcp.c \
Middlewares/Third_Party/LwIP/src/core/udp.c \
Middlewares/Third_Party/LwIP/src/core/altcp_alloc.c \
Middlewares/Third_Party/LwIP/src/core/stats.c \
Middlewares/Third_Party/LwIP/src/core/mem.c \
Middlewares/Third_Party/LwIP/src/core/sys.c \
Middlewares/Third_Party/LwIP/src/core/dns.c \
Middlewares/Third_Party/LwIP/src/core/netif.c \
Middlewares/Third_Party/LwIP/src/core/tcp_out.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
Middlewares/Third_Party/LwIP/system/OS/sys_arch.c \
Middlewares/Third_Party/LwIP/src/apps/mqtt/mqtt.c \
Core/Src/sessions.c \
Core/Src/dma.c \
Core/Src/sysmem.c \
Core/Src/syscalls.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_2.c

# ASM sources
ASM_SOURCES =  \
startup_stm32f769xx.s

# ASM sources
ASMM_SOURCES = 


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F769xx


# AS includes
AS_INCLUDES =  \
-ICore/Inc

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IUSB_DEVICE/App \
-IUSB_DEVICE/Target \
-IDrivers/STM32F7xx_HAL_Driver/Inc \
-IDrivers/STM32F7xx_HAL_Driver/Inc/Legacy \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 \
-IMiddlewares/ST/STM32_USB_Device_Library/Core/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc \
-IDrivers/CMSIS/Device/ST/STM32F7xx/Include \
-IDrivers/CMSIS/Include \
-Imicrodds/include \
-Imicrocdr/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-ILWIP/App \
-ILWIP/Target \
-IMiddlewares/Third_Party/LwIP/src/include \
-IMiddlewares/Third_Party/LwIP/system \
-IDrivers/BSP/Components/lan8742 \
-IMiddlewares/Third_Party/LwIP/src/include/netif/ppp \
-IMiddlewares/Third_Party/LwIP/src/include/lwip \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/apps \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/priv \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/prot \
-IMiddlewares/Third_Party/LwIP/src/include/netif \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/arpa \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/net \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/sys \
-IMiddlewares/Third_Party/LwIP/src/include/compat/stdc \
-IMiddlewares/Third_Party/LwIP/system/arch

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F769NIHx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASMM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASMM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
