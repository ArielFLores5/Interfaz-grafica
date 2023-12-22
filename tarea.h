#ifndef TAREA_H
#define TAREA_H

#include <QObject>
#include <QDate>

class Tarea : public QObject
{
    Q_OBJECT
private:
    QString m_nombre;
    QString m_asignatura;
    QDate m_fecha;
    QTime m_hora;
    Q_PROPERTY(QString nombre READ nombre WRITE setNombre)
    Q_PROPERTY(QString asignatura READ asignatura WRITE setAsignatura)
    Q_PROPERTY(QDate fecha READ fecha WRITE setFecha)
    Q_PROPERTY(QTime hora READ hora WRITE setHora)


public:
    explicit Tarea(QObject *parent = nullptr);
    Tarea(const QString &nombre, const QString &asignatura, const QDate &fecha, const QTime &hora);


    const QString &nombre() const;
    void setNombre(const QString &newNombre);
    const QString &asignatura() const;
    void setAsignatura(const QString &newAsignatura);
    const QDate &fecha() const;
    void setFecha(const QDate &newFecha);
    const QTime &hora() const;
    void setHora(const QTime &newHora);

signals:

    void nombreChanged();
    void asignaturaChanged();
    void fechaChanged();
    void horaChanged();
};

#endif // TAREA_H
