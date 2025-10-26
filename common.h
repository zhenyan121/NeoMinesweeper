#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 游戏配置
#define ROWS 16          // 行数
#define COLS 16          // 列数
#define MAX_BOMBS 30    // 炸弹总数
#define SAVE_NAME "gamesave.dat"
#define WINDOWS_TITLE "NeoMinesweeper v1.9"

#define TEXTSIZE 30

#define TEXT_BACKERGROUND_COLOR   (Color){255, 242, 222, 255} 
#define BOMB_COLOR     (Color){213, 126, 119, 255} 
#define COVER_COLOR   (Color){255, 209, 201, 255}
#define TEXT_COLOR   (Color){102, 84, 84, 255}   
#define FLAG_COLOR  (Color){50, 200, 180, 255}  
#define BOARD_BACKGROUND_COLOR  (Color){248, 240, 229, 255}
/*
#define TEXT_BACKERGROUND_COLOR   (Color){255, 242, 222, 255} 
#define BOMB_COLOR     (Color){188, 143, 125, 255} 
#define COVER_COLOR   (Color){255, 222, 197, 255}
#define TEXT_COLOR   (Color){102, 84, 84, 255}   
#define FLAG_COLOR  (Color){183, 206, 223, 255}  
#define BOARD_BACKGROUND_COLOR  (Color){252, 245, 235, 255}
*/
// 格子结构体
typedef struct {
    bool isBomb;            // 是否是炸弹
    int adjacentBombs;      // 周围炸弹数量
    bool revealed;          // 是否已被揭示（翻开）
    bool isflag;
} Cell;

typedef struct {
    Cell board_save[ROWS][COLS];
    float GAME_TIME_save;

} GameSave;

typedef enum {
    GAME_RUNNING,
    GAME_WIN,
    GAME_LOST
} GameState;

// 全局棋盘
extern Cell board[ROWS][COLS];

// 窗口尺寸
extern const int screenWidth;
extern const int screenHeight;

// 每个格子的像素尺寸（自动计算）
extern const int cellWidth;
extern const int cellHeight;

extern GameState GAME_STATE; // 0 - 进行中, 1 - 胜利, -1 - 失败
extern bool DEBUG_MODE; // 调试模式参数
extern float GAME_TIME;


void WriteBoardDebug();
void WriteGameSave();
bool LoadGameSave();
// 初始化棋盘：清空 + 随机布雷 + 计算周围炸弹数
void initializeBoard();
//空白自动展开
void autorevealblank(int y, int x);
// 绘制整个棋盘
void draw_board();
//进行旗帜判断胜利
void flagwincheck();
// 处理鼠标点击：揭示格子
void handleMouseClick();
void revealAllBombs();
void render_gameover();

void revealAdjacent(int y, int x);

#endif