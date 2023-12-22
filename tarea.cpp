#include "tarea.h"

const QString &Tarea::nombre() const
{
    return m_nombre;
}

void Tarea::setNombre(const QString &newNombre)
{
    if (m_nombre == newNombre)
        return;
    m_nombre = newNombre;

}

const QString &Tarea::asignatura() const
{
    return m_asignatura;
}

void Tarea::setAsignatura(const QString &newAsignatura)
{
    if (m_asignatura == newAsignatura)
        return;
    m_asignatura = newAsignatura;

}

const QDate &Tarea::fecha() const
{
    return m_fecha;
}

void Tarea::setFecha(const QDate &newFecha)
{
    if (m_fecha == newFecha)
        return;
    m_fecha = newFecha;

}

const QTime &Tarea::hora() const
{
    return m_hora;
}

void Tarea::setHora(const QTime &newHora)
{
    if (m_hora == newHora)
        return;
    m_hora = newHora;

}

Tarea::Tarea(QObject *parent)
    : QObject{parent}
{

}

Tarea::Tarea(const QString &nombre, const QString &asignatura, const QDate &fecha, const QTime &hora) : m_nombre(nombre),
    m_asignatura(asignatura),
    m_fecha(fecha),
    m_hora(hora)
{}
