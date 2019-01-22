#ifndef CAMCALIBRATION_H
#define CAMCALIBRATION_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {class CamCalibration;};
class Smp86xHandler;

class CamCalibration : public QWidget
{
	Q_OBJECT

public:
	CamCalibration(Smp86xHandler* sh, QTcpSocket* tcp1, QWidget *parent = 0);
	~CamCalibration();
protected slots:
	void on_pushButton_clicked();

	//void accept();
	//void reject();
	void on_buttonBox_clicked(QAbstractButton * button);
private:
	Ui::CamCalibration *ui;
	QTransform trans1;
};

class TableItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	TableItemDelegate(int id, QTcpSocket* tcpSocket, QObject* parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
protected slots:
	void commit();
private:
	int _id;
	QTcpSocket* _tcpSocket;
};

#endif // CAMCALIBRATION_H
