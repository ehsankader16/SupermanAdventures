# include "iGraphics.h"
# include "gl.h"
# include <stdlib.h>

double x=1;
int sun_axisX=250, sun_axisY=360, sun_R=50*x;
int major_axis[9], minor_axis[9],planet_R[9],planet_angle_adv[9], planet_angle_delay[9];
int sat_major_axis[5], sat_minor_axis[5],sat_r[5],sat_angle_adv[5]={0},sat_angle_delay[5];
int show1=2,show2=2;

void draw_sun(int x, int y, int r)
{
    iSetColor(255, 255, 0);
    iFilledCircle(x,y,r*x);
}

void draw_orb(int x, int y, int a, int b)
{
    if(show1%2==0)
    {
        iSetColor(255, 255, 255);
        iEllipse(x, y, a*x, b*x);
    }
}

void now_planet(int x, int y, int planet_major_axis, int planet_minor_axis, int planet_radius, int angle)
{
    double p = 2*acos(0);
    double rad = angle * p / 180;
    double planet_x = x + planet_major_axis * cos(rad);
    double planet_y = y + planet_minor_axis * sin(rad);

    iFilledCircle(planet_x, planet_y, planet_radius*x);
}

void move_planet_satellite()
{
    int i,j;
    for(j=0;j<9;j++)
    {
        planet_angle_adv[j]=((planet_angle_adv[j]+planet_angle_delay[j])%360);
        for(i=2;i<5;i++)
            sat_angle_adv[i]=((sat_angle_adv[i]+sat_angle_delay[i])%360);
    }

}

void pera_satellite(int x,int y , int planet_major_axis, int planet_minor_axis, int sat_major_axis,int sat_minor_axis,int sat_r,int planet_angle,int sat_angle)
{
    double p = 2*acos(0);
    double planet_rad = planet_angle * p / 180;
    double sat_rad=sat_angle*p/180;

    double planet_x = x + planet_major_axis * cos(planet_rad);
    double planet_y = y + planet_minor_axis * sin(planet_rad);

    double sat_x = planet_x + sat_major_axis * cos(sat_rad);
    double sat_y = planet_y + sat_minor_axis * sin(sat_rad);
    if(show2%2==0)
        {
            iSetColor(255, 255, 255);
            iEllipse(planet_x,planet_y,sat_major_axis*x,sat_minor_axis*x);
        }

    iFilledCircle(sat_x, sat_y, sat_r);
}



void iDraw()
{
    iClear();
    int i,j, cen_x,cen_y;
    iShowBMP(0,0,"night.bmp");

    draw_sun(sun_axisX, sun_axisY, sun_R);
    for (i = 0; i < 9; i++)
    {
        cen_x = sun_axisX + sqrt(pow(major_axis[i], 2) - pow(minor_axis[i], 2));
        cen_y = sun_axisY;

        draw_orb(cen_x,cen_y,major_axis[i],minor_axis[i]);

        iSetColor(255-(i*18), 125, 125+(i*18));
        if(i==2)
            iSetColor(0,225,125);

        now_planet(cen_x,cen_y,major_axis[i],minor_axis[i],planet_R[i],planet_angle_adv[i]);

        if (i == 2)
        {
            iSetColor(225,225,225);
            pera_satellite(cen_x,cen_y,major_axis[i],minor_axis[i],20,10,sat_r[i],planet_angle_adv[i],sat_angle_adv[i]);

        }
        if (i == 3)
        {
            {
                iSetColor(225,225,225);
                pera_satellite(cen_x,cen_y,major_axis[i],minor_axis[i],sat_major_axis[i],sat_minor_axis[i],sat_r[i],planet_angle_adv[i],sat_angle_adv[i]);
                pera_satellite(cen_x,cen_y,major_axis[i],minor_axis[i],sat_major_axis[i+1],sat_minor_axis[i+1],sat_r[i+1],planet_angle_adv[i],sat_angle_adv[i+1]);
            }

        }
    }

    iSetColor(225,225,225);
	iText(20, 20, "Press p to pause, r to resume,hit END to exit, use the arrow keys to move around & get a better view!");
}

void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void iKeyboard(unsigned char key)
{
	if(key == 'p' || key=='P')
	{
		iPauseTimer(0);
	}
	//key=='0';
	if(key == 'r' || key=='R')
	{
		iResumeTimer(0);
	}
	//key=='0';
	if(key == 'o' || key=='O')
	{
		show1++;
	}
	if(key == 's' ||key== 'S')
	{
		show2++;
	}
	if(key == 'q' ||key== 'Q')
	{
		x+=0.5;
	}
	if(key == 'w' ||key== 'W')
	{
		x-=0.5;
	}


}


void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}

	if(key==GLUT_KEY_UP)
        sun_axisY-=15;
    if(key==GLUT_KEY_DOWN)
        sun_axisY+=15;
    if(key==GLUT_KEY_LEFT)
        sun_axisX+=15;
    if(key==GLUT_KEY_RIGHT)
        sun_axisX-=15;

}


int main()
{


	major_axis[0]=150*x;
	minor_axis[0]=120*x;
	planet_R[0]=4*x;
	major_axis[1]=200*x;
	minor_axis[1]=160*x;
	planet_R[1]=7*x;
	major_axis[2]=250*x;
	minor_axis[2]=200*x;
	planet_R[2]=8*x;
	major_axis[3]=300*x;
	minor_axis[3]=260*x;
	planet_R[3]=5*x;
	major_axis[4]=350*x;
	minor_axis[4]=300*x;
	planet_R[4]=8*x;
	major_axis[5]=400*x;
	minor_axis[5]=340*x;
	planet_R[5]=7*x;
	major_axis[6]=450*x;
	minor_axis[6]=380*x;
	planet_R[6]=5*x;
	major_axis[7]=500*x;
	minor_axis[7]=420*x;
	planet_R[7]=4*x;
	major_axis[8]=1000*x;
	minor_axis[8]=485*x;
	planet_R[8]=7*x;

	planet_angle_adv[0]=0;
	planet_angle_adv[1]=0;
	planet_angle_adv[2]=0;
	planet_angle_adv[3]=0;
	planet_angle_adv[4]=0;
	planet_angle_adv[5]=0;
	planet_angle_adv[6]=0;
	planet_angle_adv[7]=0;
	planet_angle_adv[8]=0;

	planet_angle_delay[0]=14;
	planet_angle_delay[1]=12;
	planet_angle_delay[2]=11;
	planet_angle_delay[3]=8;
	planet_angle_delay[4]=7;
	planet_angle_delay[5]=6;
	planet_angle_delay[6]=4;
	planet_angle_delay[7]=2;
	planet_angle_delay[8]=7;

    sat_r[2]=2*x;
    sat_major_axis[2]=20*x;
    sat_minor_axis[3]=10*x;
    sat_r[3]=3*x;
    sat_major_axis[3]=20*x;
    sat_minor_axis[3]=10*x;
    sat_r[4]=4*x;
    sat_major_axis[4]=30*x;
    sat_minor_axis[4]=15*x;

    sat_angle_delay[2]=11;
	sat_angle_delay[3]=8;
	sat_angle_delay[4]=8;

	iSetTimer(50, move_planet_satellite);

	iInitialize(1280, 720, "Solar system Offline Pera :'(");

	return 0;
}















