#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QCheckBox>
#include <QSpinbox>
#include <QCheckBox>
#include <QComboBox>

#include <QJsonObject>
#include "ui_EnitityEditItem.h"


struct EntityData
{
public:

	QString Name;

	QString DisplayName;

	int Health = 0;
	int Damage = 0;
	int Defence = 0;

	int EnemyType = 0;

	int MaxMoney = 0;
	int MinMoney = 0;

	int Type = 0;

	EntityData(QString name,QString dispName,int health,int damage,int defence,int enemyType,int max,int min,int type):
		Name(name),DisplayName(dispName),Health(health),Damage(damage),Defence(defence),EnemyType(enemyType),MaxMoney(max),MinMoney(min)
	{}
};

class EnitityEditItem : public QWidget
{
	Q_OBJECT

public:
	EnitityEditItem(EntityData,QWidget *parent = Q_NULLPTR);
	~EnitityEditItem();

	QTextEdit* NameEdit;

	QTextEdit* DisplayNameEdit;

	
	QCheckBox* IsEnemyCheckbox;

	QSpinBox* HealthSpinbox;
	QSpinBox*DamageSpinbox;
	QSpinBox* DefenceSpinbox;
	QSpinBox* MoneyDropMinSpinbox;
	QSpinBox* MoneyDropMaxSpinbox;

	QComboBox* comboBox;

	QJsonObject GetJsonObject();
private:
	Ui::EnitityEditItem ui;
};
