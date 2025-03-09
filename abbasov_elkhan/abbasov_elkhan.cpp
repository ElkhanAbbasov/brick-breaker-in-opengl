/**********************************
 CTIS164 - Template Source Program
-----------------------------------
NAME SURNAME :
STUDENT ID :
SECTION :
HOMEWORK :
-----------------------------------
PROBLEMS :
-----------------------------------
ADDITIONAL FEATURES :
**********************************/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         0 // 0:Disable timer, 1:Enable timer
#define D2R 0.017453292
#define PI 3.141592654
#define ROWS 3
#define COLS 7



// Global Variables for Template File
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // Current Window width and height

// To draw a filled circle, centered at (x,y) with radius r
void circle(int x, int y, int r) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 3)
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	glEnd();
}

// To draw an empty circle, centered at (x,y) with radius r
void circle_wire(int x, int y, int r) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i += 3)
		glVertex2f(x + r * cos(i * D2R), y + r * sin(i * D2R));
	glEnd();
}

void drawText(const char* text, float x, float y, void* font) {
	glRasterPos2f(x, y);
	int len = strlen(text);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, text[i]);
	}
}

void print(int x, int y, const char* string, void* font) {
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]);
}

// Display text with variables
void vprint(int x, int y, void* font, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}

void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
}

void drawBrick(int x, int y) {
	// Draw filled blue brick
	glColor3f(0, 0, 1); // Blue color
	glBegin(GL_QUADS);
	glVertex2f(x, y);         // Bottom-left
	glVertex2f(x + 100, y);   // Bottom-right
	glVertex2f(x + 100, y + 50); // Top-right
	glVertex2f(x, y + 50);    // Top-left
	glEnd();

	// Draw black outline
	glColor3f(0, 0, 0); // Black color
	glLineWidth(3); // Thicker line for visibility
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);         // Bottom-left
	glVertex2f(x + 100, y);   // Bottom-right
	glVertex2f(x + 100, y + 50); // Top-right
	glVertex2f(x, y + 50);    // Top-left
	glEnd();
}

void drawBricks() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (bricks[i][j].isActive) { // Only draw active bricks
				drawBrick(bricks[i][j].x, bricks[i][j].y);
			}
		}
	}
}


struct Brick {
	int x, y;  // Position
	bool isActive; // True if the brick is still in the game
};

void InitBricks() {
	int startX = -350;
	int startY = 200;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			bricks[i][j].x = startX + j * 100;
			bricks[i][j].y = startY - i * 50;
			bricks[i][j].isActive = true; // All bricks start as active
		}
	}
}


// To display onto window using OpenGL commands
void display() {
	printf("Event: DISPLAY called.\n");

	// Set background color to dark gray (64, 64, 64)
	glClearColor(64.0 / 255, 64.0 / 255, 64.0 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw darker grid lines (32,32,32)
	glColor3ub(32, 32, 32);
	glLineWidth(1);

	glBegin(GL_LINES);

	// Draw vertical lines
	for (int x = -400; x <= 400; x += 50) {
		glVertex2f(x, -300);
		glVertex2f(x, 300);
	}

	// Draw horizontal lines
	for (int y = -300; y <= 300; y += 50) {
		glVertex2f(-400, y);
		glVertex2f(400, y);
	}

	glEnd();

	// Car
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-75, -130); // Bottom-left
	glVertex2f(75, -130);  // Bottom-right
	glVertex2f(75, -180);  // Top-right
	glVertex2f(-75, -180); // Top-left
	glEnd();

	
	// Draw blue bricks in a row
	int startX = -350;
	int startY = 50;

	for (int i = 0; i < 7; i++) {
		drawBrick(startX + (i * 100), startY);
	}

	glutSwapBuffers();
}


// Key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y) {
	// Exit when ESC is pressed
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
	// Exit when ESC is pressed
	if (key == 27)
		exit(0);

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	case GLUT_KEY_LEFT:
		left = true;
		break;
	case GLUT_KEY_RIGHT:
		right = true;
		break;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case GLUT_KEY_LEFT:
		left = false;
		break;
	case GLUT_KEY_RIGHT:
		right = false;
		break;
	}
	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// When a click occurs in the window, It provides which button
// Buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// States  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
void onResize(int w, int h) {
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // Refresh window.

	printf("Windows size changed\n to (%d,%d)", w, h);
}

void onMoveDown(int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your code here

	// To refresh the window it calls display() function
	glutPostRedisplay();
}
#endif

void Init() {
	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2,
		((glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2) - 50
	);
	glutCreateWindow("Elkhan Aabbasov CTIS164 HW1");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// Keyboard Events
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	// Mouse Events
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// Timer Event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();
	glutMainLoop();
	return 0;
}