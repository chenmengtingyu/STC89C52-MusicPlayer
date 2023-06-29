#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

#define Rest 0		//休止符
#define	C3	1		//低音
#define	Db3	2
#define	D3	3
#define	Eb3	4
#define	E3	5
#define	F3	6
#define	Gb3	7
#define	G3	8
#define	Ab4	9
#define	A4	10
#define	Bb4	11
#define	B4	12		//低音
#define	C4	13		//中音
#define	Db4	14
#define	D4	15
#define	Eb4	16
#define	E4	17
#define	F4	18
#define	Gb4	19
#define	G4	20
#define	Ab5	21
#define	A5	22
#define	Bb5	23
#define	B5	24		//中音
#define	C5	25		//高音
#define	Db5	26
#define	D5	27
#define	Eb5	28
#define	E5	29
#define	F5	30
#define	Gb5	31
#define	G5	32
#define	Ab6	33
#define	A6	34
#define	Bb6	35
#define	B6	36		//高音

sbit Buzzer = P1^5;
bit isPlaying = 0;
sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;
sbit k4 = P3^3;

unsigned char mode = 1;

unsigned int FreqTable[]={	//重装载值
	0,		//休止符
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,	//低音
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030, 	//中音
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,	//高音
};

unsigned char code MusicLittleStar[]={
	13,4,
	13,4,
	20,4,
	20,4,
	22,4,
	22,4,
	20,8,
	
	18,4,
	18,4,
	17,4,
	17,4,
	15,4,
	15,4,
	13,8,
	
	20,4,
	20,4,
	18,4,
	18,4,
	17,4,
	17,4,
	15,8,
	
	20,4,
	20,4,
	18,4,
	18,4,
	17,4,
	17,4,
	15,8,
	
	13,4,
	13,4,
	20,4,
	20,4,
	22,4,
	22,4,
	20,8,
	
	18,4,
	18,4,
	17,4,
	17,4,
	15,4,
	15,4,
	13,8,
	
	0xFF
};

unsigned char code MusicTwoTigers[] = {
	C4,4,
	D4,4,
	E4,4,
	C4,4,
	C4,4,
	D4,4,
	E4,4,
	C4,4,
	
	E4,4,
	F4,4,
	G4,8,
	E4,4,
	F4,4,
	G4,8,
	
	G4,2,
	A5,2,
	G4,2,
	F4,2,
	E4,4,
	C4,4,
	G4,2,
	A5,2,
	G4,2,
	F4,2,
	E4,4,
	C4,4,
	
	D4,4,
	G3,4,
	C4,8,
	D4,4,
	G3,4,
	C4,8,
	
	0xFF
};

unsigned char code MusicMercury[] = {
	Rest,2,
	C4,2,
	D4,2,
	E4,2,
	G4,2,
	A5,2,
	G4,2,
	E4,2,
	A5,4,
	G4,2,
	E4,2,
	A5,10,

	A5,2,
	G4,2,
	C5,2,
	E4,4,
	D4,2,
	G4,2,
	E4,4,
	D4,2,
	G4,2,
	E4,10,

	C4,2,
	D4,2,
	E4,2,
	G4,2,
	A5,2,
	G4,2,
	E4,2,
	A5,4,
	G4,2,
	E4,2,
	Ab5,4,
	G4,2,
	F4,4,

	C5,2,
	D5,2,
	C5,4,
	G4,4,
	G4,4,
	E4,2,
	C4,9,

	C4,2,
	D4,2,
	E4,2,
	A4,4,
	C4,6,

	C4,2,
	D4,2,
	E4,2,
	F4,3,
	E4,1,
	D4,6,

	E4,4,
	D4,4,
	C4,8,

	0xFF
};


unsigned char FreqSelect,MusicSelect;

void PlayMercury(){
	Timer0Init();
	isPlaying = 1;
	while(isPlaying){
		if(MusicMercury[MusicSelect] != 0xFF){
				FreqSelect = MusicMercury[MusicSelect];
				MusicSelect++;
				Delay(200 * MusicMercury[MusicSelect]); 
				MusicSelect++;
				TR0 = 0;
				Delay(10);
				TR0 = 1;
		}
		else if(MusicMercury[MusicSelect] == 0xFF){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
		if(k4 == 0){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
	}
}

void PlayTwoTigers(){
	Timer0Init();
	isPlaying = 1;
	while(isPlaying){
		if(MusicTwoTigers[MusicSelect] != 0xFF){
				FreqSelect = MusicTwoTigers[MusicSelect];
				MusicSelect++;
				Delay(100 * MusicTwoTigers[MusicSelect]); 
				MusicSelect++;
				TR0 = 0;
				Delay(10);
				TR0 = 1;
		}
		else if(MusicTwoTigers[MusicSelect] == 0xFF){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
		if(k4 == 0){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
	}
}

void PlayLittleStar(){
	Timer0Init();
	isPlaying = 1;
	while(isPlaying){
		if(MusicLittleStar[MusicSelect] != 0xFF){
				FreqSelect = MusicLittleStar[MusicSelect];
				MusicSelect++;
				Delay(120 * MusicLittleStar[MusicSelect]); 
				MusicSelect++;
				TR0 = 0;
				Delay(10);
				TR0 = 1;
		}
		else if(MusicLittleStar[MusicSelect] == 0xFF){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
		if(k4 == 0){
			MusicSelect = 0;
			TR0 = 0;
			break;
		}
	}
}

void main(){
	while(1){
		if(k1 == 0){
			PlayLittleStar();
		}
		else if(k2 == 0){
			PlayTwoTigers();
		}
		else if(k3 == 0){
			PlayMercury();
		}
	}
}

void Timer0_Routine() interrupt 1{
	if(FreqTable[FreqSelect]){
		TL0 = FreqTable[FreqSelect]%256;
		TH0 = FreqTable[FreqSelect]/256;
		Buzzer =! Buzzer;
	}
}
