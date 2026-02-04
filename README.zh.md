# Rungo

Rungo 是 **Korelin** 开发生态系统的官方专用包管理器。它旨在简化 Korelin 开发者的包安装、管理、项目初始化和版本控制流程。

## 功能特性

- **项目初始化**：快速搭建符合最佳实践的 Korelin 项目目录结构。
- **依赖管理**（开发中）：支持安装、卸载和列出包。
- **模板支持**：支持多种项目模板，包括标准应用、插件和框架。
- **跨平台**：使用现代 C++ 编写，具备高性能和良好的移植性。

## 安装指南

### 前置要求
- 支持 C++20 的 C++ 编译器
- CMake (版本 4.1 或更高)

### 源码编译

```bash
# 克隆仓库
git clone https://github.com/nexogic-org/rungo.git
cd rungo

# 使用 CMake 构建
cmake -B build
cmake --build build
```

编译完成后，可执行文件 `rungo` 将位于 `bin/` 目录下。

## 使用说明

### 初始化新项目

创建一个新的 Korelin 项目：

```bash
rungo init <project-name>
```

该命令将生成包含以下内容的项目结构：
- `project.json`：项目配置文件。
- `src/main.kri`：应用程序入口点。
- `rungo_modules/`：依赖包存放目录。

### 其他命令（即将推出）

- `rungo install <package>`：安装依赖包。
- `rungo uninstall <package>`：卸载依赖包。
- `rungo list`：列出已安装的包。

## 许可证

MIT License. 详见 LICENSE 文件。
