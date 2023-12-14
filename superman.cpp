/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
*/
# include "iGraphics.h"
# include "gl.h"
# include  <Windows.h>
#include<math.h>
#include<stdio.h>

float manx=0, many=100,
      hLaserX[3]= {500,1500,2000}, hLaserY[3]= {500,400,125},
                  vLaserX[3]= {470,1470,1970}, vLaserY[3]= {500,400,125},
                camx=0, camy=0, bmpX = 100, bmpY = 100, dx=10, dy=10;
float hLaserLen = 400, vLaserLen = 400;
float health = 100;
int leftkbhit = 0, rightkbhit = 0;
int camxLSCount = 0, camxRSCount = 0, rs = 0;


/*
	function iDraw() is called again and again by the system.
*/



void hLaser(float x[], float y[], float l)
{
    for(int i = 0; i<3; i++)
    {
        iSetColor(0,255,0);
        iRectangle(x[i]-camx, y[i]-camy, 10, 10);
        iRectangle(x[i]+l-camx, y[i]-camy, 10, 10);
        iLine(x[i]+5-camx,y[i]+5-camy,x[i]+l+5-camx, y[i]+5-camy);

    }
}

void drawHealthBar()
{
    iSetColor(255,255,255);
    iRectangle(20,700,100,5);
    iFilledRectangle(20,700,health,5);
}


void changeHealth()
{
    for(int i = 0; i<3; i++)
    {
        if(health<=0)
        {

        }
        else
        {
            if(((manx>hLaserX[i]-camx-90 && manx<hLaserX[i]-camx+hLaserLen)) && (hLaserY[i]-camy>many && hLaserY[i]-camy<100+many))
                health-=0.01;

            if((vLaserX[i]-camx>manx && vLaserX[i]-camx<90+manx) && ((many>vLaserY[i]-camy-100 && many<vLaserY[i]-camy+vLaserLen)))
                health-=0.01;
        }

    }
}

void vLaser(float x[], float y[], float l)
{
    for(int i = 0; i<3; i++)
    {
        iSetColor(0,255,0);
        iRectangle(x[i]-camx, y[i]-camy, 10, 10);
        iRectangle(x[i]-camx, y[i]+l-camy, 10, 10);
        iLine(x[i]+5-camx,y[i]+5-camy, x[i]+5-camx, y[i]+l+5-camy);

    }
}

void iDraw()
{
    //place your drawing codes here
    iClear();

    //iShowBMP(0,0,"8-bit-pixel-art-city-2o.bmp");
    iSetColor(255,0,0);
    iRectangle(manx,many,90,100);
    //iShowBMP
    //iShowBMP2(manx, many, "rightnew.bmp", 0xFFFFFF);
    iLine(0,1000-camy,1000,1000-camy);
    hLaser(hLaserX, hLaserY, hLaserLen);
    vLaser(vLaserX, vLaserY, vLaserLen);
    drawHealthBar();
    changeHealth();

    if(leftkbhit)
    {

        //NEEDS TO BE FIXED DEPENDING ON BMP
        camx-=0.4;
        manx+=0.4;
        camxLSCount++;


        if(camxLSCount>1000)
        {
            leftkbhit=0;

            if(manx<=820)
                camxLSCount=0;
        }

    }

    if(rightkbhit)
    {
        //NEEDS TO BE FIXED DEPENDING ON BMP
        camx+=0.4;
        manx-=0.4;
        camxRSCount++;


        if(camxRSCount>1000)
        {
            rightkbhit=0;

            if(manx<420)
                camxRSCount=0;
        }

    }




}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    if(key == 13)
    {
        health = 100;
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
}



void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_RIGHT && !camxRSCount)
    {

        if(manx<400)
            manx+=dx;


        else if(camx<=1800)
        {
            camx+=dx;

        }

        if(camx>1800 && manx<1256)
        {
            manx+=dx;
        }

        if(camx>=500 && manx>=450 && !rightkbhit && camx<=1500)
        {
            rightkbhit=1;
        }





    }



    if(key == GLUT_KEY_LEFT && !camxLSCount)
    {


        if(camx>=500 && manx<=405  && !leftkbhit)
        {
            leftkbhit=1;
        }

        else if(camx>1800 && manx>=800)
        {
            //leftkbhit=0;
            manx-=dx;
        }

        else if(camx> 1800 && manx>=400 && manx<800)
        {
            manx-=dx;
        }

        else if(camx > 500 && camx<=1905 && manx>=790)
        {
            camx-=dx;
        }

        //IF CAMERA MOVES IN THE FORWARD DIRECTION
        else if(camx<=500)
        {
            //leftkbhit=0;
            if(camx<=0)
            {
                if(manx<=100 && manx>10)
                    manx-=dx;
                else if(manx>100)
                {
                    manx-=dx;
                }
            }

            else
            {


            if(manx==100)
            {
                camx-=dx;

            }

            else if(manx>100 && manx <= 600)
            {
                manx-=dx;
            }

            else if(manx>200)
            {
                camx-=dx;
            }

            }

        }


    }

    if(key == GLUT_KEY_UP)
    {
        if(many<400)
            many+=dy;

        else if(camy<500)
        {
            camy+=dy;
        }

    }



    if(key == GLUT_KEY_DOWN)
    {
        if(many<=100 && camy!=0)
        {
            camy-=dy;
        }

        if(many>100 && camy!=0)
        {
            many-=dy;
        }

        if(camy==0 && many>10)
        {
            many-=dy;
        }

    }


    if(key == GLUT_KEY_END)
    {
        exit(0);
    }



    //place your codes for other keys here
}

int main()
{

    //place your own initialization codes here.
    printf("%f", manx);
    iInitialize(1366, 768, "Superman");

    return 0;
}
