#include<stdio.h>
#include<stdlib.h>
#define max 1000
    int cylinder_size;
    int cylinders[max];
    int temporary[max];
    int response_time;
    int totalmoment;
    int total_seek_time;
    int seektime;
    int request;

void FCFS(int cylinders[],int temporary[],int cylinder_size,int request,int seektime);
void SSTF(int cylinders[],int temporary[],int cylinder_size,int request,int seektime);
void SCAN(int cylinders[],int temporary[],int cylinder_size,int request,int seektime);
void LOOK(int cylinders[],int temporary[],int cylinder_size,int request,int seektime);
void C_SCAN(int cylinders[],int temporary[],int cylinder_size,int request,int seektime);
void main(){
    int choice;
   printf("\nEnter the size of cylinder:");
   scanf("%d",&cylinder_size);
   printf("\nEnter the contents of cylinders:");
   for (int i = 0; i < cylinder_size; i++)
   {
      scanf("%d",&cylinders[i]);
   }
   printf("\nEnter seek time:");
   scanf("%d",&seektime);
   printf("\nEnter request disk:");
   scanf("%d",&request);
   temporary[0] = request;
   for (int i = 1; i <= cylinder_size; i++)
   {
     temporary[i] = cylinders[i-1];
   }
   do
   {
    printf("\n1.FCFS");
    printf("\n2.SSTF");
    printf("\n3.LOOK");
    printf("\n4.SCAN");
    printf("\n5.C-SCAN");
    printf("\n6.C-LOOK");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
         FCFS(cylinders,temporary,cylinder_size,request,seektime);
         printf("\ntotal moment:%d",totalmoment);
         printf("\ntotal seek time:%d",total_seek_time);
        break;
    case 2:
         SSTF(cylinders,temporary,cylinder_size,request,seektime);
         printf("\ntotal moment:%d",totalmoment);
         printf("\ntotal seek time:%d",total_seek_time);
         break;
    default:
        break;
    }
   } while (choice != 6);
   
  
}
void FCFS(int cylinder[],int temporary[],int cylinder_size,int request,int seektime){
    int temp1,temp2,result;
    for (int i = 0; i < cylinder_size; i++)
    {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 -temp2;
        totalmoment+=(result<0) ? -result:result;
    }
    total_seek_time=totalmoment*seektime;
}
void SSTF(int cylinder[],int temporary[],int cylinder_size,int request,int seektime){
    int temp1,temp2,result,temp;
    int head_position=request;
    for (int i = 0; i <= cylinder_size; i++)
    {
        for (int j = i+1; j<=cylinder_size; j++)
        {
            if (abs(head_position - temporary[i]) > abs(head_position - temporary[j]))
            {
                temp = temporary[i];
                temporary[i]  = temporary[j];
                temporary[j] = temp;
            }
        }
    }
    for (int i = 0; i < cylinder_size; i++)
    {
        temp1= temporary[i];  
        temp2 = temporary[i-1];
        result = temp1 - temp2;
        totalmoment+=(result<0) ? -result:result;
    }
    total_seek_time=totalmoment*seektime;
}
void SCAN(int cylinders[],int temporary[],int cylinder_size,int request,int seektime){
    int temp1,temp2,result,temp,index;
    int head_position= request;
    for (int i = 0; i <= cylinder_size; i++)
    {
        for (int j = i+1; i <= cylinder_size; j++)
        {
            if (temporary[i] > temporary[j])
            {
                temp = temporary[i];
                temporary[i] = temporary[j];
                temporary[j] = temp;
            }
        }
    }
    for ( index = 0; index <= cylinder_size; index++)
    {
        if (temporary[index] == request)
        {
            break;
        }
    }
    for (int i = index; i <=cylinder_size; i++)
    {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 - temp2;
        totalmoment += (result<0) ? -result:result;
    }
    for (int i = index-1; i >= 0; i--)
    {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 -temp2;
        totalmoment +=(result<0) ? -result : result;
    }
    total_seek_time = totalmoment * seektime;
    
    
}
void LOOK(int cylinder[],int temporary[],int cylinder_size,int request,int seektime){
   int temp1,temp2,temp,index,result;
   for (int i = 0; i <= cylinder_size; i++)
   {
       for (int j = i+1; i <=cylinder_size; i++)
       {
         if (temporary[i] > temporary[j])
         {
             temp = temporary[i];
             temporary[i] =  temporary[j];
             temporary[j] = temp;
         }
       }
   }
   for (index = 0; index <=cylinder_size; index++)
   {
       if (temporary[index] == request)
       {
           break;
       }
   }
   for (int i = index; i < cylinder_size; i++)
   {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 - temp2;
        totalmoment+=(result<0) ? -result : result;
   }
   for (int i = index-1; index >= 0; i++)
   {
     temp1 = temporary[i];
     temp2 = temporary[i+1];
     result = temp1 - temp2;
     totalmoment += (result<0) ? -result :result;
   }
   total_seek_time = totalmoment * seektime;  
}
void C_SCAN(int cylinders[],int temporary[],int cylinder_size,int request,int seektime){
    int temp1,temp2,temp,index,result;
    for (int i = 0; i <= cylinder_size; i++)
    {
        for (int j = i+1; j <= cylinder_size; j++)
        {
            if (temporary[i]>temporary[j])
            {
                temp = temporary[i];
                temporary[i] = temporary[j];
                temporary[j] = temp;
            }
            
        }
        
    }
    for ( index = 0; index <= cylinder_size; index++)
    {
        if (temporary[index] == request)
        {
            break;
        }
    }
    for (int i = index; i < cylinder_size; i++)
    {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 - temp2;
        totalmoment+= (result<0) ? -result :result;
    }
    result = temporary[cylinder_size] - temporary[index];
    totalmoment+=(result<0) ? -result :result;
     for (int i = 0; i < index; i++)
     {
        temp1 = temporary[i];
        temp2 = temporary[i+1];
        result = temp1 - temp2;
        totalmoment += (result < 0) ? -result:result;
     }
     total_seek_time = totalmoment * seektime;
}
void C_LOOK(int cylinders[],int temporary[],int cylinder_size,int request,int seektime){
     int temp1,temp2,temp,index,result;
     for (int i = 0; i <= cylinder_size; i++)
     {
        for (int j = 0; j <=cylinder_size ; j++)
        {
             if (temporary[i] > temporary[j])
             {
                  temp  = temporary[i];
                  temporary[i] = temporary[j];
                  temporary[j] = temp;
             }
        }
     }
     for ( index = 0; index <=cylinder_size ; index++)
     {
           if (temporary[index] == request)
           {
               break;
           }
     }
     for (int i = index; i < cylinder_size; i++)
     {
           temp1 = temporary[i];
           temp2 = temporary[i+1];
           result = temp1 - temp2;
           totalmoment+=(result<0) ? -result:result;
     }
     totalmoment += temporary[cylinder_size] - temporary[index];
     total_seek_time = totalmoment * seektime;
}