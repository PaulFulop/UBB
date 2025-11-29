#include "EventsTableModel.h"

int EventsTableModel::rowCount(const QModelIndex& parent) const {
	return repo.events.size();
}

int EventsTableModel::columnCount(const QModelIndex& parent) const {
	return 5;
}

QVariant EventsTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		int row = index.row();
		switch (index.column())
		{
		case 0:
			return QVariant{ QString::fromStdString(this->repo.events[row].title) };
			break;
		case 1:
			return QVariant{ QString::fromStdString(this->repo.events[row].description) };
			break;
		case 2:
			return QVariant{ QString::fromStdString(this->repo.events[row].dt) };
			break;
		case 3:
			return QVariant{ QString::fromStdString(std::to_string(this->repo.events[row].nr_of_people)) };
			break;
		case 4:
			return QVariant{ QString::fromStdString(this->repo.events[row].link) };
			break;
		default:
			break;
		}
	}
	return QVariant{};
}

QVariant EventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QVariant{ "Title" };
			case 1:
				return QVariant{ "Description" };
			case 2:
				return QVariant{ "Date" };
			case 3:
				return QVariant{ "Participants" };
			case 4:
				return QVariant{ "Link" };
			default:
				break;
			}
		}
	}
	return QVariant{};
}