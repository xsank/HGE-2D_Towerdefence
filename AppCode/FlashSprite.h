//////////////////////////////////////////////////////////////////////////////////////
// Flash����
//////////////////////////////////////////////////////////////////////////////////////

#include "hge.h"
#include "hgesprite.h"

class FlashPlayer;
class hgeSpriteEx :
	public hgeSprite
{
public:
	hgeSpriteEx(HTEXTURE tex, float x, float y, float w, float h):hgeSprite(tex,x,y,w,h) {};
	~hgeSpriteEx(void) {};


	void GetQuad(hgeQuad& _quad)
	{
		_quad = quad;
	}

};

class FlashSprite
{
public:
	FlashSprite(void);
	~FlashSprite(void);

protected:
	HGE*			m_pHGE;
	FlashPlayer*	m_pFlashPlayer;
	hgeQuad			m_FlashQuad;
	float			m_nWidth;
	float			m_nHeight;

public:
	static double			GetFlashVersion();

	BOOL					StartFlash(char* lpsFlash,LONG nWidth,LONG nHeight);
	void					SetQuality(BYTE byQuality);

	BOOL					IsPlaying();	
	void					Pause();
	void					Unpause();
	void					Back();
	void					Rewind();
	void					Forward();	
	void					GotoFrame(int nFrame);

	int						GetCurrentFrame();
	int						GetTotalFrames();

	BOOL					GetLoopPlay();
	void					SetLoopPlay(BOOL bLoop);

	BOOL					Update(float dt);
	BOOL					Render(float x,float y);
};//class FlashSprite

