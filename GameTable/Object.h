#pragma once
# include <QSize>
# include <QPointF>
# include <QImage>
#include <QVector>




class Object
{
public:
	QSize size;
	QImage front_image;
	QImage back_image;
public:
	Object(QSize size, QImage front_image, QImage back_image);
	~Object();
};

class Deck {
public:
	bool backside;
	QPointF position;
	QVector<Object *> objects;
public:
	Deck(bool backside = true, QPointF position = QPointF(0, 0));
	void append(Object * obj, int count);
};