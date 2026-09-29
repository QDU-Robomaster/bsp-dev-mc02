# bsp-dev-mc02

MC02 开发板（STM32H723VGTx）的 LibXR / XRobot BSP，基于 FreeRTOS。

## 目录

```text
CtrBoard-H7_ALL.ioc       CubeMX 工程
Core/ Drivers/            CubeMX 生成的初始化代码与 ST HAL / CMSIS
Middlewares/              FreeRTOS、LibXR submodule
Modules/modules.yaml      需要的模块（`xrobot:` 固定 XRobot 版本）
Modules/sources.yaml      模块源
xrobot.lock               模块的精确 commit
User/app_main.cpp         入口：由代码生成器生成，注册硬件并调用 XROBOT_MAIN()
User/libxr_config.yaml    LibXR 外设参数（`generator:` 固定代码生成器版本）
User/xrobot.yaml          产品配置（BuzzerAlarm）
```

`Modules/<owner>/<Repo>/`、`Modules/CMakeLists.txt` 和 `User/xrobot_main.hpp` 由 `xrobot` 生成，不提交。

## 准备

```bash
git clone --recursive https://github.com/QDU-Robomaster/bsp-dev-mc02.git
cd bsp-dev-mc02
pip install xrobot==1.0.0 libxr==6.0.0   # 与 xrobot: 和 generator: 一致
xrobot setup                             # 拉取模块、检查配置、生成入口头文件
```

已克隆的仓库先运行 `git submodule update --init --recursive`。

构建需要 CMake、Ninja 和 ST 的 `starm-clang` 工具链（STM32CubeCLT 或 VS Code STM32Cube 扩展提供），`starm-clang` 须在 `PATH` 中。Preset 使用 `cmake/starm-clang.cmake`（picolibc 配置）；环境变量 `GCC_TOOLCHAIN_ROOT` 和 `CLANG_GCC_CMSIS_COMPILER` 只在把 `STARM_TOOLCHAIN_CONFIG` 改为 `STARM_HYBRID` 时使用。

## 构建

```bash
cmake --preset Debug
cmake --build --preset Debug
```

Preset 有 `Debug` 和 `Release`，输出在 `build/<preset>/CtrBoard-H7_ALL.elf`。构建前 LibXR 检查 `User/xrobot_main.hpp` 是否比配置、锁文件、入口和模块头文件新，过期时构建失败并提示对应的 `xrobot gen -c <配置>`。

修改 `User/xrobot.yaml` 或添加其他 `User/*.yaml` 产品配置的方法见 [项目管理（XRobot）](https://xrobot.work/docs/proj_man)。配置里的硬件名是 `User/app_main.cpp` 中 `XR_REGISTER` 注册的对象名（如 `fdcan1`、`can1`、`usart1`、`spi2`、`pwm_tim12_ch2`）；每个 FDCAN 同时以 `fdcanN`（`LibXR::FDCAN`）和 `canN`（`LibXR::CAN`）注册。

## 修改 CubeMX 配置后

在 CubeMX 中生成代码后，重新生成 BSP 对象（与 CI 相同的命令）：

```bash
xr_parse_ioc -d . -o .config.yaml
xr_gen_code_stm32 -i .config.yaml -o User/app_main.cpp --xrobot --libxr-config User/libxr_config.yaml
```

`User/app_main.cpp` 中 `User Code` 区域的内容会保留。提交 `User/app_main.cpp`、`User/app_main.h`、`User/flash_map.hpp` 和 `User/libxr_config.yaml`；CI 会重新生成并检查它们与提交一致。

## CI

`.github/workflows/xrobot_stm32.yml` 在 `ghcr.io/xrobot-org/docker-image-stm32:main` 中：安装固定版本的工具，重新生成并检查 BSP 对象，运行 `xrobot format --check` 和 `xrobot setup --frozen --context-ref <被构建的分支> --release-ref <目标分支>`，然后构建固件。

分支：`dev` 接收修改；`master` 只通过从 `dev` 发起的 PR 更新。目标为 `dev` 时锁定的模块提交必须在模块的 `dev` 上，目标为 `master` 或标签时必须在模块的 `master` 上。

## 许可

本仓库以 Apache-2.0 发布，见 [LICENSE](LICENSE)。随仓库分发的第三方代码保留各自的许可，见 [NOTICE](NOTICE)。
