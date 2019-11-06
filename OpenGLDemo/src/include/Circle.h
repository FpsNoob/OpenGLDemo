#pragma once

#include "basic.h"

void circle_points(int x, int y, int cx, int cy) {
	glBegin(GL_POINTS);
	glVertex2i(x + cx, y + cy); glVertex2i(y + cx, x + cy);
	glVertex2i(-x + cx, y + cy); glVertex2i(y + cx, -x + cy);
	glVertex2i(x + cx, -y + cy); glVertex2i(-y + cx, x + cy);
	glVertex2i(-x + cx, -y + cy); glVertex2i(-y + cx, -x + cy);
	glEnd();
	glFlush();
}

void extraction_circle(int cx, int cy, int r) {
	int x, y;
	x = 0;
	y = r;
	circle_points(x, y, cx, cy);
	while (x <= y) {
		x++;
		y = sqrt(r*r-x*x);
		circle_points(x, y, cx, cy);
	}
}

void midpoint_circle(int cx, int cy, int r) {  //圆形非原点，对坐标进行平移
	int x, y;
	float d;
	x = 0;
	y = r;
	d = 1.25 - r;
	circle_points(x, y, cx, cy);
	while (x <= y) {
		if (d < 0) {
			d = d + 2 * x + 3;
		}
		else {
			d = d + 2 * (x - y) + 5;
			y--;
		}
		x++;
		circle_points(x, y, cx, cy);
	}
}

void bresenham_circle(int cx, int cy, int r) {
	int x, y;
	int d;
	x = 0;
	y = r;
	d = 3 - 2 * r;
	circle_points(x, y, cx, cy);
	while (x <= y) {
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		circle_points(x, y, cx, cy);
	}
}



void display_circle(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); //点的颜色
	glPointSize(5);
	int cx = 150, cy = 250, r = 100;
	//extraction_circle(cx, cy, r);
	//midpoint_circle(cx, cy, r);
	bresenham_circle(cx, cy, r);
}



