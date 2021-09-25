# HgmBT

HGM的蓝牙数据包格式(JSON)

---

## 下位机数据包格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| **Key**|Header   |DataType  |Data        |
| **Value**|HgmBT  |dt (见下文)|data(见下文)|

可以自己添加命令实现更多功能(详见 [BT代码](./HgmBT.h) )

![](../../../Image/BasicBTCommands.png)

## 数据包示例：
**获取命令长度M（被动）** （DataType == 0）
```json
{
  "Header": "Hgm",
  "DataType": "0",
  "Data": ""
}
```
返回长度M

**普通数据接收（被动）** （DataType == 3）
```json
{
  "Header": "Hgm",
  "DataType": "3",
  "Data": "Hello world! HellGateMonitor!!!"
}
```

普通数据模式下，HGM接收后在串口终端输出相应Data信息

**WiFi配置和开启（被动）** （DataType == 4）

```json
{
  "Header": "Hgm",
  "DataType": "4",
  "Data": {
    "ssid": "xxx",
    "password": "xxx"
  }
}
```

**WiFi关闭（被动）** （DataType == 5）

```json
{
  "Header": "Hgm",
  "DataType": "5",
  "Data": "Any content"
}
```

**天气等信息配置（被动）** （DataType == 6）  
API详见“ [和风天气API](https://dev.qweather.com/docs/api/) ”，若只是使用则不需要了解

```json
{
  "Header": "Hgm",
  "DataType": "6",
  "Data": {
    "lat": "39.92149",
    "lon": "116.48641",
    "key": "xxxxxxxxxxxxxxx"
  }
}
```

**B站配置（被动）** （DataType == 7）

```json
{
  "Header": "Hgm",
  "DataType": "7",
  "Data": {
    "uid": "xxx"
  }
}
```
**配置硬件监控UI（被动）** （DataType == 8）
```json
{
  "Header": "Hgm",
  "DataType": "8",
  "Data": {
    "isDefault" : "1",
    "leftTop" : "CPU",
    "leftBottom" : "GPU",
    "rightTop" : "Memory",
    "rightBottom" : "HardDisk"
  }
}
```
**default** 为 1 代表使用默认配置，为 0 代表使用新配置，并覆写配置文件  
**Data** 候选有：CPU、GPU、Memory、HardDisk、Network

<br>

#### 中间可以添加更多命令........

<br>


**空数据包** （DataType == M）

```json
{
  "Header": "Hgm",
  "DataType": "M",
  "Data": ""
}
```

---

## 上位机接收格式

同 “下位机接收格式”

---

下位机接收成功返回给对方一个JSON数据包：  
OK（DataType == 1）

```json
{
  "Header": "Hgm",
  "DataType": "1",
  "Data": "ok"
}
```

ERROR（DataType == 2）

```json
{
  "Header": "Hgm",
  "DataType": "2",
  "Data": "error"
}
```


---




