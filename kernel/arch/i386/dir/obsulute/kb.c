#include <stdint.h>
#include <stddef.h>

#include <kernel/asmFunctions.h>
#include <kernel/isr.h>
#include <kernel/kblayout.h>

volatile char* buffer; //For storing strings
volatile char* buffer2;
volatile uint32_t kb_count = 0; //Position in buffer
volatile int gets_flag = 0;

volatile int shift_flag=0;
volatile int caps_flag=0;

unsigned short ltmp;
int ktmp = 0;

void do_gets();

static void keyboard_handler(registers_t regs)
{
    unsigned char scancode;

    //Read scancode
    scancode = inb(0x60);
    
    switch (scancode)
    {
           case 0x3A:
                /* CAPS_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 4;
                outb(0x60,ltmp);
                
                if(caps_flag)
                caps_flag=0;
                else
                caps_flag=1;
                break;
           case 0x45:
                /* NUM_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 2;
                outb(0x60,ltmp);
                break;
           case 0x46:
                /* SCROLL_LOCK LEDS */
                outb(0x60,0xED);
                ltmp |= 1;
                outb(0x60,ltmp);
                break;
           case 60: /* F12 */
                
                break;
           default:
                break;
    }

    if (scancode & 0x80)
    {
        //Key release
        
        //Left and right shifts
        if (scancode - 0x80 == 42 || scancode - 0x80 == 54)
			shift_flag = 0;
    } else {   
        //Keypress (normal)
        
        //Shift
        if (scancode == 42 || scancode == 54)
		{
			shift_flag = 1;
			return;
		}
        
        //Gets()
        if(kbdus[scancode] == '\n')
        {
             if(gets_flag == 0) do_gets();
             gets_flag++;
             for(;kb_count; kb_count--)
                  buffer[kb_count] = 0;              
        } else {
             if(kbdus[scancode] == '\b')
             {
                  if(kb_count)
                  buffer[kb_count--] = 0;
             } else {
                  buffer[kb_count++] = kbdus[scancode];
             }

printf(kbdus[scancode]);
                  
        } }}

/*void keyboard_handler(registers_t regs)
{ 
     Read from the keyboard's data buffer
   

    if (read_scan_code() & 0x80){}

    else{      
        print_char(kbdus[read_scan_code()],0);
    }

}

 uint8 read_scan_code()
    {
        return inb(KBD_DATA_PORT);
    }
 */

void keyboard_install()
{
   // register_interrupt_handler(1, keyboard_handler);
register_interrupt_handler(IRQ1, keyboard_handler);
}



void do_gets()
{
     buffer[kb_count++] = 0; //Null terminated 
     for(;kb_count; kb_count--)
     {
          buffer2[kb_count] = buffer[kb_count];
     }
     return;
} 

unsigned char getch()
{
     unsigned char getch_char;
     
     if(kbdus[inb(0x60)] != 0) //Not empty
     outb(0x60,0xf4); //Clear buffer
     
     while(kbdus[inb(0x60)] == 0); //While buffer is empty
     getch_char = kbdus[inb(0x60)];
     outb(0x60,0xf4); //Leave it emptying
     return getch_char;
}

char* gets()
{ 
     gets_flag = 0;
     while(gets_flag == 0);
     return (char*)buffer2;
}


