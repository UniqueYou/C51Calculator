#include <reg52.h>
#include <intrins.h>
unsigned  char code table[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit light1 = P2^0;
sbit light2 = P2^1;
sbit light3 = P2^2;
sbit light4 = P2^3;
int result=0;
int tempResult=0;
int countSign;
unsigned char NoInput = 22;
unsigned char Count = 23;

void delay_ms(unsigned int z);
void display( int num);
unsigned char KeyScan();
void getResult();

unsigned char KeyScan()
{
	unsigned char i = 0,j = 0;
	P1 = 0xf0;
	if(((~P1)&0xf0)!=0)
	{
		delay_ms(10);
		if(((~P1)&0xf0)==0)
			return NoInput;
		if(((~P1)&0xfe)!=0)
		{
			P1 = 0xfe;
			while(((~P1)&0x0f)!=0)
			{
				if(((~P1)&0xf0)!=0)
				{
					switch((~P1)&0xf0)
					{
						case 0x10:j = 1;break;
						case 0x20:j = 2;break;
						case 0x40:j = 3;break;
						case 0x80:j = 4;break;
					}
					while((~P1&0xf0)!=0);
					delay_ms(10);
					while((~P1&0xf0)!=0);
					return (4*i + j+5);
				}
				else 
				{
					P1 = (P1 << 1)|0x01;
					i++;				
				}
			}
		}
	}
	return NoInput;
}

//��ʱ����
void delay_ms(unsigned int z){
	unsigned char i,j;
	
	while(--z){
		_nop_();
		i =2;
		j = 199;
		do{
			while(--j);
		}while(--i);
	}
}


//�������ʾ����
void display( int k){
	unsigned int a,b,c,d;
	a = k/1000;
	b = k/100%10;
	c = k/10%10;
	d = k%10;

	light1 = 0;
	P0 = table[a];
	delay_ms(5);
	light1 = 1;
	
	light2 = 0;
	P0 = table[b];
	delay_ms(5);
	light2 = 1;
	
	light3 = 0;
	P0 = table[c];
	delay_ms(5);
	light3 = 1;
	
	light4 = 0;
	P0 = table[d];
	delay_ms(5);
	light4 = 1;

}

//��������ӳ��
 int getInput(int number)
{
		int temp = -1;
		switch(number)
	{
		case 9:temp=1;break;
		case 8:temp=2;break;
		case 7:temp=3;break;
		case 13:temp=4;break;
		case 12:temp=5;break;
		case 11:temp=6;break;
		case 17:temp=7;break;
		case 16:temp=8;break;
		case 15:temp=9;break;
		case 20:temp=0;break;
		case 6:case 10:case 14:case 18:countSign=number;temp=-2;break;
		case 19:temp=-3;break;
	}
	return temp;
}

//����
void count(int countFlag)
{
	switch(countFlag)		
	{
		case 6:result+=tempResult;break;
		case 10:result=tempResult-result;break;
		case 14:result=tempResult*result;break;
		case 18:result=tempResult/result;break;
	}
}

void main()
{
	int temp=0;
	EA = 1;
	EX0= 1;
	IT0 = 0;
	
	while(1)
	{
		temp = getInput(KeyScan());//��ȡ���������
		if(temp!=-1)//���������
		{
			if(temp==-2)//�����������������
			{			
				tempResult = result;		
				result = 0;
				display(result);

			}else  if(temp==-3)//���������ǵȺ�
			{
				count(countSign);
				display(result);
			}else
			{
			result = temp+ result*10;	
			display(result);	
			}				
		}
		else
		{
			display(result);		
		}
			
	}
}

void play() interrupt 0{
//��ˮ��

	unsigned char a ;
	int i;
	while(1){
	a= 0xff;
	for( i=0;i<9; i++){
		P0 = a;
		a = a <<1;
		delay_ms(200);
}
}
}
