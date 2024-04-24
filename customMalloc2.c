#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#define TRUE        1
#define FALSE       0

#define MAX_ALOCATION_ALLOWED       20
static unsigned char our_memory[1024 * 1024];

static int g_allocted_number = 0;
static int g_heap_base_address = 0;

typedef struct malloc_info
{
    int address;
    int size;
}malloc_info_t;

malloc_info_t   metadata_info[MAX_ALOCATION_ALLOWED] ={0};

void* my_malloc(int size)
{
    printf("my_malloc IN  size =  %d \n",size);
    int j =0;
    int index = 0 ;
    int initial_gap =0;
    int gap =0;
    int flag = FALSE;
    int initial_flag = FALSE;
    void *address = NULL;
    int heap_index = 0;
    malloc_info_t temp_info = {0};

    if(g_allocted_number >= MAX_ALOCATION_ALLOWED)
    {
        return NULL;
    }

    for(index = 0; index < g_allocted_number; index++)
    {
        if(metadata_info[index+1].address != 0 )
        {
            
            initial_gap = metadata_info[0].address - g_heap_base_address; /*Checked Initial Block (Case 3)*/
            printf(" [** here == initial_gap %d , i = %d **] \n",initial_gap, index);
            if(initial_gap >= size)
            {
                initial_flag = TRUE;
                break;
            }
            else
            {
                gap = metadata_info[index+1].address - (metadata_info[index].address + metadata_info[index].size);  /*Check Gap Between two allocated memory (Case 2)*/
                printf("[**here == gap %d , i = %d **]  \n",initial_gap , index);
                if(gap >= size)
                {
                    flag = TRUE;
                    break;
                }
            }
        }
    }

    if(flag == TRUE)    /*Get Index for allocating memory for case 2*/
    {
        printf("[CASE 2, size = %d] \n",size);
        heap_index = ((metadata_info[index].address + metadata_info[index].size) - g_heap_base_address);
    
        for(j = MAX_ALOCATION_ALLOWED -1; j > index+1; j--)
        {
            memcpy(&metadata_info[j], &metadata_info[j-1], sizeof(malloc_info_t));
        }
        address = &our_memory[heap_index];
    metadata_info[index+1].address = g_heap_base_address + heap_index;
    metadata_info[index+1].size = size;
    }
    else if (initial_flag == TRUE) /*Get Index for allocating memory for case 3*/
    {
        printf("[CASE 3, size = %d] \n",size);
        heap_index = 0;
        for(j = MAX_ALOCATION_ALLOWED -1; j > 0; j--)
        {
            printf("from index = %d , address= %p , size = %d  ==> to  index = %d , address= %p , size = %d \n", j-1,metadata_info[j-1].address,metadata_info[j-1].size , 
            j,metadata_info[j].address,metadata_info[j].size  );
            memcpy(&metadata_info[j], &metadata_info[j-1], sizeof(malloc_info_t));
        }
        address = &our_memory[heap_index];
    metadata_info[index].address = g_heap_base_address + heap_index;
    metadata_info[index].size = size;
    }
    else /*Get Index for allocating memory for case 1*/
    {
        printf("[CASE 1, size = %d] \n",size);
        if(g_allocted_number != 0)
        {
            heap_index = ((metadata_info[index -1].address + metadata_info[index-1].size) - g_heap_base_address);
        }
        else    /* 0 th Location of Metadata for First time allocation*/
            heap_index = 0;
            address = &our_memory[heap_index];
    metadata_info[index].address = g_heap_base_address + heap_index;
    metadata_info[index].size = size;
    }

    

    g_allocted_number += 1;
    printf("my_malloc out \n");
    return address;
}

void my_free(int address)
{
    printf("MY FREE IN , address = %p\n", address);
    //handle case of continuous deletion
    int i =0;
    int copy_meta_data = FALSE;
    
    for(i = 0; i < g_allocted_number; i++)
    {
        if(address == metadata_info[i].address)
        {
            // memset(&our_memory[metadata_info[i].address], 0, metadata_info[i].size);
            g_allocted_number -= 1;
            copy_meta_data = TRUE;
            printf(" **** g_allocted_number in free = %d %p\n", g_allocted_number, address);
            break;
        }
    }
    
    if(copy_meta_data == TRUE)
    {
        if(i == MAX_ALOCATION_ALLOWED -1)
        {
            metadata_info[i].address = 0;
            metadata_info[i].size = 0;
        }
        else
        {
            if(i==0)
            {

            }
            for(int j=i;j<=g_allocted_number;j++)
            memcpy(&metadata_info[j], &metadata_info[j+1], sizeof(malloc_info_t));
        }
            //memcpy(&metadata_info[i], &metadata_info[i-1], sizeof(malloc_info_t));
    }
    printf("MY FREE OUT\n");
}
void printmetadata()
{
    printf("g_allocted_number = %d , \n", g_allocted_number);
    for(int i=0;i<g_allocted_number;i++)
    {
        printf("meatadata: %p , %d\n", metadata_info[i].address , metadata_info[i].size );

    }
}
int main()
{
    int *ptr =NULL;
    int *ptr1 =NULL;
    int *ptr2 =NULL;
    int *ptr3 =NULL;
    int *ptr4 =NULL;
    int *ptr5 =NULL;
    int *ptr6 =NULL;
    
    g_heap_base_address = &our_memory[0];

    ptr = my_malloc(4);
    printmetadata();
    ptr1 = my_malloc(1);
    printmetadata();
    ptr2 = my_malloc(3);
    printmetadata();
    printf("Addresses are: %p, %p, %p,\n", ptr, ptr1, ptr2);
    my_free(ptr);
    printmetadata();
    
    ptr3 = my_malloc(4);
    printmetadata();
    my_free(ptr1);
    printmetadata();
    ptr4 = my_malloc(5);
    printmetadata();
    ptr5 = my_malloc(6);
    printmetadata();
    ptr6 = my_malloc(1);
    printmetadata();
    printf("Addresses are: %p, %p, %p, %p, %p, %p, %p\n", ptr, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6);
    my_free(ptr4);
    printmetadata();
    int* ptr7 = my_malloc(5);
    printmetadata();
    printf("Addresses are: %p, %p, %p, %p, %p, %p, %p\n", ptr, ptr1, ptr2, ptr3, ptr7, ptr5, ptr6);
    return 0;
}


/*my_malloc IN 
[CASE 1, size = 4] 
my_malloc out 
g_allocted_number = 1 , 
meatadata: 0x1e0550e0 , 4
my_malloc IN 
[CASE 1, size = 1] 
my_malloc out 
g_allocted_number = 2 , 
meatadata: 0x1e0550e0 , 4
meatadata: 0x1e0550e4 , 1
my_malloc IN 
 [** here == initial_gap 0 , i = 0 **] 
[**here == gap 0 , i = 0 **]  
[CASE 1, size = 3] 
my_malloc out 
g_allocted_number = 3 , 
meatadata: 0x1e0550e0 , 4
meatadata: 0x1e0550e4 , 1
meatadata: 0x1e0550e5 , 3
Addresses are: 0x556d1e0550e0, 0x556d1e0550e4, 0x556d1e0550e5,
 **** g_allocted_number in free = 2 0x1e0550e0
g_allocted_number = 2 , 
meatadata: 0x1e0550e4 , 1
meatadata: 0x1e0550e5 , 3
my_malloc IN 
 [** here == initial_gap 4 , i = 0 **] 
[CASE 3, size = 4] 
my_malloc out 
g_allocted_number = 3 , 
meatadata: 0x1e0550e0 , 4
meatadata: 0x1e0550e5 , 3
meatadata: 0x1e0550e5 , 3
my_malloc IN 
 [** here == initial_gap 0 , i = 0 **] 
[**here == gap 0 , i = 0 **]  
 [** here == initial_gap 0 , i = 1 **] 
[**here == gap 0 , i = 1 **]  
[CASE 1, size = 5] 
my_malloc out 
my_malloc IN 
 [** here == initial_gap 0 , i = 0 **] 
[**here == gap 0 , i = 0 **]  
 [** here == initial_gap 0 , i = 1 **] 
[**here == gap 0 , i = 1 **]  
 [** here == initial_gap 0 , i = 2 **] 
[**here == gap 0 , i = 2 **]  
[CASE 1, size = 6] 
my_malloc out 
my_malloc IN 
 [** here == initial_gap 0 , i = 0 **] 
[**here == gap 0 , i = 0 **]  
[CASE 2, size = 1] 
my_malloc out 
g_allocted_number = 6 , 
meatadata: 0x1e0550e4 , 1
meatadata: 0x1e0550e5 , 3
meatadata: 0x1e0550e5 , 3
meatadata: 0x1e0550e5 , 3
meatadata: 0x1e0550e8 , 5
meatadata: 0x1e0550ed , 6
Addresses are: 0x556d1e0550e0, 0x556d1e0550e4, 0x556d1e0550e5, 0x556d1e0550e0, 0x556d1e0550e8, 0x556d1e0550ed, 0x556d1e0550e4
partha@partha-VirtualBox:~/Learning_Practices$ */