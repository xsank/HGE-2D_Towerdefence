#ifndef __CONTROL__
#define __CONTROL__


#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <hgecolor.h>
#include <hgeguictrls.h> 

class Selector : public hgeGUIObject
{
public:
	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);

	Selector(int id, HEFFECT snd, float x, float y, hgeFont *fnt);
	~Selector(){};
	bool selected;
private:
	HEFFECT		snd;
	hgeSprite* image,* sign;
	hgeFont *fnt;
	HTEXTURE image_tex;

};


#endif