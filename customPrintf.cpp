// remember, va_list args, va_start(args , namesargs), va_end(args), va_arg(args, arg_type)
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
using namespace std;
 
void myprintf(const char* str, ...)  ///.... for variable nums of args
{
    va_list ptrs;
    va_start(ptrs, str);
    
    char token[1000];
    int k=0;
    for(int i=0;str[i]!='\0';i++)
    {
        token[k++]=str[i];
        if(str[i+1]=='%' || str[i+1]=='\0')
        {
            if(token[0]!='%')
            {
                token[k]='\0';
                //cout<<" **token j="<<token<<endl;
                fprintf(stdout, "%s", token);
                cout<<endl;
                k=0;
            }
            else
            {
                int j=0;
                token[k]='\0';
                while(token[j]<'a' && j<k)
                j++;
               // cout<<" token j="<<token<<endl;
                if(token[j]=='d'|| token[j]=='u'|| token[j]=='i' || token[j]=='h')
                {
                    fprintf(stdout,token,va_arg(ptrs,int) );
                }
                else if(token[j]=='f')
                {
                    fprintf(stdout,token,va_arg(ptrs,float) );
                }
                else if(token[j]=='c')
                {
                    fprintf(stdout,"%d",va_arg(ptrs,char) );
                }
                else if(token[j]=='l')
                {
                     if(token[j]=='d'|| token[j]=='u'|| token[j]=='i' || token[j]=='h')
                    {
                        fprintf(stdout,token,va_arg(ptrs,long) );
                    }
                    else if(token[j]=='f')
                    {
                        fprintf(stdout,token,va_arg(ptrs,double) );
                    }
                }
                else if(token[j]=='s')
                {
                    fprintf(stdout, token , va_arg(ptrs, char*));
                }
                cout<<endl;
                k=0;
                

            }
        }
    }
    va_end(ptrs);
}



int main()
{
    myprintf(" hello my name is %s  and I am  %d", "partha", 24);
}