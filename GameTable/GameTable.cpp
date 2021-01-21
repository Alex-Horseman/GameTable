#include "GameTable.h"

GameTable::GameTable(QWidget *parent)
	: QWidget(parent)
{
	table = new QGTable(this);
	layout = new QGridLayout();
	layout->addWidget(table, 0, 0, 1, 1);
	this->setLayout(layout);
}

void GameTable::init_game(QDir game_dir) {
	table->init_game(game_dir);
}