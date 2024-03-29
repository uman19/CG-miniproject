/******************STOPWATCH******************/

/***header files***/

#include <stdio.h>
#include <math.h>
#include <GL/glut.h> //
#include <windows.h>

/***defining constants***/

#define PI 3.14159 //PI=180°
#define MINUTE_HAND_LENGTH 55.0 //constant length of minute hand
#define SECOND_HAND_LENGTH 65.0 //constant length of minute hand
#define CLOCK_RADIUS 70.0 //constant radius of stopwatch

/***point coordinates***/

typedef struct Point {
    double x , y; //coordinate values of a point
}point; //object name of structure

double secondAngle = 0 , minuteAngle = 0 ; //initializing angles of both minute and second hand to 0, i.e., both hands are at 00:00

float bgr=1.0; //initializing background color value
float bgg=1.0; //initializing background color value
float bgb=1.0; //initializing background color value

/***applying background color, initializing display-viewing area***/

void init(void) {
	glClearColor(bgr,bgg,bgb,1.0); //clears buffer values and fills background color with 'bg' value
	gluOrtho2D(-100 , 100 , -100 , 100); //sets up 2D orthographic viewing region
    glMatrixMode(GL_PROJECTION); //applies subsequent matrix operation to the projection matrix stack
    glLoadIdentity(); //replace the current matrix with identity matrix
}

/***function to draw points***/

void drawPoint(point p) {
	glBegin(GL_POINTS);
		glVertex2d(p.x , p.y); //draws a point at (p.x,p.y) coordinates
	glEnd();
}

/***function to draw lines***/

void drawLine(double x , double y , double angle) {
	glVertex2f(x , x); //draw starting point of line with coordinates (x1,y1)
	glVertex2f(y*cos(angle) , y*sin(angle) ); //draw ending point of line with coordinates (x2,y2)
}

/***function to draw markings on the stopwatch to read time***/

void drawMarks(void) {
	point sp , ep , p; //defining variables for start point, end point of a imaginary line with length equals to radius of clock, and variable for marking stopwatch reading marks on clock
	int count = 0;
	double i ;
	sp.x = 0 , sp.y = 0; //start point of imaginary line is center of clock
	ep.x = 0 , ep.y = CLOCK_RADIUS; //end point of imaginary line is on circumference of clock
	glPointSize(10.0); //point size for center of clock
	drawPoint(sp); //draw point at center of clock
	//loop for 60 times
	for(i=0 ; i<=2*PI ; i+=PI/30.0) {
		//if line has to be drawn to top of center point, i.e., at position '12' of clock
		if(i==PI/2.0) {
			p.x = CLOCK_RADIUS; //x coordinate of point
		}
		//if line has to be drawn to bottom of center point, i.e., at position '6' of clock
		else if(i==3*PI/2.0) {
			p.x = -CLOCK_RADIUS; //x coordinate of point
		}
		//if line has to be drawn elsewhere on circumference of clock
		else {
			p.x = ep.y*sin(i); //x coordinate of point
		}
		p.y = ep.y*cos(i); //y coordinate of point
		//dividing points to be drawn into 12 - 5 point parts 1st point is drawn with bigger point size
		if(count%5==0) {
			glPointSize(5.0); //1st point in every part is drawn with bigger point size
			drawPoint(p);

		}
		else {
			glPointSize(3.0); //other 4 points of part is drawn with smaller point size
			drawPoint(p);
		}
		count++; //counting the point to calculate parts
	}
}

/***print name***/

void name(){
    const char *s="STOPWATCH";
    int i=strlen(s);//getting length of string
    glColor3f(0.0 , 0.0 , 1.0);//color of string
	glRasterPos2f(-20 , 90);//position of beginning of string
	for(int j=0 ; j<i ; ++j) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , s[j]);//print individual character of string onto the screen
	}
	const char *z="0";
	const char *f="15";
	const char *t="30";
	const char *ff="45";
	int zi=strlen(z);
	glRasterPos2f(-2 , 76);//position of beginning of string
	for(int j=0 ; j<zi ; ++j) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , z[j]);//print individual character of string onto the screen
	}
	int fi=strlen(f);
	glRasterPos2f(76 , -2);//position of beginning of string
	for(int j=0 ; j<fi ; ++j) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , f[j]);//print individual character of string onto the screen
	}
	int ti=strlen(t);
	glRasterPos2f(-2 , -78);//position of beginning of string
	for(int j=0 ; j<ti ; ++j) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , t[j]);//print individual character of string onto the screen
	}
	int ffi=strlen(ff);
	glRasterPos2f(-78 , -2);//position of beginning of string
	for(int j=0 ; j<ffi ; ++j) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , ff[j]);//print individual character of string onto the screen
	}
}


/***main display function, which display position of all hands and marks on stopwatch***/

void drawClock(void) {

	glClear(GL_COLOR_BUFFER_BIT); //clears the buffer currently enabled for writing
	glColor3f(0.8, 0.1 , 0.3); //color is give to draw marks
	drawMarks();

    name();

	glLineWidth(3.0); //width of minute hand
	glColor3f(0.8f, 0.4f, 0.9f); //color for minute hand
	glBegin(GL_LINES);
		drawLine(0.0 , MINUTE_HAND_LENGTH , -minuteAngle+PI/2); //drawing minute hand
	glEnd();

	glLineWidth(1.0); //width of second hand
	glColor3f(1.0f, 0.0f, 0.0f); //color for second hand
	glBegin(GL_LINES);
	    drawLine(0.0 , SECOND_HAND_LENGTH , -secondAngle+PI/2); //drawing second hand
	glEnd();
	glFlush(); //force execution of gl commands in a finite time
	glutSwapBuffers(); //promotes the content of the back buffer of the layer in use of the current window to become the contents of front buffer
}

/***function to reshape objects when screen aspect ratio is changed***/

void reshape(int w , int h) {
	double aspectRatio;
	//to avoid division by 0
	if(h==0) {
		h=1	;
	}
	glViewport(0 , 0 , (GLfloat)w , (GLfloat)h ); //affine transformation of x and y from normalized device co ordinates to window co ordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (double)w/(double)h; //width/height || no.of pixel columns /no.of pixel rows
	//portrait view
	if (w <= h)
    glOrtho (-100 , 100 , -100 / aspectRatio , 100 / aspectRatio , 1.0, -1.0); //parallel projection in portrait
    //landscape view
    else
    glOrtho (-100 * aspectRatio , 100 * aspectRatio, -100, 100 , 1.0, -1.0); //parallel projection in landscape

  glMatrixMode(GL_MODELVIEW); //applies subsequent matrix operation to the modelview matrix stack
  glLoadIdentity();
}

int cflag=0; //initializing a flag to change background color

/***function to change background color***/

void changecolor(){
    if(cflag==0){
        bgr=1.0;
        bgg=1.0;
        bgb=1.0;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=1;
    }
    else if(cflag==1){
        bgr=0.0;
        bgg=0.0;
        bgb=0.0;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=2;
    }
    else if(cflag==2){
        bgr=0.8;
        bgg=1.0;
        bgb=1.0;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=3;
    }
    else if(cflag==3){
        bgr=0.9;
        bgg=1.0;
        bgb=0.9;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=4;
    }
    else if(cflag==4){
        bgr=0.3;
        bgg=1.0;
        bgb=0.3;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=5;
    }
    else if(cflag==5){
        bgr=1.0;
        bgg=1.0;
        bgb=0.8;
        glClearColor(bgr,bgg,bgb,1.0); //set background
        cflag=0;
    }
}


int sflag=0; //initializing a flag to change state of stopwatch

/***function to redraw position of hands***/

void redraw(int value) {
    //if stopwatch needs to be started
    if(sflag==1){
        secondAngle += (double)6.0/3600.0; //angle of rotation of second hand
        minuteAngle += (double)secondAngle/115200.0; //angle of rotation of second hand
        if(secondAngle>=360.0)secondAngle-=360;
        if(minuteAngle>=360.0)minuteAngle-=360;
	glutPostRedisplay(); //marks the current window as needing to be redisplayed
	glutTimerFunc(16 , redraw , 1); //callback redraw function after 16millisecond
    }
    //if stopwatch needs to be stopped/reset
    else if(sflag==0){
        secondAngle+=0;
        minuteAngle+=0;
        drawClock();
    }
}

/***function to start or stop the stopwatch***/

void startstop(){
    if(sflag==0){
        sflag=1;
        redraw(1);
    }
    else{
        sflag=0;
        redraw(0);
    }
}

/***function to reset stopwatch***/

void reset(){
    secondAngle=0;
    minuteAngle=0;
    sflag=0;
    redraw(1);
}

/***function for mouse interaction***/

void mouse(int btn, int state, int x, int y) {
    //on clicking right mouse button, change background
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        changecolor();
}

/***function for keyboard interaction***/

void keys(unsigned char key, int x, int y){
    //s key is used to start and stop the stopwatch
    if(key=='s'){
        startstop();
    }
    //r key is used to reset the stopwatch
    if(key=='r'){
        reset();
    }
    //q key is used to quit
    if(key=='q')
        exit(0);
}

/***function to display interaction menu***/

void menu(int option){
    if(option==1)
        changecolor();
    if(option==2)
        startstop();
    if(option==3)
        reset();
    if(option==4)
        exit(0);
}

/***main driver function***/

int main(int argc,char **argv){
    glutInit(&argc,argv); //initialize glut library
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); //initialize display mode with double buffer window and rgb colors
    glutInitWindowSize(800,800); //window size in pixels
    glutInitWindowPosition(0,0); //position of window at top-left
    glutCreateWindow("stopwatch"); //name of window
    glutDisplayFunc(drawClock); //callback to display function-drawClock
    glutReshapeFunc(reshape); //callback to reshape function-reshape
    glutCreateMenu(menu); //create a menu of options
    glutAddMenuEntry("change color - right click",1);
    glutAddMenuEntry("start/stop - s",2);
    glutAddMenuEntry("reset - r",3);
    glutAddMenuEntry("quit - q",4);
    glutAttachMenu(GLUT_LEFT_BUTTON); //attach menu to mouse left button
    glutMouseFunc(mouse); //callback to mouse function-mouse
    glutKeyboardFunc(keys); //callback to keyboard function-keys
    init();
    glutMainLoop(); //glut event processing loop
}

/******************STOPWATCH******************/
