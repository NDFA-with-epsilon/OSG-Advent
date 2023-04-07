//Day 1
//cat implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define ERR_ARG \
{               \
    printf("\nSyntax: ./cat file1 file2 ...");            \
}


int calc_fsize(int fd)
{
    if(fd < 0)
    {
        return 0;
    }

    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    return size;
}

int sum(int* arr, unsigned int size)
{
    if(!arr || !size)
    {
        return -1;
    }

    int s = 0;
    for(int i = 0; i < size; i++)
    {
        s += arr[i];
    }
    
    return s;
}

void cat(int argc, char const** argv)
{
    /* allocate a buffer for storing the contents of files */
    int* arr_buf_size = calloc(argc - 1, sizeof(int));
    int* fd_val = malloc(sizeof(int) * (argc - 1));
    
    for(int idx = 1; idx < argc; idx++)
    {
        fd_val[idx - 1] = open(argv[idx], O_RDONLY);
        if(fd_val[idx - 1] < 0)
        {
            printf("\nerror code: %d", errno); /* early exit, account for closing fd's here. separate func prolly */
            exit(1);
        }

        arr_buf_size[idx - 1] += calc_fsize(fd_val[idx - 1]);
    }

    int buf_size = sum(arr_buf_size, argc - 1) ;

    char* buf = malloc(sizeof(char) * buf_size);
    char* tmp = buf;

    for(int idx = 0; idx < argc - 1; idx++)
    {
        if(read(fd_val[idx], (void*)tmp, arr_buf_size[idx]) != -1)
        {
            tmp += arr_buf_size[idx];
        }
    }        

    printf("\n%s", buf);
    
    for(int idx = 0; idx < argc - 1; idx++)
    {
        close(fd_val[idx]);
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    if(argc < 2) ERR_ARG 

    cat(argc, argv);
    return 0;
}
