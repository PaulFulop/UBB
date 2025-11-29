#pragma once
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include "Repository.h"
#include "Star.h"

class AstronomerTableModel : public QAbstractTableModel {
	Q_OBJECT
private:
	Repository<Star>* stars;
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	void AddStar(Star newStar);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	AstronomerTableModel(Repository<Star>* _stars, QObject* parent = nullptr)
		: stars(_stars), QAbstractTableModel(parent)
	{}
};

class AstronomerListModel : public QAbstractListModel {
	Q_OBJECT
private:
	Repository<Star>* stars;
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	AstronomerListModel(Repository<Star>* _stars, QObject* parent = nullptr)
		: stars(_stars), QAbstractListModel(parent)
	{}
};