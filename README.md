# Minesweeper 扫雷游戏

一个使用 C 语言和 raylib 图形库开发的扫雷游戏。

## 游戏特性

- 扫雷游戏玩法
- 右键标记旗帜功能
- 实时计时系统
- 自动存档功能
- 调试模式支持
- 随机隐藏事件
- 现代化配色方案

## 游戏规则

- **左键点击**：揭开格子
- **右键点击**：放置/取消旗帜
- **空白区域**：自动展开相邻空白区域
- **数字格快捷操作**：左键点击已揭开的数字格，若其周围旗帜数量正确，会自动揭开其余未标记的邻格
- **胜利条件**：
  - 揭开所有非炸弹格子
  - 或使用旗帜正确标记所有炸弹

## 编译说明

### 环境要求
- C 编译器（GCC、Clang 等）
- raylib 图形库

### 编译命令
**Linux系统：**
需要预先安装raylib图形库，例如：
```bash
sudo pacman -S raylib
```

```bash
gcc -o minesweeper main.c save.c board.c input.c render.c -lraylib -lGL -lm -lpthread -ldl
```

**Windows：**
需要手动指定raylib目录，例如；  
```powershell
gcc main.c save.c board.c input.c render.c -o minesweeper -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm "-Wl,--subsystem,windows"
```

## 运行方式

### 正常模式
```bash
./minesweeper
```

### 调试模式
```bash
./minesweeper --debug
```

在调试模式下，游戏会将棋盘信息保存到 `board.txt` 文件中。

## 游戏控制

- **鼠标左键**：揭开格子
- **鼠标右键**：放置/取消旗帜
- **R 键**：重新开始游戏
- **关闭窗口**：自动保存游戏进度

## 游戏配置

- **棋盘大小**：16 × 16 格子
- **炸弹数量**：30 个
- **窗口尺寸**：900 × 900 像素

## 存档系统

游戏支持自动存档功能：
- 游戏进行中关闭窗口会自动保存
- 下次启动时自动加载存档
- 存档文件：`gamesave.dat`


## 文件结构

```
minesweeper/
├── common.h          # 公共头文件和配置
├── main.c           # 主程序入口
├── game.c           # 游戏逻辑实现
├── render.c         # 渲染绘制功能
└── save.c           # 存档系统实现
```

## 其它信息

游戏使用 raylib 图形库开发，支持跨平台运行。

享受游戏！如有问题请检查调试模式输出或查看生成的棋盘文件。