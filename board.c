#include "common.h"
#include "raylib.h"

// 初始化棋盘：清空 + 随机布雷 + 计算周围炸弹数
void initializeBoard() {
    //初始化时间
    GAME_TIME = 0.0f;
    // 1. 初始化所有格子
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j].isBomb = false;
            board[i][j].adjacentBombs = 0;
            board[i][j].revealed = false;
            board[i][j].isflag = false;
            board[i][j].ismarked = false;
        }
    }

    // 2. 随机放置炸弹（确保不重复）
    srand(time(NULL));  // 初始化随机种子
    int bombsPlaced = 0;
    while (bombsPlaced < MAX_BOMBS) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (!board[row][col].isBomb) {  // 避免重复放置
            
            board[row][col].isBomb = true;
            bombsPlaced++;
            if (DEBUG_MODE == true) {
                
                printf("Placing the %d bomb at (%d, %d)\n", bombsPlaced, row, col); // 调试输出
                if (bombsPlaced == MAX_BOMBS)
                    printf("\n");
        }
    }
    }

    // 3. 计算每个非炸弹格子周围的炸弹数量
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if (!board[y][x].isBomb) {
                int count = 0;
                // 遍历 8 个相邻格子
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        int ny = y + dy;
                        int nx = x + dx;
                        // 边界检查
                        if (ny >= 0 && ny < ROWS && nx >= 0 && nx < COLS) {
                            if (board[ny][nx].isBomb) {
                                count++;
                            }
                        }
                    }
                }
                board[y][x].adjacentBombs = count;
            }
        }
    }
    if (DEBUG_MODE == true) {
        WriteBoardDebug();
    }
}

//空白自动展开，使用递归功能
void autorevealblank(int y, int x) {
    //边界检查
    if (y < 0 || y >= ROWS || x < 0 || x >= COLS) {
        return;
    }
    //如果已经翻开终止
    if (board[y][x].revealed) return ;
    //// 取消旗帜状态 使其可以进行旗帜胜利判断
    if (board[y][x].isflag) {
        board[y][x].isflag = false;
        
    }
    board[y][x].revealed = true;
    //终止条件
    if (board[y][x].adjacentBombs > 0) {
        return ;
    }
    int dx, dy;
    for (dy = -1; dy <= 1; ++dy) {
        for (dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            autorevealblank(y + dy, x + dx);
        }  
    }

}

//进行旗帜判断胜利
void flagwincheck() {
    //printf("start check\n");
   int flag_sum = 0;
   int x, y;
            for (y = 0; y < ROWS; y++) {
                for (x = 0; x < COLS; x++) {
               //     printf("ROWS = %d COLS = %d\n", y, x);
             //       printf("flag_sum = %d\n", flag_sum);
                 /*   if (y >= ROWS || x >= COLS) {

                        printf("错误: 数组越界 y=%d, x=%d\n", y, x);
                        return;
                }*/
                    if (!board[y][x].isBomb && board[y][x].isflag) {
                      //  printf("is no bomb ROWS = %d COLS = %d", y, x);
                      //  flag_sum = 0;
                      //  printf("adjence = %d isbomb = %d isflag = %d isrevealed = %d", board[y][x].adjacentBombs, board[y][x].isBomb, board[y][x].isflag, board[y][x].revealed);
                        return ;
                    }
                    if (board[y][x].isBomb && board[y][x].isflag) {
                        flag_sum++;
                    } 
                }
                
            }
           // printf("flag = %d\n", flag_sum);
            if (flag_sum == MAX_BOMBS)
                GAME_STATE = GAME_WIN; 
}

void revealAllBombs() {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if (board[y][x].isBomb) {
                board[y][x].revealed = true;
            }
        }
    }
}

void revealAdjacent(int y, int x) {
    int adjacent_flag = 0;
    int dx, dy;
    for (dy = -1; dy <= 1; dy++) {
        for (dx = -1; dx <= 1; dx++) {
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < ROWS && nx >= 0 && nx < COLS)
            if (board[ny][nx].isflag) {
                adjacent_flag++;
            }
        }
    }
    if (adjacent_flag != board[y][x].adjacentBombs ) {
        return;
    }
     for (dy = -1; dy <= 1; dy++) {
        for (dx = -1; dx <= 1; dx++) {
            int ny = y + dy;
            int nx = x + dx;
            if (ny >= 0 && ny < ROWS && nx >= 0 && nx < COLS) {
                if (!board[ny][nx].revealed && !board[ny][nx].isflag) {
                    if (board[ny][nx].adjacentBombs == 0 && !board[ny][nx].isBomb) {
                        autorevealblank(ny, nx);
                    }
                    else
                        board[ny][nx].revealed = true;
                    
                //printf("board[%d][%d]isflag = %d\n", ny, nx, board[ny][nx].isflag);
                }

                if (board[ny][nx].isBomb && board[ny][nx].revealed) {
                //printf("board[%d][%d]isflag = %d\n", ny, nx, board[ny][nx].isflag);
                    GAME_STATE = GAME_LOST;
                    return;
                }
            }
        }
     }
}

void markNumberedTiles() {
    int isStartMark;
    int isMarked = 0;
    srand(time(NULL));
    isStartMark = rand() % 100 + 1; //20%概率随机生成1到3格？格
    isMarked = rand() % 3 + 1;
    if (isStartMark <= 20) {
        while(isMarked > 0) {
            int row = rand() % ROWS;
            int col = rand() % COLS;
            if (/*board[row][col].revealed &&*/ !board[row][col].isBomb && board[row][col].adjacentBombs != 0) {
                board[row][col].ismarked = true;
                isMarked--;
            }
        }
    }
}