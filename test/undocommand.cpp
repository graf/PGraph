#include "undocommand.h"

AddCommand::AddCommand(QGraphicsItem *item, QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    myItem = item;
    setText(QObject::tr("+ ") + itemTypeToString(item));
}

void AddCommand::undo()
{
    QArc* arc = NULL;
    switch (myItem->type()){
    case QArc::Type:
        arc = qgraphicsitem_cast<QArc* >(myItem);
        arc->startItem()->removeArc(arc);
        arc->endItem()->removeArc(arc);
    }
    myGraphicsScene->removeItem(myItem);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}

void AddCommand::redo()
{
    QArc* arc = NULL;
    switch (myItem->type()){
    case QArc::Type:
        arc = qgraphicsitem_cast<QArc* >(myItem);
        arc->startItem()->addArc(arc);
        arc->endItem()->addArc(arc);
        foreach(QArc *qarc, arc->startItem()->outArcs())
            qarc->setPriority(qarc->priority() + 1);
        arc->setPriority(1);
    }
    myGraphicsScene->addItem(myItem);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}

AddCommand::~AddCommand()
{

}

DeleteCommand::DeleteCommand(QGraphicsItem *item, QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = scene;
    myItem = item;
    setText(QObject::tr("- ") + itemTypeToString(item));
}

void DeleteCommand::undo()
{
    QArc* arc = NULL;
    QTop* top = NULL;
    switch (myItem->type()){
    case QArc::Type:
        arc = qgraphicsitem_cast<QArc* >(myItem);
        foreach(QArc *qarc, arc->startItem()->outArcs())
            if (qarc->priority() >= arc->priority())
                qarc->setPriority(qarc->priority() + 1);
        arc->startItem()->addArc(arc);
        arc->endItem()->addArc(arc);
        break;
    case QTop::Type:
        top = qgraphicsitem_cast<QTop* >(myItem);
        foreach (QArc* arc, arcs) {
            arc->startItem()->addArc(arc);
            arc->endItem()->addArc(arc);
            myGraphicsScene->addItem(arc);
        }
    }
    myGraphicsScene->addItem(myItem);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}

void DeleteCommand::redo()
{
    QArc* arc = NULL;
    QTop* top = NULL;
    switch (myItem->type()){
    case QArc::Type:
        arc = qgraphicsitem_cast<QArc* >(myItem);
        arc->startItem()->removeArc(arc);
        arc->endItem()->removeArc(arc);
        break;
    case QTop::Type:
        top = qgraphicsitem_cast<QTop* >(myItem);
        arcs = top->allArcs();
        top->removeArcs();
        foreach (QArc* arc, arcs) {
            arc->endItem()->removeArc(arc);
            arc->startItem()->removeArc(arc);
            myGraphicsScene->removeItem(arc);
        }
    }
    myGraphicsScene->removeItem(myItem);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}

DeleteCommand::~DeleteCommand()
{

}

MoveCommand::MoveCommand(QGraphicsItem *item, QGraphicsScene *graphicsScene, QLineF vector, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myGraphicsScene = graphicsScene;
    myItem = item;
    myDisplacementVector = vector;
    setText(QObject::tr("> ") + itemTypeToString(item) + " (" + QString::number(myDisplacementVector.p1().x()) + ", " + QString::number(myDisplacementVector.p1().y()) + ")->" +
            "(" + QString::number(myDisplacementVector.p2().x()) + ", " + QString::number(myDisplacementVector.p2().y()) + ")");
}

void MoveCommand::undo()
{
    switch (myItem->type()){
    case QTop::Type: {
            QTop* top = qgraphicsitem_cast<QTop* >(myItem);
            top->moveBy(-myDisplacementVector.dx(), -myDisplacementVector.dy());
        }
        break;
    case QComment::Type:{
            myItem->moveBy(-myDisplacementVector.dx(), -myDisplacementVector.dy());
        }
        break;
    }
}

void MoveCommand::redo()
{
    switch (myItem->type()){
    case QTop::Type:{
            QTop* top = qgraphicsitem_cast<QTop* >(myItem);
            top->moveBy(myDisplacementVector.dx(), myDisplacementVector.dy());
        }
        break;
    case QComment::Type:{
            myItem->moveBy(myDisplacementVector.dx(), myDisplacementVector.dy());
        }
        break;
    }
}

bool MoveCommand::mergeWith(const QUndoCommand *command)
{
    const MoveCommand *moveCommand = static_cast<const MoveCommand *>(command);
    QGraphicsItem *item = moveCommand->myItem;

    if (myItem != item)
        return false;

    myDisplacementVector.setP1(myDisplacementVector.p1());
    myDisplacementVector.setP2(moveCommand->myDisplacementVector.p2());

    setText(QObject::tr("> ") + itemTypeToString(item) + " (" + QString::number(myDisplacementVector.p1().x()) + ", " + QString::number(myDisplacementVector.p1().y()) + ")->" +
                                                          "(" + QString::number(myDisplacementVector.p2().x()) + ", " + QString::number(myDisplacementVector.p2().y()) + ")");

    return true;
}

MoveCommand::~MoveCommand()
{

}