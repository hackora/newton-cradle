#ifndef GMOPENGLPROXYMODEL_H
#define GMOPENGLPROXYMODEL_H

// Qt
#include <QAbstractItemModel>

class GMOpenGLProxyModel : public QAbstractItemModel {
  Q_OBJECT
public:
  GMOpenGLProxyModel();


  // From QAbstractItemModel
  QModelIndex             index(int row, int column, const QModelIndex &parent) const override;
  QModelIndex             parent(const QModelIndex &child) const override;
  int                     rowCount(const QModelIndex &parent) const override;
  int                     columnCount(const QModelIndex &parent) const override;
  QVariant                data(const QModelIndex &index, int role) const override;

  QHash<int,QByteArray>   roleNames() const override;


private:
  enum class UserRoles : int {
    Id = Qt::UserRole + 1,
    Name,

  };



};

#endif // GMOPENGLPROXYMODEL_H
