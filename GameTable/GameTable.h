#pragma once

#include <QWidget>
#include <QSplitter>
#include <QGridLayout>
#include "QGTable.h"
#include "QPlayer.h"

class GameTable : public QSplitter
{
	Q_OBJECT
public:
	QGridLayout * layout;
	QGTable * table;
	QPlayerWidget* my_player_widget;
	QVector<QPlayerWidget* > other_player_widgets;
public:
	GameTable(QVector<QPlayer*> players, QWidget* parent = Q_NULLPTR);
	void init_game(QDir game_dir);

};
