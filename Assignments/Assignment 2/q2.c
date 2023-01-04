#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define SYS_kernel_2d_memcpy 448

int main(int argc,char **argv)
{
    int row = 2;
    int col = 3;
    float mat1[2][3] = {{3.2, 1.3, 5.4}, {3.2, 1.3, 6.5}};
    float mat2[2][3] = {{8.2, 4.3, 2.4}, {6.2, 2.3, 7.5}};

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%lf ", mat2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int ans = syscall(SYS_kernel_2d_memcpy,&mat2,&mat1,row,col);

    if(ans<0)
    {
        perror("Failed");
        abort();
    }

     for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%lf ", mat2[i][j]);
        }
        printf("\n");
    }
}