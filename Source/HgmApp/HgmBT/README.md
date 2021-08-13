# HgmBT

HGM的蓝牙数据包格式(JSON)

---

## 下位机接收格式

|------|数据头标识|数据类型    |数据块      |
|:----:|:-------:|:--------:|:----------:|
| __Key__|Header   |DataType  |Data        |
| __Value__|Hgm  |dt (见下文)|data(见下文)|

#### dt:
>__WiFiConfigInfo__
>>用于WiFi配置，Data存放ssid和password  
>>Data:["ssid":"xxx", "password":"xxx"]
>
可以自己实现更多功能

例子：
> {
"header": "Hgm",
"DataType": "WiFiConfigInfo",
"Data": {
"ssid": "xxx",
"password": "xxx"
}
}


---

## 上位机接收格式

同 “下位机接收格式”

下位机接收成功则返回给上位机一个JSON数据包：
> {"Header":"Hgm", "DataType":"status", "Data":"ok"}


---




