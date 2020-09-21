# 简介

- 本项目使用PlatformIO（以下简称PIO）进行构建，源码基于 [pio-gd32f130c6](https://github.com/maxgerhardt/pio-gd32f130c6) 仓库进行开发，感谢作者为GD32F130C6提供PIO支持。

- 本项目适用于propel生产的遥控无人机遥控器，如下图。原装只能支持自家产品，不支持输出PPM。因为某宝上价格非常便宜（本人入手￥15不包邮），质量非常好，因此值得折腾一番。
![遥控器](https://img.alicdn.com/imgextra/i2/688599798/O1CN01zDUEQj2MFXEAB7gfX_!!688599798.jpg)

- 当前主要改装目的为输出PPM训练用，其次使用原有2.4G模块实现短距离无线传输。

# 遥控器简介

- 标准美国手，可调整弹性回中
- 正面上半部分6颗LED灯，分两组，一组红色，一组蓝色；四个按钮。
- 下半部分8颗LED灯，同样分两组，一组红色，一组蓝色；一个按钮。
- 背后有耳机接口，是真的耳机音频输出，改装后可以使用这个接口输出PPM信号。
- 遥控器内有两块电路板，一大一小，大的电路板负责主要的遥控功能，小的主要是多媒体音效和震动电机驱动。大电路板搭载国产GD32处理器，与STM32相似，板上引出SWD接口，可用STLink下载固件。

# 固件写入步骤

1. 解锁CPU。出厂状态下CPU锁定，无法读写固件。
2. 连接SWD接口。
3. 下载固件到GD32。

# 出厂主芯片引脚功能

## 与无线芯片BK2425连接

软件模拟SPI

功能 | 引脚 
-----|-----
CE   | PB7
CS   | PB6
SCK  | PB5
MOSI | PB4
MISO | PB3
IRQ  | ---

## 各引脚功能

功能        | 引脚     | 注
------------|----------|----
VR4         | PA0
k1          | PA1      | 此处共同使用PA1，ADC判断具体哪个按键被按下
k2          | PA1
k3          | PA1
k4          | PA1
BT_VDD1     | PA2
BT_EN       | PA3
VR1         | PA4
VR2         | PA5
k5          | PA6      | 此处共同使用PA6，ADC判断具体哪个按键被按下
k6          | PA6
k7          | PA6
k8          | PA6
BAT_DET     | PA7      | 电池电压检测
UART3_Tx    | PA8      | 蓝牙
UART1_Tx    | PA9      | 2.4G模块
UART1_Rx    | PA10     | 2.4G模块
LED_5_6     | PA11     | 小板
PWR-DET     | PA12     | 电源按钮检测
PWR-SW      | PA15     | 电源开关
UART3_Rx    | PB0      | 蓝牙
VR3         | PB1
sw_T        | PB2      | 油门设定开关，归中高电平，不归中低电平
bk2425      | PB3-7
LED_A_EN_B  | PB8      | 大板，蓝色灯组使能
LED_A_EN_R  | PB9      | 大板，红色灯组使能
buzzer      | PB10
LED_B_EN_B  | PB11     | 小板，蓝色灯组使能
LED_B_EN_R  | PB12     | 小板，红色灯组使能
LED_11_12   | PB13     | 小板
LED_9_10    | PB14     | 小板
LED_7_8     | PB15     | 小板
LED_L1L4    | PC13     | 大板左，LED1和LED4，test1
LED_L3L6    | PC14     | 大板中，LED3和LED6
LED_L2L5    | PC15     | 大板右，LED2和LED5，test2
CHRG        | PF6      | 小板
s-soc       | PF7      | 小板，直通小板音频芯片

注：7个LED灯位都是由红蓝两种LED组成，大板和小板分别有引脚控制两种颜色使能，点亮LED需要使能对应颜色并开启对应LED，例如，点亮大板上第一个LED蓝灯，需要使能LED_A_EN_B和LED_L1L4。低电平开启/使能。

# 硬件改装步骤

## PPM输出

![小板](https://img.alicdn.com/imgextra/i3/688599798/O1CN01sK08b62MFXE9O1Ktk_!!688599798.jpg)
小板左下角为音频输出接口。把C35电容去掉，靠近音频接口的一侧飞线连接到最接近排线插座焊点的那个测试点，也就是图中R30与排线插座焊点之间那个裸露的点。

# LCD显示屏
此处改动较大，小板需要去掉，暂时省略。

# 编译步骤

1. 安装python3环境
2. 使用pip安装platformio
```
pip3 install platformio
```
3. 编译
```
pio run
```

注意：第一次编译第3步会失败，因为官方没有GD32F130的支持，解决办法如下，
- 首先找到PlatformIO目录(Windows: `C:\Users\<user>\.platformio`, Unix/Max: `/home/<user>/.platformio`)
- 进入`packages`目录
- 把项目根目录里的`framework-spl.zip`解压到`packages`目录，覆盖原有的`framework-spl`目录即可

请参考以下[pio-gd32f130c6](https://github.com/maxgerhardt/pio-gd32f130c6)仓库 README 原文

## Installation

Go to your PlatformIO home folder (Windows: `C:\Users\<user>\.platformio`, Unix/Max: `/home/<user>/.platformio`). Then go into `packages`. If the folder `framework-spl` exists, delete it. 

Unpack the `framework-spl.zip` in the `packages` folder so that the directory structure is now 

```
packages/
| - framework-spl/
| |--  gd32/
| |--  platformio/
| |--  stm32/
| |--  package.json
```

(This folder contains the `GD32F1x0_Firmware_Library_v3.1.0` files)

Then attempt compilation using `pio run`. 

## IDE export 

Use `pio init --ide=<ide here>`. See [docs](https://docs.platformio.org/en/latest/userguide/project/cmd_init.html).

## Flashing

Flash the compiled `.pio\build\GD32F130C6T6\firmware.bin` after compiling using some program or an STLink (default). Run `pio run -t upload` to attempt an OpenOCD upload via an STLink with a STM32F1 target setting (no idea if this works).

## Clock init 

Starts from internal 8MHz oscillator and then uses its PLL to go to 72MHz. Selection is done statically in `system_gd32f1x0.c` in the `framework-spl` folder.

Note: The claimed system speed is a paradox. Datasheet states 48MHz max, but the GD32F1x0 device code uses up 72 MHz with a PLL multiplier of 18...

```c
static void system_clock_72m_irc8m(void)
{
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;
    /* PLL = (IRC8M/2) * 18 = 72 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC8M_DIV2 | RCU_PLL_MUL18);
    
    /* enable PLL */
    RCU_CTL0 |= RCU_CTL0_PLLEN;

    /* wait until PLL is stable */
    while(0 == (RCU_CTL0 & RCU_CTL0_PLLSTB));

    /* select PLL as system clock */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    RCU_CFG0 |= RCU_CKSYSSRC_PLL;

    /* wait until PLL is selected as system clock */
    while(0 == (RCU_CFG0 & RCU_SCSS_PLL));
}
``` 

vs "The GD32F130xx device incorporates the ARM® Cortex®-M3 32-bit processor core operating at 48 MHz frequency"

¯\_(ツ)_/¯