#include "GameTable.h"
#include <QtWidgets/QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QVector<QPlayer*> players;
	players.append(new QPlayer());
	players.append(new QPlayer());
	players.append(new QPlayer());
	GameTable w(players,nullptr);
	
	w.init_game(QDir(".\\games\\catandao"));
	w.showMaximized();
	return a.exec();
}
