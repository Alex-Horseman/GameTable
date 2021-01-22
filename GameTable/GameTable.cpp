#include "GameTable.h"

GameTable::GameTable(QVector<QPlayer*> players, QWidget *parent)
	: QSplitter(Qt::Vertical,parent)
{
	const int handle_width = 1;
	this->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式
	this->setHandleWidth(handle_width);
	QSplitter * hsp = new QSplitter(Qt::Horizontal, this);
	hsp->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式
	hsp->setHandleWidth(handle_width);

	if (!players.isEmpty()) {
		my_player_widget = new QPlayerWidget(players[0], this);
	}
	QWidget* lw = new QWidget(hsp);
	QVBoxLayout * vb = new QVBoxLayout();
	if (players.size() > 1) {
		
		for (int i = 1; i < players.size(); i++) {
			QPlayerWidget* opw = new QPlayerWidget(players[i], lw);
			other_player_widgets.append(opw);
			vb->addWidget(opw);
		}
	}
	lw->setLayout(vb);
	table = new QGTable(hsp);

	this->setMinimumSize(800, 600);
	//setAttribute(Qt::WA_Hover, true);
}

void GameTable::init_game(QDir game_dir) {
	table->init_game(game_dir);
}