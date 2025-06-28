# DRP.004 Firmware

## Init submodules

```bash
cd ./Drivers
git clone --recursive https://github.com/STMicroelectronics/STM32CubeG0.git
cd ..
git pull
git submodule update --init --recursive
```

## Idea configuration

- Target remote: `tcp::50000`
- GDB server: `<PATH_TO_CUBE_CTL>/STLink-gdb-server/bin/ST-LINK_gdbserver`
- GDB server args: `-p 50000 -cp <PATH_TO_CUBE_CTL>/STM32CubeProgrammer/bin --swd --halt -m 0 --frequency 8000`
- 
