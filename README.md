# 花密

## 介绍

“花密”提供一种简单的密码管理方法，只需要记住一个`密码`，为不同的账号设置对应的`标识`，然后通过花密计算就可以得到对应的不同的复杂密码。

## 使用

### 帮助

```txt
	Copyright tqfx 2020~2021
option:
-i --id 	get password by id
-a --add 	add key or password
-d --del 	delete key or password
-s --show 	show key or password
parameter:
-k --key 	the key
-p --password 	the password
-l --length 	the length {1,32}
-t --type 	the type of password {0,1}
-f --filename 	filename of data
   --import 	filename of data
```

### 生成密码

```bash
key -k key -p password
```

注意：不会将记录写入数据库

### 添加密码

向数据库添加密码 `123456`

```bash
key -a -p 123456
```

### 添加标识

向数据库添加 名为 `key`，长度为 `16`，类型为 `默认` 的标识

```bash
key -a -k key -l 16 -t 0
```

向数据库添加 名为 `pay`，长度为 `6`，类型为 `数字` 的标识

```bash
key --add --key pay --length 6 --type 1
```

### 删除密码

从数据库删除密码 `123456`

```bash
key -d -p 123456
```

从数据库删除 ID 为 0 的密码

```bash
key -di -p 0
```

### 删除标识

从数据库删除标识 `key`

```bash
key -d -k key
```

从数据库删除 ID 为 0 的标识

```bash
key -di -k 0
```

### 查询密码

显示所有密码

```bash
key -s -p=
```

### 查询标识

显示包含 `key` 的标识

```bash
key -s -k key
````

### 导入数据

将 `.fp.json` 的数据导入到 `.fp.xml`

```bash
key -f .fp.xml --import .fp.json
```

## 编译

### [msys2](https://www.msys2.org/)

```bash
mkdir build
cd build
cmake .. -G "MSYS Makefiles"
make
```

### [MinGW](https://sourceforge.net/projects/mingw/) [mingw-w64](https://sourceforge.net/projects/mingw-w64/)

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

### [termux](https://github.com/termux/termux-app)

图形化界面依赖于 [termux:api](https://github.com/termux/termux-api)

```bash
pkg install -y cmake make clang proot termux-api
```

```bash
termux-chroot
mkdir build
cd build
cmake ..
make
make install
```
