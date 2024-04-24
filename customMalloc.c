
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
const int allocationNumber=20;
static int currentAllocation=0;
static unsigned char ourMemory[1024*1024];
int baseaddress=0;
typedef struct {
    int size;
    int address;
}allocation_info;
allocation_info allocationDetails[20];


void* my_malloc(int size)
{
    if(currentAllocation>allocationNumber)return NULL;
    printf("given size %d",size);
    bool addfirst=false, addmid=false;
    int i;
    for(i=0;i<currentAllocation;i++)
    {
        if(allocationDetails[0].address - baseaddress>=size)
        {
            addfirst=true;
            break;
        }
        else 
        {
            int gap=allocationDetails[i+1].address - allocationDetails[i].address -allocationDetails[i].size;
            if(gap>=size)
            {
                addmid=true;
                break;
            }
        }
    }
    void* address;
    int heapindex;
    currentAllocation++;
    if(addfirst)
    {
        heapindex=0;
        address=&ourMemory[heapindex];
        for(int j=allocationNumber-2 ;j>=i;j-- )
        {
            memcpy(&allocationDetails[j+1], &allocationDetails[j], sizeof(allocation_info));
        }
        allocationDetails[i].address=heapindex+ baseaddress;
        allocationDetails[i].size=size;
        return address;
    }
    else if(addmid)
    {
        heapindex=allocationDetails[i].address +allocationDetails[i].size - baseaddress;
        addfirst=&ourMemory[heapindex];
        for(int j=allocationNumber-2 ;j>=i+1;j-- )
        {
            memcpy(&allocationDetails[j+1], &allocationDetails[j], sizeof(allocation_info));
        }
        allocationDetails[i+1].address=heapindex+ baseaddress;
        allocationDetails[i+1].size=size;
        return address;
    }
    else
    {
        heapindex=allocationDetails[currentAllocation-2].address + allocationDetails[currentAllocation-2].size - baseaddress;
        address=&ourMemory[heapindex];
        allocationDetails[currentAllocation-1].address=heapindex+baseaddress;
        allocationDetails[currentAllocation-1].size=size;
        return address;

    }
    return NULL;

}
void myfree(int address)
{
    for(int i=0;i<currentAllocation;i++)
    {
        if(allocationDetails[i].address==address)
        {
            for(int j=i+1;j<currentAllocation;j++)
            {
                memcpy(&allocationDetails[j-1],&allocationDetails[j], sizeof(allocation_info));
            }
            currentAllocation--;
            break;
        }
    }
}
int main()
{
    baseaddress=(size_t)&ourMemory[0];
}