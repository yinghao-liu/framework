# 017
systemd-journald-journalctl

systemd-journald 是一个收集和存储日志数据的系统服务。日志数据来源主要有以下几种：
- 内核日志，通过kmsg
- 简单系统日志，通过**syslog**调用
- 结构化的系统日志，通过**sd_journal_print**
- 服务单元的标准输出和标准错误
- 审计记录




## 和dmesg区别
dmesg: print or control the kernel ring buffer
like journalctl -k

## reference
1. man systemd-journald
2. man journalctl
3. man 3 syslog
4. [Systemd 入门教程：命令篇](https://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html)
