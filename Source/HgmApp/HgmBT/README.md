# HgmBT

HGM的蓝牙数据包格式(JSON)

---

## 下位机接收格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| __Key__|Header   |DataType  |Data        |
| __Value__|Hgm  |dt (见下文)|data(见下文)|

可以自己添加命令实现更多功能(详见代码)

## JSON数据包例子：
**WiFi配置和开启** （DataType == 0）
```json
{"Header": "Hgm","DataType": "0","Data": { "ssid": "xxx", "password": "xxx" }}
```
**WiFi关闭** （DataType == 1）
```json
{"Header": "Hgm","DataType": "1", "Data": "Any content"}
```
**天气等信息配置** （DataType == 2）  
API详见“ [和风天气API](https://dev.qweather.com/docs/api/) ”，只是使用则不需要了解
```json
{ 
  "Header": "Hgm", 
  "DataType": "2", 
  "Data": { 
    "id" : "101010300",
    "adm": "Beijing", 
    "adm2": "Beijing", 
    "location":"Chaoyang",
    "lat": "39.92149", 
    "lon": "116.48641"
  }
}
```

---

## 上位机接收格式

同 “下位机接收格式”

---

下位机接收成功或上位机成功都返回给对方一个JSON数据包：  
OK（DataType == 3）  
```json
 {"Header":"Hgm", "DataType":"3", "Data":"ok"}
```

---




