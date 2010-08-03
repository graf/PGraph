#include "qvariableeditor.h"
#include "ui_qvariableeditor.h"
#include "qdatatypeeditor.h"
#include "datatype.h"
#include "databasemanager.h"
#include <QList>


QVariableEditor::QVariableEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVariableEditor)
{
    ui->setupUi(this);
}

QVariableEditor::~QVariableEditor()
{
    delete ui;
}

void QVariableEditor::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QVariableEditor::on_pushButton_clicked()
{
    QDataTypeEditor *editor = new QDataTypeEditor();
    editor->prepareForm(NULL);
    if (editor->exec()){

    }
}

void QVariableEditor::updateInterface()
{

}

void QVariableEditor::prepareForm(Variable *var)
{
    globalDBManager->getDataTypeList(typeList);
    foreach (DataType* type, typeList){
        ui->typeCmbBox->addItem(type->name, type->typedefStr);
    }

    if (var != NULL) {
        ui->nameEdt->setText(var->name);
        ui->commentTxtEdt->setPlainText(var->description);
        ui->initValueEdt->setText(var->initValue.toString());
        int idx = -1;
        for (int i = 0; i < typeList.count(); i++){
            if (var->type == typeList.at(i)->name){
                idx = i;
                break;
            }
        }
        ui->typeCmbBox->setCurrentIndex(idx);
        myVariable = var;
    }
    else
        myVariable = new Variable();
}

Variable* QVariableEditor::getResult()
{
    myVariable->name = ui->nameEdt->text();
    myVariable->initValue = ui->initValueEdt->text();
    myVariable->description = ui->commentTxtEdt->document()->toPlainText();
    myVariable->type = typeList.at(ui->typeCmbBox->currentIndex())->name;
    return myVariable;
}
