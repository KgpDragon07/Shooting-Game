#include "projectile.hpp"
#include <cstdlib>

const int fov = 90;
const int spread = 10;

class Character
{
	protected:
		int type;
		int health;
		int aim;
		Point location;
		vector<Projectile *> activeProjectiles;
	public:
		void draw()
		{
			imgv = Scalar(0);
			img = imread(IMAGE,1);
			for(float t = aim - fov/2; t <= aim + fov/2;t+=0.1)
				castRay(location,t,type);
			if(type == 0)
				circle(img, location, 4, Scalar(0,255,0),CV_FILLED);
			else if(type == 1)
				circle(img, location, 4, Scalar(0,0,255),CV_FILLED);
			circle(img, location, 4, Scalar(0,0,0), 1);
			imshow("Game",img);
		}
		Point getLocation()
		{
			return location;
		}
		void shoot()
		{
			Projectile *newProjectile = new Projectile(location, aim + (rand()%spread)*pow(-1,rand()));
			activeProjectiles.push_back(newProjectile);
		}
		void updateProjectiles()
		{
			for(int i=activeProjectiles.size()-1;i>=0;--i)
			{
				if(!activeProjectiles[i]->update())
				{
					Projectile *tempProj = activeProjectiles[i];
					activeProjectiles[i] = activeProjectiles.back();
					activeProjectiles.pop_back();
					delete tempProj;
				}
			}
		}
};
