#include<stdio.h>
#define max 100

int blocksize[max];
int file_size[max];
int process[max];
int block_no[max];
int block_used[max];
int fragment[max];
void first_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no);
void best_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no);
void worst_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no);
void main(){
    int value,blocks_no,file_no;
    printf("\nEnter the number of blocks:");
    scanf("%d",&blocks_no);
    printf("\nEnter the number of files:");
    scanf("%d",&file_no);
    printf("\nEnter the block number:");
    for (int i = 0; i < blocks_no; i++)
    {
        scanf("%d",&block_no[i]);
    }
    printf("\nEnter the size of block:");
    for (int i = 0; i < blocks_no; i++)
    {
        scanf("%d",&blocksize[i]);   
    }
    printf("\nEnter the size of files:");
    for (int i = 0; i < file_no ; i++)
    {
        scanf("%d",&file_size[i]);
    }
    worst_fit(blocksize,file_size,process,blocks_no,file_no);
    printf("File_no\tFile_size\tBlock_no\tBlock_size\tFragment\n");
    for (int i = 0; i < file_no; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, file_size[i], block_no[i]+1, block_used[i], fragment[i]);
    }    
}

void first_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no){
    int temp1,temp2,temp3,value;
    int temporary[max];
    for (int i = 0; i < blocks_no; i++)
    {
        temporary[i] = blocksize[i];
    }
    for (int i = 0; i < file_no; i++)
    {
        value = file_size[i];
        int j = 0;
        while (j<=blocks_no)
        {
            if (blocksize[j]>=value)
            {
                temp1 = blocksize[j] - value;
                blocksize[j] = temp1;
                fragment[i]  = temp1;
                temp2 = blocksize[j];
                block_used[i] = temp2;
                temp3 = block_no[j];
                process[i] = temp3;
                break;
            }
            j++;
        }
        
    }
    
}
void best_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no){
    int temp1,temp2,temp3,value,data;
    int temporary[max];
    int temporary1[max];
    for (int i = 0; i < blocks_no; i++)
    {
        temporary[i] = blocksize[i];
        temporary1[i] = blocksize[i];
    }
    for (int i = 0; i < file_no; i++)
    {
        value = file_size[i];
        int best_fit_index = -1;
        for (int j = 0; j < blocks_no; j++)
        {
            if (temporary[j] >= value)
            {
                if (best_fit_index == -1 || temporary[j] < temporary[best_fit_index])
                {
                    best_fit_index = j;
                    data = j;
                }
            }
            if ( best_fit_index != -1)
            {
                temp1 = temporary[best_fit_index] - value;
                temp2 = blocksize[j];
                temp3 = block_no[j];
                blocksize[j] = temp1;
                fragment[i] = temp1;
                block_used[i] = temp2;
                process[i] = temp3; 
            }
        }
    }
}
void worst_fit(int blocksize[],int file_size[],int process[],int blocks_no,int file_no){
    int temporary[max],temp1,temp2,temp3,value,data;
    for (int i = 0; i < blocks_no; i++)
    {
        temporary[i] = blocksize[i];
    }
    for (int i = 0; i < file_no; i++)
    {
        value = file_size[i];
        int worst_fit_index = -1;
        for (int j = 0; j < blocks_no; j++)
        {
            if (temporary[j] >= value)
            {
                if (worst_fit_index == -1 || temporary[j] > temporary[worst_fit_index])
                {
                    worst_fit_index = j;
                    data = j;
                }
                
            }
            
            if (worst_fit_index != -1)
            {
                temp1 = temporary[worst_fit_index] - value;
                fragment[i] = temp1;
                temp2 = blocksize[j];
                blocksize[j] = temp1;
                block_used[i] = temp2;
                temp3 = block_no[j];
                process[i] = temp3;
            }
            
        }
        
    }
    
}