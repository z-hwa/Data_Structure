#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int file_name[21];
int file_size[21];
int num_abs[21];

int ans[21];    //�N��p�̦n�����p�U �R���ɮת��ѵ�

int min = INT_MAX;
int delete_num, delete_size;

void solve(int i, int take, int t) {

    //��ܪ��ɮ׼ƶq  = delete
    if (take == delete_num) {
        int sum = 0;

        //�[�`���ɭ� �ݭnfor
        for (int j = 0; j < delete_num; j++) {
            //sum += file_size[i];    //DEBUG (1): ���A�p��ثe�R���ɮת��j�p �N���ӬO��num_abs

            sum += num_abs[j]; //�q0~take
        }

        // if take == 2
        // num_abs 0 1 2 (index)
        //         1 2 5 => 8
            
        //         1 9 5 (�p�O������� �|�Q�p�令����)
        //num_abs[j] = abs(sum - delete_size);    //DEBUG (2): �p�p��X�Ӫ��~�t �����ө�^�hnum_abs 
                                                //�n�Υt�~�@���ܼ��x�s �]��(1)
            
        int diff = abs(sum - delete_size);

        //�ҥH�o�̪��P�_�]�n��@�U
        //�{�b�o�ոѵ� �̦n num_abs (�q0~take
        if (diff < min) {
            min = diff;

            //��s�ѵ��Ʋ�
            /*for () {
                ans = num_abs;
            }*/
        }
        return;
    }
    if (i == 21)return;

    //�ثe�o��index i �ɮ� �p�Q�n�R��
    if (t == 1) {
        num_abs[take] = file_size[i];   //num_abs�N��p�ثe��ܤF�����ɮ׭n�Q�R�� �L�̪��j�p(1)
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
            if (count == 3) { // 3�n�令20
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