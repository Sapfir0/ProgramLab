#ifndef FOTOBASETABLEWIDGETITEM_H
#define FOTOBASETABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <databasecontroller.h>

class fotobaseTableWidgetItem : public QTableWidgetItem
{
	private:
		unsigned int id;
        DataBaseController *d;
		int column;

	public:
        fotobaseTableWidgetItem(unsigned int id, DataBaseController* d, int column) {
			this->id = id;
			this->d = d;
			this->column = column;
			update_text();
		}
		fotobaseTableWidgetItem() {d->remove(id);}
		bool operator < (const QTableWidgetItem &other) const {
			const fotobaseTableWidgetItem& tmp = static_cast<const fotobaseTableWidgetItem&>(other);
			return d->record(id) < tmp.d->record(tmp.id);
		}
//        fotobaseTableWidgetItem(uint _id, DataBaseController* _d, QString _text) {
//             id = _id;
//             d = _d;
//             this->setText(_text);
//         }
		uint get_id() {
			return id;
		}
		fotobase get_record() {
			return d->record(id);
		}
		void update_text() {
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
