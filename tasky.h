#ifndef TASKY_H
#define TASKY_H

#include <QMainWindow>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <tarea.h>
#include <QFile>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasky; }
QT_END_NAMESPACE

class Tasky : public QMainWindow
{
    Q_OBJECT

public:
    Tasky(QWidget *parent = nullptr);
    ~Tasky();

private slots:
    void on_btnAgregar_clicked();
    void closeEvent(QCloseEvent *event);


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
