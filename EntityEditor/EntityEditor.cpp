#include "EntityEditor.h"
#include <qmessagebox>
#include <QVBoxLayout>
#include "EntityEditItem.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPushButton>

#define SAFE_GET_JSON_VAR(obj,name,resultType,defaultVar) obj.keys().contains(name)?obj[name].to##resultType() : defaultVar

EntityEditor::EntityEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    scrollAreaCentralWidget = new QWidget(this);
    ui.scrollArea->setWidget(scrollAreaCentralWidget);
    scrollAreaLayout = new QVBoxLayout(scrollAreaCentralWidget);;

    connect(ui.actionOpen, &QAction::triggered, this, &EntityEditor::OpenFile);
    connect(ui.actionSave, &QAction::triggered, this, &EntityEditor::SaveFile);

    connect(ui.addNewItemButton, &QPushButton::pressed, this, &EntityEditor::AddNewItem);
}

void EntityEditor::OpenFile() 
{
    FileName = QFileDialog::getOpenFileName(this, "Open Entity File", "", "Data Files (*.dat)");
    /*Load json data*/
    QFile file;
    file.setFileName(FileName);
    QByteArray fileText;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        fileText = file.readAll();
        file.close();
        qWarning() << fileText;

        QJsonDocument doc = QJsonDocument::fromJson(fileText);
        QJsonObject obj = doc.object();
        QJsonArray array = obj["entities"].toArray();
        if (!array.empty())
        {
            int id = 0;
            for (auto it = array.begin(); it != array.end(); ++it)
            {    
                EntityEditItem* item = new EntityEditItem(
                    EntityData
                    (
                        SAFE_GET_JSON_VAR((*it).toObject(), "name", String, ""),
                        SAFE_GET_JSON_VAR((*it).toObject(), "display_name", String, ""),
                        SAFE_GET_JSON_VAR((*it).toObject(),"health",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"damage",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"defence",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"color_pair_id",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"money_drop_min",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"money_drop_max",Int,0),
                        SAFE_GET_JSON_VAR((*it).toObject(),"type",Int,0)
                    ), this);
                scrollAreaLayout->addWidget(item);
                Entities.push_back(item);
                item->Id = id;
                item->owner = this;
                id++;
            }
        }
        else
        {
            QMessageBox::critical(this, "Fatal Error!", "Failed to load data file!");
        }
    }
}

void EntityEditor::RemoveChild(int id)
{
    if (!Entities.isEmpty())
    {
        Entities.removeAt(id);
    }
}

void EntityEditor::SaveFile()
{
    if (FileName != "" && !Entities.empty())
    {
        QJsonObject obj = QJsonObject();
        
        QJsonArray array = QJsonArray();
        for (auto it = Entities.begin(); it != Entities.end(); ++it)
        {
            if (*it != nullptr)
            {
                array.append((*it)->GetJsonObject());
            }
        }
        obj["entities"] = array;
        QJsonDocument doc = QJsonDocument(obj);
        QFile file;
        file.setFileName(FileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(doc.toJson());
            file.close();
        }
        else
        {
            if (QMessageBox::critical(this, "File Error!", "Failed to load file for saving! Create new one?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            {

            }
        }
    }
}

void EntityEditor::AddNewItem()
{
    if (FileName != "")
    {
        EntityEditItem* item = new EntityEditItem(EntityData(),this);
        scrollAreaLayout->addWidget(item);
        Entities.push_back(item);
    }
}