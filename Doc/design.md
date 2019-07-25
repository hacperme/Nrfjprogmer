# 设计文档

## 需求

- 实现 编程器 对象，包含以下功能：
    1. 烧写 flash 固件，可以指定内存 起止地址；
    2. 从 flash 读取数据，保存文件，可以指定 起止地址；
    3. 固件保护 安全锁 加密功能
    4. 显示进度条
- 日志功能 对象
    1. 操作记录 输出到 日志文件
    2. 操作记录 输出到 程序日志显示区域
    3. 日志级别4个：debug info error warning
    4. 需要写个日志配置方法，配置日志级别，配置日志输出流，配置日志输出格式。
- UI

- 配置文件 ini 文件解析对象

- 发布 打包

## nrfjprog 命令行 操作 指令

- 安装路径：
```bat
    C:\Users\DELL>where nrfjprog
     C:\Program Files (x86)\Nordic Semiconductor\nrf-command-line-tools\bin\nrfjprog.exe
```

- 开启  readback protection

> nrfjprog --rbp ALL

- 关闭 readback protection
> nrfjprog --recover

- 烧写固件
> nrfjprog --program C:\Users\DELL\Desktop\20190716_江西移动_二维码答题卡V5.8_ALL.hex --verify

- 擦除 flash

> nrfjprog -e

