#pragma once
#include "basic.h"

int line_style = 0; //选择线形
unsigned int pixel_mask[] = { 0xffff, 0xf0f00, 0xfff0, 0x011 };  //mask掩码 四个线形


void doubleside_expand(int x, int y, float k,int width) {  //双向扩张
	k = abs(k); //取斜率的绝对值
	int min_width, max_width;
	if (width % 2 == 0) {
		min_width = -width / 2;
		max_width = width / 2;
	}
	else {
		min_width = -width / 2 - 1;
		max_width = width / 2;
	}
	if (k <= 1) {
		glBegin(GL_POINTS);
		for (int i = min_width; i <= max_width; i++) {
			glVertex2i(x, y + i);
		}
		glEnd();
		glFlush();
	}
	else {
		glBegin(GL_POINTS);
		for (int i = min_width; i <= max_width; i++) {
			glVertex2i(x + i, y);
		}
		glEnd();
		glFlush();
	}
}

void brush(int x, int y, int width) {  //画刷   width 为在点上的单向扩展
	int min_width, max_width;
	if (width % 2 == 0) {
		min_width = -width / 2;
		max_width = width / 2;
	}
	else {
		min_width = -width / 2 - 1;
		max_width = width / 2;
	}
	glBegin(GL_POINTS);
	for (int i = min_width; i <= max_width; i++) {
		for (int j = min_width; j <= max_width; j++) {
			glVertex2i(x + i, y + j);
		}	
	}
	glEnd();
	glFlush();
}

void line_caps(int select, int x, int y, float k, int width) {  //select: 1(方帽);2(突方帽);3(圆帽);
	if (select == 1) {
		doubleside_expand(x, y, k, width);
	}
	else if (select == 2) {
		doubleside_expand(x, y, k, width);
		doubleside_expand(x - 1, y, k, width);
	}
	else if (select == 3) {

	}
}

void dda_line(int x0, int y0, int x1, int y1)
{
	float x, y, k;
	float dx = x1 - x0, dy = y1 - y0;
	int cx = dx > 0 ? 1 : -1;
	int cy = dy > 0 ? 1 : -1;
	float ux = dx > 0 ? 0.5 : -0.5;
	float uy = dy > 0 ? 0.5 : -0.5;
	k = dy*1.0 / dx;
	unsigned int bit_mask = pixel_mask[line_style]; //选择一种线形
	if (fabs(k) <= 1) {
		if (dx < 0) {
			k = -k;
		}
		y = y0;
		for (x = x0; x != x1; x += cx) {
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				glBegin(GL_POINTS); 
				glVertex2i((int)x, (int)(y + uy));
				glEnd();
				glFlush();
			}
			y = y + k;
		}
	}
	else {
		if (dy < 0) {
			k = -k;
		}
		x = x0;
		bit_mask = pixel_mask[line_style];
		for (y = y0; y != y1; y += cy) {
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				glBegin(GL_POINTS);
				glVertex2i((int)x, (int)(y + uy));
				glEnd();
				glFlush();
			}
			x = x + 1.0 / k;
		}
	}
}

void midpoint_line(int x0, int y0, int x1, int y1)
{
	int a = y0 - y1;
	int b = x1 - x0;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));
	int x = x0;
	int y = y0;
	int d, d1, d2;
	float k = (y1 - y0)*1.0 / (x1 - x0);
	unsigned int bit_mask = pixel_mask[line_style]; //选择一种线形
	if (abs(a) <= abs(b)) {  //斜率绝对值<=1
		d = 2 * a + b;
		d1 = a * 2;
		d2 = 2 * (a + b);
		while (x != x1) {
			if (d < 0) {
				y += cy;
				d += d2;
			}
			else {
				d += d1;
			}
			x += cx;
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				brush(x, y, 4);
				//doubleside_expand(x, y, k, 4);
			}
		}
	}
	else {  //斜率绝对值>1
		d = a + 2 * b;
		d1 = b * 2;
		d2 = 2 * (a + b);
		bit_mask = pixel_mask[line_style];
		while (y != y1) {
			if (d < 0) {
				d += d1;
			}
			else {
				x += cx;
				d += d2;
			}
			y += cy;
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				brush(x, y, 4);
				//doubleside_expand(x, y, k, 4);
			}
		}
		
	}
}

void bresenham_line(int x0,int y0,int x1,int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int cx = dx > 0 ? 1 : -1;
	int cy = dy > 0 ? 1 : -1;
	int dx2 = dx * 2;
	int dy2 = dy * 2;
	float k = dy*1.0 / dx;
	unsigned int bit_mask = pixel_mask[line_style]; //选择一种线形
	if (abs(dx) > abs(dy)) { //k<=1
		int e = -dx;
		int x = x0;
		int y = y0;
		for (x = x0; x < x1; x += cx) {
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				doubleside_expand(x, y, k, 2);
			}
			e = e + dy2;
			if (e > 0) {
				y += cy;
				e = e - dx2;
			}
		}
	}
	else { //k>1
		int e = -dy;
		int x = x0;
		int y = y0;
		bit_mask = pixel_mask[line_style];
		for (y = y0; y < y1; y += cy) {
			bit_mask >>= 1;   //右移一位
			if (!bit_mask) {  //空白
				bit_mask = pixel_mask[line_style];
			}
			if (bit_mask & 1) {  //实心
				doubleside_expand(x, y, k, 5);
			}
			e = e + dx2;
			if (e > 0) {
				x += cx;
				e = e - dy2;
			}
		}
	}
}


void display_line(void)
{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); //点的颜色
	int x0 = 0, y0 = 100, x1 = 200, y1 = 200, x2 = 200, y2 = 50; //k not exist
	//dda_line(x0, y0, x1, y1);
	midpoint_line(x0, y0, x1, y1);
	midpoint_line(x1, y1, x2, y2);
	//bresenham_line(x0, y0 - 100, x1, y1 - 100);
}
