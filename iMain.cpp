//solar system with a planet and a satellite


# include "iGraphics.h"

int x, y, r=150;    //for the planet. here r=radius of the orbit`
double v=0;         //v controls my angle
int sun_x=400, sun_y=400;
int x_sat, y_sat ,r_sat=30;  //for the satellite
int x_plan2, y_plan2, r_plan2=300; // center and radius for planet 2

void iDraw()
{
    iClear();
    iSetColor(255,250,125);
    iFilledCircle(sun_x, sun_y,50);

    iSetColor(255,0,100);
    iFilledCircle(x,y,10);

    iSetColor(0,255,100);
    iFilledCircle(x_sat,y_sat,2);

    iSetColor(255,226,250);
    iFilledCircle(x_plan2,y_plan2,14);
}
void update_v(int n)         //here n=9000 or 900 or 90
{
    if(v<n)
        v++;
    if(v==n)
        v=0;
}

void PlanetCoordinates()
{

    update_v(36000);

    x = sun_x + r*sin(v/100);
    y = sun_y - r*cos(v/100);

    //printf("%d %d %d\n",x,y,v);
    update_v(3600);

    x_sat = x - r_sat*sin(v/10);
    y_sat = y - r_sat*cos(v/10);

    x_plan2 = sun_x + r_plan2*sin(v/300);
    y_plan2 = sun_y - r_plan2*cos(v/300);
}




void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{

}


void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        exit(0);
    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    if(key == GLUT_KEY_UP)
    {
        sun_y+=5;
    }

    if(key == GLUT_KEY_DOWN)
    {
        sun_y-=5;
    }

    if(key == GLUT_KEY_LEFT)
    {
        sun_x-=5;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        sun_x+=5;
    }

}


int main()
{
    iSetTimer(2,PlanetCoordinates);
    iInitialize(800, 800, "Demo!");

    return 0;
}
