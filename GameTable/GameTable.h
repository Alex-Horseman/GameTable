#pragma once

#include <QWidget>
#include <QGridLayout>
#include "QGTable.h"

class GameTable : public QWidget
{
	Q_OBJECT
public:
	QGridLayout * layout;
	QGTable * table;
public:
	GameTable(QWidget *parent = Q_NULLPTR);
	void init_game(QDir game_dir);

};
