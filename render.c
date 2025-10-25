#include "common.h"
#include "raylib.h"


// 绘制整个棋盘
void draw_board() {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            int posX = x * cellWidth;
            int posY = y * cellHeight;
            
            if (board[y][x].revealed) {
                // 已揭示：如果是炸弹，画红色；否则显示数字
                if (board[y][x].isBomb) {
                    DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, BOMB_COLOR);
                } else {
                    // 数字转字符串并绘制（0 时不显示）
                    if (board[y][x].adjacentBombs > 0) {
                        char buffer[2];
                        sprintf(buffer, "%d", board[y][x].adjacentBombs);
                        DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, TEXT_BACKERGROUND_COLOR);
                        DrawText(buffer, posX + cellWidth / 3 + 2, posY + cellHeight / 3 - 3, TEXTSIZE, TEXT_COLOR);
                    } else {
                        // 空白格子（无相邻炸弹）
                        DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, TEXT_BACKERGROUND_COLOR);
                    }
                }
            } else if (board[y][x].isflag) {
                DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, COVER_COLOR);
                //画旗帜
                DrawText("F", posX + cellWidth / 3 + 2, posY + cellHeight / 3 - 3, TEXTSIZE, FLAG_COLOR);
            } else {
                //未揭示，显示灰格子
                DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, COVER_COLOR);
            }
            
        }
    }
}

void render_gameover() {
    char temp[20];
    if (GAME_STATE != GAME_RUNNING) {
        int hours = (int)GAME_TIME / 3600;
        int minutes = (int)GAME_TIME / 60 % 60;
        int seconds = (int)GAME_TIME % 60;
        
        if (hours > 24) {
            sprintf(temp, "Time: Over 1 Day!");
        } else {
            sprintf(temp, "Time: %02d:%02d:%02d", hours, minutes, seconds);
        }
    }
    

    if (GAME_STATE == GAME_LOST) {
                DrawText("Game Over! Press R to restart", screenWidth/2 - 240, screenHeight/2 - 45, TEXTSIZE, RED);
                DrawText(temp, screenWidth/2 - 100, screenHeight/2 + 15, TEXTSIZE, RED);
                revealAllBombs();
            } else if (GAME_STATE == GAME_WIN) {
                DrawText("You Win! Press R to restart", screenWidth/2 - 220, screenHeight/2 - 45, TEXTSIZE, GREEN);
                DrawText(temp, screenWidth/2 - 100, screenHeight/2 + 15, TEXTSIZE, GREEN);
            }    
}