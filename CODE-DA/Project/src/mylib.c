
#include "mylib.h"
void myprintf2(char* format,...) 
{ 
    char *traverse; 
    int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while(( *traverse != '%' )&& (*traverse != '\0'))
        { 
            USART2_PutChar(*traverse);
            traverse++; 
        } 
				traverse++; 


        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        USART2_PutChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            USART2_PutChar('-'); 
                        } 
                        USART2_PutString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        USART2_PutString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        USART2_PutString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        USART2_PutString(convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 
////////////////////////////////////////////////////////////////////
//myprintf1
void myprintf1(char* format,...) 
{ 
    char *traverse; 
    int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while(( *traverse != '%' )&& (*traverse != '\0'))
        { 
            USART1_PutChar(*traverse);
            traverse++; 
        } 
				traverse++; 


        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        USART1_PutChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            USART1_PutChar('-'); 
                        } 
                        USART1_PutString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        USART1_PutString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        USART1_PutString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        USART1_PutString(convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

//myprintf1
void myprintf3(char* format,...) 
{ 
    char *traverse; 
    int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while(( *traverse != '%' )&& (*traverse != '\0'))
        { 
            USART3_PutChar(*traverse);
            traverse++; 
        } 
				traverse++; 


        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        USART3_PutChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            USART3_PutChar('-'); 
                        } 
                        USART3_PutString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        USART3_PutString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        USART3_PutString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        USART3_PutString(convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 
///////////////////////////////////////////////////////////////////
char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}
