# 8 Channel ADC to UART Stream

An STM32F401CC-based 8-channel ADC converter and UART transmitter, prototyped as a cost-effective feasibility test for a planned sEMG signal acquisition system for a group thesis project. Builds on an earlier ATmega328p iteration: https://github.com/J-P-Q/adc8Channel


## Hardware

- STM32F401cc (Black Pill Dev Board)
- UART TTL to USB adapter

## How It Works

- Interrupt-driven continuous 8-channel ADC conversion, streaming UART packets in parallel after each channel conversion.
- Sampling frequency configurable via timer peripheral period (1ms / 0.5ms to 1kHz / 2kHz).
- Timer interrupt triggers channel 0's conversion; each subsequent channel is triggered by the ADC ISR.
- ADC ISR enables the UART ISR to transmit newly converted data. UART ISR disables itself once the ring buffer is empty, preventing a block on constant interrupts when the UART data register is empty but no data remains to send.
- A separate PLL branch increases the timing margin within the 0.5ms sampling window, opening the door to running computation on-MCU before transmission (in anticipation of the ATmega328p to STM32F401CC hardware upgrade).

## Testing

Inputs tested using potentiometers on 2 channels at a time, with the remaining channels held at fixed 3.3V or 0V. Output verified using a pyserial-based Python script: https://github.com/J-P-Q/rPiUart

## Status

Currently functions as a raw ADC-to-UART stream to a receiver (planned to be a Raspberry Pi). The STM32 upgrade opens the possibility of pre-transmission computation on-MCU to reduce receiver-side load. The PLL branch exists to create timing margin for this, but on-MCU computation itself is not yet implemented.

## Build / Setup

- PlatformIO (VS Code)

## Demo

<link>

