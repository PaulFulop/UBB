#include "BacteriumTableModel.h"

int BacteriumTableModel::rowCount(const QModelIndex& parent) const {
	return bacterium->data.size();
}

int BacteriumTableModel::columnCount(const QModelIndex& parent) const {
	return 3;
}

QVariant BacteriumTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		int row = index.row();
		int col = index.column();

		switch (col) {
		case 0:
			return QVariant(QString::fromStdString(bacterium->data[row].name));
		case 1:
			return QVariant(QString::fromStdString(bacterium->data[row].species));
		case 2:
			return QVariant(QString::fromStdString(std::to_string(bacterium->data[row].size)));
		default:
			break;
		}
	}

	return QVariant();
}

void BacteriumTableModel::AddBacteria(Bacterium newBacteria) {
	beginInsertRows(QModelIndex(), bacterium->data.size(), bacterium->data.size());
	bacterium->Add(newBacteria);
	endInsertRows();
}

QVariant BacteriumTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if ((role == Qt::DisplayRole || role == Qt::EditRole) && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QVariant("Name");
		case 1:
			return QVariant("Species");
		case 2:
			return QVariant("Size");
		default:
			break;
		}
	}

	return QVariant();
}

bool BacteriumTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (role == Qt::EditRole) {
		std::string newValue = value.toString().toStdString();

		int row = index.row();
		int col = index.column();

		switch (col) {
		case 0:
			bacterium->data[row].name = newValue;
			bacterium->SaveToFile();
			break;
		case 1:
			bacterium->data[row].species = newValue;
			bacterium->SaveToFile();
			break;
		case 2:
			bacterium->data[row].size = std::atoi(newValue.c_str());
			bacterium->SaveToFile();
			break;
		default:
			break;
		}

		emit dataChanged(index, index, { Qt::EditRole, Qt::DisplayRole });

		return true;
	}

	return false;
}

Qt::ItemFlags BacteriumTableModel::flags(const QModelIndex& index) const {
	return { Qt::ItemIsEnabled, Qt::ItemIsEditable, Qt::ItemIsSelectable };
}