//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include <GL/glut.h> 
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

float x2_in = 0, y2_in = 0, car1_x = 0, car1_y = 0, car2_x = 0, car2_y = 0, x1_in = 0, y1_in = 0, OrangeCarX = 100, OrangeCarY = 30, BlueCarX = 650, BlueCarY = 30; 
int flag_x1 = 0, flag_y1 = 0, flag_x2 = 0, flag_y2 = 0, Level_Speed = 1;
int Menu=0;
int life=3;
int score=0;
 
int food1[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food2[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food3[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food4[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food5[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food6[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food7[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};
int food8[9]={50, 140,  230, 320, 410, 500, 590, 680, 770};




int f_eat1[9]={0,0,0,0,0,0,0,0,0};
int f_eat2[9]={0,0,0,0,0,0,0,0,0};
int f_eat3[9]={0,0,0,0,0,0,0,0,0};
int f_eat4[9]={0,0,0,0,0,0,0,0,0};
int f_eat5[9]={0,0,0,0,0,0,0,0,0};
int f_eat6[9]={0,0,0,0,0,0,0,0,0};
int f_eat7[9]={0,0,0,0,0,0,0,0,0};
int f_eat8[9]={0,0,0,0,0,0,0,0,0};









// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;

void makeCar1(float x_in, float y_in, float width_in, float height_in){
	// Drawing opponent car
        float x = x_in; 
	float y = y_in;
	car1_x = x_in;
	car1_y = y_in; 
	float width = width_in-3; 
	float height = height_in-3;
	float* color = colors[ORANGE_RED]; 
	float radius = 1.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
}

void makeCar2(float x_in, float y_in, float width_in, float height_in){
	//Drawing my car
        float a = x_in; 
	float b = y_in;
	car2_x = x_in;
	car2_y = y_in; 
	float width_a = width_in-3; 
	float height_a= height_in-3;
	float* color_a = colors[BLUE_VIOLET]; 
	float radius_a = 1.0;
	DrawRoundRect(a,b,width_a,height_a,color_a,radius_a); // bottom left tyre
	DrawRoundRect(a+width_a*3,b,width_a,height_a,color_a,radius_a); // bottom right tyre
	DrawRoundRect(a+width_a*3,b+height_a*4,width_a,height_a,color_a,radius_a); // top right tyre
	DrawRoundRect(a,b+height_a*4,width_a,height_a,color_a,radius_a); // top left tyre
	DrawRoundRect(a, b+height_a*2, width_a, height_a, color_a, radius_a/2); // body left rect
	DrawRoundRect(a+width_a, b+height_a, width_a*2, height_a*3, color_a, radius_a/2); // body center rect
	DrawRoundRect(a+width_a*3, b+height_a*2, width_a, height_a, color_a, radius_a/2); // body right rect
	glFlush();
	glutPostRedisplay();
}

int getMapId(float x, float y){
	if((x < 515 && x > 268) && (y < 378 && y > 270)){
		return 4;
	}
	if((x < 600 && x >= 185) && (y <= 456 && y >= 190)){
		return 3;
	}
	if((x < 679 && x >= 105) && (y <= 534 && y >= 110)){
		return 2;
	}
	if((x < 764 && x >= 20) && (y <= 618 && y >= 30)){
		return 1;
	}
	return 0;

}


void GameDisplay()/**/{
	
        //Dispaly Menu
          if(Menu==0){
              DrawString( 350, 750, "*MENU*", colors[RED]);
              DrawString( 300, 600, "1) Start a New Game", colors[WHITE]);
              DrawString( 300, 550, "2) See high-scores", colors[WHITE]);
              DrawString( 300, 500, "3) Help", colors[WHITE]);
              DrawString( 300, 450, "4) Exit", colors[WHITE]);
              
              
              DrawString( 250, 200, "Enter number according to your choise", colors[WHITE]);
            
          }

         if (Menu==3){
                
                glClear (GL_COLOR_BUFFER_BIT);
                 
                DrawString( 350, 650, "HELP", colors[RED]);
                DrawString( 50, 500, "Instructions :", colors[WHITE]);
                DrawString( 50, 450, " Use arrow keys to dive your (orange car).", colors[WHITE]);
                DrawString( 50, 400, "-> When ever the both cars crash your 1 life will be deducted & game restarts.", colors[WHITE]);
                DrawString( 50, 350, "-> You Have 3 Lives each , Every time you start a new game.", colors[WHITE]);
                DrawString( 50, 300, "-> Press P to pause game & Display Menu.", colors[WHITE]);
                DrawString( 50, 250, "-> This Game has 4 Levels. Each time your car eats all the ", colors[WHITE]);
                DrawString( 50, 200, "   fruit your levels changes.", colors[WHITE]);
                }
              
         //Pause Menu         
           if(Menu==5){
              DrawString( 350, 750, "*MENU*", colors[RED]);
              DrawString( 300, 600, "1) Start a New Game", colors[WHITE]);
              DrawString( 300, 550, "2) See high-scores", colors[WHITE]);
              DrawString( 300, 500, "3) Help", colors[WHITE]);
              DrawString( 300, 450, "4) Exit", colors[WHITE]);
              DrawString( 300, 400, "5) Resume Game", colors[WHITE]);     
            
          }       
                                                                                                                                                                                
         if(Menu==1){
        // set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students

	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	

         //Display Score
	 DrawString( 650, 750, "Score:", colors[WHITE]);
         DrawString( 650, 720, to_string(score), colors[WHITE]);
        
         DrawString( 80, 750, "Lives:", colors[WHITE]);
         DrawString( 90, 720, to_string(life), colors[WHITE]);
      
        //Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	 //Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	
        
        //Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	
       
        //Line from 550,50 to 550,480 with width 10
        //int x1=550 ,y1=50 ,x2=550 ,y2=480,lwidth=10;
        //float *color;
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	//Making Cars
 	
	makeCar1(OrangeCarX + x1_in, OrangeCarY + y1_in, 15, 10);
	makeCar2(BlueCarX + x2_in, BlueCarY + y2_in, 15, 10);





        // Drawing Arena id: 1
	int gap_turn = 60;
	int sx = 20;
	int sy = 10;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 8;
	float *scolor = colors[BROWN];
	DrawRectangle(sx-50, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+30, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+5+swidth*2+gap_turn, sy+sheight, sheight*2, swidth-100, scolor); // right down
	DrawRectangle(sx+5+swidth*2+gap_turn, sy-80+sheight-150+swidth+gap_turn+180, sheight*2, swidth-100, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+30, sy+810-150, swidth, sheight, scolor); // top left
	DrawRectangle(sx-50, sy+810-150, swidth, sheight, scolor); // top right
	DrawRectangle(sx-4-sheight*2, sy-80+sheight-150+swidth+gap_turn+180, sheight*2, swidth-100, scolor); // left up
	DrawRectangle(sx-4-sheight*2, sy+sheight, sheight*2, swidth-100, scolor); // left down


	// id: 2
        int gap_turn_1 = 60;
	int sx_1 = 20;
	int sy_1 = 10;
	int swidth_1 = 800/2 - gap_turn_1/2; // half width
	int sheight_1 = 8;
	float *scolor_1 = colors[BROWN];
	DrawRectangle(sx_1+79, sy_1+80, swidth_1-130, sheight_1, scolor_1); // bottom left
	DrawRectangle(sx_1 + swidth_1 + gap_turn_1+30, sy_1+80, swidth_1-110, sheight_1, scolor_1); // bottom right
	DrawRectangle(sx_1-80+swidth_1*2+gap_turn_1, sy_1+80+sheight_1, sheight_1*2, swidth_1-180, scolor_1); // right down
        DrawRectangle(sx_1-80+swidth_1*2+gap_turn_1, sy_1-80+sheight_1-150+swidth_1+gap_turn_1+180, sheight_1*2, swidth_1-180, scolor_1); // right up
	DrawRectangle(sx_1 + swidth_1 + gap_turn_1+30, sy_1-80+810-150, swidth_1-110, sheight_1, scolor_1); // top left
	DrawRectangle(sx_1+79, sy_1-80+810-150, swidth_1-130, sheight_1, scolor_1); // top right
	DrawRectangle(sx_1+80-sheight_1*2, sy_1-80+sheight_1-150+swidth_1+gap_turn_1+180, sheight_1*2, swidth_1-180, scolor_1); // left up
	DrawRectangle(sx_1+80-sheight_1*2, sy_1+80+sheight_1, sheight_1*2, swidth_1-180, scolor_1); // left down


       	// id: 3
        int gap_turn_2 = 60;
	int sx_2 = 20;
	int sy_2 = 10;
	int swidth_2 = 800/2 - gap_turn_2/2; // half width
	int sheight_2 = 5;
	float *scolor_2 = colors[BROWN];
	DrawRectangle(sx_2+159, sy_2+160, swidth_2-210, sheight_2, scolor_2); // bottom left
	DrawRectangle(sx_2 + swidth_2 + gap_turn_2+30, sy_2+160, swidth_2-189, sheight_2, scolor_2); // bottom right
	DrawRectangle(sx_2-160+swidth_2*2+gap_turn_2, sy_2+160+sheight_2, sheight_2*2, swidth_2-259, scolor_2); // right down
	DrawRectangle(sx_2-160+swidth_2*2+gap_turn_2, sy_2-80+sheight_2-150+swidth_2+gap_turn_2+180, sheight_2*2, swidth_2-259, scolor_2); // right up
	DrawRectangle(sx_2 + swidth_2 + gap_turn_2+30, sy_2-160+810-150, swidth_2-189, sheight_2, scolor_2); // top left
	DrawRectangle(sx_2+159, sy_2-160+810-150, swidth_2-210, sheight_2, scolor_2); // top right
	DrawRectangle(sx_2+160-sheight_2*2, sy_2-80+sheight_2-150+swidth_2+gap_turn_2+180, sheight_2*2, swidth_2-259, scolor_2); // left up
	DrawRectangle(sx_2+160-sheight_2*2, sy_2+160+sheight_2, sheight_2*2, swidth_2-259, scolor_2); // left down
 

	// id = 4
        int gap_turn_3 = 60;
	int sx_3 = 20;
	int sy_3 = 10;
	int swidth_3 = 800/2 - gap_turn_3/2; // half width
	int sheight_3 = 5;
	float *scolor_3 = colors[BROWN];
	DrawRectangle(sx_3+239, sy_3+240, swidth_3-290, sheight_3, scolor_3); // bottom left
	DrawRectangle(sx_3 + swidth_3 + gap_turn_3+30, sy_3+240, swidth_3-269, sheight_3, scolor_3); // bottom right
	DrawRectangle(sx_3-240+swidth_3*2+gap_turn_3, sy_3+240+sheight_3, sheight_3*2, swidth_3-345, scolor_3); // right down
	DrawRectangle(sx_3-240+swidth_3*2+gap_turn_3, sy_3-80+sheight_3-150+swidth_3+gap_turn_3+180, sheight_3*2, swidth_3-340, scolor_3); // right up
	DrawRectangle(sx_3 + swidth_3 + gap_turn_3+30, sy_3-240+810-150, swidth_3-269, sheight_3, scolor_3); // top left
	DrawRectangle(sx_3+239, sy_3-240+810-150, swidth_3-290, sheight_3, scolor_3); // top right
	DrawRectangle(sx_3+240-sheight_3*2, sy_3-80+sheight_3-150+swidth_3+gap_turn_3+180, sheight_3*2, swidth_3-340, scolor_3); // left up
	DrawRectangle(sx_3+240-sheight_3*2, sy_3+240+sheight_3, sheight_3*2, swidth_3-345, scolor_3); // left down


	// id: 5
        int gap_turn_4 = 60;
	int sx_4 = 20;
	int sy_4 = 8;
	int swidth_4 = 800/2 - gap_turn_3/2; // half width
	int sheight_4 = 5;
	float *scolor_4 = colors[BROWN];
	DrawRectangle(sx_4+320, sy_4+320, swidth_4-290, sheight_4, scolor_4); // bottom left
	DrawRectangle(sx_4-50 + swidth_4 + gap_turn_4+30, sy_4+320, swidth_4-299, sheight_4, scolor_4); // bottom right
	DrawRectangle(sx_4-320+swidth_4*2+gap_turn_4, sy_4+320+sheight_4, sheight_4*2, swidth_4-359, scolor_4); // right down
	
	DrawRectangle(sx_4-50 + swidth_4 + gap_turn_4+30, sy_4-320+810-150, swidth_4-299, sheight_4, scolor_4); // top left
	DrawRectangle(sx_4+320, sy_4-320+810-150, swidth_4-290, sheight_4, scolor_4); // top right
	
	DrawRectangle(sx_4+320-sheight_4*2, sy_4+320+sheight_4, sheight_4*2, swidth_4-359, scolor_4); // left down


               //Fruit
               for(int i=0; i<9; i++){    
		 if((food1[i] == car1_x) && (car1_y <= 608 && car1_y >= 28) && (getMapId(car1_x, car1_y) == 1)){
			f_eat1[i]=1;
                        score+=1;  
		} if(f_eat1[i]==0) {
			DrawSquare( food1[i] , 47 ,10,colors[BROWN]);
			
		}
                
                 }  
	

          	for(int i=0; i<9; i++){       
                   if((food2[i] == car1_x) && (car1_y <= 131 && car1_y >= 115)){
			f_eat2[i]=1;  
                         score+=1;
		} if(f_eat2[i]==0) {
			DrawSquare( food2[i] , 127 ,10,colors[BROWN]);
			
		}
                }  

               for(int i=0; i<9; i++){    
                   if((food3[i] == car1_x) && (car1_y <= 212&& car1_y >= 193)){
			f_eat3[i]=1;  
			 score+=1;
		} if(f_eat3[i]==0) {
			DrawSquare( food3[i] , 207 ,10,colors[BROWN]);
			
		}   
                }  

 	       for(int i=0; i<9; i++){       
                    if((food4[i] == car1_x) && (car1_y <= 292 && car1_y >= 273)){
			f_eat4[i]=1;
			 score+=1;  
		} if(f_eat4[i]==0) {
			DrawSquare( food4[i] , 287 ,10,colors[BROWN]);
			
		}               
                }  
 
               for(int i=0; i<9; i++){       
                    if((food5[i] == car1_x) && (car1_y <= 386 && car1_y >= 353)){
			f_eat5[i]=1;  
			 score+=1;
		} if(f_eat5[i]==0) {
			DrawSquare( food5[i] , 383 ,10,colors[BROWN]);
			
		}               
               }  

               for(int i=0; i<9; i++){       
                  if((food6[i] == car1_x) && (car1_y <= 469 && car1_y >= 433)){
			f_eat6[i]=1; 
			 score+=1; 
		} if(f_eat6[i]==0) {
			DrawSquare( food6[i] , 463 ,10,colors[BROWN]);
			
		}              
               }  
                
                for(int i=0; i<9; i++){    
                    if((food7[i] == car1_x) && (car1_y <= 548 && car1_y >= 513)){
			f_eat7[i]=1;
			 score+=1;  
		} if(f_eat7[i]==0) {
			DrawSquare( food7[i] , 543 ,10,colors[BROWN]);
			
		}
                }  
                
                for(int i=0; i<9; i++){       
                   if((food8[i] == car1_x) && (car1_y <= 629 && car1_y >= 595)){
			f_eat8[i]=1; 
			 score+=1; 
		}if(f_eat8[i]==0) {
			DrawSquare( food8[i] , 623 ,10,colors[BROWN]);
			
		}
                }  


             
}

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {  //Keys For Operation of My Car (Orange).

       if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		if(car1_y >= 280 && car1_y <= 350){
			x1_in -= 80;
			cout << "X: " << to_string(car1_x)  << "& Y: " << to_string(car1_x) << endl;
		}

	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
                   if(car1_y >= 280 && car1_y <= 350){
			x1_in += 80;
			cout << "X: " << to_string(car1_x)  << "& Y: " << to_string(car1_x) << endl;
		}


	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
                 
		if(car1_x >= 350 && car1_x <= 410){
			y1_in += 80;
			cout << "X: " << to_string(car1_x)  << "& Y: " << to_string(car1_y) << endl;
		}


	

        } else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
                    
		if(car1_x >= 350 && car1_x <= 410){
			y1_in -= 80;
			cout << "X: " << to_string(car1_x)  << "& Y: " << to_string(car1_y) << endl;
		}


	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}


/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {

        //Exit
	if (key == 52 /* 4 Digit key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	
	// Start Game
	if (key == 49 /* 1 key ASCII*/){
		cout << "Menu: " << to_string(Menu) << "\n";
		Menu = 1;

		x1_in = 0;
		y1_in = 0;
		x2_in = 0;
		y2_in = 0;
		//Menu = 0;
		OrangeCarX = 100;
		OrangeCarY = 32;
		BlueCarX = 650;
		BlueCarY = 32;
		glutDisplayFunc(GameDisplay);
	}

	// See High Score	
	if (key == 50 /* 2 key ASCII*/){
		//cout << "Menu: " << to_string(Menu) << "\n";
		//Menu = 1;
		//glutDisplayFunc(GameDisplay);
	}

	// Help
	if (key == 51 /* 3 key ASCII*/){
		cout << "Menu: " << to_string(Menu) << "\n";
		Menu = 3;
		
	}

         if (key == 53 /* 5 key ASCII*/){
		     Menu = 1;

		glutDisplayFunc(GameDisplay);}




	if(key == 'p' || key == 'P'){
		
		if(Menu == 5){
			Menu = 1;
		}else{
			Menu = 5;
		}	
	
	}
	
	
	
	//Blue Car Controls
  	if (key == 'd' || key == 'D') {
		if(car2_y >= 280 || car2_y <= 350){
			x2_in += 80;
			cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_x) << endl;
		}


	}
	if (key == 'w' || key == 'W') {
		if(car2_x >= 350 || car2_x <= 410){
			y2_in += 80;
			cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		}

	}
	if (key == 'a' || key == 'A') {
		if(car2_y >= 280 || car2_y <= 350){
			x2_in -= 80;
			cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_x) << endl;
		}
	}
	if (key == 's' || key == 'S') {
		if(car2_x >= 350 || car2_x <= 410){
			y2_in -= 80;
			cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		}

	}



	glutPostRedisplay();
}

// Car move 1 pixel manually for testing
/*
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII/) {
		exit(1); // exit the program when escape key is pressed.
	}

	/*if (key == 'b' || key == 'B')
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}/

	if (key == 'd' || key == 'D') {
		x2_in += 1;
		cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		cout<<"Function value: " << to_string(getMapId(car2_x, car2_y)) << " ";

	}
	if (key == 'w' || key == 'W') {
		y2_in += 1;
		cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		cout<<"Function value: " << to_string(getMapId(car2_x, car2_y)) << " ";

	}
	if (key == 'a' || key == 'A') {
		x2_in -= 1;
		cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		cout<<"Function value: " << to_string(getMapId(car2_x, car2_y)) << " ";
	}
	if (key == 's' || key == 'S') {
		y2_in -= 1;
		cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
		cout<<"Function value: " << to_string(getMapId(car2_x, car2_y)) << " ";
	}
	glutPostRedisplay();
}
*/


/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button 
	{
	cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}



void moveBlueCar (void){
 int temp = getMapId(car2_x, car2_y);
 //cout << "X: " << to_string(car2_x)  << "& Y: " << to_string(car2_y) << endl;
 //cout<<"Function value: " << to_string(getMapId(car2_x, car2_y)) << " " << endl;
    
   if(temp != getMapId(car2_x, car2_y)){
	flag_x2 = 0;
   	flag_y2 = 0;
   }	

  if(getMapId(car2_x, car2_y) == 1){
 	if(car2_x <= 760 && flag_x2 == 0){
		x2_in += Level_Speed;
	}
	else if(car2_y <= 608 && flag_y2 == 0){
		y2_in += Level_Speed;
		if(car2_y == 608){
			flag_x2 = 1;
		}
	}
	else if(car2_x >= 30 && flag_x2 == 1){
		x2_in -= Level_Speed;
		if(car2_x == 30){
			flag_y2 = 1;
		}
	}
	else if(car2_y >= 32 && flag_y2 == 1){
		y2_in -= Level_Speed;
		if(car2_y == 32){
			flag_x2 = 0;
   			flag_y2 = 0;
		}
	}
   }


    if(getMapId(car2_x, car2_y) == 2){
 	if(car2_x <= 674 && flag_x2 == 0){
		x2_in += Level_Speed;
	}
	else if(car2_y <= 526 && flag_y2 == 0){
		y2_in += Level_Speed;
		if(car2_y == 526){
			flag_x2 = 1;
		}
	}
	else if(car2_x >= 116 && flag_x2 == 1){
		x2_in -= Level_Speed;
		if(car2_x == 116){
			flag_y2 = 1;
		}
	}
	else if(car2_y >= 116 && flag_y2 == 1){
		y2_in -= Level_Speed;
		if(car2_y == 116){
			flag_x2 = 0;
   			flag_y2 = 0;
		}
	}
   }


   if(getMapId(car2_x, car2_y) == 3){

 	if(car2_x <= 590 && flag_x2 == 0){
		x2_in += Level_Speed;
	}
	else if(car2_y <= 442 && flag_y2 == 0){
		y2_in += Level_Speed;
		if(car2_y == 442){
			flag_x2 = 1;
		}
	}
	else if(car2_x >= 190 && flag_x2 == 1){
		x2_in -= Level_Speed;
		if(car2_x == 190){
			flag_y2 = 1;
		}
	}
	else if(car2_y >= 196 && flag_y2 == 1){
		y2_in -= Level_Speed;
		if(car2_y == 196){
			flag_x2 = 0;
   			flag_y2 = 0;
                    }

         }  

    }


    if(getMapId(car2_x, car2_y) == 4){
 	if(car2_x <= 510 && flag_x2 == 0){
		x2_in += Level_Speed;
	}
	else if(car2_y <= 360 && flag_y2 == 0){
		y2_in += Level_Speed;
		if(car2_y == 360){
			flag_x2 = Level_Speed;
		}
	}
	else if(car2_x >= 271 && flag_x2 == 1){
		x2_in -= Level_Speed;
		if(car2_x == 271){
			flag_y2 = Level_Speed;
		}
	}
	else if(car2_y >= 276 && flag_y2 == 1){
		y2_in -= Level_Speed;
		if(car2_y == 276){
			flag_x2 = 0;
   			flag_y2 = 0;
                    		}

         }  
 
  }

}

////////////////////////////////////////////////////////////////////////////////////////////


void moveOrangeCar (void){
 int temp = getMapId(car1_x, car1_y);
 //cout << "X: " << to_string(car1_x)  << "& Y: " << to_string(car1_y) << endl;
 //cout<<"Function value: " << to_string(getMapId(car1_x, car1_y)) << " " << endl;
    
   if(temp != getMapId(car1_x, car1_y)){
	flag_x1 = 0;
	flag_y1 = 0;
   }	

  if(getMapId(car1_x, car1_y) == 1){
 	
	if(car1_x >= 30 && flag_x1 == 0){
		x1_in -= Level_Speed;
	}
	else if(car1_y <= 608 && flag_y1 == 0){
		y1_in += Level_Speed;
		if(car1_y == 608){
			flag_x1 = 1;
		}
	}
	else if(car1_x <= 760 && flag_x1 == 1){
		x1_in += Level_Speed;
		if(car1_x == 760){
			flag_y1 = 1;
		}
	}
	else if(car1_y >= 32 && flag_y1 == 1){
		y1_in -= Level_Speed;
		if(car1_y == 32){
			flag_x1 = 0;
			flag_y1 = 0;
		}
	}
	
   }

    if(getMapId(car1_x, car1_y) == 2){
    
        if(car1_x >= 110 && flag_x1 == 0){
		x1_in -= Level_Speed;
	}    
    
    
	else if(car1_y <= 526 && flag_y1 == 0){
		y1_in += Level_Speed;
		if(car1_y == 526){
			flag_x1 = 1;
		}
	}
	
	else if(car1_x <= 674 && flag_x1 == 1){
		x1_in += Level_Speed;
		 if(car1_x == 674){
			flag_y1 = 1;
		}
	}
	
	else if(car1_y >= 116 && flag_y1 == 1){
		y1_in -= Level_Speed;
		if(car1_y == 116){
			flag_x1 = 0;
			flag_y1 = 0;
		}
	}
   }


   if(getMapId(car1_x, car1_y) == 3){

        if(car1_x >= 190 && flag_x1 == 0){
		x1_in -= Level_Speed;
 	       }
        
	else if(car1_y <= 446 && flag_y1 == 0){
		y1_in += Level_Speed;
		if(car1_y == 446){
			flag_x1 = 1;
		}
	}
	else if(car1_x <= 588 && flag_x1 == 1){
		x1_in += Level_Speed;
	
		if(car1_x == 588){
			flag_y1 = 1;
		}
	}
	else if(car1_y >= 196 && flag_y1 == 1){
		y1_in -= Level_Speed;
		if(car1_y == 196){
			flag_x1 = 0;
			flag_y1 = 0;
              	}

         }  

    }



    if(getMapId(car1_x, car1_y) == 4){
 	
     if(car1_x >= 270 && flag_x1 == 0){
		x1_in -= Level_Speed;
              }
 
	else if(car1_y <= 360 && flag_y1 == 0){
		y1_in += Level_Speed;
		if(car1_y == 360){
			flag_x1 = Level_Speed;
		}
	}
	else if(car1_x <= 512 && flag_x1 == 1){
		x1_in += Level_Speed;
		if(car1_x == 512){
		    flag_y1 = Level_Speed;
		}
	}
	else if(car1_y >= 276 && flag_y1 == 1){
		y1_in -= Level_Speed;
		if(car1_y == 276){
			flag_x1 = 0;
			flag_y1 = 0;
                    		}

         }  
  }

}

void checkCarCollsion(void){
	//cout<<"inside checkCarCollsion." << "\n";
	//cout<<"Cax 1 X:" << to_string(car1_x) <<" Cax 1 Y:" << to_string(car1_y) << "\n";// <<"Cax 2 X:" << to_string(car2_x) <<"Cax 2 Y:" << to_string(car2_y) << "\n";
	if((car1_x == car2_x) && (car1_y == car2_y) && Menu == 1){
	cout<<"Cax 1 X:" << to_string(car1_x) <<" Cax 1 Y:" << to_string(car1_y) << "\n" <<"Cax 2 X:" << to_string(car2_x) <<"Cax 2 Y:" << to_string(car2_y) << "\n";
		//glutDisplayFunc(GameDisplay);

		x1_in = 0;
		y1_in = 0;
		x2_in = 0;
		y2_in = 0;
		//Menu = 0;
		OrangeCarX = 100;
		OrangeCarY = 32;
		BlueCarX = 650;
		BlueCarY = 32;
		life--;
	}
}

void movecar(void){
	if(Menu == 1){
		checkCarCollsion();
		moveBlueCar();
		moveOrangeCar();

	}
}


/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

    /*  if((car1_x == car2_x) && (car1_y == car2_y) ){
		//cout<<"Cax 1 X:" << to_string(car1_x) <<" Cax 1 Y:" << to_string(car1_y) << "\n" <<"Cax 2 X:" << to_string(car2_x) <<"Cax 2 Y:" << to_string(car2_y) << "\n";
          

   life--;       	
  }
          	


glutDisplayFunc(GameDisplay);*/
	if(Menu == 1){
		checkCarCollsion();
		moveBlueCar();
		moveOrangeCar();

	}

     
	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1, Timer, 0);
}



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 840, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	
	//glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...


	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000, Timer, 0);
	//glutKeyboardFunc(PrintableKeys);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	
	//glutIdleFunc(movecar);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
