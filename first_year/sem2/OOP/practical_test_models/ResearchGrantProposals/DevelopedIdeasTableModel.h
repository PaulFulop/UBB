#pragma once
#include <QAbstractTableModel>
#include "Repo.h"
#include "Idea.h"

class DevelopedIdeasTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	Repo<Idea>* ideas;
	DevelopedIdeasTableModel(Repo<Idea>* _ideas) : ideas(_ideas) {}
	DevelopedIdeasTableModel() = default;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};