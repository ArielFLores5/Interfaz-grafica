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
    cabecera << "TAREA" << "ASIGNATURA" << "FECHA" << "HORA";
    ui->tblTareas->setHorizontalHeaderLabels(cabecera);
    cargar();

    // Conectar señal itemDoubleClicked con la ranura eliminarTareaConfirmacion
    connect(ui->tblTareas, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(on_tblTareas_itemDoubleClicked(QTableWidgetItem*)));
}

Tasky::~Tasky()
{
    delete ui;
}

void Tasky::on_btnAgregar_clicked()
{
    QString nombre = ui->editTarea->text();
    if(nombre.isEmpty()){
        QMessageBox::warning(this,"Agregar Tarea","El nombre de la tarea no puede estar vacío");
            ui->editTarea->setFocus();
        return;
    }
    QString asignatura = ui->cmbAsignatura->currentText();
    QTime hora = ui->dtHora->time();
    QDate fecha = ui->dtFecha->date();
    Tarea *t = new Tarea(nombre, asignatura, fecha, hora);
    agregarTarea(t);
    limpiar();
    // Guardar tareas
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

    // Calcular la diferencia en días
    int diferenciaDias = QDate::currentDate().daysTo(t->fecha());

    // Establecer el color de fondo según la diferencia en días
    if (diferenciaDias >= 0 && diferenciaDias <= 1) {
        ui->tblTareas->item(fila, TAREA)->setBackground(QBrush(Qt::red));
        ui->tblTareas->item(fila, ASIGNATURA)->setBackground(QBrush(Qt::red));
        ui->tblTareas->item(fila, FECHA)->setBackground(QBrush(Qt::red));
        ui->tblTareas->item(fila, HORA)->setBackground(QBrush(Qt::red));
    } else if (diferenciaDias > 1) {
        ui->tblTareas->item(fila, TAREA)->setBackground(QBrush(Qt::green));
        ui->tblTareas->item(fila, ASIGNATURA)->setBackground(QBrush(Qt::green));
        ui->tblTareas->item(fila, FECHA)->setBackground(QBrush(Qt::green));
        ui->tblTareas->item(fila, HORA)->setBackground(QBrush(Qt::green));
    }
}

void Tasky::limpiar()
{
    // Establecer la fecha y la hora actual
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime::currentTime();
    ui->dtFecha->setMinimumDate(hoy);
    ui->dtFecha->setDate(hoy);
    ui->dtHora->setTime(ahora);
    // Limpiar campos
    ui->editTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);
    // Setear el foco al campo de tarea
    ui->editTarea->setFocus();
}

void Tasky::guardar()
{
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
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
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if(!archivo.exists())
        return;

    // Cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        while (!entrada.atEnd()) {
            // Leer la línea del archivo
            QString linea = entrada.readLine();
            // Separar los campos por ";"
            QStringList campos = linea.split(";");
            // Obtener el nombre y la asignatura
            QString nombre = campos[0];
            QString asignatura = campos[1];
            // Obtener la fecha
            QStringList fecha= campos[2].split("/");
            QDate f(fecha[2].toInt(), fecha[1].toInt(), fecha[0].toInt());
            // Obtener la hora
            QStringList hora = campos[3].split(":");
            QTime h(hora[0].toInt(), hora[1].toInt());
            // Crear la Tarea
            Tarea *t = new Tarea(nombre, asignatura, f, h);
            // Agregar la tarea
            agregarTarea(t);
        }
        archivo.close();
    }
}

void Tasky::on_tblTareas_itemDoubleClicked(QTableWidgetItem *item)
{
    int fila = item->row();
    if (fila >= 0 && fila < m_tareas.size())
    {
        // Mostrar cuadro de diálogo de confirmación
        QMessageBox::StandardButton respuesta;
        respuesta = QMessageBox::question(this, "Eliminar Tarea", "¿Seguro que quieres eliminar esta tarea?",
                                                                      QMessageBox::Yes | QMessageBox::No);

        if (respuesta == QMessageBox::Yes)
        {
            // Eliminar la tarea
            delete m_tareas.takeAt(fila);
            ui->tblTareas->removeRow(fila);
            // Guardar después de eliminar
            guardar();
        }
    }
}

int Tasky::calcularDiferenciaDias(const QDate& fechaTarea)
{
    return QDate::currentDate().daysTo(fechaTarea);
}
