/*
**
*/
#ifndef __TOWERMANAGER__
#define __TOWERMANAGER__

#include <hge.h>
#include "Tower.h"
#include <vector>
#include <hgefont.h>
#include "enemyManager.h"

class TowerManager{
public:
	void Render();
	void AddTower(Tower * newChara);
	void Update();
	void SetCharaMOver(float x, float y);
	void	SetCharaSelected();
	void DisSelect();
	void SetFocusEnemy(Enemy * en);

	void LvUp();
	void Destroy();
	void AttackComp(Tower * chara);
	
	bool seleting;
	Tower * MOverChara, * SelectedChara;

	TowerManager(hgeFont *_fnt, EnemyManager * em);
	~TowerManager(){};
private:
	std::vector<Tower *> TowerList;
	hgeFont *fnt;
	EnemyManager * em;
};

#endif