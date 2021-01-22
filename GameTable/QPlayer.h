#pragma once
#include <qwidget.h>
#include <QString>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVector>
#include "Object.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
class QPlayer
{
public:
	int id;
	QColor color;
	QString name;
	int mark_A;
	int mark_B;
	int mark_C;
	QVector<QObject*> objects;
public:
	QPlayer();
};


class QPlayerWidget :
	public QWidget
{
	Q_OBJECT
public:
	QPlayer* player;

	QHBoxLayout* hbox;
	QVBoxLayout* vbox;
	QLabel* color_id;
	QLabel* name;
	QLabel* markA;
	QLabel* markB;
	QLabel* markC;
	//QPlayerDeckWidget* deck;

public:
	QPlayerWidget(QPlayer* player, QWidget* parent = Q_NULLPTR);
	void update_player();
	void setting();
signals:
	void emit_update(QPlayer player);
};

class QPlayerSettingDialog :public QDialog {
	Q_OBJECT
public:
	QPlayer* player;
private:
	QGridLayout * layout;
	QVector<QLabel*> keys;
	QVector<QWidget*> values;
public:
	explicit QPlayerSettingDialog( QPlayer * player, QWidget* parent = nullptr);
	void update_player();
};