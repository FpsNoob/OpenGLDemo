#pragma once

#include "basic.h"
#include "SqStack.h"

template<typename T> struct Seed {  //记录种子点
	T x;
	T y;
};

bool same_color(int x, int y, COLORREF color) {
	//color 为对比颜色
	//获得当前位置的像素颜色
	int R, G, B;
	GLubyte  iPixel;
	glReadPixels(x, y, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &iPixel);
	R = int(iPixel);
	glReadPixels(x, y, 1, 1, GL_GREEN, GL_UNSIGNED_BYTE, &iPixel);
	G = int(iPixel);
	glReadPixels(x, y, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, &iPixel);
	B = int(iPixel);

	if (R == GetRValue(color) && G == GetGValue(color) && B == GetBValue(color)) {
		return true;
	}
	else {
		return false;
	}
}

void edgemark_fill(int *points, COLORREF background,int n) {
	int maxX, minX, maxY, minY;
	maxX = minX = points[0];
	maxY = minY = points[1];
	for (int i = 0; i < n * 2; i += 2) {
		if (maxX < points[i]) {
			maxX = points[i];
		}
		if (minX > points[i]) {
			minX = points[i];
		}
	}
	for (int i = 1; i < n * 2; i += 2) {
		if (maxY < points[i]) {
			maxY = points[i];
		}
		if (minY > points[i]) {
			minY = points[i];
		}
	}
	for (int i = minY +1; i < maxY; i++) {
		bool inside = false;
		for (int j = minX; j <= maxX; j++) {
			if(same_color(j,i,background)){
				inside = !(inside);
			}
			if (inside) {
				glColor3f(0.0, 0.0, 1.0); //blue
				glBegin(GL_POINTS);
				glVertex2i(j, i);
				glEnd();
				glFlush();
			}
		}

	}
}

void ScanLineFill4(int x, int y, COLORREF oldcolor) {
	int xl, xr, i;    //xl与xr为填充段的[xl, xr]
	bool spanNeedFill;

	Seed<int> pt;              //建立种子的结构
	SqStack<Seed<int>> *stack;  //建立栈
	InitStack(stack);       //初始化栈
	pt.x = x;
	pt.y = y;
	Push(stack, pt);       //将前面生成的区段压入堆栈
	while (!StackEmpty(stack)) {
		Sleep(10);
		Pop(stack, pt); //栈顶出栈
		y = pt.y;
		x = pt.x;
		while (same_color(x, y, oldcolor)) {  //向右填充
			glColor3f(0.0, 0.0, 1.0); //blue
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
			x++;
		}
		xr = x - 1;
		x = pt.x - 1;
		while (same_color(x, y, oldcolor)) {  //向左填充
			glColor3f(0.0, 0.0, 1.0); //blue
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush();
			x--;
		}
		xl = x + 1;

		//处理上一条扫描线
		x = xl;
		y = y + 1;
		while (x <= xr) {
			spanNeedFill = false;
			while (same_color(x, y, oldcolor)) {
				spanNeedFill = true;
				x++;
			}
			if (spanNeedFill) {  //入栈最右像素作为种子
				pt.x = x - 1;
				pt.y = y;
				Push(stack, pt);
				spanNeedFill = false;
			}
			while (!(same_color(x, y, oldcolor)) && x <= xr) {
				x++;
			}
		}
		//处理下面一条扫描线，代码与处理上面一条扫描线类似
		x = xl;
		y = y - 2;
		while (x <= xr) {
			spanNeedFill = false;
			while (same_color(x, y, oldcolor)) {
				spanNeedFill = true;
				x++;
			}
			if (spanNeedFill) {
				pt.x = x - 1;
				pt. y = y;
				Push(stack, pt);
				spanNeedFill = false;
			}
			while (!(same_color(x, y, oldcolor)) && x <= xr) {
				x++;
			}
		}
	}
}


void display_fill(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); //黑色
	midpoint_line(50, 50, 200, 100);
	midpoint_line(200, 100, 200, 250);
	midpoint_line(200, 250, 100, 250);
	midpoint_line(100, 250, 50, 80);
	midpoint_line(50, 80, 50, 50);


	/*边标志扫描线填充算法*/
	//int points[12] = { 50,50,200,100,200,250,100,250,50,80,50,50 };
	//COLORREF background = RGB(0, 0, 0);  //黑色
	//int n = 6; //顶点数
	//edgemark_fill(points, background, n);

	/*扫描线种子填充算法*/
	COLORREF oldcolor = RGB(255, 255, 255);//白色
	int x = 100, y = 100;
	ScanLineFill4(x, y, oldcolor);
	
}