# DRP.004 Firmware

## Init submodules

```bash
cd ./Drivers
git clone --recursive https://github.com/STMicroelectronics/STM32CubeG0.git
cd ..
git pull
git submodule update --init --recursive
```
