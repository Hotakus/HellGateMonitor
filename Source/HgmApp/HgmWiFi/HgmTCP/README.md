# HgmBT

HGM的TCP数据包格式(JSON)

---  

## 下位机数据包格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| **Key**|Header   |DataType  |Data        |
| **Value**|HgmBT  |dt (见下文)|data(见下文)|

<br>

**识别当前接入设备是否为HGM（被动）** （DataType == 0）
```json
{
  "Header": "HgmTCP",
  "DataType": "0",
  "Data": "HellGateMonitor"
}
```

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
    "Network" : "0",
    "Fans" : "0"
  }
}
```
1 为请求，0 为略过



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
