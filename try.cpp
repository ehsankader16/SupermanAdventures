# include "iGraphics.h"
# include "gl.h"
# include  <Windows.h>
#include<math.h>
#include<stdio.h>
int man_x=10, man_y=150;
int dx, dy;
int sprint=0;
int lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;
//int laser_x[]={300,250},laser_y[]={200,150}
int movingLaserRange_x1[]={40,500,100,50},movingLaserRange_x2[]={500,900,600,500},laserMove[]={1,1,1,1},laserLen=500;
int laser_x[]={300,700,200,500},laser_y[]={190,270,400,500};
int horizontal_laser_count=4;
int vertical_movingLaserRange_y1[]={550,300},vertical_movingLaserRange_y2[]={650,500},vertical_laserMove[]={0,1};
int vertical_laser_x[]={850,700},vertical_laser_y[]={600,400};
int vertical_laser_count=2;
int level=0;
double health=100;
double health_x[]={600,300,900},health_y[]={768,768,768},hel_initial_x,hel_initial_y;
int health_taken=0,pack_len,pack_wid;//,health_yes
int man_wid,man_height;
int man_mov_right=1,man_mov_left=0,man_mov_up=0,man_mov_down=0;
int mouse_clk=0;
int bg=1;
double bomb_x[]={1336,1000,300,0},bomb_y[]={768,768,768,300},bomb_x_change[]={-2,-1.5,2,2},bomb_y_change[]={-1,-1.5,-1.5,1},
        bomb_initial_x,bomb_initial_y,bomb_r=8,bomb_len=16;
double d[5];//for bomb_chk
int hel_tm,health_pack_chk,hel_pck_num;
int bomb_tm,bomb_chk,bomb_cnt;
int back_from_howto=0,back_from_high=0;
int cont=0,new_game=0,how_to_play=0,cont_chk=1;
int gem_collected[]={0,0,0};
int game_over=0, game_over_y=0,game_end;
double max_score_count=0;
int score_count[]={0,0,0,0,0},current_score=0;
double timer=0;
int score_multiplier=1;
int high_score=0;
int dead_man_x,dead_man_y;
float camx=0, camy=0;
int leftkbhit = 0, rightkbhit = 0, camxLSCount = 0, camxRSCount = 0;
float enemyX = 1500, enemyY=600;


void menu_sound()
{
    if(level==0)
        PlaySound("music\\menu background.wav", NULL, SND_LOOP | SND_ASYNC);
    else
        PlaySound(NULL, NULL, SND_ASYNC);

}
void pause_menu_sound()
{
    if(level==0)
        PlaySound("music\\Pause menu.wav", NULL, SND_LOOP | SND_ASYNC);
    else
        PlaySound(NULL, NULL, SND_ASYNC);

}
void score_page_sound()
{
    if( high_score)
        PlaySound("music\\high score.wav", NULL, SND_ASYNC);
    else if(high_score==0)
        PlaySound(NULL, NULL, SND_ASYNC);

}
void level_one_sound()
{
    if(level==1 && game_over==0)
        PlaySound("music\\game background.wav", NULL, SND_LOOP | SND_ASYNC);
    else
        PlaySound(NULL, NULL,SND_ASYNC);

}


void game_over_sound()
{
    if(game_over)
        PlaySound("music\\Game_Over.wav", NULL, SND_ASYNC);
    else
        PlaySound(NULL, NULL, SND_ASYNC);


}

void enemy()
{
    iSetColor(0,0,0);
    iRectangle(enemyX-camx, enemyY-camy, 10, 10);
}

void changeEnemy()
{

    if((enemyX-camx<man_x+200)&&(enemyX-camx>man_x-100) && (enemyY-camy<man_y+200) && (enemyY-camy>man_y-100))
    return;


         if(enemyX-camx-man_x>10 || man_x-enemyX+camx>10)
    {
        if(enemyX-camx>man_x)
        enemyX-=10;
        else
            enemyX+=10;

        if(enemyY-camy>man_y)
        {
            enemyY-=10*((enemyY-man_y)/abs(enemyX-man_x));
        }

        else if(enemyY-camy<man_y)
        {
            enemyY+=10*((man_y-(enemyY-camy))/abs(enemyX-camx-man_x));
        }

    }



}

void changelasercolor(){

    if(changecolor==0 && lasercolorR!=255)
    {
        lasercolorR+=15;      // to change color faster
        if(lasercolorR==255)
        {
            changecolor=1;
        }
    }
    if(changecolor==1 && lasercolorR!=0)
    {
        lasercolorR-=15;      // to change color faster
        if(lasercolorR==0)
        {
            changecolor=0;
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
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && level!=1)
    {
        if(mx>=185 && mx<=185+270 && my>=382 && my<=382+100)
        {
            cont=1;
            //cont_chk=1;
            new_game=0;
            how_to_play=0;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            //iText(500,500,"Continue");

            FILE* fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8,*fp9,*fp10,*fp11, *fp12;
            fp1=fopen("man_x_man_y.txt","r");
            fscanf(fp1,"%d %d",&man_x,&man_y);
            fclose(fp1);

            fp2=fopen("dx_dy.txt","r");
            fscanf(fp2,"%d %d",&dx,&dy);
            fclose(fp2);


            fp3=fopen("horizontal_laser.txt","r");
            fscanf(fp3,"%d %d %d %d",&laser_x[0],&laser_x[1],&laser_x[2],&laser_x[3]);
            fclose(fp3);


            fp4=fopen("vertical_laser.txt","r");
            fscanf(fp4,"%d %d",&vertical_laser_y[0],&vertical_laser_y[1]);
            fclose(fp4);


            fp5=fopen("bomb1.txt","r");
            fscanf(fp5,"%d %d %d",&bomb_cnt,&bomb_chk,&bomb_tm);
            fclose(fp5);


            fp6=fopen("bomb2.txt","r");
            fscanf(fp6,"%f %f %f %f %f %f",&bomb_x[bomb_cnt-1],&bomb_y[bomb_cnt-1],&bomb_x_change[bomb_cnt-1],&bomb_y_change[bomb_cnt-1],&bomb_initial_x,&bomb_initial_y);
            fclose(fp6);


            fp7=fopen("health.txt","r");
            fscanf(fp7,"%f",&health);
            fclose(fp7);


            fp8=fopen("health_pack1.txt","r");
            fscanf(fp8,"%d %d %d",&hel_pck_num,&health_pack_chk,&hel_tm);
            fclose(fp8);


            fp9=fopen("health_pack_2.txt","r");
            fscanf(fp9,"%lf %lf %d %d",&health_x[hel_pck_num-1],&health_y[hel_pck_num-1],&hel_initial_x,&hel_initial_y);
            fclose(fp9);


            fp10=fopen("timer.txt","r");
            fscanf(fp10,"%f",&timer);
            fclose(fp10);

            fp11=fopen("score.txt","r");
            fscanf(fp11,"%d %d",&current_score, &score_multiplier);
            fclose(fp11);

            fp12=fopen("high score list.txt","r");
            for(int i=0;i<5;i++)
            {
                fscanf(fp12,"%d ",&score_count[i]);
            }
            fclose(fp12);

            level=1;
            menu_sound();
            level_one_sound();
        }

        if(mx>=185 && mx<=185+295 && my>=302 && my<=382 && level!=1)
        {

            new_game=1;
            score_multiplier=1;
            score_count[0]=0;
            score_count[1]=0;   //     EGULA VORO
            score_count[2]=0;
            score_count[3]=0;
            score_count[4]=0;
            current_score=0;
            man_x=30, man_y=150;
            health=100;
            sprint=0;
            cont=0;
            level=1;
                man_mov_right=1;
                man_mov_down=0;
                man_mov_left=0;
                man_mov_up=0;
                man_x=10;
                man_y=150;
                dx=3, dy=3;
                sprint=0;
                lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;

                laserMove[0]=1;
                laserMove[1]=1;
                laserMove[2]=1;
                laserMove[3]=1;

                laser_x[0]=300;
                laser_x[1]=700;
                laser_x[2]=200;
                laser_x[3]=500;

                laser_y[0]=190;
                laser_y[1]=270;
                laser_y[2]=400;
                laser_y[3]=500;

                vertical_laserMove[0]=0;
                vertical_laserMove[1]=1;


                vertical_laser_x[0]=850;
                vertical_laser_x[1]=700;

                vertical_laser_y[0]=600;
                vertical_laser_y[1]=400;

                vertical_laser_count=2;
                health=100;
               // health_x[]={600,300,900},health_y[]={768,768,768};

                health_x[0]=600;
                health_x[1]=300;
                health_x[2]=900;

                health_y[0]=768;
                health_y[1]=768;
                health_y[2]=768;

                hel_tm=0,health_pack_chk=0,hel_pck_num=0;

                health_taken=0;//health_yes

                bomb_x[0]=1336;
                bomb_x[2]=1000;
                bomb_x[2]=300;
                bomb_x[3]=0;

                bomb_y[0]=768;
                bomb_y[1]=768;
                bomb_y[2]=768;
                bomb_y[3]=300;

                bomb_tm=0,bomb_chk=0,bomb_cnt=0;

                gem_collected[0]=0;
                gem_collected[1]=0;
                gem_collected[2]=0;

                how_to_play=0;
                high_score=0;
                back_from_howto=0;
                back_from_high=0;
                level=1;
                menu_sound();
                level_one_sound();
        }

        if(mx>=185 && mx<=185+315 && my>=222&& my<=222+80 && level!=1)
        {
            cont=0;
            new_game=0;
            how_to_play=0;
            high_score=1;
         //   level=-1;
            menu_sound();
            score_page_sound();

            back_from_howto=0;
            back_from_high=0;
            //level=1;
        }

        if(mx>=185 && mx<=185+350 && my>=142 && my<=142+80 && level!=1)

        {
            cont=0;
            new_game=0;
            how_to_play=1;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            //level=1;
        }
        if( how_to_play && mx>=603 && mx<=603+180 && my>=50 && my<=50+65 && level!=1)
        {
            back_from_howto=1;
            back_from_high=0;
        }
        if( high_score && mx>=603 && mx<=603+180 && my>=50 && my<=50+65 && level!=1)
        {
            back_from_howto=0;
            back_from_high=1;
            high_score=0;
            score_page_sound();
            menu_sound();

        }
    }

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
    if((key=='p'||key=='P') && game_over!=1){
        level=0;
        game_over=0;
        new_game=0;
        cont=0;
        level_one_sound();
        pause_menu_sound();
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
    if(key == GLUT_KEY_DOWN)
    {
        dy=3;
        if(sprint%2==1)
            dy=8;

         if(man_y<=100 && camy!=0)
        {
            camy-=dy;
        }

        if(man_y>100 && camy!=0)
        {
            man_y-=dy;
        }

        if(camy==0 && man_y>10)
        {
            man_y-=dy;
        }


        man_mov_down=1;
        man_mov_left=0;
        man_mov_right=0;
        man_mov_up=0;

    }
    if(key == GLUT_KEY_UP)
    {
        dy=3;
        if(sprint%2==1)
            dy=8;

        if(man_y<400)
            man_y+=dy;

        else if(camy<500)
        {
            camy+=dy;
        }

        man_mov_down=0;
        man_mov_left=0;
        man_mov_right=0;
        man_mov_up=1;
    }
    if(key == GLUT_KEY_RIGHT && !camxRSCount)
    {
         dx=10;
        if(sprint%2==1)
            dx=8;


        if(man_x<400)
            man_x+=dx;


        else if(camx<=1800)
        {
            camx+=dx;

        }

        if(camx>1800 && man_x<1256)
        {
            man_x+=dx;
        }

        if(camx>=500 && man_x>=790 && !rightkbhit && camx<=1500)
        {
            rightkbhit=1;
        }


        man_mov_down=0;
        man_mov_left=0;
        man_mov_right=1;
        man_mov_up=0;

    }
    if(key == GLUT_KEY_LEFT && !camxLSCount)
    {
         dx=10;
        if(sprint%2==1)
            dx=8;

        if(camx>=500 && man_x<=405  && !leftkbhit)
        {
            leftkbhit=1;
        }

        else if(camx>1800 && man_x>=800)
        {
            //leftkbhit=0;
            man_x-=dx;
        }

        else if(camx> 1800 && man_x>=400 && man_x<800)
        {
            man_x-=dx;
        }

        else if(camx > 500 && camx<=1905 && man_x>=790)
        {
            camx-=dx;
        }

        //IF CAMERA MOVES IN THE FORWARD DIRECTION
        else if(camx<=500)
        {
            //leftkbhit=0;
            if(camx<=0)
            {
                if(man_x<=100 && man_x>10)
                    man_x-=dx;
                else if(man_x>100)
                {
                    man_x-=dx;
                }
            }

            else
            {


            if(man_x==100)
            {
                camx-=dx;

            }

            else if(man_x>100 && man_x <= 600)
            {
                man_x-=dx;
            }

            else if(man_x>200)
            {
                camx-=dx;
            }

            }

        }


        man_mov_down=0;
        man_mov_left=1;
        man_mov_right=0;
        man_mov_up=0;


    }

    if(key== GLUT_KEY_PAGE_DOWN)
    {
        sprint++;
    }

//  while(key == GLUT_KEY_PAGE_UP)
//    {
//    }

    if(key == GLUT_KEY_END)
        exit(0);
}
void health_change(int i)
{
    if((man_x>=laser_x[i]-camx-man_wid && man_x<=laser_x[i]-camx+100) && (man_y>=laser_y[i]-camy-man_height && man_y<=laser_y[i]-camy+2))
    {
        FILE  *fp;
//        fp=fopen("health.txt","r");
//        fscanf(fp,"%d",health);
//        fclose(fp);
        man_x-=2;
        man_y+=2;
        if(health>0)
            health-=1;

        fp=fopen("health.txt","w");
        fprintf(fp,"%d",health);
        fclose(fp);
    }

}
void vertical_health_change(int i)
{
    if((man_y>=vertical_laser_y[i]-camy-man_height && man_y<=vertical_laser_y[i]-camy+100) && (man_x>=vertical_laser_x[i]-camx-man_wid && man_x<=vertical_laser_x[i]-camx+3))
    {
        man_x-=2;
        man_y-=2;
        if(health>0)
            health-=1;
    }
}

void horizontalLaser(int laserLen,int i)
{
    iSetColor(lasercolorR,255,lasercolorB);
    iFilledRectangle(laser_x[i]-camx,laser_y[i]-camy,laserLen,3);
    iSetColor(0,255,0);
    iFilledRectangle(laser_x[i]-camx-10,laser_y[i]-camy-3,10,10);

    iSetColor(0,255,0);
    iFilledRectangle(laser_x[i]-camx+100,laser_y[i]-camy-3,10,10);

}
void verticalLaser(int laserLen,int i)
{
    iSetColor(lasercolorR,255,lasercolorB);
    iFilledRectangle(vertical_laser_x[i]-camx,vertical_laser_y[i]-camy,3,laserLen);
    iSetColor(0,255,0);
    iFilledRectangle(vertical_laser_x[i]-camx-3,vertical_laser_y[i]-camy-10,10,10);
    iSetColor(0,255,0);
    iFilledRectangle(vertical_laser_x[i]-camx-3,vertical_laser_y[i]-camy+100,10,10);
}
void healthPack()
{
    if(health_pack_chk){
        if(hel_pck_num<=3)
        {
            pack_len=26, pack_wid=22;
            iSetColor(211,211,211);
            iFilledRectangle(health_x[hel_pck_num-1]-camx,health_y[hel_pck_num-1]-camy,pack_len,pack_wid);
            iSetColor(0,0,0);
            iFilledRectangle(health_x[hel_pck_num-1]-camx+(pack_len/2)-2,health_y[hel_pck_num-1]+3-camy,4,pack_wid-6);
            iFilledRectangle(health_x[hel_pck_num-1]+3-camx,health_y[hel_pck_num-1]+(pack_wid/2)-2-camy,pack_len-6,4);
            if(health_y[hel_pck_num-1]>0)
                health_y[hel_pck_num-1]-=.5;
        }
         if((man_x>=health_x[hel_pck_num-1]-man_wid-camx && man_x<=health_x[hel_pck_num-1]+pack_len-camx) && (man_y>=health_y[hel_pck_num-1]-man_height-camy && man_y<=health_y[hel_pck_num-1]+pack_wid-camy))
        {
            //health_taken=1;
            health_x[hel_pck_num-1]=-10;  //making the healthpacks disappear
            health_y[hel_pck_num-1]=-10;
            if (health>=80)
                health=100;
            else
                health+=20;
            health_pack_chk=0;
        }
        if(health_y[hel_pck_num-1]<=50){
            health_pack_chk=0;
            health_x[hel_pck_num-1]=hel_initial_x;
            health_y[hel_pck_num-1]=hel_initial_y;
        }
    }

}
void bomb()
{
 //   BOMB ER RESPONSE CAM DEPENDENT KORA LAGBE
 //       SUMON ER CODE



    if(bomb_chk){
        iSetColor(255,0,0);
        iFilledCircle(bomb_x[bomb_cnt-1]-camx,bomb_y[bomb_cnt-1]-camy,bomb_r,100);
        bomb_x[bomb_cnt-1]+=bomb_x_change[bomb_cnt-1];
        bomb_y[bomb_cnt-1]+=bomb_y_change[bomb_cnt-1];
        d[0]=sqrt((man_x-camx-bomb_x[bomb_cnt-1])*(man_x-camx-bomb_x[bomb_cnt-1])+(man_y-camy-bomb_y[bomb_cnt-1])*(man_y-camy-bomb_y[bomb_cnt-1]));
        d[1]=sqrt(((man_x+man_wid)-bomb_x[bomb_cnt-1])*((man_x+man_wid)-bomb_x[bomb_cnt-1])+(man_y-bomb_y[bomb_cnt-1])*(man_y-bomb_y[bomb_cnt-1]));
        d[2]=sqrt((man_x-bomb_x[bomb_cnt-1])*(man_x-bomb_x[bomb_cnt-1])+((man_y+man_height)-bomb_y[bomb_cnt-1])*((man_y+man_height)-bomb_y[bomb_cnt-1]));
        d[3]=sqrt(((man_x+man_wid)-bomb_x[bomb_cnt-1])*((man_x+man_wid)-bomb_x[bomb_cnt-1])+((man_y+man_height)-bomb_y[bomb_cnt-1])*((man_y+man_height)-bomb_y[bomb_cnt-1]));
        if(d[0]<=bomb_r||d[1]<=bomb_r||d[2]<=bomb_r||d[3]<=bomb_r){
            if(health>50)
                health-=50;
            else
                health=0;
        }
        if(bomb_y[bomb_cnt-1]<=50||bomb_y[3]>=768){
            bomb_chk=0;
            bomb_x[bomb_cnt-1]=bomb_initial_x;
            bomb_y[bomb_cnt-1]=bomb_initial_y;
        }

    }
}

void score_show_live()
{
    char curr_score[100], buf[100];
    strcpy(curr_score,"CURRENT SCORE: ");
    strcat(curr_score,itoa(current_score,buf,10));
    iSetColor(255,0,0);
    iText(10,750,curr_score);

    char score_mul[100];
    strcpy(score_mul,"SCORE MULTIPLIER: X");
    strcat(score_mul,itoa(score_multiplier,buf,10));
    iSetColor(255,0,0);
    iText(10,730,score_mul);

    char hi_score[100];
    strcpy(hi_score,"HIGH SCORE: ");
    strcat(hi_score,itoa(score_count[0],buf,10));
    iSetColor(255,0,0);
    iText(10,710,hi_score);
}

void score()
{
    current_score+=1*score_multiplier;
}

//void gem_collection(int man_x, int man_y)
//{
//    int gem_cou;
//    if(man_x>=1000 && man_x<=1000+40 && man_y>=700 && man_y<=700+40)
//        gem_collected[gem_cou]=1;
//    //if(gem_collected[])
//}

void iDraw()
{

    iClear();

    if(leftkbhit)
    {

        //NEEDS TO BE FIXED DEPENDING ON BMP
        camx-=20;
        man_x+=20;
        camxLSCount++;


        if(camxLSCount>20)
        {
            leftkbhit=0;

            if(man_x<=820)
                camxLSCount=0;
        }

    }

    if(rightkbhit)
    {
        //NEEDS TO BE FIXED DEPENDING ON BMP
        camx+=20;
        man_x-=20;
        camxRSCount++;


        if(camxRSCount>20)
        {
            rightkbhit=0;

            if(man_x<420)
                camxRSCount=0;
        }

    }




//level=0;


    if(level==0)
    {
        if(bg>=1&&bg<15)
            iShowBMP(0,0,"images\\1.bmp");
        if(bg>=15&&bg<30)
            iShowBMP(0,0,"images\\2.bmp");
        if(bg>=30&&bg<55)
            iShowBMP(0,0,"images\\3.bmp");
        if(bg>=45&&bg<60)
            iShowBMP(0,0,"images\\4.bmp");

        bg++;
        if(bg>=60)
            bg=1;

//        iRectangle(185,382,270,100);
//        iRectangle(185,382-80,295,80);
//        iRectangle(185,382-160,315,80);
//        iRectangle(185,382-240,350,80);


        //if(cont==1)
        //{
            FILE* fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8,*fp9,*fp10,*fp11 , *fp12;
            fp1=fopen("man_x_man_y.txt","r");
            fscanf(fp1,"%d %d",&man_x,&man_y);
            fclose(fp1);

            fp2=fopen("dx_dy.txt","r");
            fscanf(fp2,"%d %d",&dx,&dy);
            fclose(fp2);


            fp3=fopen("horizontal_laser.txt","r");
            fscanf(fp3,"%d %d %d %d",&laser_x[0],&laser_x[1],&laser_x[2],&laser_x[3]);
            fclose(fp3);


            fp4=fopen("vertical_laser.txt","r");
            fscanf(fp4,"%d %d",&vertical_laser_y[0],&vertical_laser_y[1]);
            fclose(fp4);


            fp5=fopen("bomb1.txt","r");
            fscanf(fp5,"%d %d %d",&bomb_cnt,&bomb_chk,&bomb_tm);
            fclose(fp5);


            fp6=fopen("bomb2.txt","r");
            fscanf(fp6,"%f %f %f %f %f %f",&bomb_x[bomb_cnt-1],&bomb_y[bomb_cnt-1],&bomb_x_change[bomb_cnt-1],&bomb_y_change[bomb_cnt-1],&bomb_initial_x,&bomb_initial_y);
            fclose(fp6);


            fp7=fopen("health.txt","r");
            fscanf(fp7,"%f",&health);
            fclose(fp7);


            fp8=fopen("health_pack1.txt","r");
            fscanf(fp8,"%d %d %d",&hel_pck_num,&health_pack_chk,&hel_tm);
            fclose(fp8);


            fp9=fopen("health_pack_2.txt","r");
            fscanf(fp9,"%lf %lf %d %d",&health_x[hel_pck_num-1],&health_y[hel_pck_num-1],&hel_initial_x,&hel_initial_y);
            fclose(fp9);


            fp10=fopen("timer.txt","r");
            fscanf(fp10,"%f",&timer);
            fclose(fp10);

            fp11=fopen("score.txt","r");
            fscanf(fp11,"%d %d",&current_score,&score_multiplier);
            fclose(fp11);

            fp12=fopen("high score list.txt","r");
            for(int i=0;i<5;i++)
            {
                fscanf(fp12,"%d ",&score_count[i]);
            }
            fclose(fp12);
            //iText(500,500,"Continue");
            cont=0;
        //}
        if(how_to_play==1)
        {
            iShowBMP(0,0,"images\\howto.bmp");
            if(back_from_howto)
                how_to_play=0;
            iRectangle(603,50,180,65);
            //iText(500,500,"how");
        }
        if(new_game==1)
        {
            timer=0;
            //iText(500,500,"new");
            level=1;
            new_game=0;
            cont=0;
        }
        if(high_score==1)
        {
            //level=-1;
            iShowBMP(0,0,"images\\highscore.bmp");
            if(back_from_high)
            {
                high_score=0;
            }
            iRectangle(603,50,180,65);
        }

    }

    man_wid=60,man_height=80;
//level=1;
    if(level==1)
    {
        //iRectangle(man_x,man_y,man_wid,man_height);

        timer+=.01;

//        score_count[0]+=1*score_multiplier;


        if(timer>=10)
            score_multiplier=2;
        if(timer>=50)
            score_multiplier=5;
//        if(timer>=10)
//            health=110;
//           takes 36 seconds to reach 0 to 10

        iShowBMP(0,0,"images\\background-game-3.bmp");
        score_show_live();
        int gem_cou;
        if(man_x>=1000-man_wid && man_x<=1000+40 && man_y>=700-man_height && man_y<=700+40)      // make it like bomb touch
            gem_collected[0]=1;                      //show the gem in one corner in small size if taken
        if(!gem_collected[0])
            iShowBMP2(1000,700,"images\\pink-gem.bmp",0xFFFFFF);    //this is gem 1

        if(gem_collected[0])
            iText(80,700,"CONGRATULATIONS! You have collected a gem");
        iSetColor(255, 100, 10);

        iRectangle(man_x,man_y,man_wid,man_height);
        //iRectangle(dead_man_x,dead_man_y,man_wid,man_height);

        if(man_mov_left && sprint%2==0)
            iShowBMP2(man_x,man_y,"images\\left.bmp",0xFFFFFF);
        if(man_mov_left && sprint%2!=0)
            iShowBMP2(man_x,man_y,"images\\leftsprint.bmp",0xFFFFFF);
        if(man_mov_right && sprint%2==0)
            iShowBMP2(man_x,man_y,"images\\right.bmp",0xFFFFFF);
        if(man_mov_right && sprint%2!=0)
            iShowBMP2(man_x,man_y,"images\\rightsprint.bmp",0xFFFFFF);
        if(man_mov_down || man_mov_up)
            iShowBMP2(man_x,man_y,"images\\right.bmp",0xFFFFFF);
        changelasercolor();
        int i;
        for(i=0;i<horizontal_laser_count;i++)
        {
            if(laserMove[i]==0 && laser_x[i]!=movingLaserRange_x2[i])
            {
            laser_x[i]+=1;
            if(laser_x[i]==movingLaserRange_x2[i])
            {
                laserMove[i]=1;
            }
            }
            if(laserMove[i]==1 && laser_x[i]!=movingLaserRange_x1[i])
            {
                laser_x[i]-=1;
                if(laser_x[i]==movingLaserRange_x1[i])
                {
                laserMove[i]=0;
                }
            }
            horizontalLaser(laserLen,i);
            health_change(i);
            if(health>50)
                iSetColor(0,255,0);
            else if(health>20&&health<40)
                iSetColor(255,255,0);
            else
                iSetColor(255,0,0);
            iFilledRectangle(1200,700,health,4);
        }

        for(i=0;i<vertical_laser_count;i++)
        {
            if(vertical_laserMove[i]==0 && vertical_laser_y[i]>=vertical_movingLaserRange_y1[i])
            {
                vertical_laser_y[i]-=1;
                if(vertical_laser_y[i]==vertical_movingLaserRange_y1[i])
                {
                    vertical_laserMove[i]=1;
                }
            }
            if(vertical_laserMove[i]==1 && vertical_laser_y[i]<=vertical_movingLaserRange_y2[i])
            {
                vertical_laser_y[i]+=1;
                if(vertical_laser_y[i]==vertical_movingLaserRange_y2[i])
                {
                    vertical_laserMove[i]=0;
                }
            }
            verticalLaser(100,i);
            vertical_health_change(i);
            if(health>50)
                iSetColor(0,255,0);
            else if(health>20&&health<=50)
                iSetColor(255,255,0);
            else
                iSetColor(255,0,0);
            iFilledRectangle(1200,700,health,4);
        }

        if(!health_pack_chk)
        {
            hel_tm++;
            if(hel_pck_num==3)
                hel_pck_num=0;
            if(hel_tm%400==0){
                health_pack_chk=1;
                hel_tm=0;
                hel_pck_num++;
                hel_initial_x=health_x[hel_pck_num-1];
                hel_initial_y=health_y[hel_pck_num-1];
            }
        }
        if(health_pack_chk)
            healthPack();
        if(!bomb_chk)
        {
            bomb_tm++;
            if(bomb_cnt==4)
                bomb_cnt=0;
            if(bomb_tm%200==0)
            {
                bomb_chk=1;
                bomb_tm=0;
                bomb_cnt++;
                bomb_initial_x=bomb_x[bomb_cnt-1];
                bomb_initial_y=bomb_y[bomb_cnt-1];
            }
        }
        if(bomb_chk)
            bomb();

    //    iSetColor(0,255,0);
    //    iFilledRectangle(1200,700,health,4);
        iSetColor(0,255,0);
        iRectangle(1200,700,100,4);

        if(health==100)
            iText(1200,700-13,"Health = Full");
        else if(health<20 && health!=0)
            iText(1200,700-13,"Health Critical");
        else if(health==0)
            iText(1200,700-13,"Zero Health");
        else
            iText(1200,700-13,"Health");
//health=0;
        if(!health)
          {
            game_over = 1;
            level_one_sound();
            game_over_sound();
            health = 0.1;
          }

          enemy();

    }
    if(game_over)
    {

     //   dead_man_y=man_y,dead_man_x=man_x;
        man_x=-1000, man_y=-1000;
        //if(game_over)
       // if(dead_man_y>=10)
           // dead_man_y--;
      //  kam baki ase
     //   iFilledRectangle(man_x,man_y,30,40),

        iShowBMP2(470,game_over_y,"images\\game_over.bmp",0xFFFFFF);
        if(game_over_y<=280)
            game_over_y+=4;
        if(game_over_y>=280)
        {
            game_end++;
            if(game_end==100){


                man_x=30, man_y=150;
                health=100;
                sprint=0;
                cont=0;
                //level=1;
                high_score=1;
                game_over=0;
                game_over_sound();
                score_page_sound();


                man_x=10;
                man_y=150;
                dx=3, dy=3;
                sprint=0;
                lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;

                int laserMove[]={1,1,1,1},laser_x[]={300,700,200,500},laser_y[]={190,270,400,500};

                vertical_laserMove[0]=0;
                vertical_laserMove[1]=1;


                vertical_laser_x[0]=850;
                vertical_laser_x[1]=700;

                vertical_laser_y[0]=600;
                vertical_laser_y[1]=400;

                vertical_laser_count=2;
                health=100;
               // health_x[]={600,300,900},health_y[]={768,768,768};

                health_x[0]=600;
                health_x[1]=300;
                health_x[2]=900;

                health_y[0]=768;
                health_y[1]=768;
                health_y[2]=768;

                hel_tm=0,health_pack_chk=0,hel_pck_num=0;

                health_taken=0;//health_yes

                bomb_x[0]=1336;
                bomb_x[2]=1000;
                bomb_x[2]=300;
                bomb_x[3]=0;

                bomb_y[0]=768;
                bomb_y[1]=768;
                bomb_y[2]=768;
                bomb_y[3]=300;

                bomb_tm=0,bomb_chk=0,bomb_cnt=0;

                gem_collected[0]=0;
                gem_collected[1]=0;
                gem_collected[2]=0;

                level=0;  // level=2 indicating the score page
                game_over=0;
                new_game=0;
                cont=0;
                game_end=0;

            }

        }
    }

    FILE * fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7,*fp8,*fp9, *fp10,*fp11, *fp12;
    fp1=fopen("man_x_man_y.txt","w");
    fprintf(fp1,"%d %d",man_x,man_y);
    fclose(fp1);


    fp2=fopen("dx_dy.txt","w");
    fprintf(fp2,"%d %d",dx,dy);
    fclose(fp2);

    fp3=fopen("horizontal_laser.txt","w");
    fprintf(fp3,"%d %d %d %d",laser_x[0],laser_x[1],laser_x[2],laser_x[3]);
    fclose(fp3);


    fp4=fopen("vertical_laser.txt","w");
    fprintf(fp4,"%d %d",vertical_laser_y[0],vertical_laser_y[1]);
    fclose(fp4);


    fp5=fopen("bomb1.txt","w");
    fprintf(fp5,"%d %d %d",bomb_cnt,bomb_chk,bomb_tm);
    fclose(fp5);

    fp6=fopen("bomb2.txt","w");
    fprintf(fp6,"%f %f %f %f %f %f",bomb_x[bomb_cnt-1],bomb_y[bomb_cnt-1],bomb_x_change[bomb_cnt-1],bomb_y_change[bomb_cnt-1],bomb_initial_x,bomb_initial_y);
    fclose(fp6);


    fp7=fopen("health.txt","w");
    fprintf(fp7,"%f",health);
    fclose(fp7);


    fp8=fopen("health_pack1.txt","w");
    fprintf(fp8,"%d %d %d",hel_pck_num,health_pack_chk,hel_tm);
    fclose(fp8);


    fp9=fopen("health_pack_2.txt","w");
    fprintf(fp9,"%f %f %f %f",health_x[hel_pck_num-1],health_y[hel_pck_num-1],hel_initial_x,hel_initial_y);
    fclose(fp9);

    fp10=fopen("timer.txt","w");
    fprintf(fp10,"%f",timer);
    fclose(fp10);

    fp11=fopen("score.txt","w");
    fprintf(fp11,"%d %d",current_score,score_multiplier);
    fclose(fp11);

    fp12=fopen("high score list.txt","w");
    for(int i=0;i<5;i++)
    {
        fprintf(fp12,"%d ",score_count[i]);
    }
    fclose(fp12);

    int i,j;
    for(i=0;i<5;i++)
    {
        if(current_score>score_count[i])
        {
            for(j=4;j>i;j--)
            {
                score_count[j]=score_count[j-1];
            }
            score_count[i]=current_score;
            break;
        }
    }
//    for(i=0;i<5;i++){
//        printf("%d ",score_count[i]);
//    }

}

int main()
{
    menu_sound();
    iSetTimer(50, changeEnemy);
    iSetTimer(100,score);

//    PlaySound((LPCSTR) "C:\\Users\\Public\\Music\\Sample Music\\Sleep Away.mp3", NULL, SND_FILENAME | SND_ASYNC);
   //DWORD dwError = GetLastError();

    //place your own initialization codes here.
//  iSetTimer(5, ballChange);
//

    iInitialize(1366, 768, "Superman Adventures ver 1.2");

    return 0;
}
