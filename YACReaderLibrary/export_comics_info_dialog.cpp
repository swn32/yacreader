#include "export_comics_info_dialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>

#include "data_base_management.h"

ExportComicsInfoDialog::ExportComicsInfoDialog(QWidget *parent)
	: QDialog(parent)
{
	textLabel = new QLabel(tr("Output file : "));
	path = new QLineEdit;
	textLabel->setBuddy(path);

	accept = new QPushButton(tr("Create"));
	accept->setDisabled(true);
	connect(accept,SIGNAL(clicked()),this,SLOT(exportComicsInfo()));

	cancel = new QPushButton(tr("Cancel"));
	connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
	connect(cancel,SIGNAL(clicked()),this,SIGNAL(rejected()));

	find = new QPushButton(QIcon(":/images/db.png"),"");
	connect(find,SIGNAL(clicked()),this,SLOT(findPath()));

	QHBoxLayout *libraryLayout = new QHBoxLayout;

	libraryLayout->addWidget(textLabel);
	libraryLayout->addWidget(path);
	libraryLayout->addWidget(find);
	libraryLayout->setStretchFactor(find,0); //TODO

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(accept);
	bottomLayout->addWidget(cancel);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(libraryLayout);
	mainLayout->addWidget(progress=new QLabel());
	mainLayout->addStretch();
	mainLayout->addLayout(bottomLayout);

	QHBoxLayout * imgMainLayout = new QHBoxLayout;
	QLabel * imgLabel = new QLabel(this);
	QPixmap p(":/images/exportComicsInfo.png");
	imgLabel->setPixmap(p);
	imgMainLayout->addWidget(imgLabel);
	imgMainLayout->addLayout(mainLayout);
	
	setLayout(imgMainLayout);

	setModal(true);
	setWindowTitle(tr("Export comics info"));
}

ExportComicsInfoDialog::~ExportComicsInfoDialog()
{

}

void ExportComicsInfoDialog::findPath()
{
	QString s = QFileDialog::getSaveFileName(this,tr("Destination database name"),".","*.ydb");
	if(!s.isEmpty())
	{
		path->setText(s);
		accept->setEnabled(true);
	}
}

void ExportComicsInfoDialog::exportComicsInfo()
{
	DataBaseManagement::exportComicsInfo(source,path->text());
	close();
}

void ExportComicsInfoDialog::close()
{
	path->clear();
	QDialog::close();
}