/*
**
*/
#include "enemyManager.h"

extern bool iswin;

EnemyManager::EnemyManager(hgeFont *_fnt)
{
	hge=hgeCreate(HGE_VERSION);
	MOverEnemy=NULL;
	SelectedEnemy=NULL;
	fnt=_fnt;
	seleting=false;
	started=false;
	timer=0;
	round=0;
	earn_gold = 0;
	cut_life=1;
	cycle=0;
	abled=true;
}
void EnemyManager::Render()
{
	std::vector<Enemy*>::iterator i;

	for(i = EnemyList.begin(); i != EnemyList.end(); i++)
	{
		(*i)->Render(fnt);
	}
}

void EnemyManager::Update()
{
	std::vector<Enemy*>::iterator i;
	for(i = EnemyList.begin(); i != EnemyList.end(); )
	{
		(*i)->Update();
		if ((*i)->movephase == 8 || (*i)->dead)
		{
			if ((*i)->dead)
				earn_gold = 100;
			if((*i)->movephase==8)
				cut_life=1;
			delete (*i);
			i=EnemyList.erase(i);
		}
		else
			i++;
	}
	if (started)
	{		
		switch (round)
		{
		case 1:
			cycle++;
			timer = (timer++) % 600;
			if(cycle>0 && cycle<600)
			{
				if(timer==1)
					AddEnemy(new Enemy(1,1));
				else if(timer==100)
					AddEnemy(new Enemy(1,1));
				else if(timer==200)
					AddEnemy(new Enemy(1,1));
				else if(timer==300)
					AddEnemy(new Enemy(1,1));
				else if(timer==400)
					AddEnemy(new Enemy(2,1));
				else if(timer==500)
					AddEnemy(new Enemy(2,1));
			}
			else if(cycle>3100 && cycle<3700)
			{
				if(timer==1)
					AddEnemy(new Enemy(1,1));
				else if(timer==100)
					AddEnemy(new Enemy(1,1));
				else if(timer==200)
					AddEnemy(new Enemy(1,1));
				else if(timer==300)
					AddEnemy(new Enemy(2,1));
				else if(timer==400)
					AddEnemy(new Enemy(1,1));
				else if(timer==500)
					AddEnemy(new Enemy(3,1));
			}
			else if(cycle>6000 && cycle<6600)
			{
				if(timer==1)
					AddEnemy(new Enemy(1,1));
				else if(timer==100)
					AddEnemy(new Enemy(1,1));
				else if(timer==200)
					AddEnemy(new Enemy(2,1));
				else if(timer==300)
					AddEnemy(new Enemy(2,1));
				else if(timer==400)
					AddEnemy(new Enemy(1,1));
				else if(timer==500)
					AddEnemy(new Enemy(3,1));
				else if(timer==600)
					AddEnemy(new Enemy(3,1));
			}
			else if(cycle>9000 && cycle<9600)
			{
				if(timer==1)
					AddEnemy(new Enemy(1,1));
				else if(timer==100)
					AddEnemy(new Enemy(1,1));
				else if(timer==200)
					AddEnemy(new Enemy(2,1));
				else if(timer==300)
					AddEnemy(new Enemy(3,1));
				else if(timer==400)
					AddEnemy(new Enemy(3,1));
				else if(timer==500)
					AddEnemy(new Enemy(4,1));
			}
			if(cycle>11500)
			{
				started=false;
				iswin=true;
			}
			break;
		case 2:
			break;
		}

	}
}

void EnemyManager::AddEnemy(Enemy * newEnemy)
{
	EnemyList.push_back(newEnemy);
}


void EnemyManager::SetEnemyMOver(float x, float y)
{
	std::vector<Enemy*>::iterator i;
	MOverEnemy = NULL;
	for(i = EnemyList.begin(); i != EnemyList.end(); i++)
	{
		if((*i)->MouseOver(x,y) == true)
		{
			(*i)->SetMOver(true);
			MOverEnemy = (*i);
		}
		else
		{
			(*i)->SetMOver(false);
		}
	}
}

Enemy * EnemyManager::SetEnemySelected()
{
	seleting=true;
	if (SelectedEnemy != NULL)
		SelectedEnemy->SetSelected(false);
	SelectedEnemy = MOverEnemy;
	SelectedEnemy->SetSelected(true);
	return SelectedEnemy;
}

void EnemyManager::DisSelect()
{
	seleting=false;
	if (SelectedEnemy != NULL)
		SelectedEnemy->SetSelected(false);
	SelectedEnemy = NULL;	
}

void EnemyManager::LevelStart(int rround)
{
	round=rround;
	started=true;
}