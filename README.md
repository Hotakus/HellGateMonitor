# Hell Gate Monitor（HGM）
### 微型的MC风格多功能无线监控副屏  

---
[![LICENSE](https://img.shields.io/github/license/Hotakus/HellGateMonitor?style=flat-square)](./LICENSE)
[![BiliBili](https://img.shields.io/badge/BiliBili-Video-blue?style=flat-square&logo=Bilibili)](https://space.bilibili.com/341974201)
[![BiliBili](https://img.shields.io/badge/BiliBili-Space-pink?style=flat-square&logo=Bilibili)](https://space.bilibili.com/341974201)

![HellGateMonitor](./HellGateMonitor.png)
---

---

## 基本信息：

---
> 主控： &nbsp;  &nbsp; &nbsp; &nbsp; ESP32-PICO-D4，240Mhz，4MB Flash，512KB RAM  
> PSRAM：&nbsp; &nbsp; ESP-PSRAM64，8MB SPI RAM  
> 电源IC：&nbsp; &nbsp; &nbsp; BQ25896  
> IMU: &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; MPU6050  
> USB串口：&nbsp; CP2104    
> LDO芯片：&nbsp; XC6210B332，700mA  
> 屏幕：&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 1.14英寸 135x240分辨率IPS  
> 锂电池： &nbsp; &nbsp; &nbsp; 700mAh  
> 
> LVGL：&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;V8.1.0 dev

---
## 基本功能：
>通过蓝牙安卓APP进行Hell Gate Monitor 的 __实时控制与WiFi配置等__  
>通过WiFi对局域网PC进行实时的 __硬件信息监控__ 显示（通过我的另外一个项目 
> [HGMC]()
> ）  
>通过WiFi进行PC的 __屏幕投屏__  
>通过WiFi进行实时的 __天气与时钟显示__  
>通过WiFi进行实时的 __B站基本信息显示__（通过我的蓝牙APP进行B站配置）  

__蓝牙默认名：__ HellGateMonitorBT  
Bluetooth 和 Wi-Fi TCP 为本人规定固定格式的json数据包组成，采用命令代码方式进行数据交互
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
<br>
<br>
a