//#include "include\basic.h"
//
//
////int main(int argc, char *argv[])
////{
////	/*��ʼ��*/
////	glutInit(&argc, argv);
////	/*����ģʽ*/
////	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
////	/*����λ��*/
////	glutInitWindowPosition(100, 100);
////	/*���ڴ�С*/
////	glutInitWindowSize(500, 500);
////	glutCreateWindow("Circle");
////	/*���������Ϊ��ǰ��ɫ*/
////	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
////	/*ָ���趨ͶӰ����*/
////	glMatrixMode(GL_PROJECTION);
////	/*����ͶӰ����*/
////	gluOrtho2D(0.0, 500, 0.0, 500);
////	glutDisplayFunc(&display_line);
////	glutMainLoop();
////}
//
//int main(int argc, char **argv)
//{
//	//��ʼ��
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
//	glutInitWindowSize(600, 600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Cohen-Sutherland�㷨");
//	glClearColor(1, 1, 1, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
//
//	glutKeyboardFunc(myKeyBoard);   //�����������
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
	//insert Seat values(1,'02C','������','F','D236')
	string str = "";
	for (int i = 1; i < 2; i++) {   //����
		for (int j = 1; j < 17; j++) {  //��λ����
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu='A'+k;
				if (j < 10) {
					
					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', '������','F','D236')";
				str = "insert Seat values(" + to_string(i) + "', '������')";
				cout << str << endl;
			//}
		}
	}

	for (int i = 2; i < 4; i++) {   //����
		for (int j = 1; j < 17; j++) {  //��λ����
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu = 'A' + k;
				if (j < 10) {

					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', 'һ����', 'D236')";
				str = "insert Seat values(" + to_string(i) + "', 'һ����')";
				cout << str << endl;
			//}
		}
	}

	for (int i = 4; i < 15; i++) {   //����
		for (int j = 1; j < 17; j++) {  //��λ����
			//for (int k = 0; k < 5; k++) {
				string seat_no;
				char zifu = 'A' + k;
				if (j < 10) {

					seat_no = '0' + to_string(j) + zifu;
				}
				else {
					seat_no = to_string(j) + zifu;
				}
				str = "insert Seat values(" + to_string(i) + ",'" + seat_no + "', '������', 'D236')";
				str = "insert Seat values(" + to_string(i) + "', '������')";
				cout << str << endl;
			//}
		}
	}


}