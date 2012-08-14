#ifndef __MENU__
#define __MENU__


#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <hgecolor.h>


class hgeGUIMenuItem : public hgeGUIObject
{
public:
	hgeGUIMenuItem(int id, hgeFont *fnt, HEFFECT snd, float x, float y, float delay, char *_title);

	virtual void	Render();
	virtual void	Update(float dt);

	virtual void	Enter();
	virtual void	Leave();
	virtual bool	IsDone();
	virtual void	Focus(bool bFocused);
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseLButton(bool bDown);
	virtual bool	KeyClick(int key, int chr);

private:
	hgeFont		*fnt;
	HEFFECT		snd;
	float		delay;
	char * title;
	hgeColor	scolor, dcolor, scolor2, dcolor2, sshadow, dshadow;
	hgeColor	color, shadow;
	float		soffset, doffset, offset;
	float		timer, timer2;
};


#endif 