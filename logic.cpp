#include <2048.h>

//sinh số ngẫu nhiên 2 hoặc 4 tỉ lệ 9:1
void add_Number(){
    vector<pair<int,int>> emptySlots

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(BOARD[i][j]==0){
                emptySlots.push_back({i,j});
            }
        }
    }

    if(!emptySlots.empty()){
        int ran= rand()% emptySlots.size();
        board[emtyTiles[ran].first][emptySlots[ran].second]=(rand()%10)?4:2;
    }
}
bool abilitymove() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return true;  // Còn ô trống
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return true; // Có thể gộp ngang
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return true; // Có thể gộp dọc
        }
    }
    return false;
}


