
#include "main.h"

#pragma comment( lib, "hge.lib")
#pragma comment( lib, "hgehelp.lib")

//============================================
//  游戏重置函数
//============================================
void rollBack()
{
	scene_id=0;
	timer_gameover = 0;
	gold = 1000;

	em=new EnemyManager(FontLv);
	tm=new TowerManager(FontLv, em);
	pg=new Progress(10,140,11,22,22,hge->Texture_Load("../Source/progress.png"));

	Font=new hgeFont("../Source/font1.fnt");
	Font->SetProportion(1.0);

	flash_timer = 0;
	pFlashSprite = new FlashSprite;
	pFlashSprite->StartFlash("../Source/welcome.swf", 800, 600);

	
	treelife = 7;
	tree_tex=hge->Texture_Load("../Source/tree1.png");
	tree=new hgeSprite(tree_tex,0,0,150,150);
}
//============================================
//option菜单函数
//============================================
void optFunc()
{
	//Option菜单
	float dt=hge->Timer_GetDelta();
	int id_opt = gui_opt->Update(dt);
	static int lastid=0;
	if (id_opt == -1)
	{
		if (lastid == 1)
		{
			//返回按钮
			scene_id = 0;
			gui->Enter();
		}
		else if (lastid == 2)
		{
			//随机化背景音乐 
			srand(hge->Timer_GetTime());
			int num = (rand() % 22) + 1;
			mus_bg = hge->Music_Play(mus, true, 20, num);
			gui_opt->Enter();
		}
		else if (lastid == 3)
		{
			//调节音量
			int value = hSlider->GetValue();
			hge->Channel_SetVolume(mus_bg, value);
			gui_opt->Enter();
		}
		else if (lastid == 4)
		{
			//静音操作
			if (!mute)
			{
				hge->Channel_PauseAll();
				mute = true; 
			}
			else 
			{
				hge->Channel_ResumeAll();
				mute = false;
			}
			gui_opt->Enter();
		}

		else gui_opt->Enter();

	}
	else if(id_opt) { lastid=id_opt; gui_opt->Leave(); }
}
//==========================================
///说明菜单
//==========================================
void htpFunc()
{
	//Option菜单
	float dt=hge->Timer_GetDelta();
	int id_htp = gui_htp->Update(dt);
	static int lastid=0;
	if (id_htp == -1)
	{
		if (lastid == 1)
		{
			//返回按钮
			scene_id = 0;
			gui->Enter();
		}
		else
			gui_htp->Enter();
	}
	else if(id_htp) { lastid=id_htp; gui_htp->Leave(); }
		
}

//==========================================
///介绍菜单
//==========================================
void auFunc()
{
	//Option菜单
	float dt=hge->Timer_GetDelta();
	int id_au = gui_au->Update(dt);
	static int lastid=0;
	if (id_au == -1)
	{
		if (lastid == 1)
		{
			//返回按钮
			scene_id = 0;
			gui->Enter();
		}
		else
			gui_au->Enter();
	}
	else if(id_au) { lastid=id_au; gui_au->Leave(); }

}

//============================================
//游戏运行函数
//============================================
void runGame()
{
	static int lastid2=0;
	float dt=hge->Timer_GetDelta();
	int id2;

	//falsh播放
	if (flash_isplay)
	{
		pFlashSprite->StartFlash("../Source/welcome.swf", 800, 600);
		flash_isplay  = false;
	}
	if (flash_timer < FLASH_LIFE+2)
	{
		flash_timer++;
	}
	
	if (flash_timer < FLASH_LIFE)
	{
		// 更新flash精灵帧
		pFlashSprite->Update(dt);
		on_show = false;
	}
	else if (flash_timer == FLASH_LIFE)
	{
		// 销毁flash精灵
		if (pFlashSprite)
			delete pFlashSprite;
		pFlashSprite = NULL;
		on_show = true;
	}

	if(on_show)
	{
		id2=gui2->Update(dt);
		if(id2 == -1&&SetCharacter==0)
		{
			switch(lastid2)
			{
			case 1:						
				if (gold >= char_price[0])
				{
					SetCharacter=1;
					select_char=new Tower(SetCharacter, mx, my);
					select_char->SetSelected(true);
				}
				else
					gui2->Enter();
				break;
			case 2:
				if (gold >= char_price[1])
				{
					SetCharacter=2;
					select_char=new Tower(SetCharacter, mx, my);
					select_char->SetSelected(true);
				}
				else
					gui2->Enter();
				break;
			case 3:
				if (gold >= char_price[2])
				{
					SetCharacter=3;
					select_char=new Tower(SetCharacter, mx, my);
					select_char->SetSelected(true);
				}
				else
					gui2->Enter();
				break;
			case 4:
				if (gold >= char_price[3])
				{
					SetCharacter=4;
					select_char=new Tower(SetCharacter, mx, my);
					select_char->SetSelected(true);
				}
				else
					gui2->Enter();
				break;
			case 5:
				if (gold >= char_price[4])
				{
					SetCharacter=5;
					select_char=new Tower(SetCharacter, mx, my);
					select_char->SetSelected(true);
				}
				else
					gui2->Enter();
				break;
			case 6:
				if ((HasSelectedChar && gold >= char_price[tm->SelectedChara->model_id-1]*tm->SelectedChara->level) && tm->SelectedChara->level < 2)
				{
					gold -= char_price[tm->SelectedChara->model_id-1]*tm->SelectedChara->level;
					tm->LvUp();
				}
				else
					gui2->Enter();
				break;
			case 7:
				if (HasSelectedChar)
				{
					gold += char_price[tm->SelectedChara->model_id-1]*tm->SelectedChara->level/2;
					tm->Destroy();
					HasSelectedChar=false;
				}
				else 
					gui2->Enter();
				break;
			case 8:
				em->LevelStart(1);
				pg->Start(true);		
				gui2->Enter();				
				break;
			case 9:
				rollBack();
				gui->Enter();
				break;
			}
		}
		else if(id2) { lastid2=id2; gui2->Leave(); }
		pg->Update();
		em->Update();
		if (em->earn_gold > 0)
		{
			gold += em->earn_gold;
			em->earn_gold = 0;
		}
		if(em->cut_life==1)
		{
			treelife-=em->cut_life;
			em->cut_life=0;
		}
		switch(treelife)
		{
			case 7:
				tree_tex=hge->Texture_Load("../Source/tree1.png");
				tree=new hgeSprite(tree_tex,0,0,150,150);
				break;
			case 4:
				tree_tex=hge->Texture_Load("../Source/tree2.png");
				tree=new hgeSprite(tree_tex,0,0,150,150);
				break;
			case 2:
				tree_tex=hge->Texture_Load("../Source/tree3.png");
				tree=new hgeSprite(tree_tex,0,0,150,150);
				break;
			case 0:
				isover=true;
				scene_id = 10;//死亡画面


				break;
			default:
				break;
		}
		tm->Update();
		if(isover)
		{
			gameover->Render(0,0);
			///gameover->SetColor(0,((globaltimer%100)/100.0));
		}
		if (SetCharacter==0)
		{
			tm->SetCharaMOver(mx, my);
			em->SetEnemyMOver(mx, my);
			if ((hge->Input_GetKeyState(HGEK_LBUTTON)) && my < 600)
			{				
				if (tm->MOverChara != NULL)
				{
					//MessageBox(0,"hello","",0);
					tm->SetCharaSelected();
					em->DisSelect();
					HasSelectedEnemy=false;
					HasSelectedChar=true;
				}
				else if (em->MOverEnemy != NULL)
				{
					tm->SetFocusEnemy(em->SetEnemySelected());
					tm->DisSelect();
					HasSelectedEnemy=true;
					HasSelectedChar=false;
				}
			/*	else
				{
					tm->DisSelect();
					em->DisSelect();
					HasSelectedChar=false;
					HasSelectedEnemy=false;
				}*/
			}
		}
		else
		{
			int_x=mx/40;
			int_y=my/40;
			int_num=int_x+int_y*15;
			if (includes(int_num+1, 1))
				CanPlace=false;
			else
				CanPlace=true;
			if(int_x>14&&int_x<20)
				CanPlace=false;
			select_char->SetPos(int_x*40+20, int_y*40+20);
			if ((hge->Input_GetKeyState(HGEK_LBUTTON)) && my < 600 && CanPlace)
			{
				gold -= char_price[SetCharacter-1];
				tm->AddTower(new Tower(SetCharacter, int_x*40+20, int_y*40+20));
				SetCharacter=0;
				select_char=NULL;
				gui2->Enter();
			}
			else 
				if (hge->Input_GetKeyState(HGEK_RBUTTON))
				{
					select_char=NULL;
					SetCharacter=0;
					gui2->Enter();
				}
		}
	}
}

//============================================
//帧函数
//============================================
bool FrameFunc()
{
	
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	globaltimer++;
	hge->Input_GetMousePos(&mx,&my);
	par->MoveTo(mx, my);
	par->Update(dt);

	if (scene_id==0)
	{
		//Show List
		static int lastid=0;
		if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gui->Leave(); }
		int id_list=gui->Update(dt);
		
		//pFlashSprite->Update(dt);
		if(id_list == -1)
		{
			switch(lastid)
			{
				case 1:	
					scene_id = 1;
					gui2->Enter();
					break;
				case 2:
					//gui->SetFocus(lastid);
					//gui->Enter();
					scene_id=2;
					gui_htp->Enter();
					break;
				case 3:
					scene_id = 3;
					gui_opt->Enter();
					break;
				case 4:
					//gui->SetFocus(lastid);
					//gui->Enter();
					scene_id = 4;
					gui_au->Enter();
					break;
				case 5: return true;
			}
		}
		else if(id_list) { lastid=id_list; gui->Leave(); }
	}
	else if (scene_id == 1)
	{
		//游戏运行, 场景1
		runGame();
	}
	else if (scene_id == 2)
	{
		//how to play菜单
		htpFunc();
	}
	else if (scene_id == 3)
	{	
		//option菜单
		optFunc();
	}
	else if (scene_id == 4)
	{
		//介绍菜单
		auFunc();
	}
	else if (scene_id == 10)
	{
		//死亡场景
		timer_gameover = (timer_gameover+1) % 150;
		if (timer_gameover == 148)
		{
			rollBack();
			gui->Enter();
		}
	}

	return false;
}

//============================================
//渲染函数
//============================================
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

    switch(scene_id)
	{
		case 0:		
			bg->Render(0,0);
			par->Render();  //鼠标粒子化渲染
			gui->Render();
			break;
		case 1:
			//falsh渲染
			if (flash_timer < FLASH_LIFE)
			{
				// 绘制flash到指定坐标
				pFlashSprite->Render(0, 0);
			}
			else
			{
				round_bg->Render(0, 0);
				//menu_bg->Render(0,480);
				tree->Render(450,215);
				progress->Render(136,10);
				progress->SetZ(0.5);
				FontM->SetColor(0xffffffff);
				FontM->printf(635,18,0,"Money: %d", gold);
				//Font->SetScale(1.0);
				pg->Update();
				gui2->Render();
				em->Render();
				tm->Render();
				if (SetCharacter!=0 && int_y<20 && CanPlace)
				{
					select_char->Render(FontLv);
				}
				show_the_description();
				FontLv->SetScale(1.0);
			}
			if(iswin)
			{
				win->Render(0,0);
				win->SetZ(0.0);
			}
			break;
		case 2:
			bg->Render(0,0);
			htop->Render(0,0);
			par->Render();
			gui_htp->Render();
			break;
		case 3:
			bg->Render(0, 0);
			hOptBk->Render(0, 0);
			hMus->Render(360, 230);
			par->Render();  //鼠标粒子化渲染
			gui_opt->Render();
			break;
		case 4:
			bg->Render(0, 0);
			au->Render(0, 0);
			par->Render(); 
			gui_au->Render();
			break;
		case 10:
			if (timer_gameover < 148)
				gameover->Render(0, 0);
			break;
	}

	hge->Gfx_EndScene();	
	return false;
}

//============================================
//入口主函数
//============================================
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_SHOWSPLASH,false);
	hge->System_SetState(HGE_LOGFILE, "test.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "TowerDefence");

	hge->System_SetState(HGE_FPS, 60);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_ZBUFFER,true); 

	if(hge->System_Initiate())
	{	
		
		bg_tex=hge->Texture_Load("../Source/bg.jpg"); //载入背景图片
		r_tex=hge->Texture_Load("../Source/main_game.jpg");  //地图图片
		//menu_tex=hge->Texture_Load("../Source/bg_menu.png");
		progress_bk=hge->Texture_Load("../Source/progress_bk.png");//进度条背景
		mus_background = hge->Texture_Load("../Source/mus1_bg.png");  //音量条背景图片
		htp_tex=hge->Texture_Load("../Source/how_to_play.png");//how to play说明图片
		au_tex=hge->Texture_Load("../Source/about.png");//关于我们说明
		//载入鼠标样式图片
		cur_tex=hge->Texture_Load("../Source/cursor.png");
		//菜单背景音乐
		mus=hge->Music_Load("../Source/Music.mo3");
		//菜单特效音乐
		snd=hge->Effect_Load("../Source/mouseover.ogg");
		tree_tex=hge->Texture_Load("../Source/tree1.png");//生命之树
		final_tex=hge->Texture_Load("../Source/gameover.jpg");
		tree=new hgeSprite(tree_tex,0,0,150,150);
		//字体
		Font=new hgeFont("../Source/font1.fnt");
		FontM=new hgeFont("../Source/font1.fnt");
		FontLv = new hgeFont("../Source/font1.fnt");
		win_tex=hge->Texture_Load("../Source/pass.jpg");
		win=new hgeSprite(win_tex,0,0,800,600);
		//鼠标精灵
		cursor=new hgeSprite(cur_tex,0,0,32,32);
		//背景图片精灵
		bg=new hgeSprite(bg_tex,0,0,800,600);
		round_bg=new hgeSprite(r_tex,0,0,800,600);
		gameover=new hgeSprite(final_tex,0,0,800,600);
		htop=new hgeSprite(htp_tex,0,0,800,600);
		au=new hgeSprite(au_tex,0,0,800,600);
		hMus = new hgeSprite(mus_background, 0, 0, 126, 25);  //音量条背景精灵
		hOptBk = new hgeSprite(hge->Texture_Load("../Source/option.png"), 0, 0, 800, 600);

		//menu_bg=new hgeSprite(menu_tex,0,0,800,120);
		progress=new hgeSprite(progress_bk,0,0,330,27);
		//show_bg=new hgeSprite(hge->Texture_Load("../Source/show_bg.png"),0,0,800,300);
		//show_lvcom=new hgeSprite(hge->Texture_Load("../Source/show_lvcom.png"),0,0,800,300);
		//show_lvst=new hgeSprite(hge->Texture_Load("../Source/show_lvst.png"),0,0,800,300);
		show_attr1=new hgeSprite(hge->Texture_Load("../Source/showattr1.png"),0,0,200,237);
		show_attr2=new hgeSprite(hge->Texture_Load("../Source/showattr2.png"),0,0,200,237);
		show_attr3=new hgeSprite(hge->Texture_Load("../Source/showattr3.png"),0,0,200,237);
		show_attr4=new hgeSprite(hge->Texture_Load("../Source/showattr4.png"),0,0,200,237);

		//生成菜单
		gui=new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(1,Font,snd,630,50,0.0f,"New Game"));
		gui->AddCtrl(new hgeGUIMenuItem(2,Font,snd,675,90,0.1f,"How to Play"));
		gui->AddCtrl(new hgeGUIMenuItem(3,Font,snd,625,130,0.2f,"Options"));
		gui->AddCtrl(new hgeGUIMenuItem(4,Font,snd,675,170,0.3f,"About us"));
		gui->AddCtrl(new hgeGUIMenuItem(5,Font,snd,620,210,0.4f,"Exit"));
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(cursor);
		gui->SetFocus(1);
		gui->Enter();
		
		///生成how to play 菜单
		gui_htp=new hgeGUI();
		gui_htp->AddCtrl(new hgeGUIMenuItem(1,Font,snd,700,500,0.0f,"Back"));
		gui_htp->SetNavMode(HGEGUI_LEFTRIGHT | HGEGUI_CYCLED);
		gui_htp->SetCursor(cursor);
		gui_htp->SetFocus(3);


		///生成介绍菜单
		gui_au=new hgeGUI();
		gui_au->AddCtrl(new hgeGUIMenuItem(1,Font,snd,700,500,0.0f,"Back"));
		gui_au->SetNavMode(HGEGUI_LEFTRIGHT | HGEGUI_CYCLED);
		gui_au->SetCursor(cursor);
		gui_au->SetFocus(3);


		//生成option菜单
		gui_opt = new hgeGUI();
		gui_opt->AddCtrl(new hgeGUIMenuItem(1, Font, snd, 700, 500, 0.0f, "Back"));
		gui_opt->AddCtrl(new hgeGUIButton(2, 350, 275, 171, 52, hge->Texture_Load("../Source/chang_music.png"), 0, 0));
		hSlider = new optSlider(3, 360, 230, 126, 25,  hge->Texture_Load("../Source/mus1.png"), 0, 0, 11, 20);
		gui_opt->AddCtrl(hSlider);
		hButton = new hgeGUIButton(4, 400,340, 44, 36, hge->Texture_Load("../Source/mus_btn.png"), 0, 0);
		hButton->SetMode(true);  //启用checkbox模式
		gui_opt->AddCtrl(hButton);
		gui_opt->SetNavMode(HGEGUI_LEFTRIGHT | HGEGUI_CYCLED);
		gui_opt->SetCursor(cursor);
		gui_opt->SetFocus(2);

		//生成游戏界面
		gui2=new hgeGUI();
		selector1 = new Selector(1, snd, 642, 156, Font);
		selector2 = new Selector(2, snd, 700, 178, Font);
		selector3 = new Selector(3, snd, 668, 213, Font);
		selector4 = new Selector(4, snd, 710, 246, Font);
		gui2->AddCtrl(selector1);
		gui2->AddCtrl(selector2);
		gui2->AddCtrl(selector3);
		gui2->AddCtrl(selector4);
		gui2->AddCtrl(new hgeGUIButton(8, 685, 366, 75, 24, hge->Texture_Load("../Source/fight.png"), 0, 0));
		gui2->AddCtrl(new hgeGUIButton(6, 670, 400, 75, 24, hge->Texture_Load("../Source/levelup.png"), 0, 0));
		gui2->AddCtrl(new hgeGUIButton(7, 678, 434, 75, 24, hge->Texture_Load("../Source/sold.png"), 0, 0));
		gui2->AddCtrl(new hgeGUIButton(9, 685, 468, 75, 24, hge->Texture_Load("../Source/back.png"), 0, 0));
		gui2->SetNavMode(HGEGUI_NONAVKEYS);
		gui2->SetCursor(cursor);

		em=new EnemyManager(FontLv);
		tm=new TowerManager(FontLv, em);
		pg=new Progress(10,140,11,22,22,hge->Texture_Load("../Source/progress.png"));

		//播放背景音乐
		mus_bg = hge->Music_Play(mus, true, 20, 1);

		//跟随鼠标的粒子效果
		spt=new hgeSprite(hge->Texture_Load("../Source/particles.png"), 64, 0, 32, 32);
		spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		spt->SetHotSpot(16,16);
		par = new hgeParticleSystem("../Source/trail.psi", spt);
		par->Fire();  //粒子化启动

		// 创建flash精灵
		pFlashSprite = new FlashSprite;
		// 加载flash文件
		//pFlashSprite->StartFlash("../Source/welcome.swf", 800, 600);

		//进入帧循环
		hge->System_Start();

		//析构
		delete gui;
		delete Font;
		delete cursor;
		hge->Texture_Free(cur_tex);
		hge->Texture_Free(bg_tex);
		hge->Texture_Free(r_tex);
		hge->Effect_Free(snd);
		hge->Music_Free(mus);
		// 销毁flash精灵
		if (pFlashSprite)
			delete pFlashSprite;
	}
	else 
	{
		//VS2005与VS2008此处编译有不相符的地方出现bug
		//MessageBox(NULL, (LPCWSTR) hge->System_GetErrorMessage(), (LPCWSTR) "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}

	hge->System_Shutdown();
	hge->Release();
	return 0;
}