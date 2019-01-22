#include "StdAfx.h"
#include "camcalibration.h"
#include "ui_camcalibration.h"

//extern QMutex mutex_smp86x;
//extern SMP86X_STATUS smp86x_status[];
Smp86xHandler* smp86xHandler;

#ifdef _YAMAHA_ROBOT
extern QMutex mutex_yamaha;
extern YAMAHA_STATUS yamaha_status[];
//extern YamahaHandler* ymhHandler;
#endif // _YAMAHA_ROBOT

#pragma region
//////////////////////////////////////////////////////////////////////////
// OpenCV struct
typedef struct CvMat
{
	int type;
	int step;

	/* for internal use only */
	int* refcount;
	int hdr_refcount;

	union
	{
		uchar* ptr;
		short* s;
		int* i;
		float* fl;
		double* db;
	} data;

#ifdef __cplusplus
	union
	{
		int rows;
		int height;
	};

	union
	{
		int cols;
		int width;
	};
#else
	int rows;
	int cols;
#endif

}
CvMat;

typedef struct CvPoint2D32f
{
	float x; /* X坐标, 通常以0为基点*/
	float y; /* Y坐标, 通常以0为基点*/
}CvPoint2D32f;

QTransform vector_to_hom_mat2d(const QPointF p[], const QPointF q[]);
//template<class fn>
//bool readTcpData( QTcpSocket* socket, int m, double* x, double* y, double* a, int delay, fn fun );

QTransform vector_to_hom_mat2d(const QPointF p[], const QPointF q[])
{
#ifdef _DEBUG
	HMODULE hModule = ::LoadLibrary(L"opencv_imgproc246d.dll");
	HMODULE hModule1 = ::LoadLibrary(L"opencv_core246d.dll");
#else
	HMODULE hModule = ::LoadLibrary(L"opencv_imgproc246.dll");
	HMODULE hModule1 = ::LoadLibrary(L"opencv_core246.dll");
#endif // _DEBUG
	QTransform trans;

	if(hModule && hModule1)
	{
		CvPoint2D32f src[3], dst[3];
		src[0].x = p[0].x(), src[0].y = p[0].y();
		src[1].x = p[1].x(), src[1].y = p[1].y();
		src[2].x = p[2].x(), src[2].y = p[2].y();
		dst[0].x = q[0].x(), dst[0].y = q[0].y();
		dst[1].x = q[1].x(), dst[1].y = q[1].y();
		dst[2].x = q[2].x(), dst[2].y = q[2].y();
		auto cvCreateMat = (CvMat* (*)(int rows, int cols, int type))::GetProcAddress(hModule1, "cvCreateMat");
		auto cvReleaseMat = (void (*)(CvMat** mat))::GetProcAddress(hModule1, "cvReleaseMat");
		auto cvGetAffineTransform = (CvMat* (*)(CvPoint2D32f src[], CvPoint2D32f dst[], CvMat* map_matrix))::GetProcAddress(hModule, "cvGetAffineTransform");
		if(cvGetAffineTransform && cvCreateMat && cvReleaseMat)
		{
			CvMat* mat = cvCreateMat(2, 3, 5);
			cvGetAffineTransform(src, dst, mat);
			trans = QTransform(mat->data.fl[0], mat->data.fl[3], mat->data.fl[1], mat->data.fl[4], mat->data.fl[2], mat->data.fl[5]);
			cvReleaseMat(&mat);
		}
		FreeLibrary(hModule);
		FreeLibrary(hModule1);
	}
	return trans;
}
#pragma endregion

CamCalibration::CamCalibration(Smp86xHandler* sh, QTcpSocket* tcp1, QWidget *parent)
	: QWidget(parent, Qt::Window|Qt::MSWindowsFixedSizeDialogHint)
	, ui(new Ui::CamCalibration())
{
	smp86xHandler = sh;
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui->tableWidget  ->setItemDelegate(new TableItemDelegate(0, tcp1, ui->tableWidget  ));
	ui->lineEdit  ->setValidator(new QRegExpValidator(QRegExp("^\\d+$"), ui->lineEdit  ));
	ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("^\\d+$"), ui->lineEdit_2));

	QSettings settings;
	//QStringList data1 = settings.value("Calibration/data1", QList<QVariant>() << 1 << 0 << 0 << 0 << 1 << 0).toStringList();
	//trans1 = QTransform(data1[0].toDouble(), data1[3].toDouble(), data1[1].toDouble(), data1[4].toDouble(), data1[2].toDouble(), data1[5].toDouble());
	trans1 = qTransformFromByteArray(settings.value("Calibration/data1", qTransformToByteArray(QTransform())).toByteArray());
	ui->label_2->setText(QString("[%1, %2, %3]").arg(trans1.m11(), 8, 'f', 3).arg(trans1.m21(), 8, 'f', 3).arg(trans1.m31(), 8, 'f', 3));
	ui->label_3->setText(QString("[%1, %2, %3]").arg(trans1.m12(), 8, 'f', 3).arg(trans1.m22(), 8, 'f', 3).arg(trans1.m32(), 8, 'f', 3));
	ui->lineEdit  ->setText(settings.value("Calibration/res_w1", 0).toString());
	ui->lineEdit_2->setText(settings.value("Calibration/res_h1", 0).toString());

	for(int i=0; i<3; i++)
	{
		ui->tableWidget->item(i, 0)->setText(settings.value(QString("Calibration/c%1_x").arg(i), "0.000").toString());
		ui->tableWidget->item(i, 1)->setText(settings.value(QString("Calibration/c%1_y").arg(i), "0.000").toString());
		ui->tableWidget->item(i, 2)->setText(settings.value(QString("Calibration/p%1_x").arg(i), "0.000").toString());
		ui->tableWidget->item(i, 3)->setText(settings.value(QString("Calibration/p%1_y").arg(i), "0.000").toString());
	}

	//connect(ui->buttonBox, SIGNAL(accepted()), SLOT(accept()));
	//connect(ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));
}

CamCalibration::~CamCalibration()
{
	delete ui;
}

//void CamCalibration::accept()
//{
//	close();
//}
//
//void CamCalibration::reject()
//{
//	close();
//}
//
void CamCalibration::on_pushButton_clicked()
{
	int ix = ui->lineEdit  ->text().toInt();
	int iy = ui->lineEdit_2->text().toInt();
	QPointF p[3], q[3];
	double x, y;
	for (int i=0; i<3; i++)
	{
		x = ui->tableWidget->item(i, 0)->text().toDouble();
		y = ui->tableWidget->item(i, 1)->text().toDouble();
		p[i] = QPointF(x, y)-QPointF(iy/2.0, ix/2.0);

		x = ui->tableWidget->item(i, 3)->text().toDouble();
		y = ui->tableWidget->item(i, 2)->text().toDouble();
		q[i] = QPointF(x, y);
	}

	trans1 = vector_to_hom_mat2d(p, q);
	ui->label_2->setText(QString("[%1, %2, %3]").arg(trans1.m11(), 8, 'f', 3).arg(trans1.m21(), 8, 'f', 3).arg(trans1.m31(), 8, 'f', 3));
	ui->label_3->setText(QString("[%1, %2, %3]").arg(trans1.m12(), 8, 'f', 3).arg(trans1.m22(), 8, 'f', 3).arg(trans1.m32(), 8, 'f', 3));
//	ui->label_4->setText(QString("[%1, %2, %3]").arg(trans.m13(), 8, 'f', 3).arg(trans.m23(), 8, 'f', 3).arg(trans.m33(), 8, 'f', 3));
}

void CamCalibration::on_buttonBox_clicked( QAbstractButton * button )
{
	if (QDialogButtonBox::ApplyRole == ui->buttonBox->buttonRole(button))
	{
		QSettings settings;
		//settings.setValue("Calibration/data1", QList<QVariant>() << trans1.m11() << trans1.m21() 
		//	<< trans1.m31() << trans1.m12() << trans1.m22() << trans1.m32());
		settings.setValue("Calibration/data1", qTransformToByteArray(trans1));
		settings.setValue("Calibration/res_w1", ui->lineEdit  ->text());
		settings.setValue("Calibration/res_h1", ui->lineEdit_2->text());

		for(int i=0; i<3; i++)
		{
			settings.setValue(QString("Calibration/c%1_x").arg(i), ui->tableWidget->item(i, 0)->text());
			settings.setValue(QString("Calibration/c%1_y").arg(i), ui->tableWidget->item(i, 1)->text());
			settings.setValue(QString("Calibration/p%1_x").arg(i), ui->tableWidget->item(i, 2)->text());
			settings.setValue(QString("Calibration/p%1_y").arg(i), ui->tableWidget->item(i, 3)->text());
		}
	}
	if (QDialogButtonBox::RejectRole == ui->buttonBox->buttonRole(button))
		close();
	if (QDialogButtonBox::AcceptRole == ui->buttonBox->buttonRole(button))
		close();
}

//////////////////////////////////////////////////////////////////////////
TableItemDelegate::TableItemDelegate( int id, QTcpSocket* tcpSocket, QObject* parent /*= 0*/ )
	: _id(id)
	, _tcpSocket(tcpSocket)
{
}

QWidget * TableItemDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	switch(index.column())
	{
	case 0:
	case 1:
		{
			QPushButton* pushButton = new QPushButton(parent);
			pushButton->setText(QString::fromUtf16(L"获取"));
			pushButton->setProperty("index", index);
			connect(pushButton, SIGNAL(clicked()), this, SLOT(commit()));
			QTimer::singleShot(0, pushButton, SLOT(click()));
			return pushButton;
		}
		break;
	default:
		return QStyledItemDelegate::createEditor(parent, option, index);
	}
	return NULL;
}

void TableItemDelegate::setEditorData( QWidget *editor, const QModelIndex &index ) const
{
	switch(index.column())
	{
	case 0:
	case 1:
		{
			QPushButton* pushButton = qobject_cast<QPushButton*>(editor);
			pushButton->setProperty("point", index.model()->data(index, Qt::UserRole));
		}
		break;
	default:
		return QStyledItemDelegate::setEditorData(editor, index);
	}
}

void TableItemDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	switch(index.column())
	{
	case 0:
	case 1:
		//{
		//	QPushButton* pushButton = qobject_cast<QPushButton*>(editor);
		//	QPointF point = pushButton->property("point").toPointF();
		//	model->setData(index, point, Qt::UserRole);
		//	model->setData(index, QString("(%1, %2)").arg(point.x(), 0, 'f', 3).arg(point.y(), 0, 'f', 3), Qt::EditRole);
		//}
		break;
	default:
		return QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void TableItemDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

void TableItemDelegate::commit()
{
//	QSettings settings;
//
//#ifdef _YAMAHA_ROBOT
//	YAMAHA_STATUS ys[2];
//	memset(ys, 0, sizeof(ys));
//	mutex_yamaha.lock();
//	memcpy(&ys[0], yamaha_status, sizeof(YAMAHA_STATUS));
//	mutex_yamaha.unlock();
//#else
//	double pulseEquivalent[4];
//	for (int i=0; i<4; i++)
//	{
//		pulseEquivalent[i] = settings.value(QString("PulseEquivalent%1/%2").arg(_id+1).arg(i), 0.01).toDouble();
//	}
//	SMP86X_STATUS ss = smp86xHandler/*[_id]*/->getSmp86xStatus();
//#endif // _YAMAHA_ROBOT

	QPushButton* pushButton = qobject_cast<QPushButton*>(sender());
	QModelIndex index = pushButton->property("index").toModelIndex();
	QPointF point = pushButton->property("point").toPointF();
	int row = index.row();
		
	double ix, iy, ia;
	switch(index.column())
	{
	case 0:
	case 1:
		blockSignals(true);
		sendTcpData(_tcpSocket, 0);
		if(readTcpData(_tcpSocket, &ix, &iy, &ia))
		{
			//point.setX(iy);point.setY(ix);
			point = QPointF(iy, ix);
		}
		blockSignals(false);
		break;
	}
	//pushButton->setProperty("point", QVariant::fromValue(point));
	//const_cast<QAbstractItemModel*>(index.model())->setData(index, point, Qt::UserRole);
	//const_cast<QAbstractItemModel*>(index.model())->setData(index, QString("(%1, %2)").arg(point.x(), 0, 'f', 3).arg(point.y(), 0, 'f', 3), Qt::EditRole);
	const_cast<QAbstractItemModel*>(index.model())->setData(index.sibling(row, 0), QString("%1").arg(point.x(), 0, 'f', 3), Qt::EditRole);
	const_cast<QAbstractItemModel*>(index.model())->setData(index.sibling(row, 1), QString("%1").arg(point.y(), 0, 'f', 3), Qt::EditRole);
	emit commitData(qobject_cast<QWidget*>(sender()));
	emit closeEditor(qobject_cast<QWidget*>(sender()));
	//QMetaObject::invokeMethod(sender(), "close");
}
