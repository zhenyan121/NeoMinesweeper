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
    if (GAME_STATE != GAME_RUNNING) {
        initializeBoard ();
    }
        GameSave gamedata;
        memcpy(gamedata.board_save, board, sizeof(board));
        gamedata.GAME_TIME_save = GAME_TIME;
        gamedata.HELP_MENU_save = HELP_MENU;
        SaveFileData(SAVE_NAME, &gamedata, sizeof(GameSave));
        
    
}

bool LoadGameSave() {
    GameSave gamedata;
    int datasize = 0;
    unsigned char * filedata = LoadFileData(SAVE_NAME, &datasize);
    if (filedata == NULL) {
       // UnloadFileData(filedate);
        remove(SAVE_NAME);
        return false;
    }
    if (datasize != sizeof(GameSave)) {
        UnloadFileData(filedata);
        remove(SAVE_NAME);
        return false;
    }
    memcpy(&gamedata, filedata, sizeof(GameSave));
    memcpy(board, gamedata.board_save, sizeof(board));
    GAME_TIME = gamedata.GAME_TIME_save;
    HELP_MENU = gamedata.HELP_MENU_save;
    UnloadFileData(filedata);
    
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
    return true;
}