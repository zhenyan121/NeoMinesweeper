#include "common.h"
#include "raylib.h"

// 处理鼠标点击：揭示格子
void handleMouseClick() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        // 计算点击的格子坐标
        int clickedCol = (int)(mousePos.x / cellWidth);
        int clickedRow = (int)(mousePos.y / cellHeight);

        // 边界保护（理论上不会越界，但安全起见）
        if (clickedRow >= 0 && clickedRow < ROWS && clickedCol >= 0 && clickedCol < COLS) {
            if (board[clickedRow][clickedCol].adjacentBombs == 0 && !board[clickedRow][clickedCol].isBomb) {
                autorevealblank(clickedRow, clickedCol);
            }
            else if (board[clickedRow][clickedCol].revealed && board[clickedRow][clickedCol].adjacentBombs != 0) {
                revealAdjacent(clickedRow, clickedCol);
                //printf("revealAdjacent %d %d\n", clickedRow, clickedCol);
            }
            else { 
                // 揭示该格子
                board[clickedRow][clickedCol].revealed = true;
                // 取消旗帜状态 使其可以进行旗帜胜利判断
                if (board[clickedRow][clickedCol].isflag) {
                board[clickedRow][clickedCol].isflag = false;
                //printf("cancer flag succes");
                }
            }

            // 调试输出
        //    printf("Revealed cell: Row %d, Col %d\n", clickedRow, clickedCol);
            
            if (board[clickedRow][clickedCol].isBomb)
                GAME_STATE = GAME_LOST; // 失败 
            for (int y = 0; y < ROWS; y++) {
                 for (int x = 0; x < COLS; x ++){
                    
                    if (!board[y][x].isBomb && !board[y][x].revealed) {
              //          printf("is still reverd\n");
                        return ;
                    }
                }
            }
            //printf("the game win");
            GAME_STATE = GAME_WIN; // 胜利
        }
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
         Vector2 mousePos = GetMousePosition();

        // 计算点击的格子坐标
        int clickedCol = (int)(mousePos.x / cellWidth);
        int clickedRow = (int)(mousePos.y / cellHeight);

        // 边界保护（理论上不会越界，但安全起见）
        if (clickedRow >= 0 && clickedRow < ROWS && clickedCol >= 0 && clickedCol < COLS) {
            // 揭示该格子
            if (!board[clickedRow][clickedCol].revealed && !board[clickedRow][clickedCol].isflag) {
                board[clickedRow][clickedCol].isflag = true;
             flagwincheck();
            return ;
            }
            if (!board[clickedRow][clickedCol].revealed && board[clickedRow][clickedCol].isflag)
                board[clickedRow][clickedCol].isflag = false;
            flagwincheck();
        }
    }
}
