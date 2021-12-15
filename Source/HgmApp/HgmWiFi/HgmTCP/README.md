# HgmTCP

HGM的TCP数据包格式(JSON)

---  

蓝牙默认开启，在HGMC与HGM进行TCP连接时，HGMC可手动控制蓝牙开关，
若开启投屏模式，则自动断开蓝牙连接，TCP断开连接或关闭投屏则自动开启蓝牙。
这么做的目的是 为了投屏腾出充足的内存空间，内存中接收的图像数据通过LVGL的机制，
异步刷新显示在屏幕上。  

若HGM在连接状态且打开硬件监控，HGM默认每2秒向HGMC请求一次硬件数据（不建议小于两秒），连续请求失败次数过多则退出监控模式  

## 下位机数据包格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| **Key**|Header   |DataType  |Data        |
| **Value**|HgmBT  |dt (见下文)|data(见下文)|


## 数据包示例
**识别当前接入设备是否为HGM（主动）** （DataType == 0）
```json
{
  "Header": "HgmTCP",
  "DataType": "0",
  "Data": "HellGateMonitor"
}
```
匹配后，匹配标志置为真

**从HGMC请求硬件参数（主动）** （DataType == 3）
```json
{
  "Header": "HgmTCP",
  "DataType": "3",
  "Data": {
    "CPU" : "1",
    "GPU" : "1",
    "Memory" : "1",
    "HardDisk" : "1",
    "Network" : "0"
  }
}
```


**数据源匹配（被动）** （DataType == 5）
```json
{
  "Header": "HgmTCP",
  "DataType": "5",
  "Data": "match"
}
```

1 为请求，0 为不请求  
请求成功则接收到OK数据包，紧跟着“硬件信息”数据包

**硬件信息数据包** （DataType == 4）  
[硬件信息数据包JSON示例文件](HardwareJsonPack.json)  
若发送请求时未请求对应的硬件信息，则对应参数返回空值，若对应参数请求但返回空值，则认为其请求错误（待实现）

**TCP普通数据模式（被动）** （DataType == M-1）
```json
{
  "Header": "HgmTCP",
  "DataType": "M-1",
  "Data": "Hello HellGateMonitor"
}
```
普通数据模式下，显示Data内容到HGM串口

**投屏开启** （DataType == 6）

```json
{
  "Header": "HgmTCP",
  "DataType": "6",
  "Data": {
    "cf": "JPG"  // 表明本次投屏图像格式，如JPG、PNG、RAW
  }
}
```
在投屏模式下，并收到投屏图像帧信息数据包时，则开启投屏一帧图像，每接收到一帧则投一帧，
无接收则停止。  
一帧投屏数据由三部分组成：
- 帧头（0x20 0x21 0x12，共三字节）
- 主体图像数据
  - 图像帧长度（三字节，例：0x10，0x20，0x30）
    - 则字节数：(0x10<<16) | (0x20<<8) | (0x30<<0) = 1056816 Bytes = 1032 KiB
  - 指定格式图像数据（JPG、PNG、RAW的原始数据）
- 帧尾（0x12 0x21 0x20，共三字节）
---


**投屏结束** （DataType == 7）

```json
{
  "Header": "HgmTCP",
  "DataType": "7",
  "Data": ""
  }
```

下位机接收成功返回给对方一个JSON数据包：  
OK（DataType == 1）

```json
{
  "Header": "HgmTCP",
  "DataType": "1",
  "Data": "ok"
}
```

ERROR（DataType == 2）

```json
{
  "Header": "HgmTCP",
  "DataType": "2",
  "Data": "error"
}
```
