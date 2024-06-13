#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("E:/Qt Practice/SqlDatabaseEntery/record.db");

    if(!myDB.open())
    {
        ui->Status_lbl->setText("Failed to open database");
    }
    else
    {
        ui->Status_lbl->setText("Database connected...");
    }

    setUp();
    connect(ui->AddBtn,&QPushButton::clicked,this,&MainWindow::on_AddBtn);
    connect(ui->UpdateBtn,&QPushButton::clicked,this,&MainWindow::on_UpdateBtn);
    connect(ui->PrintBtn,&QPushButton::clicked,this,&MainWindow::on_PrintBtn);
    connect(ui->ResetBtn,&QPushButton::clicked,this,&MainWindow::on_ResetBtn);
    connect(ui->ShowBtn,&QPushButton::clicked,this,&MainWindow::on_ShowBtn);
    connect(ui->DeleteBtn,&QPushButton::clicked,this,&MainWindow::on_DeleteBtn);

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[0-9]{12}"),this);
    ui->lineedit_Id->setValidator(validator);
    ui->lineEdit_Postcode->setValidator(new QIntValidator(0, 999999, ui->lineEdit_Postcode));
    ui->lineEdit_Telephone->setValidator(new QIntValidator(0, 1000000000, ui->lineEdit_Telephone));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUp()
{
    QStringList header = {"Id", "First Name", "Surname", "Address", "Postcode", "Telephone"};

    QStandardItemModel *model = new QStandardItemModel(0,header.length(),this);

    model->setHorizontalHeaderLabels(header);

    ui->tableView->setModel(model);

    showData();
    ui->lineedit_Id->setEnabled(true);
    ui->lineEdit_FirstName->setEnabled(true);
    ui->lineEdit_Surname->setEnabled(true);
    ui->lineEdit_Address->setEnabled(true);
    ui->lineEdit_Postcode->setEnabled(true);
    ui->lineEdit_Telephone->setEnabled(true);

}

void MainWindow::showData()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery* qry = new QSqlQuery(myDB);

    qry->prepare("select * from StudentRecord");
    qry->exec();

    model->setQuery(*qry);

    ui->tableView->setModel(model);

}


void MainWindow::on_AddBtn()
{
    QString id = ui->lineedit_Id->text();
    QString name = ui->lineEdit_FirstName->text();
    QString surname = ui->lineEdit_Surname->text();
    QString address = ui->lineEdit_Address->text();
    QString postalcode = ui->lineEdit_Postcode->text();
    QString mobNo = ui->lineEdit_Telephone->text();
    QSqlQuery qry;

    qry.prepare("insert into StudentRecord (Id, Name, Surname, Address, PostalCode,Telephone)"
                " values ('"+id+"','"+name+"', '"+surname+"', '"+address+"', '"+postalcode+"', '"+mobNo+"')");

    if (!qry.exec())
    {
        qDebug() << "Error inserting account into database: " << qry.lastError().text();
    }
    showData();
}


void MainWindow::on_UpdateBtn()
{
    QSqlQuery qry;
    qry.prepare("update StudentRecord set Name = '"+ui->lineEdit_FirstName->text()+"'");
    qry.exec();
    showData();
}


void MainWindow::on_PrintBtn()
{
    on_ShowBtn();
    QMessageBox::information(this,"Student Record", "Student Record\n"+ui->lineedit_Id->text()+"\n"
                             + ui->lineEdit_FirstName->text() +"\n" +
                             ui->lineEdit_Surname->text()+"\n" +
                             ui->lineEdit_Address->text()+"\n" +
                             ui->lineEdit_Postcode->text()+"\n" +
                             ui->lineEdit_Telephone->text());
}


void MainWindow::on_ResetBtn()
{
    ui->lineedit_Id->clear();
    ui->lineEdit_FirstName->clear();
    ui->lineEdit_Surname->clear();
    ui->lineEdit_Address->clear();
    ui->lineEdit_Postcode->clear();
    ui->lineEdit_Telephone->clear();

}


void MainWindow::on_DeleteBtn()
{
    QSqlQuery qry;
    qry.prepare("delete from StudentRecord where Id = '"+ui->lineedit_Id->text()+"'");
    qry.exec();
    showData();
}


void MainWindow::on_ShowBtn()
{
    QSqlQuery qry;

    qry.prepare("select * from StudentRecord where Id = '"+ui->lineedit_Id->text()+"'");
    if(qry.exec())
    {
        if(qry.next())
        {
            ui->lineedit_Id->setText(qry.value(0).toString());
            ui->lineEdit_FirstName->setText(qry.value(1).toString());
            ui->lineEdit_Surname->setText(qry.value(2).toString());
            ui->lineEdit_Address->setText(qry.value(3).toString());
            ui->lineEdit_Postcode->setText(qry.value(4).toString());
            ui->lineEdit_Telephone->setText(qry.value(5).toString());
        }
        else
        {
            QMessageBox::information(this,"Not Found", "Record Not Found!");
            return;
        }
    }

}


