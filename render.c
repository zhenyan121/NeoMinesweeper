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
                    if (board[y][x].adjacentBombs > 0 && !board[y][x].ismarked) {
                        char buffer[2];
                        sprintf(buffer, "%d", board[y][x].adjacentBombs);
                        DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, TEXT_BACKERGROUND_COLOR);
                        DrawText(buffer, posX + cellWidth / 3 + 2, posY + cellHeight / 3 - 3, TEXTSIZE, TEXT_COLOR);
                    } else {

                        if(board[y][x].ismarked) {
                            DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, TEXT_BACKERGROUND_COLOR);
                            DrawText("?", posX + cellWidth / 3 + 2, posY + cellHeight / 3 - 3, TEXTSIZE, TEXT_COLOR);
                        } else {
                        // 空白格子（无相邻炸弹）
                        DrawRectangle(posX, posY, cellWidth - 1, cellHeight - 1, TEXT_BACKERGROUND_COLOR);
                    }
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

void render_help_menu() {
    if (GAME_STATE != GAME_RUNNING || !HELP_MENU) {
        return;
    }
   /* int titlesize = TEXTSIZE + 30;
    int mainsize = titlesize * 0.75;
    int smalltitlesize = titlesize * 0.8;
    int overgamesize = titlesize * 0.7;
    int detailsize = titlesize * 0.65;*/
    DrawText("Help   Menu",screenWidth/2 - 125, screenHeight/2 - 350, TEXTSIZE + 5, HELP_MENU_COLOR);
    DrawText("Controls:",screenWidth/2 - 400, screenHeight/2 - 300, TEXTSIZE + 3, HELP_MENU_COLOR);
    DrawText("Left click: Reveal a tile",screenWidth/2 - 300, screenHeight/2 - 250, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("Right click: Place or remove a flag",screenWidth/2 - 300, screenHeight/2 - 200, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("How to Win:",screenWidth/2 - 400, screenHeight/2 - 150, TEXTSIZE + 3, HELP_MENU_COLOR);
    DrawText("Reveal all tiles that are not mines, or",screenWidth/2 - 300, screenHeight/2 - 100, TEXTSIZE , HELP_MENU_COLOR);
    DrawText("Correctly flag all mines",screenWidth/2 - 300, screenHeight/2 - 50, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("Others:",screenWidth/2 - 400, screenHeight/2, TEXTSIZE + 3, HELP_MENU_COLOR);
    DrawText("Press H to toggle this help menu",screenWidth/2 - 300, screenHeight/2 + 50, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("Click anywhere on the board to close this menu",screenWidth/2 - 300, screenHeight/2 + 100, TEXTSIZE , HELP_MENU_COLOR);
    DrawText("Tips:",screenWidth/2 - 400, screenHeight/2 + 150, TEXTSIZE + 3, HELP_MENU_COLOR);
    DrawText("Quick Reveal: Left-click a revealed number tile.",screenWidth/2 - 370, screenHeight/2 + 200, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("If the correct number of flags is placed around it,",screenWidth/2 - 370, screenHeight/2 + 250, TEXTSIZE, HELP_MENU_COLOR);
    DrawText("all unflagged neighboring tiles will automatically open.",screenWidth/2 - 370, screenHeight/2 + 300, TEXTSIZE, HELP_MENU_COLOR);
    


}