#include <stdio.h>

#define NULL 0

#define ErrNo signed int

#define FILE_NAME(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#define LOGGER(M, ...)                                 \
    do{                                         \
        printf("[%s: %d] Method <%s> " M "\r\n", FILE_NAME(__FILE__), __LINE__, __FUNCTION__,##__VA_ARGS__);  \
    } while(0)

// ==== BRANCH PREDICTION & EXPRESSION EVALUATION ====
#if( !defined( unlikely ) )
#define unlikely( EXPRESSSION )     !!(EXPRESSSION)
#endif

/*! @defined    require_action
    @abstract   Requires that an expression evaluate to true with an action to execute otherwise.
    @discussion

    If expression evaluates to false, this prints debugging information (actual expression string, file, line number,
    function name, etc.) using the default debugging output method then executes an action and jumps to a label.
*/
#if( !defined( require_action ) )
#define require_action( X, LABEL, ACTION )                                                                  \
        do                                                                                                  \
        {                                                                                                   \
            if( unlikely( !(X) ) )                                                                          \
            {   /*debug_log();*/                                                                                            \
                { ACTION; }                                                                                 \
                goto LABEL;                                                                                 \
            }                                                                                               \
        }   while ( 1 == 0 )
#endif

// int fputc(int ch,  FILE *f)  
// {
//          
//     USART_SendData(USART1,  (u8) ch);      
//     while (!(USART_GetFlagStatus(USART1,  USART_FLAG_TXE)  ==  SET));      
//     return ch;   
// }  

// int fgetc(FILE *f)  
// {
//          
//     while (!(USART_GetFlagStatus(USART1,  USART_FLAG_RXNE)  ==  SET));      
//     return (USART_ReceiveData(USART1));   
// } 

