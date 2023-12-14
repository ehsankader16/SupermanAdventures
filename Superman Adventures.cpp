# include "iGraphics.h"
# include "gl.h"
# include  <Windows.h>
#include<math.h>
#include<stdio.h>
#define enemyNum 21

typedef struct{
    char name[21];
    int score;

}Leaderboard;

Leaderboard HighScore[5];
int leaderboardIndex = 0;

int man_x, man_y;
int dx, dy;
int sprint=0;
int lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;
//int laser_x[]={300,250},laser_y[]={200,150}
int movingLaserRange_x1[]={50,500,100,50,900,1100,900,4200,4100},movingLaserRange_x2[]={500,900,600,500,1100,1300,1100,4200,4300},laserMove[]={1,1,1,1,1,1,1,1,1},laserLen=150;
int laser_x[]={300,700,200,500,1000,1200,1050,4000,4200},laser_y[]={700,270,400,500,270,400,650,500,300};
int horizontal_laser_count=9;
int vertical_movingLaserRange_y1[]={450,200,400,200,350,150,450,200,400,200,350,150,450},vertical_movingLaserRange_y2[]={700,500,650,550,700,400,700,500,650,550,700,400,700},vertical_laserMove[]={0,1,0,1,0,1,0,1,0,1,0,1,0};
int vertical_laser_count=13;  // NOW ACTING AS vertical_shooter()
int vertical_laser_x[]={700,1400,2100,2800,3600,4400,5100,5900,6700,7500,8200,8800,9400},vertical_laser_y[]={550,400,500,450,300,200,450,200,400,200,350,150,550};
//=============================static vertical laser====================
int static_ver_laser_count=18;
int static_ver_laser_x[]={1500,1500,2500,2500,4000,4000,4700,4700,5600,5600,6500,6500,7300,7300,8100,8100,9000,9000},static_ver_laser_y[]={500,20,500,20,500,20,500,20,500,20,500,20,500,20,500,20,500,20};
int static_laserLen=250;

int vln=0;//vertical_laser_num
int level=0;
double health=100;
double health_x[]={600,300,900},health_y[]={768,768,768},hel_initial_x,hel_initial_y;
int health_taken=0,pack_len,pack_wid;//,health_yes
int man_wid,man_height;
int man_mov_right=1,man_mov_left=0,man_mov_up=0,man_mov_down=0;
int back_from_credit=0,ex=0,credit=0;
int mouse_clk=0;
int stop_sound=0;
int bg=1;
double bomb_x[]={1336,1000,300,0},bomb_y[]={768,768,768,300},bomb_x_change[]={-2,-1.5,2,2},bomb_y_change[]={-1,-1.5,-1.5,1},
        bomb_initial_x,bomb_initial_y,bomb_r=8;
double d[5];//for bomb_chk
int hel_tm,health_pack_chk,hel_pck_num;
int bomb_tm,bomb_chk,bomb_cnt;
double bmb_rnge_x,bmb_rnge_y;
int back_from_howto=0,back_from_high=0;
int cont=0,new_game=0,high_score=0,how_to_play=0,cont_chk=1;
int gem_collected[]={0,0,0};
int game_over=0, game_over_y=0,game_end;
double max_score_count=0;
int score_count[]={0,0,0,0,0},current_score=0;
double timer=0;
int score_multiplier=1;
float camx=0, camy=0;
int leftkbhit = 0, rightkbhit = 0, camxLSCount = 0, camxRSCount = 0;
float enemyFX = 1500, enemyFY=600;

////======================== MENU PAGE DECORATION ================================
//int cont_rectangle_sweep=0,newgame_rectangle_sweep=0,high_score_rectangle_sweep=0,how_to_play_rectangle_sweep=0;
//int rec_swap_len=0;

//ENEMY VARIABLES:

float enemyX[] = {500, 1100, 1800, 2200,2450,3650,4650,5550,6450,7250,8050,3110,3090,3120,3300,2450+2000,3650+2200, 5650-500, 5650-490, 5650-510,5650-300}, enemyY[] = {250,200,150,300,350,350,350,350,350,350,350,400,600,200,400,300,300,300,200,400,600,500};
float enemyHealth[] = {100,100,100,100,100,100,100,100,100,100,100,200,200,200,400,100,100,100,100,100,300};
float enemyWidth[] = {80,80,80,80,80,80,80,80,80,80,80,80,80,80,150,80,80,80,80,80,80,200};
float enemyHeight[] = {80,80,80,80,80,80,80,80,80,80,80,80,80,80,230,80,80,80,80,80,80,300};
int enemyHitIndex;
int enemyDamageRate[] = {2,2,2,2,2,2,2,2,1,1,1,1,1,1,2,2,1,1,1,2,2};
int enemyFireIndex[enemyNum] ={0};
float enemyFireX[enemyNum], enemyFireY[enemyNum];
int enemyFireSuppress[enemyNum] = {0};
int enemyFireLR[enemyNum] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int enemyFireRenderOff[enemyNum] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

//VERTICAL ENEMY MOVE VARIABLES BY SUMON:
int enemyRange_y1[]= {100,100,200,200,300,300,300,300,300,300,300,390,590,190,350,200,100,100,350,550,200}, enemyRange_y2[]= {550,400,700,600,380,380,380,380,380,380,380,410,610,210,450,400,700,300,450,700,700}, enemyMove[]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float enemydY[] = {1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,2,1,1,1,1,1};


//ENEMY IMAGE VARIABLES
int enemyImageTrack[enemyNum]={-5,0,5,10,5,10,10,10,5,10,10,10,5,10,5,0,0,5,0,5,5};
int enemyDamageStatus[enemyNum] = {0};

//SUPERMAN HIT BY FIRE VARIABLES
int manHitToLeft, manHitToRight;
int manLeftDisplacement, manRightDisplacement;

//CHARACTER IMAGE VARIABLES
int manMove;
int reset = 11;
int manImageTrack = 0;
int manLaserImageTrack = 0;


//GAME OVER VARIABLES
int getname = 0;
int kill_count=0;



//******************************* ANUP NEW *************************
int flag=0;
char str[100];
int name_input_len=0;



//******************************* ANUP NEW *************************

//LASER VARIABLES:
float laserEnd;
int laserSwitch = 0, laserTimer=0, laserStat = 0;
float laserHealth = 100;
int manLeft = 0, manRight = 1;

int world_len_right=10000;

int test[]={0,9,18,27,36,45,54,63,72,81},bul[10],bul_ctrl=90;
double bul_x[10],bul_y[10];
double bul_l=10,bul_h=4;
int bul_k=0;
//int bul_out,bul_active=1;
//int dis[10];
int game_completed=0;
int congrats=0;

int reset_curr_score=0;
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
void your_score_page_sound()
{
    if(level==2)
        PlaySound("music\\score clap.wav", NULL, SND_ASYNC);
    else
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
void iMouse(int button, int state, int mx, int my)
{


    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && level!=1)
    {
        if(mx>=110 && mx<=110+206 && my>=403 && my<=403+50)
        {
            cont=1;
            //cont_chk=1;
            new_game=0;
            how_to_play=0;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            back_from_credit=0;

            if(reset_curr_score )
            {
                current_score=0;
                kill_count=0;
                score_multiplier=1;
                timer=0;


            }
            reset_curr_score=0;
            level=1;
            menu_sound();
            level_one_sound();
            credit=0;
            ex=0;
        }

        if(mx>=110 && mx<=110+221 && my>=352 && my<=352+50 && level!=1)
        {

            new_game=1;
            camx=0,camy=0;
            score_multiplier=1;
            score_count[0]=0;
            score_count[1]=0;
            score_count[2]=0;
            score_count[3]=0;
            score_count[4]=0;
            current_score=0;
            health=100;
            sprint=0;
            cont=0;
            level=1;
                man_mov_right=1;
                man_mov_down=0;
                man_mov_left=0;
                man_mov_up=0;
                man_x=80;
                man_y=150;
                dx=5, dy=5;
                sprint=0;
                lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;

                laserMove[0]=1;
                laserMove[1]=1;
                laserMove[2]=1;
                laserMove[3]=1;
                laserMove[4]=1;
                laserMove[5]=1;
                laserMove[6]=1;

                laser_x[0]=300;
                laser_x[1]=700;
                laser_x[2]=200;
                laser_x[3]=500;
                laser_x[4]=1000;
                laser_x[5]=1200;
                laser_x[6]=1050;
                laser_x[7]=4200;
                laser_x[8]=4200;

//                laser_y[0]=700;
//                laser_y[1]=270;
//                laser_y[2]=400;
//                laser_y[3]=500;
//                laser_y[4]=270;
//                laser_y[5]=400;
//                laser_y[6]=650;

                vertical_laserMove[0]=0;
                vertical_laserMove[1]=1;
                vertical_laserMove[2]=0;
                vertical_laserMove[3]=1;
                vertical_laserMove[4]=0;
                vertical_laserMove[5]=1;
                vertical_laserMove[6]=0;
                vertical_laserMove[7]=1;
                vertical_laserMove[8]=0;
                vertical_laserMove[9]=1;
                vertical_laserMove[10]=0;
                vertical_laserMove[11]=1;
                vertical_laserMove[12]=0;


                vertical_laser_y[0]=550;
                vertical_laser_y[1]=400;
                vertical_laser_y[2]=500;
                vertical_laser_y[3]=450;
                vertical_laser_y[4]=400;
                vertical_laser_y[5]=200;
                vertical_laser_y[6]=550;
                vertical_laser_y[7]=400;
                vertical_laser_y[8]=500;
                vertical_laser_y[9]=450;
                vertical_laser_y[10]=400;
                vertical_laser_y[11]=200;
                vertical_laser_y[12]=550;

                vertical_laser_count=13;

                health=100;

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

                bmb_rnge_x=0;
                bmb_rnge_y=0;

                test[0]=0,test[1]=9,test[2]=18,test[3]=27,test[4]=36,test[5]=45,test[6]=54,test[7]=63,test[8]=72,test[9]=81;
                int i;
                for(i=0;i<10;i++){
                    bul[i]=0;
                }
                vln=0;
                bul_k=0;



                enemyY[0]=250;
                enemyY[1]=200;
                enemyY[2]=150;
                enemyY[3]= 350 ;
                enemyY[4]=350  ;
                enemyY[5]=350  ;
                enemyY[6]=350  ;
                enemyY[7]= 350 ;
                enemyY[8]= 350 ;
                enemyY[9]= 350 ;
                enemyY[10]= 350 ;
                enemyY[11]= 400 ;
                enemyY[12]=600;
                enemyY[13]=200;
                enemyY[14]=400;
                enemyY[15]=300;
                enemyY[16]=300;
                enemyY[17]=200;
                enemyY[18]=400;
                enemyY[19]=600;
                enemyY[20]=400;


//                enemyX[0]= 500 ;
//                enemyX[1]= 1100 ;
//                enemyX[2]= 1800 ;
//                enemyX[3]= 2200 ;
//                enemyX[4]= 2450 ;
//                enemyX[5]= 3650 ;
//                enemyX[6]= 4650 ;
//                enemyX[7]= 5550 ;
//                enemyX[8]= 6450 ;
//                enemyX[9]= 7250 ;
//                enemyX[10]= 8050 ;
//                enemyX[11]= 3100 ;
//                enemyX[12]=3100;
//                enemyX[13]=3100;
//                enemyX[14]=3300;

                enemyHealth[0]=100;
                enemyHealth[1]=100;
                enemyHealth[2]=100;
                enemyHealth[3]=100;
                enemyHealth[4]=100;
                enemyHealth[5]=100;
                enemyHealth[6]=100;
                enemyHealth[7]=100;
                enemyHealth[8]=100;
                enemyHealth[9]=100;
                enemyHealth[10]=100;
                enemyHealth[11]=200;
                enemyHealth[12]=200;
                enemyHealth[13]=200;
                enemyHealth[14]=400;
                 enemyHealth[15]=100;
                 enemyHealth[16]=100;
                 enemyHealth[17]=400;
                 enemyHealth[18]=100;
                 enemyHealth[19]=100;
                 enemyHealth[20]=300;


                how_to_play=0;
                high_score=0;
                back_from_howto=0;
                back_from_high=0;
                back_from_credit=0;
                level=1;
                menu_sound();
                level_one_sound();
                credit=0;
                ex=0;

                laserHealth=100;
                laserSwitch=0;

                for(int i=0; i<enemyNum; i++)
                    enemyFireX[i]=-50;
        }




        if(mx>=110 && mx<=110+234 && my>=300&& my<=300+50 && level!=1)
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
            back_from_credit=0;
            credit=0;
            ex=0;
            //level=1;
        }

        if(mx>=110 && mx<=110+260 && my>=250 && my<=250+50 && level!=1)

        {
            cont=0;
            new_game=0;
            how_to_play=1;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            back_from_credit=0;
            credit=0;
            ex=0;
            //level=1;
        }
        if( how_to_play && mx>=603 && mx<=603+180 && my>=50 && my<=50+65 && level!=1)
        {
            back_from_howto=1;
            back_from_high=0;
            back_from_credit=0;
        }
        if( high_score && mx>=603 && mx<=603+180 && my>=50 && my<=50+65 && level!=1)
        {
            back_from_howto=0;
            back_from_high=1;
            back_from_credit=0;
            high_score=0;
            score_page_sound();
            menu_sound();

        }
        if( credit && mx>=603 && mx<=603+180 && my>=50 && my<=50+65 && level!=1)
        {
            back_from_howto=0;
            back_from_high=0;
            back_from_credit=1;
        }

        if(mx>=110 && mx<=110+168 && my>=200 && my<=200+50 && level!=1)
        {
            cont=0;
            new_game=0;
            how_to_play=0;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            back_from_credit=0;
            credit=1;
            ex=0;
        }
        if(mx>=110 && mx<=110+100 && my>=150 && my<=150+50 && level!=1)
        {
            cont=0;
            new_game=0;
            how_to_play=0;
            high_score=0;
            back_from_howto=0;
            back_from_high=0;
            back_from_credit=0;
            credit=0;
         //   ex=1;
            exit(0);
        }
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

    }
}



/*
********************************** FOLLOWING AND STATIC ENEMY CODE *********************************************************
*/

void detectMotion()
{
    reset++;
}



void renderSuperMan()
{
    if(!laserSwitch)
    {
        if(!game_over && manHitToLeft && !manHitToRight)
    {
        if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\lefthit1.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\lefthit2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;

    }

    if(!game_over && manHitToRight && !manHitToLeft)
    {
        if(manImageTrack<=10 )
            iShowBMP2(man_x,man_y,"images\\righthit1.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\righthit2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
    }

    if(manMove && !game_over && !manHitToLeft && !manHitToRight)
    {

        if(man_mov_left)
        {
             if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\leftmove.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\leftmove2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;

        }

        if(man_mov_right)
        {
            if(manImageTrack<=10)
            iShowBMP2(man_x-30,man_y,"images\\rightmove.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x-30,man_y,"images\\rightmove2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
        }

        if(man_mov_down && manLeft)
        {
            if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\downleft.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\downleft2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
        }

        if(man_mov_up && manLeft)
        {
            if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\upleft.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\upleft2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
        }


        if(man_mov_down && manRight)
        {
            if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\downright.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\downright2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
        }

        if(man_mov_up && manRight)
        {
            if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\upright.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\upright2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;
        }

    }

    else if(!game_over)
    {
        if(manLeft && !manHitToLeft && !manHitToRight)
            iShowBMP2(man_x,man_y,"images\\left.bmp",0xFFFFFF);
        if(manRight && !manHitToLeft && !manHitToRight)
            iShowBMP2(man_x,man_y,"images\\right.bmp",0xFFFFFF);
    }

    }

    else
    {
        if(manRight)
        {
            if(manLaserImageTrack<=5)
            {
                iShowBMP2(man_x,man_y,"images\\laserright1.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=10)
            {
                iShowBMP2(man_x,man_y,"images\\laserright2.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=15)
            {
                iShowBMP2(man_x,man_y,"images\\laserright3.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=20)
            {
                iShowBMP2(man_x,man_y,"images\\laserright4.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=25)
            {
                iShowBMP2(man_x,man_y,"images\\laserright3.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=30)
            {
                iShowBMP2(man_x,man_y,"images\\laserright4.bmp",0xFFFFFF);
            }
            else
            {
                iShowBMP2(man_x,man_y,"images\\laserright1.bmp",0xFFFFFF);
            }


        }
        if(manLeft)
        {
            if(manLaserImageTrack<=5)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft1.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=10)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft2.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=15)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft3.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=20)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft4.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=25)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft3.bmp",0xFFFFFF);
            }
            else if(manLaserImageTrack<=30)
            {
                iShowBMP2(man_x,man_y,"images\\laserleft4.bmp",0xFFFFFF);
            }
            else
            {
                iShowBMP2(man_x,man_y,"images\\laserleft1.bmp",0xFFFFFF);
            }


        }

    }


}

void reduceManHealth()
{
    for(int i=0; i<enemyNum; i++)
    {
        if(enemyFireX[i]-camx-man_x<50 && enemyFireX[i]-camx-man_x>0 && enemyFireY[i]-man_y<80 && enemyFireY[i]-man_y>0)
        {
            enemyFireRenderOff[i]=1;
            if(health>2)
                health-=2;
            else
                health=0;

             if(enemyFireLR[i]==0)
             {
                 if(manHitToLeft!=1)
                    manHitToLeft=1;
                    laserSwitch=0;
             }

             if(enemyFireLR[i]==1)
             {
                 if(manHitToRight!=1)
                    manHitToRight=1;
                    laserSwitch=0;
             }

        }

    }
}

void enemy()
{
    iSetColor(0,0,255);
    for(int i = 0; i<enemyNum; i++)
    {
        if(enemyHealth[i]>0.1)

        {
            if(i==14 || i==20)
            {
                iSetColor(255,0,0);
                if(i==14)
                iRectangle(enemyX[i]-camx,enemyY[i]-camy+200,200,10);
                if(i==20)
                    iRectangle(enemyX[i]-camx,enemyY[i]-camy+200,150,10);
                iFilledRectangle(enemyX[i]-camx,enemyY[i]-camy+200,enemyHealth[i]/2,10);
                if(man_x<enemyX[i]-camx)
                    {

                    if(enemyImageTrack[i]<=10)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossleft1.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=20)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossleft2.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=30)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossleft3.bmp",0xFFFFFF);
                    else
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossleft2.bmp",0xFFFFFF);

                    if(enemyImageTrack[i]>40)
                        enemyImageTrack[i]=0;

                    }

                else
                {
                    if(enemyImageTrack[i]<=10)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossright1.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=20)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossright2.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=30)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossright3.bmp",0xFFFFFF);
                    else
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\bossright2.bmp",0xFFFFFF);

                    if(enemyImageTrack[i]>40)
                        enemyImageTrack[i]=0;
                }

            }

            else
            {
                    if(man_x<enemyX[i]-camx)
                    {

                    if(enemyDamageStatus[i]==0)
                    {
                    if(enemyImageTrack[i]<=10)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyleft1.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=20)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyleft2.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=30)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyleft3.bmp",0xFFFFFF);
                    else
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyleft2.bmp",0xFFFFFF);

                    if(enemyImageTrack[i]>40)
                        enemyImageTrack[i]=0;

                    }

                    else if(enemyDamageStatus[i]==1)
                    {
                        iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyhitleft.bmp",0xFFFFFF);
                    }

                    }

                    else
                    {
                        if(!enemyDamageStatus[i])
                        {
                            if(enemyImageTrack[i]<=10)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyright1.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=20)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyright2.bmp",0xFFFFFF);
                    else if(enemyImageTrack[i]<=30)
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyright3.bmp",0xFFFFFF);
                    else
                    iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyright2.bmp",0xFFFFFF);

                    if(enemyImageTrack[i]>40)
                        enemyImageTrack[i]=0;
                        }

                        else
                        {
                            iShowBMP2(enemyX[i]-camx,enemyY[i]-camy,"images\\enemyhitright.bmp",0xFFFFFF);
                        }

                    }
            }


        }
            //iRectangle((enemyX[i]-camx), (enemyY[i]-camy), enemyWidth[i], enemyHeight[i]);

    }


}

void changeEnemyY()
{
    for(int i=0; i<enemyNum; i++)
    {
        if(enemyMove[i]==0 && enemyY[i]>=enemyRange_y1[i])
    {
        enemyY[i]-=enemydY[i];
        if(enemyY[i]==enemyRange_y1[i])
        {
            enemyMove[i]=1;
        }
    }

    if(enemyMove[i]==1 && enemyY[i]<=enemyRange_y2[i])
    {
        enemyY[i]+=enemydY[i];
        if(enemyY[i]==enemyRange_y2[i])
        {
            enemyMove[i]=0;
        }
    }

    }

}

void enemyFire()
{
    for(int i=0; i<enemyNum; i++)
    {
        if(enemyX[i]-camx<1366 && enemyX[i]-camx > 0 && enemyHealth[i]>0.01 && enemyDamageStatus[i]==0)
        {
            if(abs(enemyY[i]-man_y)<20 && !enemyFireSuppress[i])
            {
                enemyFireIndex[i]=1;
            }
        }
    }
}

void enemyFireControl()
{
    for(int i=0; i<enemyNum; i++)
    {
        if(enemyFireIndex[i])
        {
            enemyFireSuppress[i] = 1;

            if(man_x<enemyX[i]-camx)
            {
            enemyFireX[i]=enemyX[i];
            enemyFireY[i]=enemyY[i]+50;
            }

            else
            {
            enemyFireX[i]=enemyX[i]+50;
            enemyFireY[i]=enemyY[i]+50;
            }

            enemyFireIndex[i]=0;
        }
    }
}

void enemyFireChange()
{
    for(int i=0; i<enemyNum; i++)
    {
            if(man_x<enemyX[i]-camx)
                {
                if(enemyFireLR[i]==-1)
                enemyFireLR[i]=0;   //something which will stay put until suppression is 0. ebong ami eta ke hatabo na until it has gone to the left
                //enemyFireX[i]-=5;   //controls speed of fire
                }

            else
                {
                if(enemyFireLR[i]==-1)
                enemyFireLR[i]=1;
                //enemyFireX[i]+=5;  //controls speed of fire

                }


        if(enemyFireX[i]-camx<-30 || enemyFireX[i]-camx>1396)
        {
            enemyFireSuppress[i]=0;
            enemyFireLR[i]=-1;
            enemyFireRenderOff[i]=0;
        }

    }

}

void drawEnemyFire()
{
    for(int i=0; i<enemyNum; i++)
    {
        if(enemyFireLR[i]==0)
            enemyFireX[i]-=12;
        else if(enemyFireLR[i]==1)
            enemyFireX[i]+=12;
    }
}





float laserEndDetect(float laserX, float laserY)  //FUNCTION TO DETECT THE ENDING POINT OF A LASER
{
    float matchX[100]; //KEEPS RECORD OF ALL X'S WHICH MATCH THE REQUIREMENTS
    int c=0; //KEEPS TRACK OF THE NUMBER OF ELEMENTS IN ARRAY AKA THE NUMBER OF MATCHES+1 (REASON BELOW)

    if(manRight)
    {
        for(int i=0; i<enemyNum; i++)
        {

            if(laserY-(enemyY[i]-camy)>0 && laserY-(enemyY[i]-camy)<enemyHeight[i] && laserX<(enemyX[i]-camx) && enemyHealth[i]>0.01 && enemyX[i]-camx<1366)
            {
                //POPULATING THE ARRAY
                matchX[c] = (enemyX[i]-camx);

                c++; //CAUSES C TO ALWAYS BE LARGER BY 1


            }
        }

        if(!c)//IF THERE ARE NO MATCHES
        {
            enemyHitIndex = -1;
            return 1366; //INFINITE LASER
        }


        else
        {
            //finding the minimum

            float minX = matchX[0];
            for(int i = 0; i<c; i++)
            {
                if(matchX[i]<minX)
                    minX = matchX[i];

            }

            for(int i=0; i<enemyNum; i++)
            {
                if(minX == (enemyX[i]-camx))
                    enemyHitIndex = i;
            }

            return minX;
        }
    }

    if(manLeft)
    {
        for(int i=0; i<enemyNum; i++)
    {

        if(laserY-(enemyY[i]-camy)>0 && laserY-(enemyY[i]-camy)<enemyHeight[i] && laserX>(enemyX[i]-camx) && enemyHealth[i]>0.01 && enemyX[i]-camx>0)
        {
            //POPULATING THE ARRAY
            matchX[c] = (enemyX[i]-camx);
            c++; //CAUSES C TO ALWAYS BE LARGER BY 1


        }
    }

    if(!c)//IF THERE ARE NO MATCHES
    {
        enemyHitIndex = -1;
        return 0; //INFINITE LASER
    }


    else
    {
        //finding the minimum

        float minX = matchX[0];
        for(int i = 0; i<c; i++)
        {
            if(matchX[i]<minX)
                minX = matchX[i];

        }

        for(int i=0; i<enemyNum; i++)
        {
            if(minX == (enemyX[i]-camx))
                enemyHitIndex = i;
        }

        return minX+enemyWidth[enemyHitIndex];
    }
    }
}

int reduceEnemyHealth() //FUNCTION TO REDUCE ENEMY HEALTH TO 0
{
    int i;
    for( i=0; i<enemyNum; i++)
        enemyDamageStatus[i]=0;

    if(laserSwitch == 1 && enemyHitIndex != -1)
    {
        if(enemyHealth[enemyHitIndex]>=0)
        {
            enemyDamageStatus[enemyHitIndex] = 1;
            enemyHealth[enemyHitIndex]-=enemyDamageRate[enemyHitIndex];  //ADJUST TO REDUCE DAMAGE RATE

        }
    }

    return 1;
}

void laser()
{

    if(manRight && !game_over)
    {
        float laserX = man_x+50;
        float laserY = man_y+85;

        iSetColor(255,0,0);
        iLine(laserX-15, laserY+2, laserEndDetect(laserX, laserY)+25, laserY+2);
        iSetColor(255,0,0);
        iLine(laserX-15, laserY+1, laserEndDetect(laserX, laserY)+25, laserY+1);
        iSetColor(255,255,0);
        iLine(laserX-15, laserY, laserEndDetect(laserX, laserY)+25, laserY);
        iSetColor(255,0,0);
        iLine(laserX-15, laserY-1, laserEndDetect(laserX, laserY)+25, laserY-1);
        iSetColor(255,0,0);
        iLine(laserX-15, laserY-2, laserEndDetect(laserX, laserY)+25, laserY-2);

    }

    if(manLeft && !game_over)
    {
        float laserX = man_x+20;
        float laserY = man_y+85;

        iSetColor(255,0,0);
        iLine(laserX, laserY+2, laserEndDetect(laserX, laserY), laserY+2);
        iSetColor(255,0,0);
        iLine(laserX, laserY+1, laserEndDetect(laserX, laserY), laserY+1);
        iSetColor(255,255,0);
        iLine(laserX, laserY, laserEndDetect(laserX, laserY), laserY);
        iSetColor(255,0,0);
        iLine(laserX, laserY-1, laserEndDetect(laserX, laserY), laserY-1);
        iSetColor(255,0,0);
        iLine(laserX, laserY-2, laserEndDetect(laserX, laserY), laserY-2);
    }

}



void enemyF()
{
    iSetColor(0,0,0);
    iRectangle(enemyFX-camx, enemyFY-camy, 10, 10);
}

void changeEnemy()
{

    if((enemyFX-camx<man_x+200)&&(enemyFX-camx>man_x-100) && (enemyFY-camy<man_y+200) && (enemyFY-camy>man_y-100))
    return;


         if(enemyFX-camx-man_x>10 || man_x-enemyFX+camx>10)
    {
        if(enemyFX-camx>man_x)
        enemyFX-=10;
        else
            enemyFX+=10;

        if(enemyFY-camy>man_y)
        {
            enemyFY-=10*((enemyFY-man_y)/abs(enemyFX-man_x));
        }

        else if(enemyFY-camy<man_y)
        {
            enemyFY+=10*((man_y-(enemyFY-camy))/abs(enemyFX-camx-man_x));
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

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    if(level==2 && getname)
    {
        if(key==8)
        {
            if(name_input_len)
                {
                    str[name_input_len-1]='\0';
                    name_input_len--;
                    if(name_input_len<0)
                        name_input_len=0;
                }
            else
                name_input_len=0;
        }
        else if((key>=48 && key<=57) || (key>=65 && key<=90) || (key>=97 && key<=122))
        {
            str[name_input_len]=key;
            //name_input_len++;
            str[++name_input_len]='\0';
        }
    }
    if(name_input_len>20)
        name_input_len=20;
    if((key==27) && game_over!=1){
        level=0;
        game_over=0;
        new_game=0;
        cont=0;
        level_one_sound();
        pause_menu_sound();
    }
    if(key == 13 && level==2)
    {
       // ******************************************************
  //      EKHANE STRING TA FILE E NITE HOBE MUST


        //name_input_len=1;
        if(getname){
        if(strlen(str)!=0)strcpy(HighScore[leaderboardIndex].name, str);
        for(int i=name_input_len;i>=0;i--){
            str[i]=0;
        }

        FILE* fp21 = fopen("high score.txt", "w");

        for(int i=0; i<5; i++)
        {
            fprintf(fp21, "%s %d\n", HighScore[i].name, HighScore[i].score);
        }

        fclose(fp21);
        current_score=0;
        score_multiplier=1;

        str[0]='\0';
        name_input_len=0;
        getname=0;
        }


        reset_curr_score=1;

        level=0;
        your_score_page_sound();
        menu_sound();
    }

     if((key == 'e' || key=='E') && !laserStat && level==1 && !manMove)
    {
        laserSwitch = 1;
    }
    if(key=='k')
        health=100;

    if(key=='s')
        {
            dx=20;
            dy=20;
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
    if(key == GLUT_KEY_DOWN && !manHitToLeft && !manHitToRight)
    {
        reset = 0;
        dy=5;
        if(sprint%2==1)
            dy=10;

        if(man_y>55)
            man_y-=dy;


        man_mov_down=1;
        man_mov_left=0;
        man_mov_right=0;
        man_mov_up=0;

    }
    if(key == GLUT_KEY_UP && !manHitToLeft && !manHitToRight)
    {
        reset = 0;
        dy=5;
        if(sprint%2==1)
            dy=10;

        if(man_y<660)
            man_y+=dy;

//        else if(camy<500)
//        {
//            camy+=dy;
//        }

        man_mov_down=0;
        man_mov_left=0;
        man_mov_right=0;
        man_mov_up=1;
    }
    if(key == GLUT_KEY_RIGHT && !manHitToLeft && !manHitToRight)
    {
        reset = 0;
        dx=5;
        if(sprint%2==1)
            dx=10;

        manLeft=0;
        manRight=1;

        if(man_x<1246)
        {

            //COORDINATION BETWEEN MAN AND CAMERA: FIRST 500 UNITS WITHOUT CHANGING THE CAMERA POSITION
            if(man_x<=500)
            {
                man_x+=dx;
            }
            //MIDDLE MOVEMENT HAPPENS WHEN MAN X TIRES TO EXCEED 400 AND CAMERA IS BETWEEN 0 AND 1000
            else if(man_x>500)
            {
                if(camx<=world_len_right)
                    camx+=dx;
            }

            //STOPPING THE CAMERA AFTER CAMERA X TRIES TO EXCEED 1000
            if(camx>world_len_right)
            {
                man_x+=dx;
            }


        }


        man_mov_down=0;
        man_mov_left=0;
        man_mov_right=1;
        man_mov_up=0;

    }
    if(key == GLUT_KEY_LEFT && !manHitToLeft && !manHitToRight)
    {
        reset = 0;
         dx=5;
        if(sprint%2==1)
            dx=10;

        manLeft=1;
        manRight=0;

        //BASE CONDITION: UNTIL THE MAN REACHES 10
        if(man_x>50)
        {

            //ONCE CAMX TRIES TO GO TO A NEGATIVE VALUE, REDUCE man_x UP TILL BASE CONDITION AT THE TOP

            if(camx<0)
            {
                man_x-=dx;
            }


            //IF CAMERA X IS GREATER THAN 1000 (5 added to make small buffer (ALWAYS LESS THAN dx))


            //IF man_x TRIES TO GO BELOW 800, REDUCE CAMERA X UNTIL CAMERA X BECOMES EQUAL TO 0
            if(man_x<=700)
            {
                if(camx>=0)
                    camx-=dx;
            }

            if(man_x>=700)
                man_x-=dx;
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

void enemyFire_health(int i)
{
    if( man_x>=enemyFireX[i]-man_wid-camx && man_x<=enemyFireX[i]-man_x-camx+10 && man_y>=enemyFireY[i]-man_height-camy && man_y<=enemyFireY[i]+10-camy )
    {
        if(health>0)
            health-=1;
        else health=0;
    }
}

void vertical_health_change(int i)
{
    if((man_y>=vertical_laser_y[i]-camy-man_height && man_y<=vertical_laser_y[i]-camy+40) && (man_x>=vertical_laser_x[i]-camx-man_wid && man_x<=vertical_laser_x[i]-camx+40))
    {
        if(man_x>=30 && man_x<=1350 && man_y>=50 && man_y<=660)
        {
            man_x-=2;
            man_y-=2;
        }
        if(health>0)
            health-=1;
        else health=0;
    }
}
void static_vertical_health_change(int len,int i)
{
    if((man_y>=static_ver_laser_y[i]-camy-man_height && man_y<=static_ver_laser_y[i]-camy+len) && (man_x>=static_ver_laser_x[i]-camx-man_wid && man_x<=static_ver_laser_x[i]-camx+10))
    {
        if(man_x>=30 && man_x<=1350 && man_y>=50 && man_y<=660)
        {
            man_x-=2;
            man_y-=2;
        }
        if(health>5)
            health-=5;
        else health=0;
    }
}

void horizontalLaser(int laserLen,int i)
{
    iSetColor(lasercolorR,255,lasercolorB);
    iFilledRectangle(laser_x[i]-camx,laser_y[i]-camy,laserLen,3);
    iSetColor(0,255,0);
    iFilledRectangle(laser_x[i]-camx-10,laser_y[i]-camy-3,10,10);

    iSetColor(0,255,0);
    iFilledRectangle(laser_x[i]-camx+laserLen,laser_y[i]-camy-3,10,10);

}
//void verticalLaser(int laserLen,int i)
//{
//    iSetColor(lasercolorR,255,lasercolorB);
//    iFilledRectangle(vertical_laser_x[i]-camx,vertical_laser_y[i]-camy,3,laserLen);
//    iSetColor(0,255,0);
//    iFilledRectangle(vertical_laser_x[i]-camx-3,vertical_laser_y[i]-camy-10,10,10);
//    iSetColor(0,255,0);
//    iFilledRectangle(vertical_laser_x[i]-camx-3,vertical_laser_y[i]-camy+100,10,10);
//}

void static_verticalLaser(int laserLen,int i)
{
    iSetColor(255,lasercolorR,lasercolorB);
    iFilledRectangle(static_ver_laser_x[i]-camx,static_ver_laser_y[i]-camy,10,laserLen);
    iSetColor(122,122,122);
    iFilledRectangle(static_ver_laser_x[i]-camx-10,static_ver_laser_y[i]-camy-10,20,20);
    iSetColor(122,122,122);
    iFilledRectangle(static_ver_laser_x[i]-camx-10,static_ver_laser_y[i]-camy+laserLen,20,20);
}
//**************************
void vertical_shooter(int i)
{
    iShowBMP2(vertical_laser_x[i]-camx,vertical_laser_y[i]-camy-5,"images\\fly.bmp",0xFFFFFF);
}
//******************************************
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
                health_y[hel_pck_num-1]-=2;
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
    if(bomb_chk){
        iSetColor(255,0,0);
       // iFilledCircle(bomb_x[bomb_cnt-1]-camx,bomb_y[bomb_cnt-1],bomb_r,100);
        iShowBMP2(bomb_x[bomb_cnt-1]-camx,bomb_y[bomb_cnt-1],"images\\bomb.bmp",0xFFFFFF);
        bomb_x[bomb_cnt-1]=bomb_x[bomb_cnt-1]+bomb_x_change[bomb_cnt-1];
        bomb_y[bomb_cnt-1]+=bomb_y_change[bomb_cnt-1];
//        d[0]=sqrt((man_x-bomb_x[bomb_cnt-1])*(man_x-bomb_x[bomb_cnt-1])+(man_y-bomb_y[bomb_cnt-1])*(man_y-bomb_y[bomb_cnt-1]));
//        d[1]=sqrt(((man_x+man_wid)-bomb_x[bomb_cnt-1])*((man_x+man_wid)-bomb_x[bomb_cnt-1])+(man_y-bomb_y[bomb_cnt-1])*(man_y-bomb_y[bomb_cnt-1]));
//        d[2]=sqrt((man_x-bomb_x[bomb_cnt-1])*(man_x-bomb_x[bomb_cnt-1])+((man_y+man_height)-bomb_y[bomb_cnt-1])*((man_y+man_height)-bomb_y[bomb_cnt-1]));
//        d[3]=sqrt(((man_x+man_wid)-bomb_x[bomb_cnt-1])*((man_x+man_wid)-bomb_x[bomb_cnt-1])+((man_y+man_height)-bomb_y[bomb_cnt-1])*((man_y+man_height)-bomb_y[bomb_cnt-1]));
        bmb_rnge_x=bomb_x[bomb_cnt-1]-bomb_r;
        bmb_rnge_y=bomb_y[bomb_cnt-1]-bomb_r;
//        if(d[0]<=bomb_r||d[1]<=bomb_r||d[2]<=bomb_r||d[3]<=bomb_r){
//            if(health>2)
//                health-=2;
//            else
//                health=0;
//        }
        if(((man_x+man_wid)>=bmb_rnge_x-camx&& man_x<=(bmb_rnge_x+2*bomb_r-camx)) && ((man_y+man_height)>=bmb_rnge_y && man_y<=(bmb_rnge_y+2*bomb_r))){
            bomb_chk=0;
            bomb_x[bomb_cnt-1]=bomb_initial_x;
            bomb_y[bomb_cnt-1]=bomb_initial_y;
        if(man_x>=30 && man_x<=1350 && man_y>=50 && man_y<=660)
        {
            man_x-=2;
            man_y-=2;
        }
            if(health>10)
                health-=10;
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

void enemyplane(int m)
{
    if(bul[m]==1){
        iSetColor(100,100,100);
        //dis[m]=dis[m]+3;
        bul_x[m]=bul_x[m]-3;
        iFilledRectangle(bul_x[m]-camx,bul_y[m],6,4);

            if(bul_x[m]-camx<-4){
                bul[m]=0;
                test[m]=1;
            }
            if((man_x>=bul_x[m]-camx-man_wid && man_x<=bul_x[m]-camx+6) && (man_y>=bul_y[m]-man_height && man_y<=bul_y[m]+4))
        {
            bul_x[m]=-100,bul_y[m]=-100;

            if(health>0.3)
                health-=.3;
            else health=0;

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
    strcat(hi_score,itoa(HighScore[0].score,buf,10));
    iSetColor(255,0,0);
    iText(10,710,hi_score);
}


void show_current_score_lead()
{
    char curr_scr[100], buf[100];
    strcpy(curr_scr,"YOUR SCORE: ");
    strcat(curr_scr,itoa(current_score,buf,10));
    iSetColor(255,255,255);
    iText(460,520,"CONGRATULATIONS! You have made it to the leaderboard!");
    iText(560,550,curr_scr,GLUT_BITMAP_TIMES_ROMAN_24);
}
void show_current_score_lost()
{
    char curr_scr[100], buf[100];
    strcpy(curr_scr,"YOUR SCORE: ");
    strcat(curr_scr,itoa(current_score,buf,10));
    iSetColor(255,255,255);
    iText(560,400,curr_scr,GLUT_BITMAP_TIMES_ROMAN_24);
    iText(460,350,"SORRY! You couldn't make it to the leaderboard :(");
    iText(560,320,"Press ENTER to Continue");
}
void High_scores()
{
    int i;
    char ch[21];
    int x=400;
    int y=550;
    for(i=0;i<5;i++)
    {
        sprintf(ch,"%s",HighScore[i].name);
        iSetColor(255,255,255);
        iText(x,y,ch,GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(ch,"%d",HighScore[i].score);
        iSetColor(255,255,255);
        iText(x+300,y,ch,GLUT_BITMAP_TIMES_ROMAN_24);
        y-=35;
    }
}

void score()
{   if(!game_over && level==1 && !game_completed){
        current_score+=1*score_multiplier;
    }
}
void health_change(int i)
{
    if((man_x>=laser_x[i]-camx-man_wid && man_x<=laser_x[i]-camx+100) && (man_y>=laser_y[i]-camy-man_height && man_y<=laser_y[i]-camy+2))
    {
        if(man_x>=30 && man_x<=1350 && man_y>=50 && man_y<=660)
        {
            man_x-=2;
            man_y+=2;
        }
        if(health>0)
            health-=1;
        else health=0;
    }
}

//******************************* ANUP NEW *************************
void enemyTouch_health_change(int i)
{
    if((man_x>=enemyX[i]-camx-man_wid && man_x<=enemyX[i]-camx+enemyHeight[i]) && (man_y>=enemyY[i]-camy-man_height && man_y<=enemyY[i]-camy+enemyWidth[i]) && enemyHealth[i]>.01)
    {
        if(man_x>=30 && man_x<=1350 && man_y>=50 && man_y<=660)
        {
            if(man_mov_left)
                man_x+=6;
            if(man_mov_right)
                man_x-=6;
            if(man_mov_down)
                man_y+=6;
            if(man_mov_up)
                man_y-=6;
        }
        if(health>0)
            health-=1;
        else health=0;
    }
}


void laser_move(int i)
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
        }

//******************************* ANUP NEW *************************
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
    if(reset<10)
    {
        manMove=1;
    }
    else
        manMove=0;

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
        if(bg==60)
            bg=1;
      //  iShowBMP(0,0,"images\\1.bmp");

//        iRectangle(185,382,270,100);
//        iRectangle(185,382-80,295,80);
//        iRectangle(185,382-160,315,80);
//        iRectangle(185,382-240,350,80);


        //if(cont==1)
        //{
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


             fp4=fopen("vertical_laser.txt","w");
            for(int i=0;i<vertical_laser_count;i++){
                fscanf(fp4,"%d",&vertical_laser_y[i]);
            }
            fclose(fp4);


            fp5=fopen("bomb1.txt","r");
            fscanf(fp5,"%d %d %d",&bomb_cnt,&bomb_chk,&bomb_tm);
            fclose(fp5);


            fp6=fopen("bomb2.txt","r");
            fscanf(fp6,"%lf %lf %lf %lf %lf %lf %lf %lf",&bomb_x[bomb_cnt-1],&bomb_y[bomb_cnt-1],&bomb_x_change[bomb_cnt-1],&bomb_y_change[bomb_cnt-1],&bomb_initial_x,&bomb_initial_y,&bmb_rnge_x,&bmb_rnge_y);
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

            FILE *fp13;
            fp13=fopen("bul.txt","r");
            int m;
            for(m=0;m<10;m++){
                fscanf(fp13,"%d %d %f %f %d %d",&bul[m],&test[m],&bul_x[m],&bul_y[m],&bul_k,&vln);
            }
            fclose(fp13);

            FILE *fp14;
            fp14=fopen("camera.txt","r");
            fscanf(fp14,"%f %f",&camx,&camy);
            fclose(fp14);
int i;
            FILE *fp15;
            fp15=fopen("enemy_info.txt","r");
            for(i=0;i<enemyNum;i++)
            {
                fscanf(fp15,"%f %f ",&enemyY[i],&enemyHealth[i]);
            }
            fclose(fp15);

            //iText(500,500,"Continue");
            cont=0;


        //}
        if(how_to_play==1)
        {
            iShowBMP(0,0,"images\\howto.bmp");
            if(back_from_howto)
                how_to_play=0;
          //  iRectangle(603,50,180,65);
            //iText(500,500,"how");
        }
        if(new_game==1)
        {
            timer=0;
            new_game=1;
            score_multiplier=1;
            score_count[0]=0;
            score_count[1]=0;
            score_count[2]=0;
            score_count[3]=0;
            score_count[4]=0;
            current_score=0;
            health=100;
            sprint=0;
            cont=0;
            level=1;
                man_mov_right=1;
                man_mov_down=0;
                man_mov_left=0;
                man_mov_up=0;
                man_x=80;
                man_y=150;
                dx=3, dy=3;
                sprint=0;
                lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;

                laserMove[0]=1;
                laserMove[1]=1;
                laserMove[2]=1;
                laserMove[3]=1;
                laserMove[4]=1;
                laserMove[5]=1;
                laserMove[6]=1;

                laser_x[0]=300;
                laser_x[1]=700;
                laser_x[2]=200;
                laser_x[3]=500;
                laser_x[4]=1000;
                laser_x[5]=1200;
                laser_x[6]=1050;
                laser_x[7]=4200;
                laser_x[8]=4200;

//                laser_y[0]=700;
//                laser_y[1]=270;
//                laser_y[2]=400;
//                laser_y[3]=500;
//                laser_y[4]=270;
//                laser_y[5]=400;
//                laser_y[6]=650;

                vertical_laserMove[0]=0;
                vertical_laserMove[1]=1;
                vertical_laserMove[2]=0;
                vertical_laserMove[3]=1;
                vertical_laserMove[4]=0;
                vertical_laserMove[5]=1;
                vertical_laserMove[6]=0;
                vertical_laserMove[7]=1;
                vertical_laserMove[8]=0;
                vertical_laserMove[9]=1;
                vertical_laserMove[10]=0;
                vertical_laserMove[11]=1;
                vertical_laserMove[12]=0;


                vertical_laser_y[0]=550;
                vertical_laser_y[1]=400;
                vertical_laser_y[2]=500;
                vertical_laser_y[3]=450;
                vertical_laser_y[4]=300;
                vertical_laser_y[5]=200;
                vertical_laser_y[6]=550;
                vertical_laser_y[7]=400;
                vertical_laser_y[8]=500;
                vertical_laser_y[9]=450;
                vertical_laser_y[10]=300;
                vertical_laser_y[11]=200;
                vertical_laser_y[12]=550;

                vertical_laser_count=13;
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

                bmb_rnge_x=0;
                bmb_rnge_y=0;

                test[0]=0,test[1]=9,test[2]=18,test[3]=27,test[4]=36,test[5]=45,test[6]=54,test[7]=63,test[8]=72,test[9]=81;
                int i;
                for(i=0;i<10;i++){
                    bul[i]=0;
                }
                vln=0;
                bul_k=0;

                camx=0;
                camy=0;




                gem_collected[0]=0;
                gem_collected[1]=0;
                gem_collected[2]=0;

                laserHealth=100;
                laserSwitch=0;
            //iText(500,500,"new");
            level=1;
            new_game=0;
            cont=0;
        }
        if(high_score==1)
        {
            //level=-1;
            iShowBMP(0,0,"images\\highscore.bmp");
            //for(int i=0;i<5;i++)
                High_scores();
            if(back_from_high)
            {
                high_score=0;
            }
          //  iRectangle(603,50,180,65);
        }
        if(credit)
        {
            iShowBMP(0,0,"images\\credits.bmp");
            if(back_from_credit)
            {
                credit=0;
            }
        }

//        if(cont_rectangle_sweep)
//        {
//            iSetColor(0,0,0);
//            iRectangle(185,375,280,75);
//        }

    }

    man_wid=60,man_height=95;
//level=1;
    if(level==1)
    {
        int i;
        //iRectangle(man_x,man_y,man_wid,man_height);
        for(i=0; i<enemyNum; i++)
        enemyImageTrack[i]++;
        manImageTrack++;

        if(laserSwitch)
            manLaserImageTrack++;

        else
            manLaserImageTrack=0;



        if(!game_completed)
            timer+=.01;


        for(i=0;i<enemyNum;i++)
        {
            if(enemyHealth[i]<0.01)
            {
                if(enemyHealth[i]==-1)
                    continue;
                kill_count++;
                score_multiplier++;
                enemyHealth[i]=-1;
            }
        }

//        if(timer>=10)
//            health=110;
//           takes 36 seconds to reach 0 to 10

        iShowBMP(0,0,"images\\BG2.bmp");
        //        *********************** moving illusion ****************

        for(i=0;i<10;i++)
        {iSetColor(245,245,245);
        iFilledEllipse(400+i*1000-camx/2,600,60,30);
        iFilledEllipse(400-50+i*1000-camx/2,600,30,20);
        iFilledEllipse(400+100+i*1000-camx/2,600,40,20);

        iFilledEllipse(400+20+i*1000-camx/2,610,80,40);
        iFilledEllipse(400+20+i*1000-camx/4,600,80,40);
        iFilledEllipse(400+40+i*1000-camx/5,620,80,50);}
        iShowBMP2(1200-camx/10,670,"images\\sun.bmp",0xFFFFFF);

//        *********************** moving illusion ****************
        //ENEMIES:
    enemy();
    reduceEnemyHealth();
    changeEnemyY();
    enemyFire();
    enemyFireControl();
    enemyFireChange();
    drawEnemyFire();
    reduceManHealth();

    //DRAWING ENEMY FIRE
    iSetColor(255,0,0);
    for(int i=0; i<enemyNum; i++){

            if(!enemyFireRenderOff[i])
            {
                 if(enemyFireY[i]-man_y<80 && enemyFireY[i]-man_y>0)
        {
            if(enemyFireLR[i]==0 && enemyFireX[i]-camx-man_x>50)
            {
                iShowBMP2(enemyFireX[i]-camx, enemyFireY[i], "images\\fireleft.bmp", 0xFFFFFF);

            }



            if(enemyFireLR[i]==1 && man_x-enemyFireX[i]+camx>0)
            {
                iShowBMP2(enemyFireX[i]-camx, enemyFireY[i], "images\\fireright.bmp", 0xFFFFFF);
            }

        }

        else
        {
            if(enemyFireLR[i]==0)
            iShowBMP2(enemyFireX[i]-camx, enemyFireY[i], "images\\fireleft.bmp", 0xFFFFFF);
            else if(enemyFireLR[i]==1)
            iShowBMP2(enemyFireX[i]-camx, enemyFireY[i], "images\\fireright.bmp", 0xFFFFFF);

        }
            }


    }

    if(manHitToLeft)
    {
        if(manLeftDisplacement<20)
        {
            if(man_x>10)
            man_x-=2;
            manLeftDisplacement++;
        }
        else
        {
            manLeftDisplacement=0;
            manHitToLeft=0;
        }

    }

    if(manHitToRight)
    {
        if(manRightDisplacement<20)
        {
            if(man_x<1340)
            man_x+=2;
            manRightDisplacement++;
        }
        else
        {
            manRightDisplacement=0;
            manHitToRight=0;
        }

    }

//        int gem_cou;
//        if(man_x>=1000-man_wid && man_x<=1000+40 && man_y>=700-man_height && man_y<=700+40)      // make it like bomb touch
//            gem_collected[0]=1;                      //show the gem in one corner in small size if taken
//        if(!gem_collected[0])
//            iShowBMP2(1000,700,"images\\pink-gem.bmp",0xFFFFFF);    //this is gem 1

//        if(gem_collected[0])
//            iText(80,700,"CONGRATULATIONS! You have collected a gem");
////      GEM TEXT
        iSetColor(255, 100, 10);

       // iRectangle(man_x,man_y,man_wid,man_height);
        //iRectangle(dead_man_x,dead_man_y,man_wid,man_height);

        renderSuperMan();

        changelasercolor();

//******************************* ANUP NEW *************************

        for(i=0;i<horizontal_laser_count;i++)
        {
            laser_move(i);
        }


        for(i=0;i<enemyNum;i++)
        {
            enemyTouch_health_change(i);
        }

//******************************* ANUP NEW *************************

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
           // verticalLaser(100,i);
            vertical_shooter(i);
            vertical_health_change(i);

        }
        for(i=0;i<static_ver_laser_count;i++)
        {
            static_verticalLaser(static_laserLen,i);
            static_vertical_health_change(static_laserLen,i);
        }

        if(!health_pack_chk)
        {
            hel_tm++;
            if(hel_pck_num==3)
                hel_pck_num=0;
            if(hel_tm%300==0){
                health_pack_chk=1;
                hel_tm=0;
                hel_pck_num++;
                hel_initial_x=health_x[hel_pck_num-1];
                hel_initial_y=health_y[hel_pck_num-1];
                health_x[hel_pck_num-1]=health_x[hel_pck_num-1]+camx;
            }
        }
        if(health_pack_chk)
            healthPack();
        if(!bomb_chk)
        {
            bomb_tm++;
            if(bomb_cnt==4)
                bomb_cnt=0;
            if(bomb_tm%150==0)
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

         // enemyF();

    //LASER BAR
    iSetColor(255,0,0);
    iText(1200,660, "Laser Power");
    iRectangle(1200,670,100,6);
    iFilledRectangle(1200,670,laserHealth,6);


     //LASER INITIATE CODE
    if(!laserStat) //INDICATES ONE COMPLETE CYCLE OF LASER
    {
        if(laserSwitch) //INDICATES ON/OFF OF LASER
        {
            laser();
            laserTimer++;
            if(laserHealth>0)
                laserHealth-=1; //PRODUCT OF LASERHEALTH AND LASERTIMER IS ALWAYS EQUAL TO 100 - THE SIZE OF THE LASER BAR

            if(laserTimer>100) //INCREASE THIS NUMBER TO INCREASE DURATION OF LASER
            {
                laserStat=1;
                laserTimer=0;
                laserSwitch=0;
            }

        }

    }
    if(health>50)
                iSetColor(0,255,0);
            else if(health>20&&health<=50)
                iSetColor(255,255,0);
            else
                iSetColor(255,0,0);
            iRectangle(1200,700,100,8);
            iFilledRectangle(1200,700,health,8);

    //REFILLING THE LASER

    if(laserStat)
    {
        laserHealth+=2;         //CONTROLLING REFILLING OF LASER/REFILL THE LASER

        if(laserHealth>=100)
            laserStat=0;
    }
    score_show_live();

    int m;
        FILE *fp13;
        fp13=fopen("bul.txt","w");

        for(m=0;m<10;m++){
            if(bul[m]==0){
                test[m]++;
                if(bul_k==10){
                    bul_k=0;
                    vln++;
                    if(vln>vertical_laser_count){
                        vln=1;
                    }
                }
            }
            if(test[m]%bul_ctrl==0){

                if(vertical_laser_x[vln-1]-camx>0&&vertical_laser_x[vln-1]-camx<1366&&man_x<vertical_laser_x[vln-1]-camx){
                    bul_x[m]=vertical_laser_x[vln-1];
               //dis[m]=0;
                    bul_y[m]=vertical_laser_y[vln-1];
                    bul_k++;
                }
                else {
                     vln++;
                    if(vln>vertical_laser_count){
                        vln=1;
                    }
                }
                bul[m]=1;
                test[m]=1;
            }
            enemyplane(m);
            fprintf(fp13,"%d %d %lf %lf %d %d\n",bul[m],test[m],bul_x[m],bul_y[m],bul_k,vln);
        }
        fclose(fp13);
        //     if(camx==0)
        if(enemyHealth[20]<0.01)    //SEX
        {
            game_completed=1;
        }
        if(game_completed)
        {

            iSetColor(100,100,100);
            iText(450,congrats,"YOU HAVE COMPLETED THE GAME!!!",GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP2(10,congrats,"images\\congo.bmp",0xFFFFFF);
            if(congrats<=320)
                congrats+=4;
            else
                {
                    game_completed=0;
                    congrats=0;
                    goto LLL;
                }
        }
    }
    if(game_over)
    {
        if(man_y>=50)
            {
                man_y-=5;
            if(manImageTrack<=10)
            iShowBMP2(man_x,man_y,"images\\deadleft1.bmp",0xFFFFFF);
            else
            iShowBMP2(man_x,man_y,"images\\deadleft2.bmp",0xFFFFFF);

            if(manImageTrack>20)
                manImageTrack=0;

            }


        iShowBMP2(470,game_over_y,"images\\game_over.bmp",0xFFFFFF);
        if(game_over_y<=280)
            game_over_y+=4;
        if(game_over_y>=280)
        {
            game_end++;
            if(game_end==50){

                LLL: game_over_y=0;

                health=100;
                sprint=0;
                cont=0;

                Leaderboard temp, save;
                save.score = current_score;
                strcpy(save.name, "PLAYER");
                for(int i=0; i<5; i++)
                {
                    if(HighScore[i].score<=save.score)
                    {
                        if(getname == 0)leaderboardIndex=i;
                        getname = 1;
                        temp = HighScore[i];
                        HighScore[i] = save;
                        save = temp;
                    }
//                    for(int j=0;j<5;j++){
//                        printf("%s\t%d\n",HighScore[j].name,HighScore[j].score);
//                    }
//                    else
//                       getname == 0;
                }

                game_over=0;
                level=2;
                game_over_sound();
                your_score_page_sound();


                man_x=80;
                man_y=150;
                dx=3, dy=3;
                sprint=0;
                lasercolorR = 0,lasercolorG = 0,lasercolorB = 0, changecolor = 0;


                laserMove[0]=1;
                laserMove[1]=1;
                laserMove[2]=1;
                laserMove[3]=1;



                 enemyY[0]=250;
                enemyY[1]=200;
                enemyY[2]=150;
                enemyY[3]= 350 ;
                enemyY[4]=350  ;
                enemyY[5]=350  ;
                enemyY[6]=350  ;
                enemyY[7]= 350 ;
                enemyY[8]= 350 ;
                enemyY[9]= 350 ;
                enemyY[10]= 350 ;
                enemyY[11]= 400 ;
                enemyY[12]=600;
                enemyY[13]=200;
                enemyY[14]=400;
                enemyY[15]=300;
                enemyY[16]=300;
                enemyY[17]=200;
                enemyY[18]=400;
                enemyY[19]=600;
                enemyY[20]=400;



//                enemyX[0]= 500 ;
//                enemyX[1]= 1100 ;
//                enemyX[2]= 1800 ;
//                enemyX[3]= 2200 ;
//                enemyX[4]= 2450 ;
//                enemyX[5]= 3650 ;
//                enemyX[6]= 4650 ;
//                enemyX[7]= 5550 ;
//                enemyX[8]= 6450 ;
//                enemyX[9]= 7250 ;
//                enemyX[10]= 8050 ;
//                enemyX[11]= 3100 ;
//                enemyX[12]=3100;
//                enemyX[13]=3100;
//                enemyX[14]=3300;
//                enemyX[15]=300;

                enemyHealth[0]=100;
                enemyHealth[1]=100;
                enemyHealth[2]=100;
                enemyHealth[3]=100;
                enemyHealth[4]=100;
                enemyHealth[5]=100;
                enemyHealth[6]=100;
                enemyHealth[7]=100;
                enemyHealth[8]=100;
                enemyHealth[9]=100;
                enemyHealth[10]=100;
                enemyHealth[11]=200;
                enemyHealth[12]=200;
                enemyHealth[13]=200;
                enemyHealth[14]=400;
                enemyHealth[15]=100;
                enemyHealth[16]=100;
                enemyHealth[17]=100;
                enemyHealth[18]=100;
                enemyHealth[19]=100;
                enemyHealth[20]=300;



                vertical_laserMove[0]=0;
                vertical_laserMove[1]=1;
                vertical_laserMove[2]=0;
                vertical_laserMove[3]=1;
                vertical_laserMove[4]=0;
                vertical_laserMove[5]=1;
                vertical_laserMove[6]=0;
                vertical_laserMove[7]=1;
                vertical_laserMove[8]=0;
                vertical_laserMove[9]=1;
                vertical_laserMove[10]=0;
                vertical_laserMove[11]=1;
                vertical_laserMove[12]=0;


                vertical_laser_y[0]=550;
                vertical_laser_y[1]=400;
                vertical_laser_y[2]=500;
                vertical_laser_y[3]=450;
                vertical_laser_y[4]=300;
                vertical_laser_y[5]=200;
                vertical_laser_y[6]=550;
                vertical_laser_y[7]=400;
                vertical_laser_y[8]=500;
                vertical_laser_y[9]=450;
                vertical_laser_y[10]=300;
                vertical_laser_y[11]=200;
                vertical_laser_y[12]=550;

                vertical_laser_count=13;

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

                bmb_rnge_x=0;
                bmb_rnge_y=0;

                test[0]=0,test[1]=9,test[2]=18,test[3]=27,test[4]=36,test[5]=45,test[6]=54,test[7]=63,test[8]=72,test[9]=81;
                int i;
                for(i=0;i<10;i++){
                    bul[i]=0;
                }
                bul_k=0;
                vln=0;

                gem_collected[0]=0;
                gem_collected[1]=0;
                gem_collected[2]=0;


//                current_score=0;
//                score_multiplier=1;
                camx=0;
                camy=0;

                level=2;  // level=2 indicating the your score page

                new_game=0;
                cont=0;
                game_end=0;
                //PLEASE CHANGE THIS IF YOU INTEND TO CHANGE THE INITIAL POSITIONS
//                enemyX[0] = 200;
//                enemyX[1] = 400;
//                enemyX[2] = 600;
//                enemyX[3] = 1000;







            }

        }
    }
  //  level=2;
    if(level==2)
    {
        iShowBMP(0,0,"images\\yourscore.bmp");
        if(getname)
        {
            show_current_score_lead();
            iSetColor(255,255,255);
            iFilledRectangle(417+40,386,420,50);
            iSetColor(192,192,192);
            iFilledRectangle(417+5+40,386+5,420-10,50-10);

            iSetColor(255,255,255);
            iText(460,450,"Enter Your Nickname: (Please don't enter any spaces or special characters)");

            iSetColor(0,0,0);
            iSetColor(255,255,255);
            iText(417+20+40,386+18,str,GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,255);
            iText(460,400-35,"HIT ENTER TO CONTINUE");
        }
        else
            show_current_score_lost();
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
    for(int i=0;i<vertical_laser_count;i++){
        fprintf(fp4,"%d",vertical_laser_y[i]);
    }
    fclose(fp4);


    fp5=fopen("bomb1.txt","w");
    fprintf(fp5,"%d %d %d",bomb_cnt,bomb_chk,bomb_tm);
    fclose(fp5);

    fp6=fopen("bomb2.txt","w");
    fprintf(fp6,"%f %f %f %f %f %f %f %f",bomb_x[bomb_cnt-1],bomb_y[bomb_cnt-1],bomb_x_change[bomb_cnt-1],bomb_y_change[bomb_cnt-1],bomb_initial_x,bomb_initial_y,bmb_rnge_x,bmb_rnge_y);
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


    FILE *fp13;
    fp13=fopen("bul.txt","w");
    int m;
    for(m=0;m<10;m++){
        fprintf(fp13,"%d %d %f %f %d %d\n",bul[m],test[m],bul_x[m],bul_y[m],bul_k,vln);
    }
    fclose(fp13);

    FILE *fp14;
    fp14=fopen("camera.txt","w");
    fprintf(fp14,"%f %f",camx,camy);
    fclose(fp14);

    FILE *fp15;
    fp15=fopen("enemy_info.txt","w");
    int i;
    for(i=0;i<enemyNum;i++)
    {
        fprintf(fp15,"%f %f ", enemyY[i],enemyHealth[i]);
    }
    fclose(fp15);
}
int main()
{


    FILE *fp20 = fopen("high score.txt", "r");

    for(int i=0; i<5; i++)
    {
        fscanf(fp20, "%s %d\n", HighScore[i].name, &HighScore[i].score);

    }

    fclose(fp20);

    menu_sound();
    iSetTimer(50, changeEnemy);
    iSetTimer(50, detectMotion);
    iSetTimer(100,score);
//    PlaySound((LPCSTR) "C:\\Users\\Public\\Music\\Sample Music\\Sleep Away.mp3", NULL, SND_FILENAME | SND_ASYNC);
   //DWORD dwError = GetLastError();

    //place your own initialization codes here.
//  iSetTimer(5, ballChange);
//

    iInitialize(1366, 768, "Superman Adventures ver 1.6");

    return 0;
}
