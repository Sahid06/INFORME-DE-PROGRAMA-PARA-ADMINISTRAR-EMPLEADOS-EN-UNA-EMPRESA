#include <iostream>
#include <string>
#include <fstream>  
using namespace std;

class Empleado {
protected:
    string nombre;
    string apellido;
    int edad;
    string ocupacion;
    int horas;
    double sueldo;
    int tiempoServicio;

public:
    Empleado(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) {
        nombre = _nombre;
        apellido = _apellido;
        edad = _edad;
        ocupacion = _ocupacion;
        horas = 40; 
        sueldo = 0; 
        tiempoServicio = _tiempoServicio; 
    }

    virtual ~Empleado() {}

    virtual void calcularSueldo() = 0;

    int getTiempoServicio() {
        return tiempoServicio;
    }
    
    string getNombreCompleto() {
        return nombre + " " + apellido;
    }

    double getSueldo() {
        return sueldo;
    }

    string getOcupacion() {
        return ocupacion;
    }

    int getEdad() {
        return edad;
    }

    int getHoras() {
        return horas;
    }

    void mostrarDatos() {
        cout << "Nombre Completo: " << nombre << " " << apellido << endl;
        cout << "Edad: " << edad << " anos" << endl;
        cout << "Ocupacion: " << ocupacion << endl;
        cout << "Horas Trabajadas: " << horas << " horas" << endl;
        cout << "Tiempo en la empresa: " << tiempoServicio << " anos" << endl;
        cout << "Sueldo Mensual: $" << sueldo << endl;
    }
};

class EmpleadoPorHora : public Empleado {
public:
    EmpleadoPorHora(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) 
        : Empleado(_nombre, _apellido, _edad, _ocupacion, _tiempoServicio) {}

    void calcularSueldo() override {
        sueldo = horas * 50; 
    }
};

class EmpleadoPlanta : public Empleado {
private:
    double tarifaPorHora;

public:
    EmpleadoPlanta(string _nombre, string _apellido, int _edad, string _ocupacion, int _tiempoServicio) 
        : Empleado(_nombre, _apellido, _edad, _ocupacion, _tiempoServicio) {}

    void calcularSueldo() override {
        if (ocupacion == "Supervisor" || ocupacion == "supervisor") {
            tarifaPorHora = 80;
        } else if (ocupacion == "Gerente" || ocupacion == "gerente") {
            tarifaPorHora = 100;
        } else {
            tarifaPorHora = 40;
        }
        sueldo = horas * tarifaPorHora;
    }
};

void generarReporteYFichero(Empleado* trabajadores[], int total) {
    ofstream archivo("reporte_empleados.txt");
    
    if (!archivo.is_open()) {
        cout << "\nNo se pudo generar el archivo de texto." << endl;
        return;
    }

    int maxTiempo = -1;
    string nombreMayor = "";

    archivo << "Reporte general de trabajadores registrados \n";

    cout << "\n\t Lista de empleados de la empresa\n" << endl;

    for (int i = 0; i < total; i++) {
        if (trabajadores[i] != nullptr) {
            
            trabajadores[i]->calcularSueldo();
            
            trabajadores[i]->mostrarDatos();

            archivo << "Trabajador #" << (i + 1) << "\n";
            archivo << "Nombre Completo: " << trabajadores[i]->getNombreCompleto() << "\n";
            archivo << "Edad: " << trabajadores[i]->getEdad() << " anos\n";
            archivo << "Ocupacion: " << trabajadores[i]->getOcupacion() << "\n";
            archivo << "Horas Laboradas: " << trabajadores[i]->getHoras() << " hrs\n";
            archivo << "Tiempo de Servicio: " << trabajadores[i]->getTiempoServicio() << " anos\n";
            archivo << "Sueldo Mensual: $" << trabajadores[i]->getSueldo() << "\n";

            if (trabajadores[i]->getTiempoServicio() > maxTiempo) {
                maxTiempo = trabajadores[i]->getTiempoServicio();
                nombreMayor = trabajadores[i]->getNombreCompleto();
            }
        }
    }

    cout << "\n>>> EL EMPLEADO CON MAS TIEMPO EN LA EMPRESA ES: <<<" << endl;
    cout << "Empleado: " << nombreMayor << " con " << maxTiempo << " anos de servicio.\n" << endl;

    archivo << "\n>>> Conclusion:Empleado con mas tiempo en la empresa<<<\n";
    archivo << "Nombre: " << nombreMayor << "\n";
    archivo << "Antiguedad: " << maxTiempo << " anos de servicio.\n";

    archivo.close();
    cout << ">>>El archivo 'reporte_empleados.txt' ha sido actualizado correctamente. <<<\n" << endl;
}

int main() {
    const int TOTAL_TRABAJADORES = 10;
    Empleado* trabajadores[TOTAL_TRABAJADORES];

    cout << "     SISTEMA DE REGISTRO INTERACTIVO (10 TRABAJADORES)   " << endl;

    for (int i = 0; i < TOTAL_TRABAJADORES; i++) {
        string nom, ape, ocup;
        int ed, tServicio, tipoEmp;

        cout << "\n--- Ingreso de Datos del Trabajador #" << (i + 1) << " ---" << endl;
        cout << "Ingrese Nombre: ";
        cin >> nom;
        cout << "Ingrese Apellido: ";
        cin >> ape;
        cout << "Ingrese Edad: ";
        cin >> ed;
        cout << "Ingrese Tiempo de Servicio (en anos): ";
        cin >> tServicio;
        
        cout << "Seleccione Tipo de Contrato (1: Por Hora, 2: Planta): ";
        cin >> tipoEmp;

        if (tipoEmp == 1) {
            ocup = "Operador";
            trabajadores[i] = new EmpleadoPorHora(nom, ape, ed, ocup, tServicio);
        } else {
            int opOcup;
            cout << "Seleccione Rol de Planta (1: Supervisor, 2: Gerente, 3: Planta Base): ";
            cin >> opOcup;
            if (opOcup == 1) ocup = "Supervisor";
            else if (opOcup == 2) ocup = "Gerente";
            else ocup = "Planta Base";

            trabajadores[i] = new EmpleadoPlanta(nom, ape, ed, ocup, tServicio);
        }
    }

    generarReporteYFichero(trabajadores, TOTAL_TRABAJADORES);

    for (int i = 0; i < TOTAL_TRABAJADORES; i++) {
        delete trabajadores[i];
    }

    return 0;
}