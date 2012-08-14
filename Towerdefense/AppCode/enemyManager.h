/*
**
*/
#ifndef __ENEMYMANAGER__
#define __ENEMYMANAGER__

#include <hge.h>
#include "enemy.h"
#include <vector>
#include <hgefont.h>

class EnemyManager{
public:

	std::vector<Enemy *> EnemyList;
	bool seleting;
	bool started;
	bool abled;
	Enemy * MOverEnemy, * SelectedEnemy;

	void Render();
	void AddEnemy(Enemy * newEnemy);
	void Update();
	void SetEnemyMOver(float x, float y);
	Enemy * SetEnemySelected();
	void DisSelect();

	void LevelStart(int round);
	int earn_gold;
	int cut_life;

	EnemyManager(hgeFont *_fnt);
	~EnemyManager(){};
private:
	int round;
	hgeFont *fnt;
	HGE *hge;
	int timer;
	int cycle;
};

#endif