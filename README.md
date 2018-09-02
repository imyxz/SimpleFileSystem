# SimpleFileSystem
### a filesystem over filesystem
### 基于现有文件系统的二级文件系统。
### 带有基本的文件读写、权限管理、用户系统等功能，同时带有一个简易的shell。
```
adduser 新建用户
cd      改变当前工作目录
chmod   更改文件权限
chown   更改文件所有者
delete  删除文件
exit    退出shell
ls      列出该目录下的文件
mkdir   创建目录（支持递归创建）
read    读入文件内容
rename  重命名文件
su      切换用户
touch   改变文件访问时间，文件不存在时则创建
users   查看用户列表
write   写入文件内容
```
## 编码
目前编码为UTF-8，可能在windows下会有乱码。如需在windows下测试只需将main.cpp的编码转化为GB2312即可
## 编译
### Linux:
```
cmake ./ && make
```
### Windows:
使用visual studio编译即可