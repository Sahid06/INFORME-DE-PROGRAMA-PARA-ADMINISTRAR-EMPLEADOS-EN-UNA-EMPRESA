#include <iostream>
#include <string>

using namespace std;
    
// --- CLASE PADRE ---
class Empleado {
protected:
    string nombre;
    string apellido;
    int edad;
    string ocupacion;
    int horas;
    double sueldo;
    int tiempoServicio; // Nuevo atributo: Tiempo en la empresa (en anos)

public:
    // Constructor modificado para recibir el tiempo de servicio
    Empleado(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) {
        nombre = _nombre;
        apellido = _apellido;
        edad = _edad;
        ocupacion = _ocupacion;
        horas = 40; 
        sueldo = 0; 
        tiempoServicio = _tiempoServicio; 
    }

    // Métodos "get" públicos para poder acceder a los datos desde fuera de la clase
    int getTiempoServicio() {
        return tiempoServicio;
    }
    
    string getNombreCompleto() {
        return nombre + " " + apellido;
    }

    // Método mostrarDatos modificado
    void mostrarDatos() {
        cout << "========================================" << endl;
        cout << "Nombre Completo: " << nombre << " " << apellido << endl;
        cout << "Edad: " << edad << " anos" << endl;
        cout << "Ocupacion: " << ocupacion << endl;
        cout << "Horas Trabajadas: " << horas << " horas" << endl;
        cout << "Tiempo en la empresa: " << tiempoServicio << " anos" << endl; // Modificacion aqui
        cout << "Sueldo Mensual: $" << sueldo << endl;
        cout << "========================================" << endl;
    }
};

// --- CLASES HIJAS ---

class EmpleadoPorHora : public Empleado {
public:
    // Pasa el nuevo parametro _tiempoServicio al padre
    EmpleadoPorHora(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) 
        : Empleado(_nombre, _apellido, _edad, _ocupacion, _tiempoServicio) {}

    void calcularSueldoHora() {
        sueldo = horas * 50; 
    }
};

class EmpleadoPlanta : public Empleado {
private:
    double tarifaPorHora;

public:
    // Pasa el nuevo parametro _tiempoServicio al padre
    EmpleadoPlanta(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) 
        : Empleado(_nombre, _apellido, _edad, _ocupacion, _tiempoServicio) {}

    void calcularSueldoPlanta() {
        if (ocupacion == "Supervisor" || ocupacion == "supervisor") {
            tarifaPorHora = 80;
        } else if (ocupacion == "Gerente" || ocupacion == "gerente") {
            tarifaPorHora = 100;
        } else {
            tarifaPorHora = 0;
        }
        sueldo = horas * tarifaPorHora;
    }
};

// --- FUNCIÓN EXTERNA PARA CALCULAR EL MAYOR TIEMPO ---
// Recibe como parametros los objetos individuales creados en el main
void calcularMayorTiempo(EmpleadoPorHora e1, EmpleadoPorHora e2, EmpleadoPorHora e3, EmpleadoPlanta e4, EmpleadoPlanta e5) {
    
    // Asumimos inicialmente que el primero es el que tiene mas tiempo
    int maxTiempo = e1.getTiempoServicio();
    string nombreMayor = e1.getNombreCompleto();

    // Vamos comparando uno a uno con los demas
    if (e2.getTiempoServicio() > maxTiempo) {
        maxTiempo = e2.getTiempoServicio();
        nombreMayor = e2.getNombreCompleto();
    }
    if (e3.getTiempoServicio() > maxTiempo) {
        maxTiempo = e3.getTiempoServicio();
        nombreMayor = e3.getNombreCompleto();
    }
    if (e4.getTiempoServicio() > maxTiempo) {
        maxTiempo = e4.getTiempoServicio();
        nombreMayor = e4.getNombreCompleto();
    }
    if (e5.getTiempoServicio() > maxTiempo) {
        maxTiempo = e5.getTiempoServicio();
        nombreMayor = e5.getNombreCompleto();
    }

    // Mostramos el resultado final
    cout << "\n>>> EL EMPLEADO CON MAS TIEMPO EN LA EMPRESA ES: <<<" << endl;
    cout << "Empleado: " << nombreMayor << " con " << maxTiempo << " anos de servicio.\n" << endl;
}

// --- FUNCIÓN PRINCIPAL ---
int main() {
    // Agregamos el ultimo numero que representa los anos trabajando
    EmpleadoPorHora emp1("Carlos", "Mendoza", 23, "Operador", 2); // 2 anos
    EmpleadoPorHora emp2("Ana", "Gomez", 28, "Operador", 5);     // 5 anos
    EmpleadoPorHora emp3("Luis", "Torres", 31, "Operador", 1);    // 1 ano

    EmpleadoPlanta emp4("Sofia", "Castro", 35, "Supervisor", 8);  // 8 anos
    EmpleadoPlanta emp5("Javier", "Lopez", 42, "Gerente", 4);     // 4 anos

    // Calcular los sueldos
    emp1.calcularSueldoHora();
    emp2.calcularSueldoHora();
    emp3.calcularSueldoHora();
    emp4.calcularSueldoPlanta();
    emp5.calcularSueldoPlanta();

    // Mostrar la lista
    cout << "\n\t--- LISTA DE EMPLEADOS DE LA EMPRESA ---\n" << endl;
    emp1.mostrarDatos();
    emp2.mostrarDatos();
    emp3.mostrarDatos();
    emp4.mostrarDatos();
    emp5.mostrarDatos();

    // Llamar a la funcion para calcular quien trabajo mas tiempo
    calcularMayorTiempo(emp1, emp2, emp3, emp4, emp5);

    return 0;
}