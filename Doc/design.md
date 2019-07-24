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
- UI

- 配置文件 ini 文件解析对象

- 发布 打包

## nrfjprog 命令行 操作 指令

 安装路径：
```bat
    C:\Users\DELL>where nrfjprog
     C:\Program Files (x86)\Nordic Semiconductor\nrf-command-line-tools\bin\nrfjprog.exe
```

