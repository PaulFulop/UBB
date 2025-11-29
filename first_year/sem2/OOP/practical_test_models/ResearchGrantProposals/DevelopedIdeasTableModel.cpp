#include "DevelopedIdeasTableModel.h"
#include <QPushButton>

int DevelopedIdeasTableModel::rowCount(const QModelIndex& parent) const {
	return ideas->data.size();
}

int DevelopedIdeasTableModel::columnCount(const QModelIndex& parent) const {
	return 6;
}

QVariant DevelopedIdeasTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int row = index.row();
		int col = index.column();

		switch (col) {
		case 0:
			return QVariant(QString::fromStdString(ideas->data[row].description));
		case 1:
			return QVariant(QString::fromStdString(ideas->data[row].title));
		case 2:
			return QVariant(QString::fromStdString(ideas->data[row].status));
		case 3:
			return QVariant(QString::fromStdString(ideas->data[row].creator));
		case 4:
			return QVariant(QString::fromStdString(std::to_string(ideas->data[row].duration)));
		case 5:
			return QVariant();
		default:
			break;
		}
	}

	return QVariant();
}

QVariant DevelopedIdeasTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if ((role == Qt::DisplayRole || role == Qt::EditRole) && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QVariant("Description");
		case 1:
			return QVariant("Title");
		case 2:
			return QVariant("Status");
		case 3:
			return QVariant("Creator");
		case 4:
			return QVariant("Duration");
		case 5:
			return QVariant("Manage");
		default:
			break;
		}
	}

	return QVariant();
}

Qt::ItemFlags DevelopedIdeasTableModel::flags(const QModelIndex& index) const {
	if(index.column() == 0)
		return { Qt::ItemIsEnabled, Qt::ItemIsSelectable, Qt::ItemIsEditable };

	return { Qt::ItemIsEnabled, Qt::ItemIsSelectable };
}