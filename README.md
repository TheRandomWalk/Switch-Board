# Open-source Switch Board

## Introduction
This open-source project aims to create a switch board useful to automate tasks that involve power supplies, digital multimeters, or source measure units.

The initial [prototype](https://therandomwalk.org/wp/designing-a-switch-board-part-1/) was based on ESP32, and accepted for crowdfunding on [Crowdsupply](https://www.crowdsupply.com/). While working on the firmware, I made the decision to switch from using an ESP32 to an STM32 in order to incorporate [VXI-11](https://www.vxibus.org/specifications.html) ethernet and [USBTMC](https://www.usb.org/document-library/test-measurement-class-specification) connectivity. Additionally, the STM32 offered an increased number of peripherals and pins, which were comparatively restricted in the ESP32.

## Development

I am currently using the [NUCLEO-H743ZI](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) as test platform, but the final board may use a different STM32 microcontroller depending on factors such as availability, price, pin count, size, etc.

## To Do

- [x] System setup
  - [x] Startup code
  - [x] RCC setup
  - [x] Syscalls
  - [x] GPIO setup
- [x] FreeRTOS
- [x] UART HAL
- [ ] USB HAL
  - [x] CDC serial device
  - [x] MSC disk
  - [ ] USBTMC
- [ ] Ethernet HAL
- [ ] ADC HAL
- [ ] Logging
- [ ] CLI
- [ ] TCP/IP stack
- [ ] VXI-11
- [ ] SCPI parser
