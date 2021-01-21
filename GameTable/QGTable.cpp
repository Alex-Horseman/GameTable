#include "QGTable.h"



QGTable::QGTable(QWidget *parent)
	: QWidget(parent)
{
}


QGTable::~QGTable()
{
}

void QGTable::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	for (QVector<Deck *>::iterator pdeck = decks.begin(); pdeck != decks.end(); pdeck++){
		if (!(*pdeck)->objects.isEmpty()) {
			if ((*pdeck)->backside) {
				painter.drawImage((*pdeck)->position, (*pdeck)->objects[0]->back_image);
			}
			else {
				painter.drawImage((*pdeck)->position, (*pdeck)->objects[0]->front_image);
			}
		}
	}
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
			if (list.size() == 2) {
				if (list[1] == "B") {
					this->decks.append(new Deck(true));
					qDebug() << "deck b";
				}
				else {
					this->decks.append(new Deck(false));
					qDebug() << "deck f";
				}
			}
			this->decks.append(new Deck(false));
		}
		else if (list.size() == 5) {
			qDebug() << "card";
			init_cardline(list);
		}
	}
	this->update();
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