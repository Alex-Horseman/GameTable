#pragma once
#include <qwidget.h>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "Object.h"
#include <QPainter>
#include <QDir> 
#include <QDebug>

class ImageWithPath{
public:
	QString path;
	QImage image;
	ImageWithPath(QDir  game_dir, QString image_path) {
		this->path = image_path;
		this->image = QImage(game_dir.filePath(image_path));
	}
};

class QGTable :
	public QWidget
{
public:
	QDir game_dir;
	QVector<Deck *> decks;
	QVector<ImageWithPath *> image_list;
public:
	QGTable(QWidget *parent = Q_NULLPTR);
	~QGTable();
	void init_game(QDir  game_dir);
protected:
	void paintEvent(QPaintEvent * event);

private:
	void init_cardline(QStringList list);
	QImage read_image( QString image_path);
};

