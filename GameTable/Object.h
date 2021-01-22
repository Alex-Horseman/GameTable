#pragma once
# include <QSize>
# include <QPointF>
# include <QImage>
#include <QVector>




class Object
{
public:
	static int OBJECT_ID_ITERATOR;
	int id;
	QSize size;
	QImage front_image;
	QImage back_image;
	bool visible; // 在手牌中时，其他玩家是否可见
public:
	Object(QSize size, QImage front_image, QImage back_image);
	~Object();
	Object* copy_with_new_id();
};



class Deck {
public:
	static int DECK_ID_ITERATOR;
	int id;
	int chosen_id; // 被玩家选中 唯一
	QVector<int> over_id; //玩家鼠标在上面没按下
	bool backside;
	QPointF position;
	QVector<Object *> objects;
public:
	Deck(bool backside = true, QPointF position = QPointF(0, 0));
	void append(Object * obj, int count);
};