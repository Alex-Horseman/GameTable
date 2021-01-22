#include "QGTable.h"



QGTable::QGTable(QWidget *parent)
	: QWidget(parent)
{
	cam_scale = 1;
	cam_center = QPointF(0, 0);
	mouse_right_down = false;
	mouse_left_down = false;
	//chosen_deck_pointer = NULL;
	my_player_id = 0;
	player_colors.append(Qt::red);
	my_deck_id_over = -1;
	my_deck_holding = nullptr;
	//setAttribute(Qt::WA_Hover, true);
	setMouseTracking(true);

	QObject::connect(this, &QGTable::emit_over_changed, this, &QGTable::recv_change_deck_over);
}


QGTable::~QGTable()
{

}

void QGTable::paintEvent(QPaintEvent * event)
{
	const int max_deck_shadows = 5;
	const float shadow_bias = 0.02;
	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(table_color);
	painter.drawPolygon(cam_transform(table_vertex));
	QImage obj_image;
	QSizeF image_size;
	QRectF image_rect;
	for (QVector<Deck *>::iterator pdeck = decks.begin(); pdeck != decks.end(); pdeck++){
		if (!(*pdeck)->objects.isEmpty()) {
			int shadow_begin = max_deck_shadows;
			if (shadow_begin >= (*pdeck)->objects.size()) {
				shadow_begin = (*pdeck)->objects.size()-1;
			}
			for (int i = shadow_begin; i > 0; i--) {
				image_size = (*pdeck)->objects[i]->size * cam_scale;
				obj_image = (*pdeck)->objects[i]->back_image;
				QPointF bias = shadow_bias * QPointF((*pdeck)->objects[i]->size.width(), (*pdeck)->objects[i]->size.height());
				image_rect = QRectF(cam_transform((*pdeck)->position+bias*i), image_size);
				painter.drawImage(image_rect, obj_image);
			}
			image_size = (*pdeck)->objects[0]->size * cam_scale;
			if ((*pdeck)->backside) {
				obj_image = (*pdeck)->objects[0]->back_image;
			}
			else {
				obj_image = (*pdeck)->objects[0]->front_image;
			}
			image_rect = QRectF(cam_transform((*pdeck)->position), image_size);
			painter.drawImage(image_rect, obj_image);
			if (!(*pdeck)->over_id.isEmpty()) {
				painter.setPen(QPen(player_colors[(*pdeck)->over_id.last()], 5, Qt::SolidLine, Qt::RoundCap));
				painter.setBrush(Qt::transparent);
				painter.drawRect(image_rect);
			}
			if ((*pdeck)->chosen_id >= 0) {
				painter.setPen(Qt::transparent);
				QColor c = player_colors[(*pdeck)->chosen_id];
				c.setAlpha(100);
				painter.setBrush(c);
				painter.drawRect(image_rect);
			}
		}
	}
}

void QGTable::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton)
	{
		mouse_right_down = true;
		mouse_start_point = event->pos();
	}
	else if (event->button() == Qt::LeftButton) {
		mouse_left_down = true;
		mouse_start_point = event->pos();
		Deck* target_deck = find_deck_byid(my_deck_id_over,true);
		if (target_deck != nullptr) {
			if (target_deck->chosen_id < 0) {
				my_deck_holding = target_deck;
				my_deck_holding->chosen_id = my_player_id;
				emit emit_drag_changed(my_player_id, my_deck_id_over, true, target_deck->position);
			}
		}
	}
}
void QGTable::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton)
	{
		mouse_right_down = false;
	}
	else if (event->button() == Qt::LeftButton) {
		mouse_left_down = false;
		if (my_deck_holding != nullptr) {
			emit emit_drag_changed(my_player_id, my_deck_id_over, false, my_deck_holding->position);
			my_deck_holding->chosen_id = -1;
			my_deck_holding = nullptr;
			update();
		}
	}
}
void QGTable::mouseMoveEvent(QMouseEvent* event) {
	if (mouse_right_down) {
		cam_center += event->pos() - mouse_start_point;
		mouse_start_point = event->pos();
		update();
	}
	else if (mouse_left_down) {
		if (my_deck_holding != nullptr) {
			my_deck_holding->position += (event->pos() - mouse_start_point)/cam_scale;
			mouse_start_point = event->pos();
			emit emit_drag_changed(my_player_id, my_deck_id_over, true, my_deck_holding->position);
		}
		update();
	}
	check_over(event->pos());
}
void QGTable::wheelEvent(QWheelEvent* event) {
	int s = event->delta() / 120;
	const float scale = 1.2;
	cam_scale *= pow(scale,s);
	update();
}

void QGTable::init_game(QDir  game_dir) {
	this->game_dir = game_dir;
	QString txt_file = game_dir.filePath(game_dir.dirName() + ".txt");
	QFile file(txt_file);
	qDebug() << txt_file;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << txt_file << "not found";
		return;
	}
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList list = line.split(" ");
		if (list[0] == "DECK") {
			if (list.size() == 4) {
				init_deck(list);
			}
		}
		else if (list[0] == "TABLE") {
			if (list.size() == 7) {
				init_table(list);
			}
		}
		else if (list.size() == 5) {
			qDebug() << "card";
			init_cardline(list);
		}
	}
	this->update();
}

void QGTable::recv_change_deck_over(int player_id, int deck_id, int deck_id_leave) {
	Deck* over_deck = find_deck_byid(deck_id);
	if (over_deck != nullptr) {
		over_deck->over_id.append(player_id);
	}
	Deck* over_deck_leave = find_deck_byid(deck_id_leave);
	if (over_deck_leave != nullptr) {
		for (QVector<int>::iterator pid = over_deck_leave->over_id.begin(); pid != over_deck_leave->over_id.end(); pid++) {
			if (*pid == player_id) {
				over_deck_leave->over_id.erase(pid);
				break;
			}
		}
	}
	update();
}

void QGTable::init_cardline(QStringList list) {
	int width = list[0].toInt();
	int height = list[1].toInt();
	int count = list[2].toInt();
	QString image_path_front = list[3];
	QString image_path_back = list[4];
	Deck * deck = this->decks.last();
	deck->append(new Object(QSize(width, height), read_image(image_path_front), read_image(image_path_back)), count);
}

void QGTable::init_table(QStringList list) {
	int side_number = list[1].toInt();
	int angle = list[2].toInt();
	int radius = list[3].toInt();
	int R = list[4].toInt();
	int G = list[5].toInt();
	int B = list[6].toInt();
	for (int i = 0; i < side_number; i++) {
		float theta = i * M_PI * 2 / side_number + angle*M_PI/180.0;
		this->table_vertex.append(QPointF((float)radius * cos(theta), (float)radius * sin(theta)));
	}
	this->table_color = QColor(R, G, B);
}

void QGTable::init_deck(QStringList list){
	bool backside = list[1] == "B";
	int x = list[2].toInt();
	int y = list[3].toInt();
	this->decks.append(new Deck(backside,QPointF(x,y)));
}

QImage QGTable::read_image(QString image_path) {
	for (QVector<ImageWithPath *>::iterator piwp = image_list.begin(); piwp != image_list.end(); piwp++) {
		if ((*piwp)->path == image_path) {
			return (*piwp)->image;
		}
	}
	ImageWithPath * p = new ImageWithPath(this->game_dir, image_path);
	image_list.append(p);
	return p->image;
}

QPointF QGTable::cam_transform(QPointF world_point) {
	return world_point * cam_scale + cam_center;
}

QVector<QPointF> QGTable::cam_transform(QVector<QPointF> world_points) {
	QVector<QPointF> out;
	for (QVector<QPointF>::iterator p = world_points.begin(); p != world_points.end(); p++) {
		out.append(cam_transform(*p));
	}
	return out;
}

void QGTable::check_over(QPointF mouse_pos){
	int my_deck_id_over_new = -1;
	for (QVector<Deck*>::iterator pdeck = decks.end(); pdeck != decks.begin(); ) {
		pdeck--;
		if (!(*pdeck)->objects.isEmpty()) {
			QSizeF image_size = (*pdeck)->objects[0]->size * cam_scale;
			if (QRectF(cam_transform((*pdeck)->position), image_size).contains(mouse_pos)) {
				my_deck_id_over_new = (*pdeck)->id;
				break;
			}
		}
	}
	if (my_deck_id_over_new != my_deck_id_over) {
		emit emit_over_changed(my_player_id, my_deck_id_over_new, my_deck_id_over);
		qDebug() << "over changed" << my_player_id << my_deck_id_over_new << my_deck_id_over;
		my_deck_id_over = my_deck_id_over_new;
	}
}

Deck* QGTable::find_deck_byid(int id, bool to_toplayer) {
	if (id < 0) {
		return nullptr;
	}
	for (QVector<Deck*>::iterator pdeck = decks.begin(); pdeck != decks.end(); pdeck++) {
		if ((*pdeck)->id == id) {
			if (to_toplayer) {
				decks.append(*pdeck);
				decks.erase(pdeck);
				return decks.last();
			}
			else {
				return *pdeck;
			}
		}
	}
	return nullptr;
}