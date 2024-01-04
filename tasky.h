#ifndef TASKY_H
#define TASKY_H

#include <QMainWindow>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <tarea.h>
#include <QFile>
#include <QCloseEvent>
#include <QTableWidgetItem>
#include <QBrush>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasky; }
QT_END_NAMESPACE

class Tasky : public QMainWindow
{
    Q_OBJECT

public:
    int calcularDiferenciaDias(const QDate& fechaTarea);
    Tasky(QWidget *parent = nullptr);
    ~Tasky();

private slots:
    void on_btnAgregar_clicked();
    void on_tblTareas_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::Tasky *ui;
    QList<Tarea*> m_tareas; // coleccion de elementos en el tipo Tarea
    const QString ARCHIVO = "tarea.csv";
    enum Columna
    {
        TAREA, ASIGNATURA, FECHA, HORA
    };
    void agregarTarea(Tarea *t);
    void limpiar();
    void guardar();
    void cargar();

};
#endif // TASKY_H
