#include "EnitityEditItem.h"
#include <QJsonArray>
//Simple macro to simplify adding new items to this widget
#define CREATEFIELD(field,class) field = new class(this);ui.horizontalLayout->addWidget(field)

EnitityEditItem::EnitityEditItem(EntityData data, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//Create fields
	CREATEFIELD(NameEdit, QTextEdit);
	CREATEFIELD(DisplayNameEdit, QTextEdit);
	CREATEFIELD(HealthSpinbox, QSpinBox);
	CREATEFIELD(DamageSpinbox, QSpinBox);
	CREATEFIELD(DefenceSpinbox, QSpinBox);
	CREATEFIELD(MoneyDropMinSpinbox, QSpinBox);
	CREATEFIELD(MoneyDropMaxSpinbox, QSpinBox);
	CREATEFIELD(IsEnemyCheckbox, QCheckBox);
	CREATEFIELD(comboBox, QComboBox);

	//set values for combobox
	comboBox->addItem("Melee");
	comboBox->addItem("Range");
	comboBox->addItem("Trap");

	//Update upper and lower borders for spinboxes
	MoneyDropMaxSpinbox->setMaximum(INT_MAX);
	MoneyDropMinSpinbox->setMaximum(INT_MAX);
	HealthSpinbox->setMaximum(INT_MAX);
	DefenceSpinbox->setMaximum(INT_MAX);
	DamageSpinbox->setMaximum(INT_MAX);

	MoneyDropMaxSpinbox->setMinimum(0);
	MoneyDropMinSpinbox->setMinimum(0);
	HealthSpinbox->setMinimum(0);
	DefenceSpinbox->setMinimum(0);
	DamageSpinbox->setMinimum(0);

	//fill field
	NameEdit->setText(data.Name);
	DisplayNameEdit->setText(data.DisplayName);

	HealthSpinbox->setValue(data.Health);
	DamageSpinbox->setValue(data.Damage);
	DefenceSpinbox->setValue(data.Defence);
	MoneyDropMinSpinbox->setValue(data.MinMoney);
	MoneyDropMaxSpinbox->setValue(data.MaxMoney);

}

EnitityEditItem::~EnitityEditItem()
{
	delete HealthSpinbox;
	delete DamageSpinbox;
	delete DefenceSpinbox;
	delete MoneyDropMinSpinbox;
	delete MoneyDropMaxSpinbox;
	delete NameEdit;
	delete DisplayNameEdit;
}

QJsonObject EnitityEditItem::GetJsonObject()
{
	QJsonObject result = QJsonObject();

	result["name"] = NameEdit->toPlainText();
	result["displayName"] = DisplayNameEdit->toPlainText();
	result["health"] = HealthSpinbox->value();
	result["defence"] = DefenceSpinbox->value();
	result["damage"] = DamageSpinbox->value();
	result["money_drop_min"] = MoneyDropMinSpinbox->value();
	result["money_drop_max"] = MoneyDropMaxSpinbox->value();
	result["enemy"] = IsEnemyCheckbox->isChecked();
	result["color_pair_id"] = 0;
	result["items"] = QJsonArray();
	result["type"] = comboBox->currentIndex();

	return result;
}
