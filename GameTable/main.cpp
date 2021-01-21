#include "GameTable.h"
#include <QtWidgets/QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameTable w;
	
	w.init_game(QDir(".\\games\\catandao"));
	w.show();
	return a.exec();
}
