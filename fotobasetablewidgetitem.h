#ifndef FOTOBASETABLEWIDGETITEM_H
#define FOTOBASETABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include "fotodatabase.h"

class fotobaseTableWidgetItem : public QTableWidgetItem //мы проходили наследование вроде
{
	private:
		unsigned int id;
        fotoDatabase *d; //указатель на бдшку
		int column;

	public:
        fotobaseTableWidgetItem(unsigned int idF, fotoDatabase* f, int columnF) {
            id = idF;
            d = f;

            column = columnF;
            update_text();
		}

        fotobaseTableWidgetItem() {
            d->remove(id);
        }

        bool operator < (const QTableWidgetItem &other) {
			const fotobaseTableWidgetItem& tmp = static_cast<const fotobaseTableWidgetItem&>(other);

            return  d->record(id) < tmp.d->record(tmp.id);
		}

        uint get_id() {
			return id;
		}

        fotobase get_record() { //возвращает запись
			return d->record(id);
		}

        void update_text() { // хех
			switch (column) {
                case 0: {
					setText(d->record(id).getNameOfModel());
					break;
				}
				case 1: {
					 setText(QString::number(d->record(id).getCost()));
					break;
				}
			}
		}
};

#endif // FOTOBASETABLEWIDGETITEM_H
