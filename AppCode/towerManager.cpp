/*
**
*/
#include "towerManager.h"

TowerManager::TowerManager(hgeFont *_fnt, EnemyManager * _em)
{
	MOverChara=NULL;
	SelectedChara=NULL;
	fnt=_fnt;
	em=_em;
	seleting=false;
}
void TowerManager::Render()
{
	std::vector<Tower*>::iterator i;

	for(i = TowerList.begin(); i != TowerList.end(); i++)
	{
		(*i)->Render(fnt);
	}
}

void TowerManager::Update()
{
	std::vector<Tower*>::iterator i;

	for(i = TowerList.begin(); i != TowerList.end(); i++)
	{
		(*i)->Update();
		AttackComp(*i);
	}
}

void TowerManager::AddTower(Tower * newChara)
{
	TowerList.push_back(newChara);
}


void TowerManager::SetCharaMOver(float x, float y)
{
	std::vector<Tower*>::iterator i;
	MOverChara = NULL;
	for(i = TowerList.begin(); i != TowerList.end(); i++)
	{
		if((*i)->MouseOver(x,y) == true)
		{
			(*i)->SetMOver(true);
			MOverChara = (*i);
		}
		else
		{
			(*i)->SetMOver(false);
		}
	}
}

void TowerManager::SetCharaSelected()
{
	seleting=true;
	if (SelectedChara != NULL)
		SelectedChara->SetSelected(false);
	SelectedChara = MOverChara;
	SelectedChara->SetSelected(true);
}

void TowerManager::DisSelect()
{
	seleting=false;
	if (SelectedChara != NULL)
		SelectedChara->SetSelected(false);
	SelectedChara = NULL;	
}

void TowerManager::Destroy()
{	
	std::vector<Tower*>::iterator i;
	for(i = TowerList.begin(); i != TowerList.end(); )
	{
		if((*i)==SelectedChara)
		{
			delete (*i);
			i=TowerList.erase(i);
		}
		else
			i++;
	}
	SelectedChara = NULL;
}

void TowerManager::LvUp()
{
	SelectedChara->LvUp();
}


void TowerManager::AttackComp(Tower * chara)
{
	std::vector<Enemy*>::iterator i;

	for(i = em->EnemyList.begin(); i != em->EnemyList.end(); i++)
	{
		chara->DistanceCalc(*i);
	}
}

void TowerManager::SetFocusEnemy(Enemy * en)
{
	std::vector<Tower*>::iterator i;
	for(i = TowerList.begin(); i != TowerList.end(); i++)
	{
		(*i)->SetFocus(en);
	}
}