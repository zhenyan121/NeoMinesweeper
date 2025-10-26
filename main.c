#include "raylib.h"
#include "common.h"
const int screenWidth = 900;
const int screenHeight = 900;

// 每个格子的像素尺寸（自动计算）
const int cellWidth = screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;

GameState GAME_STATE = GAME_RUNNING; 
bool DEBUG_MODE = false; // 调试模式参数
float GAME_TIME = 0.0f;

// 全局棋盘
Cell board[ROWS][COLS];




// 主函数
int main(int argc, char * argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--debug"))
        DEBUG_MODE = true;
    
    // 初始化窗口
    InitWindow(screenWidth, screenHeight, WINDOWS_TITLE);
    SetTargetFPS(60);  // 设置帧率
    if (!LoadGameSave())
        // 初始化棋盘
        initializeBoard();

    // 主游戏循环
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            GAME_STATE = GAME_RUNNING;
            initializeBoard();
        }
       
        if (GAME_STATE == GAME_RUNNING) {
            // 处理输入
            handleMouseClick();
            //计算时间
            GAME_TIME += GetFrameTime();
        }
        // 绘制
        BeginDrawing();
        ClearBackground(BOARD_BACKGROUND_COLOR);
        draw_board();               // 绘制棋盘
        render_gameover();    
        EndDrawing();
    }
    WriteGameSave();
    // 关闭窗口
    CloseWindow();
    return 0;
}