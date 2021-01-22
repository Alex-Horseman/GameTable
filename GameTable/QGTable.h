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
#include <QMouseEvent>
#include <QWheelEvent>
#define _USE_MATH_DEFINES
#include <math.h>


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
	Q_OBJECT
public:
	QDir game_dir;
	QVector<QPointF> table_vertex;
	QColor table_color;
	QVector<Deck *> decks;
	QVector<ImageWithPath *> image_list;

	float cam_scale;
	QPointF cam_center;
	QVector<QColor> player_colors;
	int my_player_id;
private:
	bool mouse_left_down;
	bool mouse_right_down;
	QPointF mouse_start_point;
	QPointF mouse_end_point;
	//QVector<Deck*>::iterator chosen_deck_pointer;
	int my_deck_id_over; // 本机玩家鼠标悬浮
	Deck* my_deck_holding;
public:
	QGTable(QWidget *parent = Q_NULLPTR);
	~QGTable();
	void init_game(QDir  game_dir);
	void recv_change_deck_over(int player_id, int deck_id, int deck_id_leave);


protected:
	void paintEvent(QPaintEvent * event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);

private:
	void init_cardline(QStringList list);
	void init_table(QStringList list);
	void init_deck(QStringList list);
	QImage read_image( QString image_path);
	QPointF cam_transform(QPointF world_point);
	QVector<QPointF> cam_transform(QVector<QPointF> world_points);
	void check_over(QPointF mouse_pos);
	Deck* find_deck_byid(int id, bool to_toplayer = false);
signals:
	void emit_over_changed(int player_id, int deck_id, int deck_id_leave);
	void emit_drag_changed(int player_id, int deck_id, bool holding, QPointF position = QPointF());
};

