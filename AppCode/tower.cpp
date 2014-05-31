

#include "Tower.h"

char * filename[4]={"../Source/tower1.png","../Source/tower2.png","../Source/tower3.png","../Source/tower4.png"};
char * description_all[4] = { "xiaoA", "xiaoB", "xiaoC", "xiaoD"};
int rangedata[4][2]={{150,150},{150,150},{200,200},{150,150}};
int atk_speed[4]={40,40,30,60};
int atkdata[4][2]={{10,15},{20,25},{10,20},{30,50}};

extern void show_description(int prio, int id);

Tower::Tower(int mmodel_id, float xx, float yy)
{
	hge=hgeCreate(HGE_VERSION);
	model_id=mmodel_id;
	m_x=xx;
	b_x=xx;
	m_y=yy;
	b_y=yy;
	image_tex=hge->Texture_Load(filename[model_id-1]);
	Init();
}

Tower::~Tower()
{
	hge->Texture_Free(image_tex);
	//hge->Texture_Free(ring_tex);
	delete image;
	//delete ring;
	hge->Release();
}

void Tower::Init()
{	
	level=1;
	image=new hgeSprite(image_tex,0, 0,40,40);
	//ring_tex=hge->Texture_Load("../Source/cursor.png");
	//ring=new hgeSprite(ring_tex,0,32,32,32);
	circle=new hgeSprite(hge->Texture_Load("../Source/circle.png"),0,0,500,500);
	bullet=new hgeSprite(hge->Texture_Load("../Source/bullet00.png"),0,4*16,16,16);
	bullet->SetZ(0.05f);
	image->SetZ(0.1f);
	//ring->SetZ(0.2f);
	circle->SetZ(0.55f);
	selected = false;
	mover = false;
	bullet_hit = false;
	t_e_distance = 8888;
	t_e = NULL;
	atk=atkdata[model_id-1][0];
	range=rangedata[model_id-1][0];
	atk_timer=atk_speed[model_id-1]-1;
}

void Tower::Render(hgeFont *fnt)
{	

	if (selected)
	{
		image->SetTextureRect(38, 0, 38,38);
		//ring->Render(m_x-16,m_y-16);
		circle->RenderEx(m_x-range, m_y-range, 0, (float)range*2/500);
	}
	else
	{
		if (mover)
		{
			image->SetTextureRect(38, 0, 38,38);
			circle->RenderEx(m_x-range, m_y-range, 0, (float)range*2/500);
		}
		else
		{
			image->SetTextureRect(0, 0, 38,38);
		}
	}
	if (BulletList.size() != 0)
	{
		std::vector<Bullet*>::iterator i;
		for(i = BulletList.begin(); i != BulletList.end(); i++)
		{
			(*i)->Render();
		}
	}
	image->Render(m_x-18,m_y-24);	
	fnt->SetColor(0xffffff00);
	fnt->SetProportion(0.4);
	fnt->printf(m_x-10,m_y-40, 0,"Lv: %d", level);
}

void Tower::Update()
{
	bool hit=false;
	TargetEnemyCalc();
	if (t_e != NULL)
	{
		atk_timer+=1;
		if (atk_timer == atk_speed[model_id-1])
		{
			BulletList.push_back(new Bullet(model_id, m_x, m_y, t_e, atk));
			atk_timer=0;
		}	
	}
	else
		atk_timer=0;
	if (BulletList.size() != 0)
	{
		std::vector<Bullet*>::iterator i;
		for(i = BulletList.begin(); i != BulletList.end(); )
		{
			hit=(*i)->Update();
			if (hit)
			{
				delete (*i);
				i=BulletList.erase(i);
			}
			else
				i++;
		}
	}
}

bool Tower::MouseOver(float x, float y)
{
	if((x>m_x-20)&&(x<m_x+20)&&(y>m_y-20)&&(y<m_y+16))
		return true;

	return false;
}


void Tower::DistanceCalc(Enemy * en)
{
	float distance, tt_x, tt_y;
	std::vector<Enemy*>::iterator i;
	tt_x=en->x;
	tt_y=en->y;
	distance=sqrt((tt_x-m_x)*(tt_x-m_x)+(tt_y-m_y)*(tt_y-m_y));
	for(i = TargetEnemyList.begin(); i !=TargetEnemyList.end(); i++)
	{
		if (en==(*i))
		{
			return;
		}
	}
	if (distance <= range)
	{
		TargetEnemyList.push_back(en);
	}
}

void Tower::TargetEnemyCalc()
{
	float distance, tt_x, tt_y;
	std::vector<Enemy*>::iterator i;
	for(i = TargetEnemyList.begin(); i !=TargetEnemyList.end(); )
	{
		tt_x=(*i)->x;
		tt_y=(*i)->y;
		distance=sqrt((tt_x-m_x)*(tt_x-m_x)+(tt_y-m_y)*(tt_y-m_y));
		if (focus_e == (*i))
		{
			t_e = (*i);
			t_e_distance = distance;
		}
		else if (t_e_distance > distance)
		{
			t_e = (*i);
			t_e_distance = distance;
		}
		if (distance > range || (*i)->dead)
		{
			if (t_e == (*i))
			{
				t_e = NULL;
				t_e_distance = 8888;
				b_x = m_x;
				b_y = m_y;
			}
			i=TargetEnemyList.erase(i);
		}
		else
		{
			i++;
		}
	}
	if (TargetEnemyList.size() == 0 || t_e == NULL)
	{
		t_e_distance = 8888;
		t_e = NULL;
		b_x = m_x;
		b_y = m_y;
	}
	else
	{
		t_x = t_e->x;
		t_y = t_e->y;
	}
}

void Tower::LvUp()
{
	level += 1;
	atk=atkdata[model_id-1][level-1];
	range=rangedata[model_id-1][level-1];
}