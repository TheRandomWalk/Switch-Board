# OS-independent macros
ifeq ($(OS),Windows_NT)
    RM = @del /Q /F
	RMDIR = -@rmdir /s /q
	MKDIR = -@mkdir
	NUL = >nul 2>&1 || (exit 0)
else
    RM = @rm -f
	RMDIR = @rmdir -rf
	MKDIR = @mkdir -p
	NUL = >/dev/null 2>&1 || true
endif

# C++ directives
GXXFLAGS += -std=c++17

# C directives
GCCFLAGS += -std=c17

# Compiler directives
CFLAGS += -o0
CFLAGS += -mcpu=cortex-m7
CFLAGS += -mthumb
CFLAGS += -mfloat-abi=hard
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -fmessage-length=0
CFLAGS += -fno-exceptions 
CFLAGS += -iquotesrc
CFLAGS += -iquotesrc/config
CFLAGS += -iquotelib/CMSIS/Core
CFLAGS += -iquotelib/CMSIS/STM32H7xx/Include
CFLAGS += -iquotelib/FreeRTOS-Kernel/include
CFLAGS += -iquotelib/FreeRTOS-Kernel/portable/GCC/ARM_CM7/r0p1
CFLAGS += -iquotelib/TinyUSB
CFLAGS += -iquotelib/TinyUSB/class
CFLAGS += -iquotelib/TinyUSB/common
CFLAGS += -iquotelib/TinyUSB/device
CFLAGS += -iquotelib/TinyUSB/host
CFLAGS += -iquotelib/TinyUSB/osal
CFLAGS += -iquotelib/TinyUSB/portable
CFLAGS += -iquotelib/TinyUSB/portable/synopsys/dwc2
CFLAGS += -iquotelib/TinyUSB/class/audio
CFLAGS += -iquotelib/TinyUSB/class/cdc
CFLAGS += -iquotelib/TinyUSB/class/dfu
CFLAGS += -iquotelib/TinyUSB/class/hid
CFLAGS += -iquotelib/TinyUSB/class/midi
CFLAGS += -iquotelib/TinyUSB/class/msc
CFLAGS += -iquotelib/TinyUSB/class/net
CFLAGS += -iquotelib/TinyUSB/class/usbtmc
CFLAGS += -iquotelib/TinyUSB/class/video
CFLAGS += -iquotelib/TinyUSB/class/vendor
CFLAGS += -DSTM32H743xx

# Linker directives
LFLAGS += -Tsrc/link.ld 

# Source files
OBJ += build/startup.o
OBJ += build/syscalls.o
OBJ += build/main.o
OBJ += build/system.o
OBJ += build/gpio.o
OBJ += build/led.o
OBJ += build/usart.o
OBJ += build/systick.o
OBJ += build/usb_descriptors.o
OBJ += build/usb_device.o
OBJ += build/usb_cdc.o
OBJ += build/usb_msc.o
OBJ += build/usb_tmc.o
OBJ += build/lib/CMSIS/STM32H7xx/Source/Templates/system_stm32h7xx.o
OBJ += build/lib/FreeRTOS-Kernel/croutine.o
OBJ += build/lib/FreeRTOS-Kernel/event_groups.o
OBJ += build/lib/FreeRTOS-Kernel/list.o
OBJ += build/lib/FreeRTOS-Kernel/queue.o
OBJ += build/lib/FreeRTOS-Kernel/stream_buffer.o
OBJ += build/lib/FreeRTOS-Kernel/tasks.o
OBJ += build/lib/FreeRTOS-Kernel/timers.o
OBJ += build/lib/FreeRTOS-Kernel/portable/MemMang/heap_5.o
OBJ += build/lib/FreeRTOS-Kernel/portable/GCC/ARM_CM7/r0p1/port.o
OBJ += build/lib/TinyUSB/tusb.o
OBJ += build/lib/TinyUSB/common/tusb_fifo.o
OBJ += build/lib/TinyUSB/device/usbd.o
OBJ += build/lib/TinyUSB/device/usbd_control.o
OBJ += build/lib/TinyUSB/class/audio/audio_device.o
OBJ += build/lib/TinyUSB/class/cdc/cdc_device.o
OBJ += build/lib/TinyUSB/class/dfu/dfu_device.o
OBJ += build/lib/TinyUSB/class/dfu/dfu_rt_device.o
OBJ += build/lib/TinyUSB/class/hid/hid_device.o
OBJ += build/lib/TinyUSB/class/midi/midi_device.o
OBJ += build/lib/TinyUSB/class/msc/msc_device.o
OBJ += build/lib/TinyUSB/class/net/ecm_rndis_device.o
OBJ += build/lib/TinyUSB/class/net/ncm_device.o
OBJ += build/lib/TinyUSB/class/usbtmc/usbtmc_device.o
OBJ += build/lib/TinyUSB/class/vendor/vendor_device.o
OBJ += build/lib/TinyUSB/class/video/video_device.o
OBJ += build/lib/TinyUSB/portable/synopsys/dwc2/dcd_dwc2.o

build: build/firmware.bin

build/firmware.bin: build/firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

build/firmware.elf: $(OBJ)
	arm-none-eabi-g++ $(OBJ) $(GXXFLAGS) $(CFLAGS) $(LFLAGS) -o $@

build/%.o: src/%.cpp
	$(MKDIR) build $(NUL)
	arm-none-eabi-g++ $< $(GXXFLAGS) $(CFLAGS) -c -o $@

build/%.o: src/%.c
	$(MKDIR) build $(NUL)
	arm-none-eabi-gcc $< $(CXXFLAGS) $(CFLAGS) -c -o $@

build/lib/%.o: lib/%.c
	$(MKDIR) "$(@D)" $(NUL)
	arm-none-eabi-gcc $< $(CXXFLAGS) $(CFLAGS) -c -o $@

flash: build/firmware.bin
	st-flash --reset --freq=24000 write $< 0x8000000

clean:
	$(RMDIR) build
