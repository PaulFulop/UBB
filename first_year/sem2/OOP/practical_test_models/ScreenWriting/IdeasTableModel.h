#pragma once
#include <QAbstractTableModel>
#include "Repo.h"
#include "Idea.h"
#include "Writer.h"

class IdeasTableModel : public QAbstractTableModel {
public:
	Repo<Idea>* ideas;
	bool* sorted;

	IdeasTableModel() = default;
	IdeasTableModel(Repo<Idea>* ideas, bool* _sorted)
		: ideas(ideas), sorted(_sorted)
	{}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void RefreshModel();

	void AddIdea(Idea& idea);
	void Sort();
	void AcceptIdea(Idea& idea);
	std::vector<Idea*> WriterAcceptedIdeas(const Writer& w);
	std::vector<Idea> AcceptedIdeas();
};

