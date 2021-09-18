# HgmTCP

HGM的TCP数据包格式(JSON)

---  



## 与HGMC的通信流程
1. HGM与HGMC通过局域网TCP链接后，HGMC可由用户手动发送识别请求
2. 识别成功则HGM返回给HGMC："HellGateMonitor"
3. HGM正确响应后进入工作模式，等待HGMC的进一步操作
4. 若HGMC打开“普通模式”，则正常进行普通的TCP通信，通信内容会实时显示在HGM串口
5. 若HGMC打开“HGM模式”，则只接收和响应HGM特定的命令数据包，且不会显示内容到HGM串口
6. 若断开TCP连接，则自动关闭HGM的“硬件监控”，并等待下一次连接
7. 若HGM当前不处于硬件监控状态，则只响应普通TCP数据，并实时显示TCP数据到HGM串口 
8. 若HGM在连接状态且打开硬件监控，HGM默认每2秒向HGMC请求一次硬件数据（不建议小于两秒），连续请求失败次数过多则退出监控模式


## 下位机数据包格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| **Key**|Header   |DataType  |Data        |
| **Value**|HgmBT  |dt (见下文)|data(见下文)|


## 数据包示例
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
请求成功则接收到OK数据包，紧跟着“硬件信息”数据包

**硬件信息数据包** （DataType == 4）  
[硬件信息数据包JSON示例文件](HardwareJsonPack.json)  
若发送请求时未请求对应的硬件信息，则对应参数返回空值，若对应参数请求但返回空值，则认为其请求错误

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
