#ifndef __MAIN__
#define __MAIN__



#include <cstdlib>
#include <hge.h> 
#include <cassert>
#include <hgesprite.h>
#include <hgeparticle.h>
#include <hgegui.h>
#include <hgeguictrls.h>

#include "menu.h" 
#include "control.h"
#include "enemy.h"
#include "tower.h"
#include "bullet.h"
#include "towerManager.h"
#include "enemyManager.h"
#include "option.h"
#include "progress.h"
#include "FlashSprite.h"

#define FLASH_LIFE 760

//////////////////////////////////////////////////////////////////////////
// 全局变量
//////////////////////////////////////////////////////////////////////////
HGE *hge=0;
int scene_id = 0;  //0是菜单, 1是游戏,2是说明, 3是选项
hgeFont * Font,*FontM, *FontLv;
hgeGUI	 *gui, *gui_opt, *gui2,*gui_htp,*gui_au;
hgeSprite *bg, *cursor;
HEFFECT snd; //菜单特效音
HMUSIC mus; //背景音乐
hgeParticleSystem*	par;   // 粒子系统
hgeSprite *spt;  //粒子系统精灵
int globaltimer=0;
bool isover=false;

//////////////////////////////////////////////////////////////////////////
// 场景1，，游戏过程中
//////////////////////////////////////////////////////////////////////////
hgeSprite *round_bg, * menu_bg,  *show_attr1,*progress,*tree,*gameover,*htop,*au,*win,*show_attr2,*show_attr3,*show_attr4;
HTEXTURE cur_tex, bg_tex, menu_tex,r_tex,progress_bk,tree_tex,final_tex,htp_tex,au_tex,win_tex;

Tower *select_char;
TowerManager* tm;
EnemyManager* em;
Progress * pg;
Selector * selector1, * selector2, * selector3, * selector4, * selector5;
FlashSprite *pFlashSprite = NULL;  //falsh精灵

bool CanPlace=false;
int flash_timer = 0;  //flash计时器
bool flash_isplay = true;  //falsh开始播放标记

bool HasSelectedChar=false;
bool HasSelectedEnemy=false;
bool on_show=true;
bool st_or_com=true;

float mx, my;
int int_x, int_y, int_num;
int SetCharacter=0;
int show_timer=0;
int gold=1000;
int treelife=7;
int char_price[4]={100,200,400,800};

extern wchar_t * description_all[4];
extern int rangedata[4][2];
extern int atk_speed[4];
extern int atkdata[4][2];
bool iswin=false;


static int river[]={2,17,32,33,34,35,36,37,38,39,40,41,56,71,77,78,79,80,81,82,83,84,85,86,92,107,122,137,149,152,164,167,
168,169,170,171,172,173,174,175,176,177,178,179};

static int barrier[]={4,5,6,88,89,103,104,105,110,111,112,113,117,118,119,120,129,133,134,135,145,146,147};


//////////////////////////////////////////////////////////////////////////
// 场景3，，option菜单
//////////////////////////////////////////////////////////////////////////
bool mute = false;  //true表示处于静音状态
optSlider* hSlider;
hgeGUIButton* hButton;
HCHANNEL mus_bg;  //播放背景音乐的通道，用于控制音量
HTEXTURE mus_background;  //音量条背景图片
hgeSprite *hMus, *hOptBk;

//////////////////////////////////////////////////////////////////////////
//场景10 ， 树死亡画面
//////////////////////////////////////////////////////////////////////////
int timer_gameover = 0;  //死亡画面计时器



/************************************************************************/
/* 以下是一些函数                                                          */
/************************************************************************/
bool includes(int num, int round)
{
	int *cap;
	int *cap1;
	int size;
	int size1;
	switch(round)
	{
	case 1:
		cap=river;
		size=150;
		cap1=barrier;
		size1=100;
		break;
	case 2:
		break;
	}
	for (int i=0; i< size; i++)
	{
		if (cap[i]==num)
			return true;
		if(cap1[i]==num)
			return true;
	}
	return false;
}

//void lvshow()
//{
//	if (on_show)
//	{
//		if (st_or_com)
//		{
//			if (show_timer < 100)
//				show_bg->Render(0,100);
//			if (show_timer < 60)
//				show_lvst->Render(800-show_timer*15,100);
//			else if ((show_timer >= 60) && (show_timer < 70))
//				show_lvst->Render(-100,100);
//			else if ((show_timer >= 70) && (show_timer < 90))
//				show_lvst->Render(-100+(show_timer-70)*5,100);
//			else if ((show_timer >= 90) && (show_timer < 100))
//				show_lvst->Render(0,100);
//			else
//			{
//				show_bg->Render(0,100);
//				show_bg->SetColor(ARGB(255-(show_timer-100)*10,255,255,255));
//				show_lvst->Render(0,100);
//				show_lvst->SetColor(ARGB(255-(show_timer-100)*10,255,255,255));
//			}
//		}
//		else
//		{
//			if (show_timer < 100)
//				show_bg->Render(0,100);
//			if (show_timer < 60)
//				show_lvcom->Render(800-show_timer*15,100);
//			else if ((show_timer >= 60) && (show_timer < 70))
//				show_lvcom->Render(-100,100);
//			else if ((show_timer >= 70) && (show_timer < 90))
//				show_lvcom->Render(-100+(show_timer-70)*5,100);
//			else if ((show_timer >= 90) && (show_timer < 100))
//				show_lvcom->Render(0,100);
//			else
//			{
//				show_bg->Render(0,100);
//				show_bg->SetColor(ARGB(255-(show_timer-100)*10,255,255,255));
//				show_lvcom->Render(0,100);
//				show_lvcom->SetColor(ARGB(255-(show_timer-100)*10,255,255,255));
//			}
//		}
//	}
//}

void show_the_description()
{
	int id = -1;
	int level = 1;
	if (selector1->selected)
		id = 1;
	else if (selector2->selected)
		id = 2;
	else if (selector3->selected)
		id = 3;
	else if (selector4->selected)
		id = 4;
	if (id != -1)
	{
		//show_attr->Render(mx-200, my);
		switch(id)
		{
		case 1:
			show_attr1->Render(mx-200, my);
			break;
		case 2:
			show_attr2->Render(mx-200, my);
			break;
		case 3:
			show_attr3->Render(mx-200, my);
			break;
		case 4:
			show_attr4->Render(mx-200, my);
			break;
		default:break;
		}
	}
}


#endif
