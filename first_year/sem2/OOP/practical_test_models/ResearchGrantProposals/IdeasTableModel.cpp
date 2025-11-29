#include "IdeasTableModel.h"

int IdeasTableModel::rowCount(const QModelIndex& parent) const {
	return ideas->data.size();
}

int IdeasTableModel::columnCount(const QModelIndex& parent) const {
	return 4;
}

QVariant IdeasTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int row = index.row();
		int col = index.column();

		switch (col) {
		case 0:
			return QVariant(QString::fromStdString(ideas->data[row].title));
		case 1:
			return QVariant(QString::fromStdString(ideas->data[row].status));
		case 2:
			return QVariant(QString::fromStdString(ideas->data[row].creator));
		case 3:
			return QVariant(QString::fromStdString(std::to_string(ideas->data[row].duration)));
		default:
			break;
		}
	}

	return QVariant();
}

QVariant IdeasTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if ((role == Qt::DisplayRole || role == Qt::EditRole) && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QVariant("Title");
		case 1:
			return QVariant("Status");
		case 2:
			return QVariant("Creator");
		case 3:
			return QVariant("Duration");
		default:
			break;
		}
	}

	return QVariant();
}

Qt::ItemFlags IdeasTableModel::flags(const QModelIndex& index) const {
	return {Qt::ItemIsEnabled, Qt::ItemIsSelectable };
}

void IdeasTableModel::AddNewIdea(Idea newIdea) {
	beginInsertRows(QModelIndex(), ideas->data.size(), ideas->data.size());
	ideas->Add(newIdea);
	endInsertRows();
}

void IdeasTableModel::AcceptIdea(int pos) {
	beginResetModel();
	ideas->data[pos].status = "accepted";
	endResetModel();
}