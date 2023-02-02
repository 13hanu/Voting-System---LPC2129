#include<lpc21xx.h>
#include "phearderfile.h"
#include "plcdh.h"
  
extern int k,BJP=0,AAP=0,TDP=0,CPM=0;
  
int r,c;

//-----------LCD interfacting-------------------
	
	void lcd_cmd(char c)
		{
		IOPIN0 = (c<<15)|(IOPIN0 & ~(0xff<<15));
		IOCLR0 = RS;
		IOCLR0 = RW;
		IOSET0 = EN;
		delay(50);
		IOCLR0 = EN;
		}

	void lcd_init(void)
		{
		IODIR0 |=LCD;
		lcd_cmd(0x38);
		lcd_cmd(0x0E);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		}

	void lcd_data(char c)
		{
		//IOPIN0 = (data<<15);
		IOPIN0 = (c<<15)|(IOPIN0 & ~(0xff<<15));
		IOSET0 = RS;
		IOCLR0 = RW;
		IOSET0 = EN;
		delay(50);
		IOCLR0 = EN;
        }

	void lcd_num(unsigned int num)
		{
			if(num)
		   {
		   lcd_num(num/10);
		   lcd_data((num%10) + 48);
		   }
		}

	void lcd_str(char *str)
		{
		while(*str)
		
		lcd_data(*str++);
		
		}
	
	void lcd_str2(char *str)
	{
		int ct=0;
		lcd_cmd(0x01);
	 	lcd_cmd(0x80);
			while(*str)
			{
			lcd_data(*str++);
			ct=(ct+1)%32;
			if(ct==16)
			lcd_cmd(0xc0);
			if(ct==0)
			{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			} 
	        }
	}


//--------------------------------

	
//---------main_menu--------------

void main_menu()
	{
	lcd_init();
	lcd_str("Welcome");
	delay(2000);
	lcd_init();
	lcd_str("Press '1'->voter");
	lcd_cmd(0xC0);
	lcd_str("Press '2'->Admin");
	
	
	}
//---------Display1--------------


void display1(r,c)
		{
		if(r && c)
		{
		k=(r+(4*(c-1)));
		lcd_init();
		while(k!=13)
          {
					if (k==9)
					{
					lcd_str("voted for 'BJP'");
					delay(1000);
					BJP++;
					voter();
					}
					else if(k==10)
					{ 
					lcd_str("voted for 'TDP'");
					delay(1000);
					TDP++;
					voter();
					}
					else if(k==11)
					{ 
					lcd_str("voted for 'AAP'");
					delay(1000);
					AAP++;
					voter();
					}
					else if(k==12)
					{ 
					lcd_str("voted for 'CPM'");
					delay(1000);
					CPM++;
					voter();
					}
					else 
					{
					lcd_str("ERROR");
					delay(500);
					voter();
					}
			}
		  getCOLS(); 
	     }
	}	

 
//---------Display--------------

void display(r,c)
		{
		if(r && c)
		{
		k=(r+(4*(c-1)));
		lcd_init(); 
		
		if(k==1)
	      {
	        voter();

          }
   else if(k==2)
	      {
	        admin();
	      }	 
   else
	      {
	         main_menu();
	      }
	      }

}
//---------Get_col1--------------

int getCOLS1()
{
int r=c=0,val;
while(1)
{
IODIR1 |= ROWS;
IODIR1 &= ~(COLS);
									 	
val= (IOPIN1 & COLS);
val= val>>21;
switch(val)
{
case 0xe : c=1;
			r = getRow();
			break;
case 0xd : c=2;
			r = getRow();
			    
			break;
case 0xb : c=3;
			r = getRow();
			    
			break;
case 0x7 : c=4;
			r = getRow();
							
			break;
default : 	break;

			
}
display1(r,c);
}
}							
//---------Get_col--------------

int getCOLS()
{
int r=c=0,val;
while(1)
{
IODIR1 |= ROWS;
IODIR1 &= ~(COLS);
									 	
val= (IOPIN1 & COLS);
val= val>>21;
switch(val)
{
case 0xe : c=1;
			r = getRow();
			break;
case 0xd : c=2;
			r = getRow();
			    
			break;
case 0xb : c=3;
			r = getRow();
			    
			break;
case 0x7 : c=4;
			r = getRow();
							
			break;
default : 	break;

			
}
display(r,c);
}
}	

//---------Getrow--------------

int getRow()
{
 int val;
 IODIR1 =COLS;
 IOCLR1 =COLS;
 val=((IOPIN1 & ROWS)>>17);

switch(val)
{
case 0xe: return 1;
case 0xd: return 2;
case 0xb: return 3;
case 0x7: return 4;
default:  return  0;
}	
}

//---------Voter--------------
void voter()
{ 
int r=c=0;
lcd_init();
lcd_cmd(0x80);
lcd_str("1.BJP");
lcd_cmd(0x88);
lcd_str("2.TDP");
lcd_cmd(0xC0);
lcd_str("3.AAP");
lcd_cmd(0xC8);
lcd_str("4.CPM");
getCOLS1();
	
main_menu();
}
	
//---------ADMIN--------------

void admin()
{
lcd_init();
lcd_str("BJP :");
lcd_num(BJP);

lcd_cmd(0x88);
lcd_str("TDP :");
lcd_num(TDP);

lcd_cmd(0xC0);
lcd_str("AAP :");
lcd_num(AAP);

lcd_cmd(0xC8);
lcd_str("CPM :");
lcd_num(CPM);


delay(5000);


}
				