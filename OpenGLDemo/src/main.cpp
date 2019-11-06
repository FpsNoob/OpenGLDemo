//#include "include\basic.h"
//
//
////int main(int argc, char *argv[])
////{
////	/*初始化*/
////	glutInit(&argc, argv);
////	/*窗口模式*/
////	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
////	/*窗口位置*/
////	glutInitWindowPosition(100, 100);
////	/*窗口大小*/
////	glutInitWindowSize(500, 500);
////	glutCreateWindow("Circle");
////	/*将窗口清除为当前颜色*/
////	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
////	/*指定设定投影参数*/
////	glMatrixMode(GL_PROJECTION);
////	/*设置投影参数*/
////	gluOrtho2D(0.0, 500, 0.0, 500);
////	glutDisplayFunc(&display_line);
////	glutMainLoop();
////}
//
//int main(int argc, char **argv)
//{
//	//初始化
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
//	glutInitWindowSize(600, 600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Cohen-Sutherland算法");
//	glClearColor(1, 1, 1, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
//
//	glutKeyboardFunc(myKeyBoard);   //键盘输入控制
//	glutDisplayFunc(display);
//
//	glutMainLoop();
//	return 0;
//
//}

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//insert Seat values(1,'02C','商务座','F','D236')
	string str = "";
	for (int i = 1; i < 2; i++) {   //车厢
		for (int j = 1; j < 17; j++) {  //座位行数
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu='A'+k;
				if (j < 10) {
					
					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', '商务座','F','D236')";
				str = "insert Seat values(" + to_string(i) + "', '商务座')";
				cout << str << endl;
			//}
		}
	}

	for (int i = 2; i < 4; i++) {   //车厢
		for (int j = 1; j < 17; j++) {  //座位行数
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu = 'A' + k;
				if (j < 10) {

					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', '一等座', 'D236')";
				str = "insert Seat values(" + to_string(i) + "', '一等座')";
				cout << str << endl;
			//}
		}
	}

	for (int i = 4; i < 15; i++) {   //车厢
		for (int j = 1; j < 17; j++) {  //座位行数
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu = 'A' + k;
				if (j < 10) {

					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', '二等座', 'D236')";
				str = "insert Seat values(" + to_string(i) + "', '二等座')";
				cout << str << endl;
			//}
		}
	}


}