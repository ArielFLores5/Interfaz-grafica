#include "tasky.h"
#include "ui_tasky.h"

Tasky::Tasky(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasky)
{
    ui->setupUi(this);

    limpiar();
    ui->tblTareas->setColumnCount(4);
    QStringList cabecera;
    cabecera<<"TAREA"<<"ASIGNATURA"<<"FECHA"<<"HORA";
    ui->tblTareas->setHorizontalHeaderLabels(cabecera);
}

Tasky::~Tasky()
{
    delete ui;
}


void Tasky::on_btnAgregar_clicked()
{
    QString nombre = ui->editTarea->text();
    if(nombre.length() ==0){
        QMessageBox::warning(this,"Agregar Tarea","El nombre de la tarea no puede estar vacio");
        ui->editTarea->setFocus();
        return;
    }
    QString asignatura= ui->cmbAsignatura->currentText();
    QTime hora = ui->dtHora->time();
    QDate fecha= ui->dtFecha->date();
    Tarea *t = new Tarea(nombre, asignatura, fecha, hora);
    agregarTarea(t);
    limpiar();
    //fuardar tareas
    guardar();
}

void Tasky::agregarTarea(Tarea *t)
{
    m_tareas.append(t);
    int fila = ui->tblTareas->rowCount();
    ui->tblTareas->insertRow(fila);
    ui->tblTareas->setItem(fila, TAREA, new QTableWidgetItem(t->nombre()));
    ui->tblTareas->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->asignatura()));
    ui->tblTareas->setItem(fila, FECHA, new QTableWidgetItem(t->fecha().toString("dd/MM/yyyy")));
    ui->tblTareas->setItem(fila, HORA, new QTableWidgetItem(t->hora().toString("hh:mm")));
}

void Tasky::limpiar()
{
    //Establecer la fecha y la hora actual
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime::currentTime();
    ui->dtFecha->setMinimumDate(hoy);
    ui->dtFecha->setDate(hoy);
    ui->dtHora->setTime(ahora);
    //limpiar campos
    ui->editTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);
    //setear el foco al campo de tarea
    ui->editTarea->setFocus();
}

void Tasky::guardar()
{
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream salida(&archivo);
        Tarea *t;
        foreach(t, m_tareas) {
            salida << t->nombre() << ";" << t->asignatura() << ";";
            salida << t->fecha().toString("dd/MM/yyyy") << ";";
            salida << t->hora().toString("hh:mm") << "\n";
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Guardar tareas", "No se puede escribir sobre " + ARCHIVO);
    }
}

void Tasky::cargar()
{
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        while (!entrada.atEnd()) {
            QString linea = entrada.readLine();
            QStringList campos = linea.split(";");
            if (campos.size() == 4) {
                QString nombre = campos[0];
                QString asignatura = campos[1];
                QDate fecha = QDate::fromString(campos[2], "dd/MM/yyyy");
                QTime hora = QTime::fromString(campos[3], "hh:mm");
                Tarea *t = new Tarea(nombre, asignatura, fecha, hora);
                agregarTarea(t);
            }
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Cargar tareas", "No se puede leer desde " + ARCHIVO);
    }
}
void Tasky::closeEvent(QCloseEvent *event)
{
    guardar();
    event->accept();
}

/*1.- Cuando se abra la aplicacion en tasky primero leerlo
2.- Crear un objeto
3.- split: separamos campos  (metodo de la clase string, permite partir una cadena de caracteres)
tenemos que crear un nuevo QDate, los comodines son los separadres
4.-Instanciar una tarea
5.-AgregarTarea(t*)
hacerlo por cada linea dentro de el archivo
*/

