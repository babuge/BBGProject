# BBGProject说明

动态管理所有资源，保证所有动态库有可控的生命周期

跨平台应用

## 项目结构
```
├─App
├─ThirdParty
├─Plugins
|    ├─PluginsManager
├─Modules
|    ├─TryModule
|    ├─ResourceManagerModule
|    ├─ModulesManager
|    ├─LoggerManager
|    ├─BussinessModule
├─install
├─Build
├─.clang-format
├─.config.json
├─.gitignore
├─.qmake.conf
├─BBGProject.pro
├─CMakeLists.txt
├─LICENSE
├─README.MD
```
## 界面展示

界面

#### 开发环境及配置

1. QtCreator5.12及以上，Windows，linux。
2. 内存:2GB+，磁盘:16G+
3. qtCreator构建运行配置：

   * 配置realese
   * Build目录配置为当前项目下的Build目录
   * run设置：

     1. Executable：build目录下 执行项目名.执行文件扩展名
     2. Working directory： 为build设置的build目录
     3. qt临时编译环境：windows的qtcreator编译选项有add library to path,而linux的qtcreator（ubuntu目前qt5，使用默认环境）
4. 打包生产环境配置：
   对打包后安装目录的lib目录添加到环境变量path中或者library_path中。
   或者将lib目录下*.dll拷贝到执行文件同级目录
   将.config.json拷贝到执行文件目录下
5. 项目基于C++11，Qt6，QtCreator开发前配置：

   * 配置llvm-format
   * 设置git本地仓库和远端仓库
   * 设置文件名大小区分
   * 设置Use "#pragma once"

#### 编译方式

1. 工具qtcreator （qt6.4 mingw11.0 cmake3.20.*）
2. qmake编译：
   1. qtcreator 通过 xxxx.pro 打开项目
   2. 清除 项目（切换编译工具，需要重新构建）
   3. 编译 运行
3. cmake编译：
   1. qtcreator 通过 CMakeLists.txt 打开项目
   2. 清除 项目 （切换编译工具，需要重新构建）
   3. 编译 运行

#### 项目简介

作者：`Babuge`

2024/08/21
