# DRP.004 Firmware

## Init submodules

```bash
cd ./Drivers
git clone --recursive https://github.com/STMicroelectronics/STM32CubeG0.git
cd ..
git pull
git submodule update --init --recursive
```
Or clone this repo with `--recursive` flag

## Issues to overcome

### Hardware

 [Hardware repository](https://github.com/MuffinKing-jpeg/DRP.004/tree/main)

### Software

- Move drivers to submodule
- Write docs
- Unit tests
- Sync control MOSFETs to adc trigger (require new HW)

## CLion configuration

### ST-Link

- Target remote: `tcp::50000`
- GDB server: `<PATH_TO_CUBE_CTL>/STLink-gdb-server/bin/ST-LINK_gdbserver`
- GDB server args: `-p 50000 -cp <PATH_TO_CUBE_CTL>/STM32CubeProgrammer/bin --swd --halt -m 0 --frequency 8000`

### J-Link

 - Target remote: `tcp::2331`
- GDB server: `<PATH_TO_JLINK_SW>/JLinkGDBServer`
- GDB server args: `-USB 0 -device STM32G031G6 -endian little -if SWD -speed 8000 -noir -LocalhostOnly -nologtofile -port 2331 -SWOPort 2332 -TelnetPort 2333`

You can generate configuration with `JLinkGDBServerExe`
