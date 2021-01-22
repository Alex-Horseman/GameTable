#include "QPlayer.h"


QPlayer::QPlayer() {
	this->color = Qt::red;
	this->id = 0;
	this->name = "张三";
	this->mark_A = 0;
	this->mark_B = 0;
	this->mark_C = 0;
}



QPlayerWidget::QPlayerWidget(QPlayer* player,QWidget* parent):QWidget(parent) {
	const int the_height = 50;
	this->player = player;
	hbox = new QHBoxLayout();
	vbox = new QVBoxLayout();
	color_id = new QLabel(this);
	name = new QLabel(this);
	markA = new QLabel(this);
	markB = new QLabel(this);
	markC = new QLabel(this);
	hbox->addWidget(color_id);
	hbox->addWidget(name);
	hbox->addWidget(markA);
	hbox->addWidget(markB);
	hbox->addWidget(markC);
	vbox->addLayout(hbox);
	this->setLayout(vbox);
	update_player();
}

void QPlayerWidget::update_player() {
	QPalette pal = color_id->palette();
	pal.setColor(QPalette::Button, player->color);
	color_id->setPalette(pal);
	color_id->setAutoFillBackground(true);
	color_id->setText(QString::number(player->id));
	name->setText(player->name);
	markA->setText(QString::number(player->mark_A));
	markB->setText(QString::number(player->mark_B));
	markC->setText(QString::number(player->mark_C));
	update();
}


void QPlayerWidget::setting() {
	QPlayerSettingDialog* dlg = new QPlayerSettingDialog(player,this);
	if (dlg->exec() == QDialog::Accepted) {
		emit emit_update(*player);
	}
}

QPlayerSettingDialog::QPlayerSettingDialog( QPlayer* player, QWidget* parent):QDialog(parent) {
	layout = new QGridLayout;
	keys.append(new QLabel("ID", this));
	keys.append(new QLabel("颜色", this));
	keys.append(new QLabel("昵称", this));
	keys.append(new QLabel("分数-甲", this));
	keys.append(new QLabel("分数-乙", this));
	keys.append(new QLabel("分数-丙", this));
	int row = 0;
	for (QVector<QLabel*>::iterator pw = keys.begin(); pw != keys.end();pw++) {
		layout->addWidget(*pw, row++, 0);
	}
	values.append(new QLabel(QString::number(player->id), this));
	values.append(new QPushButton(this));
	QPalette pal = values[1]->palette();
	pal.setColor(QPalette::Button, player->color);
	values[1]->setPalette(pal);
	values[1]->setAutoFillBackground(true);
	values.append(new QLineEdit(player->name, this));
	values.append(new QSpinBox(this));
	values.append(new QSpinBox(this));
	values.append(new QSpinBox(this));
	((QSpinBox*)values[3])->setValue(player->mark_A);
	((QSpinBox*)values[4])->setValue(player->mark_B);
	((QSpinBox*)values[5])->setValue(player->mark_C);
	for (QVector<QWidget*>::iterator pw = values.begin(); pw != values.end(); pw++) {
		layout->addWidget(*pw, row++, 1);
	}
	this->setLayout(layout);
	QObject::connect(this, &QPlayerSettingDialog::update_player, this, &QPlayerSettingDialog::accepted);
}


void QPlayerSettingDialog::update_player() {
	player->color = values[1]->palette().color(QPalette::Button);
	player->name = ((QLineEdit*)values[2])->text();
	player->mark_A = ((QSpinBox*)values[3])->value();
	player->mark_B = ((QSpinBox*)values[4])->value();
	player->mark_C = ((QSpinBox*)values[5])->value();
}