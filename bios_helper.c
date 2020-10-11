
#include"types.h"
#define SERIAL_COM1   0x2e8
#define SERIAL_COM2   0x3f8


#define CONFIG_COM    SERIAL_COM1




#define PORTB           0x61
#define TIMER_CONTROL   0x43
#define TIMER_COUNTER2  0x42

static unsigned long long tick_in_5700us;


static void bios_clear_time_counter()
{
	_asm{
		push	eax
		push 	ecx
		push 	edx
		
		xor  eax, eax
		xor  edx, edx
		mov  ecx, 010h
		_emit 	00fh
		_emit	030h
		
		pop edx
		pop ecx
		pop eax
	}
	
}

static void bios_sleep570us(u16 count)
{
    _asm{
        push    ax
        push    bx
        push    cx
        push    dx
        mov     al, 00
        mov     cx, count
        mov     bl, al                  
        in      al, PORTB               
        mov     bh, al                 
        and     al, 0FCh               
        or      al, bl                 
        or      al, 01                 
        out     PORTB, al              
        mov     al, 0B6h                
        out     TIMER_CONTROL, al      
        mov     al, 50h                
        out     TIMER_COUNTER2, al      
        mov     al, 05h                
        out     TIMER_COUNTER2, al     
        mov     dx, 0FFFFh           
            
NextCycle:
        mov     al, 80h            
        out     TIMER_CONTROL, al     
        in      al, TIMER_COUNTER2    
        mov     ah, al               
        in      al, TIMER_COUNTER2  
        xchg    al, ah               
        cmp     ax, dx               
        mov     dx, ax               
        jb      NextCycle             
        loop    NextCycle             
        in      al, PORTB               
        and     al, bh                 
        out     PORTB, al              
        pop     dx
        pop     cx
        pop     bx
        pop     ax
    }
}

static u64 bios_current_time_counter()
{
	u64 dtsc = 0;
	u32 high_tsc = 0;
	u32 low_tsc = 0;
	
	_asm{
		push    eax
        push    ecx
        push    edx
        
        mov ecx, 010h
        _emit   00Fh
        _emit   032h
    
        mov low_tsc, eax
        mov  high_tsc, edx
        
        pop edx
        pop ecx
        pop eax
    }
    dtsc = ((u64 )high_tsc << 32) + low_tsc;
    return dtsc;
	
}

static u64 bios_ticks_in_5700us(void)
{
	bios_clear_time_counter();
	bios_sleep570us(10);
	
	return bios_current_time_counter();
	
}

void bios_get_system_time(u64 *time)
{
	u32 ticks_1us = (u32)(tick_in_5700us / 5700);
	u64 ticks = bios_current_time_counter();
	
	*time = ticks / ticks_1us;
}

void bios_delay_micro_seconds(u32 value)
{
	u64 start = 0, end = 0;
	u64 stop_cnt = 0;
	
	stop_cnt = value * (tick_in_5700us / 5700);
	
	start = bios_current_time_counter();
	
	while (end < (stop_cnt + start))
	{
		end = bios_current_time_counter();
	}
}


void bios_print(char * string)
{
	u32 i;
	
	while (string[i])
	{
		if (string[i] == '\n')
		{
			outp(CONFIG_COM, '\r');
		}
		outp(CONFIG_COM, string[i]);
		bios_delay_micro_seconds(87);
		i++;
	}

}

// bios_get_cache_state
// return 0: cache disabled 1: cache enable

u32 bios_get_cache_state()
{
	u32 t = 0;
	u32 ret = 0;     
	
	_asm{
        mov eax,cr0
        mov t,eax
    }
	
	if (t & 0x40000000)
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	
	return ret;
}


void bios_set_cache_state(u32 value)
{
	if (value == 0)
	{
		_asm{
            mov eax,cr0
            or  eax,0x40000000
            mov cr0,eax
        }
	}
	else
	{
		 _asm{
            mov eax,cr0
            and eax,0xBFFFFFFF
            mov cr0,eax
        }
	}
}


u8 bios_read_io(u8 * register_port)
{
	u8 value = 0;
	u16 port = (u16)register_port;
	
	_asm
	{ 
		mov dx,port
        in  al,dx        
        mov value,al
    }
	return value;
}

void bios_write_io(u8 * register_port, u8 value)
{
	u16 port = (u16)register_port;
	
	_asm
	{
		mov dx, port
		mov al, value
		out dx, al
	}
}



void bios_helper_init()
{
	tick_in_5700us = bios_ticks_in_5700us();
	
}

u16 bios_read_pci_config_byte(u8 bus, u8 dev, u8 func, u16 reg, u8 *data)
{
	u16 retval = 0x0000;
	
	_asm
    {
		mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov esi, data

        shl al, 3
        or  bl, al
        mov ax, 0x0B108
        int 1Ah
        jc  RBError
        mov [esi], cl
        
    RBError:
        shr ax, 8
        mov retval, ax
    };
    return retval;
}


u16 bios_read_pci_config_word(u8 bus, u8 dev, u8 func,
                                       u16 reg, u16 *data)
{
	u16 retval = 0x0;
	_asm{
        mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov esi, data

        shl al, 3
        or  bl, al
        mov ax, 0x0B109
        int 1Ah
        jc  RWError
        mov [esi], cx
        
    RWError:
        shr ax, 8

        mov retval,ax
    };
    return retval;
}

u16 bios_write_pci_config_byte(u8 bus, u8 dev, u8 func,
                                    u16 reg, u8 data)
{
	u16 retval = 0x0;
	
	_asm{
		mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov cl, data
        
        shl al, 3       
        or  bl, al
        mov ax, 0x0B10B
        int 1Ah 
        shr ax, 8       
        
        mov retval,ax
    };
    return retval;
}

u16 bios_write_pci_config_word(u8 bus, u8 dev, u8 func,
                                          u16 reg,  u16 data)
{
	u16 retval = 0x0;
	
	_asm{
		mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov cx, data
        
        shl al, 3       
        or  bl, al
        mov ax, 0x0B10C
        int 1Ah 
        shr ax, 8       
        
        mov retval,ax
    };
    return retval;
}


u16 bios_write_pci_config_dword(u8 bus, u8 dev, u8 func,
                                           u16 reg, u32 data)
{
	u16 retval = 0x0;
	
	_asm{
		mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov ecx, data
        
        shl al, 3
        or  bl, al
        mov ax, 0x0B10D
        int 1Ah 
        shr ax, 8       
        
        mov retval,ax
    };
    return retval;
}

u16 bios_read_pci_config_dword(u8 bus, u8 dev, u8 func,
											u16 reg, u32 *data)
{
	u16 retval = 0x0;
	
	_asm{
		mov bh, bus
        mov al, dev
        mov bl, func
        mov di, reg
        mov esi, data
        
        shl al, 3
        or  bl, al
        mov ax, 0x0B10A
        int 1Ah
        jc  RDError
        mov [esi], ecx
    RDError:
        shr ax, 8

        mov retval,ax
    };
    return retval;
}


// Todo: int31 ?
u32 bios_get_linear_addr(u32 phy_addr, u32 size, u32 *linear_addr)
{
    u32 temp_addr = 0;
    u16 dpmi_error = 0;

    _asm{
        mov     ax,  0x0800
        mov     edi, size
        mov     ecx, phy_addr
        shld    esi, edi, 0x10
        shld    ebx, ecx, 0x10
        int     0x31
        jnc     success
        mov     dpmi_error, ax
        xor     eax, eax
        int     3
    success:
        pushfd
        shl     ecx, 0x10
        shrd    ecx, ebx, 0x10
        mov     temp_addr, ecx
        popfd
        mov     eax, ecx
        mov     dpmi_error, 0
    }

    if (!dpmi_error)
    {
        *linear_addr = temp_addr;
        return 1;
    }
    return 0;
}

