# include<stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

void bubblesort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        printf("%d \t", arr[k]);
    }
}

int main() {
    int my_arr[] = {10, 13, 45, 78, 3, 45, 78};
    int n = sizeof(my_arr) / sizeof(my_arr[0]);

    pid_t pid = fork();

    if (pid < 0) {
        printf("Process failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child process\n");
        execlp("/bin/sort", "sort", "-n", (char*)NULL);
    } else {
        wait(NULL);  // Uncomment this line if you want the parent to wait for the child
        printf("Parent process\n");
        bubblesort(my_arr, n);
    }

    return 0;
}
