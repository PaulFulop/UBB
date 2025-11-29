#include "IdeasTableModel.h"
#include <algorithm>

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
			return QVariant(QString::fromStdString(ideas->data[row].desc));
		case 1:
			return QVariant(QString::fromStdString(ideas->data[row].status));
		case 2:
			return QVariant(QString::fromStdString(ideas->data[row].creator));
		case 3:
			return QVariant(QString::fromStdString(std::to_string(ideas->data[row].act)));
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
			return QVariant("Description");
		case 1:
			return QVariant("Status");
		case 2:
			return QVariant("Creator");
		case 3:
			return QVariant("Act");
		default:
			break;
		}
	}

	return QVariant();
}

void IdeasTableModel::AddIdea(Idea& idea) {
	if(idea.desc == "") throw std::exception("Empty description!");
	if (idea.act < 1 || idea.act > 3) throw std::exception("Invalid act!");
	for (const auto& i : ideas->data)
		if (idea == i) throw std::exception("There is another identical idea to this one!");

	beginInsertRows(QModelIndex(), ideas->data.size(), ideas->data.size());
	*sorted = false;
	ideas->Add(idea);
	endInsertRows();
}

void IdeasTableModel::Sort() {
	beginResetModel();
	if(*sorted == false)
		std::sort(ideas->data.begin(), ideas->data.end(), [](const Idea& i1, const Idea& i2) {return i1.act < i2.act; });
	*sorted = true;
	endResetModel();
}

void IdeasTableModel::AcceptIdea(Idea& idea) {
	beginResetModel();
	idea.status = "accepted";
	endResetModel();
}

std::vector<Idea*> IdeasTableModel::WriterAcceptedIdeas(const Writer& w) {
	std::vector<Idea*> acceptedIdeas;

	for (auto& idea : ideas->data)
		if (idea.creator == w.name && idea.status == "accepted")
			acceptedIdeas.push_back(&idea);

	return acceptedIdeas;
}

std::vector<Idea> IdeasTableModel::AcceptedIdeas() {
	std::vector<Idea> acceptedIdeas;
	for (auto& idea : ideas->data)
		if (idea.status == "accepted")
			acceptedIdeas.push_back(idea);

	return acceptedIdeas;
}

void IdeasTableModel::RefreshModel() {
	beginResetModel();
	endResetModel();
}