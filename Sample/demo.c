#include "mrc_base.h"

#define BMP_NAME	"hellostr.bmp"
#define MID_NAME	"xj.mid"
#define BMP_W		210
#define BMP_H		40

int32	g_timerH;
uint16	* pBmp;
int32	bmpDataLen;
int32 Counter = 0;
int32 w = 0, h = 0;
void TimerCB(int32 data)
{
	static int32 x_Value = 0;
	mr_screeninfo  ms;
	mrc_getScreenInfo(&ms);
	
	mrc_clearScreen(mrc_rand() , mrc_rand(), mrc_rand());

	mrc_textWidthHeight("M-CAP7AIN", FALSE, MR_FONT_BIG, &w, &h);
	mrc_drawText("M-CAP7AIN" , (ms.width-w)/2 , (ms.height-h)/2 , 255 , 255 , 255 , 0 , MR_FONT_BIG);
	w = 0;
	mrc_textWidthHeight("M-CAP7AIN", FALSE, MR_FONT_MEDIUM, &w, &h);
	mrc_drawText("http://ictcaptain.blog.ir" , 25 , (ms.height-h)/1.7 , 255 , 255 , 255 , 0 , MR_FONT_MEDIUM);

	mrc_drawLine(20,20, ms.width-20,20, 200, 200, 200);
	mrc_drawLine(20,30, 20,ms.height-20, 200, 200, 200);
	mrc_drawLine(30,ms.height-20, ms.width-20,ms.height-20, 200, 200, 200);

	mrc_refreshScreen(0, 0, ms.width, ms.height);
}


int32 mrc_init(void)
{
	g_timerH = mrc_timerCreate();
	if(g_timerH)
	{
		mrc_timerStart(g_timerH, 700, 0, TimerCB, 1);
	}

	mrc_setVolume(1);
	if(MR_SUCCESS == mrc_soundSet(0, MID_NAME, MR_SOUND_MIDI))
	{
		mrc_soundPlay(0, 1);
	}

	return MR_SUCCESS;
}


int32 mrc_event(int32 code, int32 param0, int32 param1)
{
	switch(code)
	{	
		case MR_KEY_PRESS:
			mrc_soundStop(0);
			mrc_exit();
			break;
		default:
			break;
	}
	return MR_SUCCESS;
}

int32 mrc_pause(void)
{
	return MR_SUCCESS;	
}

int32 mrc_resume(void)
{
	return MR_SUCCESS;
}

int32 mrc_exitApp(void)
{	
	if(g_timerH)
	{
		mrc_timerDelete(g_timerH);
		g_timerH = 0;
	}
	if(pBmp)
	{
		mrc_freeFileData(pBmp, bmpDataLen);
		pBmp = NULL;
	}

	mrc_soundSet(0, "*", MR_SOUND_MIDI);
	return MR_SUCCESS;
}

int32 mrc_extRecvAppEventEx(void)
{
	return MR_SUCCESS;	
}

int32 mrc_extRecvAppEvent(void)
{
	return MR_SUCCESS;	
}