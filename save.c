#include "common.h"
#include "raylib.h"


void WriteBoardDebug() {
    FILE * fp;
    fp = fopen("board.txt", "w");
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (board[y][x].isBomb)
                fprintf(fp, "B ");
            else {
                fprintf(fp, "%d ", board[y][x].adjacentBombs);
            }

        }
        fprintf(fp, "\n");
    }
    fclose(fp);   
}

void WriteGameSave() {
    if (GAME_STATE == GAME_RUNNING) {
        SaveFileData(SAVE_NAME, board, sizeof(Cell) * ROWS * COLS);
        SaveFileData(TIME_SAVE_NAME, &GAME_TIME, sizeof(float));
    }
}

bool LoadGameSave() {
    int datasize = 0;
    unsigned char * filedata = LoadFileData(SAVE_NAME, &datasize);
    if (filedata == NULL) {
       // UnloadFileData(filedate);
        remove(SAVE_NAME);
        remove(TIME_SAVE_NAME);
        return false;
    }
    if (datasize != sizeof(board)) {
        UnloadFileData(filedata);
        remove(SAVE_NAME);
        remove(TIME_SAVE_NAME);
        return false;
    }
    memcpy(board, filedata, sizeof(board));
    UnloadFileData(filedata);
    remove(SAVE_NAME);
    filedata = NULL;
    datasize = 0;
    if (DEBUG_MODE == true) {
        WriteBoardDebug();
        int bombsPlaced = 0;
        for (int y = 0; y < ROWS; y++)
            for (int x = 0; x < COLS; x++) {
                if (board[y][x].isBomb){
                    bombsPlaced++;
                    printf("Placing the %d bomb at (%d, %d)\n", bombsPlaced, y, x); // 调试输出
                    if (bombsPlaced == MAX_BOMBS)
                        printf("\n");
                }
            }
    }
    filedata = LoadFileData(TIME_SAVE_NAME, &datasize);
    if (filedata == NULL) {
       // UnloadFileData(filedate);
        remove(SAVE_NAME);
        remove(TIME_SAVE_NAME);
        return false;
    }
    if (datasize != sizeof(float)) {
        UnloadFileData(filedata);
        remove(TIME_SAVE_NAME);
        remove(SAVE_NAME);
        return false;
    }
    memcpy(&GAME_TIME, filedata, sizeof(float));
    UnloadFileData(filedata);
    remove(TIME_SAVE_NAME);
    return true;
}