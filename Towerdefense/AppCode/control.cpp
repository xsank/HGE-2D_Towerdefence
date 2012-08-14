
#include "control.h"

extern void show_description(int prio, int id);

Selector::Selector(int _id, HEFFECT _snd, float _x, float _y, hgeFont *_fnt)
{
	//int xx,yy;
	id=_id;
	snd=_snd;
	rect.Set(_x, _y, _x+40, _y+40);
	fnt = _fnt;

	bStatic=false;
	bVisible=true;
	bEnabled=true;
	selected=false;
	switch(id)
	{
	case 1:
		image_tex=hge->Texture_Load("../Source/tower1.png");
		image=new hgeSprite(image_tex,0,0,38,38);
		sign=new hgeSprite(image_tex,38,0,38,38);
		break;
	case 2:
		image_tex=hge->Texture_Load("../Source/tower2.png");
		image=new hgeSprite(image_tex,0,0,38,38);
		sign=new hgeSprite(image_tex,38,0,38,38);
		break;
	case 3:
		image_tex=hge->Texture_Load("../Source/tower3.png");
		image=new hgeSprite(image_tex,0,0,38,38);
		sign=new hgeSprite(image_tex,38,0,38,38);
		break;
	case 4:
		image_tex=hge->Texture_Load("../Source/tower4.png");
		image=new hgeSprite(image_tex,0,0,38,38);
		sign=new hgeSprite(image_tex,38,0,38,38);
		break;
	default:
		break;
	}
	//xx=(id-1)%8;
	//yy=(id-1)/8;
}

void Selector::Render()
{
	image->Render(rect.x1,rect.y1);
	if (selected)
	{
		sign->Render(rect.x1,rect.y1);
	}
}

void Selector::Update(float dt)
{

}

void Selector::Enter()
{
}

void Selector::Leave()
{
	selected=false;
}

bool Selector::IsDone()
{
	return true;
}

void Selector::MouseOver(bool bOver)
{
	if(bOver)
		selected=true;
	else
		selected=false;
}

bool Selector::MouseLButton(bool bDown)
{
	if(!bDown)
	{
		return true;
	}
	else 
	{
		hge->Effect_Play(snd);
		return false;
	}
}

bool Selector::KeyClick(int key, int chr)
{
	if(key==HGEK_ENTER || key==HGEK_SPACE)
	{
		MouseLButton(true);
		return MouseLButton(false);
	}

	return false;
}

void Selector::Focus(bool bFocused)
{
	if(bFocused)
	{
	}
	else
	{		
	}
}
