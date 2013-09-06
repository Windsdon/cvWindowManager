/*
 * testing.cpp
 *
 *  Created on: 05/09/2013
 *      Author: windsdon
 */

#include "Window.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Mat teste1 = Mat::zeros(500, 500, CV_8UC1);
	Mat teste2 = Mat::zeros(800, 800, CV_8UC1);
	Mat teste3 = Mat::zeros(500, 500, CV_8UC1);
	Mat teste4 = Mat::zeros(200, 200, CV_8UC1);

	Window win1("teste1");
	Window win2("teste2");
	Window win3("teste3");
	Window win4("teste4");

	win1.display(teste1);
	win2.display(teste2);
	win3.display(teste3);
	win4.display(teste3);

	waitKey(3000);

	win1.display(teste2);

	waitKey(2000);

	return 0;
}
