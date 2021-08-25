# Hell Gate Monitor（HGM）
### 微型的MC风格多功能无线监控副屏  

---
[![LICENSE](https://img.shields.io/github/license/Hotakus/HellGateMonitor?label=LICENSE&logo=GNU&style=flat-square)](./LICENSE)
[![BiliBili](https://img.shields.io/badge/Kicad-硬件原理图-yellow?style=flat-square&logo=Files)](Hardware)
[![BiliBili](https://img.shields.io/badge/BiliBili-视频介绍-blue?style=flat-square&logo=Bilibili)](https://space.bilibili.com/341974201)
[![BiliBili](https://img.shields.io/badge/BiliBili-我的空间-red?style=flat-square&logo=Bilibili)](https://space.bilibili.com/341974201)
[![BiliBili](https://img.shields.io/badge/IDE-VisualStudio-blueviolet?style=flat-square&logo=VisualStudio)](https://visualstudio.microsoft.com/zh-hans/vs/)


<p align="center"> 
<img src="Image/HellGateMonitor.png"/>
</p>

![HellGateMonitor](Image/HellGateMonitor.png)

---

## 基本信息：

> 主控: &emsp; &emsp; ESP32-PICO-D4，240Mhz，4MB Flash，512KB RAM  
> PSRAM: &emsp;ESP-PSRAM64，8MB SPI RAM  
> 电源IC: &emsp; &nbsp;BQ25896  
> IMU: &emsp; &emsp; &nbsp;MPU6050  
> USB串口:&emsp;CP2104    
> LDO芯片:&emsp;XC6210B332，700mA  
> 屏幕: &emsp; &emsp; 1.14英寸 135x240分辨率IPS  
> 锂电池:&emsp; &nbsp; 700mAh  
>

从硬件上看，ESP32系列只要支持**PSRAM**，则代码通用。 

---
## 基本功能：
>通过蓝牙安卓APP进行Hell Gate Monitor 的 __实时控制与WiFi配置等__  
>通过WiFi对局域网PC进行实时的 __硬件信息监控__ 显示（通过我的另外一个项目 
> [HGMC]() 后续考虑Linux版本
> ）  
>通过WiFi进行PC的 __屏幕投屏__  
>通过WiFi进行实时的 __天气与时钟显示__  
>通过WiFi进行实时的 __B站基本信息显示__（通过我的蓝牙APP进行B站配置）  

__蓝牙默认名：__ HellGateMonitorBT  
Bluetooth 和 Wi-Fi TCP 与上位机通信的数据包格式为本人规定的固定格式的json数据包组成，采用命令代码方式进行数据交互
，可通过命令和固件定制，添加更多功能。  

[HGM 的蓝牙JSON数据包格式](./Source/HgmApp/HgmBT/README.md)  
[HGM 的WiFi TCP JSON数据包格式]

---

## 项目克隆：
项目使用了 __子模块__，clone 时要加 __--recurse-submodules__  
一、需要为你的Github账号配置 SSH key（方法请百度）
```shell
git clone --recurse-submodules git@github.com:Hotakus/HellGateMonitor.git
```
二、不需要配置 SSH key
```shell
git clone --recurse-submodules https://github.com/Hotakus/HellGateMonitor.git
```

---

## 项目基本结构：
下位机所有的程序源码都放在Source文件夹下  
![HellGateMonitor](Image/SourceStruct.png)  
LVGL源码采用子模块的方式引用到此项目中，这样可以方便的对LVGL版本进行实时同步更新。  
另外，由于此项目使用的是Arduino平台，所以在使用此项目前，你应该先安装指定库：
* **ArduinoJson** （解析/打包JSON数据）
* **TFT_eSPI** （屏幕驱动库）
* **TJpg_Decoder**（JPG解码库）
* **MPU6050_light** （MPU6050 轻量库）  
* **ESP32Time** （本地RTC库）  

另外，你应该在Arduino的 File-->preferences中 添加乐鑫的ESP32板包：
```shell
https://dl.espressif.com/dl/package_esp32_index.json
```

当然，不能直接在Arduino的官方IDE中直接编译项目，因为它的项目管理能力太差了。
我们使用Visual Studio 2019作为开发环境，这里也不推荐vscode，理由同Arduino官方IDE。

---

## 开始项目编译：
如果上述工作都正确完成了，那么接下来可以编译项目了。  
首先，你应该在 VS2019 的“扩展”--“管理扩展”中，搜索并添加Arduino的扩展，
扩展安装方法不赘述，关于VS2019的Arduino扩展，请自行摸索一遍，再对项目使用。

现在，我默认你已经搞清楚了Arduino的扩展，接下来找到vMicro按照我下图进行简单配置。

![ArduinoConfig](Image/ArduinoConfig.png)  
我之所以选这个是因为这个开发板环境和此项目几乎完美契合。

然后，将项目Debug改为Release，不然项目跑不起来。  
__最后：__  
![tb](Image/tb.png)

如果编译烧写正常，那么串口会出现以下信息(115200)：  
![HGM](Image/HGM.png)  
则项目构建完成。

---

## HGM的初次上电启动流程（重要）：
HGM的上电时需要对各个功能组件进行检查：

- **Bluetooth**（用于HGM的控制和配置等）
- **Config**（初次启动没有任何配置文件，所以首次运行到这里就会failed，用[HGMA]()配置）
- **WiFi**（HGM的各个功能基本依赖于此，非常重要，必须进行配置，所以配置文件非常重要）
- **Time**（基本时钟矫正，开启后每12小时矫正一次）
- **Weather**（天气组件，同样依赖于配置文件，每1小时获取一次）
- **BiliBili**（B站组件，同样依赖于配置文件，每1小时获取一次B站信息）



---

## 部分功能上手配置说明：
### 1、如何配置并使用局域网PC硬件监控功能（HGM核心功能）
需要使用我的PC上位机配套项目：[HGMC（TODO）]()   
要想使用PC硬件监控功能，那么必须要配合上位机实现，
参考我的另外一个开源项目[HGMC（TODO）]()（PC端硬件监控和HGM投屏管理中心软件），
使用[HGMC]()对PC进行监控或投屏，监控数据会实时发送给HGM，投屏功能可选择开启。

### 2、如何配置并使用天气功能
天气功能所使用的API为“ [和风天气](https://id.qweather.com) ”提供的API
，要想使用天气功能，
那么你必须去“ [和风天气控制台](https://id.qweather.com/#/login?redirect=https%3A%2F%2Fconsole.qweather.com) ”创建应用，
然后获得APP key（免费），这个key是天气功能开启的关键，HGM默认不开启天气功能，要想使用天气功能，
需要获得key后，用[HGMA]()（HGM的安卓配置APP）配置HGM，即可使用。

### 3、如何使用安卓APP配置和控制HGM
需要使用我的安卓APP配套项目：[HGMA（TODO）]()   
**HGMA**可以干什么？
* 配置WiFi（配置后自动在SPIFFS里生成 **/wifi.conf** 文件，SSID和password）
* 配置天气API（配置后自动在SPIFFS里生成 **/weather.conf** 文件，包括APP key和天气获取的默认地区等信息）
* 配置B站信息（配置后自动在SPIFFS里生成 **/bilibili.conf** 文件，即你的B站UID、头像地址等信息）
* 配置”硬件监控UI“
* 模拟操控HGM
* 提供简单的蓝牙调试功能，不是HGM也能用

配置完成后，以后每次启动HGM都会优先读取SPIFFS的各个配置文件，以后不用再打开HGMA，除非需要二次配置。

---

## FA♂Q
#### Q: 成本是多少？
A：TODO



---


<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
