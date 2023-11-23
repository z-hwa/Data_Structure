#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int file_name[21];
int file_size[21];
int num_abs[21];

int ans[21];    //代表妳最好的情況下 刪除檔案的解答

int min = INT_MAX;
int delete_num, delete_size;

void solve(int i, int take, int t) {

    //選擇的檔案數量  = delete
    if (take == delete_num) {
        int sum = 0;

        //加總的時候 需要for
        for (int j = 0; j < delete_num; j++) {
            //sum += file_size[i];    //DEBUG (1): 那你計算目前刪除檔案的大小 就應該是用num_abs

            sum += num_abs[j]; //從0~take
        }

        // if take == 2
        // num_abs 0 1 2 (index)
        //         1 2 5 => 8
            
        //         1 9 5 (妳記錄的資料 會被妳改成錯的)
        //num_abs[j] = abs(sum - delete_size);    //DEBUG (2): 妳計算出來的誤差 不應該放回去num_abs 
                                                //要用另外一個變數儲存 因為(1)
            
        int diff = abs(sum - delete_size);

        //所以這裡的判斷也要改一下
        //現在這組解答 最好 num_abs (從0~take
        if (diff < min) {
            min = diff;

            //更新解答數組
            /*for () {
                ans = num_abs;
            }*/
        }
        return;
    }
    if (i == 21)return;

    //目前這個index i 檔案 妳想要刪掉
    if (t == 1) {
        num_abs[take] = file_size[i];   //num_abs代表妳目前選擇了哪些檔案要被刪除 他們的大小(1)
    }

    solve(i + 1, take + 1, 1);
    solve(i + 1, take, 0);
}

int main() {
    int opt;
    int count = 0;
    int valid[21];
    for (int i = 0; i < 21; i++) {
        valid[i] = 0;
    }

    do {
        printf("Options: ");
        scanf("%d", &opt);
        int found;
        switch (opt) {
        case 1:
            printf("Please input file name and file size: ");
            int a, b;
            scanf("%d %d", &a, &b);
            for (int i = 0; i < count; i++) {
                if (valid[i] == -1) {
                    file_name[i] = a;
                    file_size[i] = b;
                    valid[i] = 1;
                    break;
                }
            }
            if (count == 3) { // 3要改成20
                printf("Hard drive exceeds its capacity, please enter the number of "
                    "files to be deleted: ");

                scanf("%d %d", &delete_num, &delete_size);
                solve(0, 0, 1);

                for (int i = 0; i < count; i++) {
                    if (file_name[i] == delete_num) {
                        valid[i] = -1;
                    }
                }
                count -= delete_num;
                break;
            }
            file_name[count] = a;
            file_size[count] = b;
            valid[count] = 1;
            count++;
            break;

        case 2:
            printf("Please input the file name: ");
            int name = 0;
            scanf("%d", &name);
            for (int i = 0; i < count; i++) {
                if ((file_name[i] == name) && (valid[i] == 1)) {
                    found = 1;
                }
            }
            if (found) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
            found = 0;
            break;

        case 3:
            return 0;
            break;
        }
    } while (opt != 3);
    return 0;
}