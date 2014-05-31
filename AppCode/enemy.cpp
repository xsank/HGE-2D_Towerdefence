

#include "enemy.h"

char * enemyfilename[4]={"../Source/enemy1.png","../Source/enemy2.png","../Source/enemy3.png","../Source/enemy4.png"};
int maxhp[4]={100,200,400,800};
int maxarmor[4]={10,20,30,40};

Enemy::Enemy(int mmodel_id, int rround)
{
	hge=hgeCreate(HGE_VERSION);
	round=rround;
	switch(round)
	{
	case 1:
		x=40+18;
		y=18;
		break;
	case 2:
		break;
	}
	model_id=mmodel_id;
	image_tex=hge->Texture_Load(enemyfilename[model_id-1]);
	Init();
}

Enemy::~Enemy()
{
	hge->Texture_Free(image_tex);
	//hge->Texture_Free(ring_tex);
	delete image;
	//delete ring;
	hge->Release();
}

void Enemy::Init()
{
	movephase=1;
	showphase=1;
	level=1;
	image=new hgeSprite(image_tex,0,0,36,36);
	//ring_tex=hge->Texture_Load("../Source/cursor.png");
	//ring=new hgeSprite(ring_tex,32,32,32,32);
	image->SetZ(0.12f);
	//ring->SetZ(0.22f);
	selected = false;
	mover = false;
	armor=maxarmor[model_id-1];
	hp=maxhp[model_id-1];
	move_speed=1;
	dead=false;
}

void Enemy::Render(hgeFont *fnt)
{	
	if (selected)
	{
		r_y=2;
		//ring->Render(x-16,y-16);
	}
	else	
	{
		if (mover)
		{
			r_y=2;
		}
		else
			r_y=0;
	}
	image->Render(x-18,y-24);
}

void Enemy::Update()
{
	float distance;

	switch(round)
	{
	case 1:
		switch(movephase)
		{
		case 1:
			r_x=0+showphase;
			y+=move_speed;
			if (y==40*2+20)
				movephase += 1;
			break;
		case 2:
			r_x=6+showphase;
			x+=move_speed;
			if (x==40*10+20)
				movephase += 1;
			break;
		case 3:
			r_x=0+showphase;
			y+=move_speed;
			if (y==40*5+20)
				movephase += 1;
			break;
		case 4:
			r_x=9+showphase;
			x-=move_speed;
			if (x==40*1+20)
				movephase += 1;
			break;
		case 5:
			r_x=0+showphase;
			y+=move_speed;
			if (y==40*11+20)
				movephase += 1;
			break;
		case 6:
			r_x=6+showphase;
			x+=move_speed;
			if (x==40*13+20)
				movephase += 1;
			break;
		case 7:
			r_x=3+showphase;
			y-=move_speed;
			if (y==40*8+20)
				movephase += 1;
			break;
		}
		break;
	case 2:
		break;
	}
	image->SetTextureRect(36*r_x, 36*r_y, 36,36);
	if (showphase>=2.9)
		showphase=1;
	else
		showphase+=0.05*move_speed;
}

bool Enemy::MouseOver(float x, float y)
{
	if((x>this->x-18)&&(x<this->x+18)&&(y>this->y-20)&&(y<this->y+16))
		return true;

	return false;
}

void Enemy::gethit(int damage)
{
	if (hp > (damage*(100-armor)/100))
		hp -= (damage*(100-armor)/100);
	else
		hp = 0;
	if (hp == 0)
		dead = true;
}