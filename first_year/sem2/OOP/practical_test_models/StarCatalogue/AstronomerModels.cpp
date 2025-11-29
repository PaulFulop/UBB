#include "AstronomerModels.h"

int AstronomerTableModel::rowCount(const QModelIndex& parent) const {
	return stars->data.size();
}

int AstronomerTableModel::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant AstronomerTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int row = index.row();
		int col = index.column();

		switch (col) {
		case 0:
			return QVariant(QString::fromStdString(stars->data[row].name));
		case 1:
			return QVariant(QString::fromStdString(stars->data[row].constellation));
		case 2:
			return QVariant(QString::fromStdString(std::to_string(stars->data[row].RA)));
		case 3:
			return QVariant(QString::fromStdString(std::to_string(stars->data[row].Dec)));
		case 4:
			return QVariant(QString::fromStdString(std::to_string(stars->data[row].diameter)));
		default:
			break;
		}
	}

	return QVariant();
}

void AstronomerTableModel::AddStar(Star newStar) {
	beginInsertRows(QModelIndex(), stars->data.size(), stars->data.size());
	stars->Add(newStar);
	endInsertRows();
}

QVariant AstronomerTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Horizontal && (role == Qt::DisplayRole || role == Qt::EditRole)) {
		switch (section) {
		case 0:
			return QVariant("Name");
		case 1:
			return QVariant("Constellation");
		case 2:
			return QVariant("Right Ascension"); 
		case 3:
			return QVariant("Declination");
		case 4:
			return QVariant("Diameter");
		default:
			break;
		}
	}

	return QVariant();
}

int AstronomerListModel::rowCount(const QModelIndex& parent) const {
	return stars->data.size();
}

QVariant AstronomerListModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		return QVariant(QString::fromStdString(stars->data[index.row()].ToString()));
	}

	return QVariant();
}