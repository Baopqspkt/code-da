/**
 *	Define ahtlab for STM32F407VET6 kit
 *
 *	@author 	Phuoc Nguyen
 *	@email		hoangphuoc261@gmail.com
 *	@website	ahtlab.com
 *	@ide		Keil uVision 5
 */
#include "mylib.h"  
#include "uart.h"
#include "stdio.h"
#include "stdarg.h" 

void myprintf(char* format,...) 
{ 
    char *traverse; 
    uint_32t i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while( *traverse != '%' ) 
        { 
            USART_PutChar(*traverse);
            traverse++; 
        } 

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        USART_PutChar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i < 0) 
                        { 
                            i = -i;
                            USART_PutChar('-'); 
                        } 
                        USART_PutString(convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        USART_PutString(convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        USART_PutString(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        USART_PutString(convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

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
