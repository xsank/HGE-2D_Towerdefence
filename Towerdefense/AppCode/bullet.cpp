

#include "bullet.h"

int bullet_speed[4] = {3, 3, 5,4};
int bullet_image[4] = {5,8, 10, 11};

Bullet::Bullet(int mmodel_id, float xx, float yy, Enemy *eem, int aatk)
{
	hge=hgeCreate(HGE_VERSION);
	model_id=mmodel_id;
	image_tex=hge->Texture_Load("../Source/bullet00.png");
	image=new hgeSprite(image_tex,0,bullet_image[model_id-1]*16,16,16);
	b_x = xx;
	b_y = yy;
	m_x = xx;
	m_y = yy;
	em = eem;
	atk = aatk;
}

Bullet::~Bullet()
{
	hge->Texture_Free(image_tex);
	delete image;
	hge->Release();
}

void	Bullet::Render()
{
	image->Render(b_x-8, b_y-8);
}

bool	Bullet::Update()
{
	float distance, angle, t_x, t_y;
	bool up, left;
	if (em->dead)
		return true;
	t_x=em->x;
	t_y=em->y;
	distance=sqrt((t_x-b_x)*(t_x-b_x)+(t_y-b_y)*(t_y-b_y));
	angle=atan((t_x-b_x)/(t_y-b_y))*180/3.1415926;
	up=(b_y>t_y)? true:false;
	left=(b_x>t_x)? true:false;
	if (left)
	{
		if ((angle > -11.25) && !up)
			image->SetTextureRect(8*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -11.25) && (angle > -33.75))
			image->SetTextureRect(9*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -33.75) && (angle > -56.25))
			image->SetTextureRect(10*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -56.25) && (angle > -78.75))
			image->SetTextureRect(11*16,bullet_image[model_id-1]*16,16,16);
		else if (((angle < -78.75) && (angle > -91)) || ((angle < 91) && (angle > 78.75)))
			image->SetTextureRect(12*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 78.75) && (angle > 56.25))
			image->SetTextureRect(13*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 56.25) && (angle > 33.75))
			image->SetTextureRect(14*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 33.75) && (angle > 11.25))
			image->SetTextureRect(15*16,bullet_image[model_id-1]*16,16,16);
		else
			image->SetTextureRect(0,bullet_image[model_id-1]*16,16,16);
	}
	else
	{
		if ((angle > -11.25) && up)
			image->SetTextureRect(0,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -11.25) && (angle > -33.75))
			image->SetTextureRect(1*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -33.75) && (angle > -56.25))
			image->SetTextureRect(2*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < -56.25) && (angle > -78.75))
			image->SetTextureRect(3*16,bullet_image[model_id-1]*16,16,16);
		else if (((angle < -78.75) && (angle > -91)) || ((angle < 91) && (angle > 78.75)))
			image->SetTextureRect(4*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 78.75) && (angle > 56.25))
			image->SetTextureRect(5*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 56.25) && (angle > 33.75))
			image->SetTextureRect(6*16,bullet_image[model_id-1]*16,16,16);
		else if ((angle < 33.75) && (angle > 11.25))
			image->SetTextureRect(7*16,bullet_image[model_id-1]*16,16,16);
		else
			image->SetTextureRect(8*16,bullet_image[model_id-1]*16,16,16);
	}		
	if (distance<5)
	{
		em->gethit(atk);
		return true;
	}
	else
	{			
		b_x=b_x+(t_x-b_x)/distance*bullet_speed[model_id-1];
		b_y=b_y+(t_y-b_y)/distance*bullet_speed[model_id-1];
		return false;
	}
}