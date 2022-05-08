#include <QTreeView>
#include "tree_model.h"

class ReordableTreeModel : public TreeModel {

    public:
        ReordableTreeModel(QObject *parent = nullptr);
        void swapItems(QModelIndex sourceIndex, QModelIndex destinationIndex);
};

class ReordableTreeView : public QTreeView {
    Q_OBJECT

    public:
        ReordableTreeView(QWidget *parent = nullptr);
        ~ReordableTreeView();
        void setModel(ReordableTreeModel *model);
        ReordableTreeModel *model() const;

    private:
        void startDrag(Qt::DropActions supportedActions);
        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);
        void dragLeaveEvent(QDragLeaveEvent *event);


        QModelIndex dragIndex;
        QModelIndex dropIndex;
};
