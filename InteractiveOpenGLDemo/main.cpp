
#include <conio.h>
#include <iostream>
#include <string>
#include "ModelViewer.h"

using namespace std;

int main(int argc, char **argv)
{
	string filePath;

	if (argc == 2)
	{
		filePath = argv[1];
	}
	else
	{
        filePath = "cow.obj";
	}

	ModelViewer* mainModelViewer = ModelViewer::GetInstance();

	mainModelViewer->Show(argc, argv, filePath);


	getch();

	return 0;
}
