#pragma once
#include "Repo.h"
#include "Bacterium.h"
#include <QAbstractTableModel>

class BacteriumTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	Repo<Bacterium>* bacterium;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	void AddBacteria(Bacterium newBacteria);

	BacteriumTableModel() = default;
	BacteriumTableModel(Repo<Bacterium>* bacterium)
		: bacterium(bacterium){ }
};