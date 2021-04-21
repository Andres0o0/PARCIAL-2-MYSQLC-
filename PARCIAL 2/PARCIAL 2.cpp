// PARCIAL 2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mysql.h>
#include<string>

using namespace std;
int q_estado;

void menu();
void ingresar(int opcion, MYSQL* conectar);
void buscar(int opcion, MYSQL* conectar);
void modificar(int opcion, MYSQL* conectar);
void eliminar(int opcion, MYSQL* conectar);
void mostrar(int opcion, MYSQL* conectar);

int main()
{
    menu();
}

void menu() {
    MYSQL* conectar;
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "usr_empresa", "Empres@123", "bd_parcial2", 3306, NULL, 0);
    if (conectar) {
        int opcion, a = 0;
        do {
            system("cls");
            cout << "----------CRUD BASE DE DATOS----------" << endl;
            cout << "A QUE TABLA DESEA INGRESAR: " << endl;
            cout << "TABLA MARCAS                [1]" << endl;
            cout << "TABLA PRODUCTOS             [2]" << endl;
            cout << "SALIR DEL PROGRAMA          [3]" << endl;
            cout << "INGRESE UNA DE LAS OPCIONES: " << endl;
            cin >> opcion;

            if ((opcion == 2 || opcion == 1)) {
                do {
                    system("cls");
                    if (opcion == 2) {
                        cout << "    TABLA PRODUCTOS" << endl;
                    }
                    if (opcion == 1) {
                        cout << "      TABLA MARCA" << endl;
                    }
                    cout << "----------------------" << endl;
                    cout << "QUE DESEA HACER: " << endl << endl;
                    cout << " INGRESAR DATOS                 [1]" << endl;
                    cout << " BUSCAR DATO                    [2]" << endl;
                    cout << " ACTUALIZAR DATOS               [3]" << endl;
                    cout << " ELIMINAR DATOS                 [4]" << endl;
                    cout << " LEER LISTA DE DATOS COMPLETA   [5]" << endl;
                    cout << " REGRESAR                       [6]" << endl;
                    cout << " Ingrese opcion: [ ]\b\b";
                    cin >> a;
                    switch (a)
                    {
                    case 1:
                        system("cls");
                        ingresar(opcion, conectar);
                        break;
                    case 2:
                        system("cls");
                        buscar(opcion, conectar);
                        break;
                    case 3:
                        system("cls");
                        modificar(opcion, conectar);
                        break;
                    case 4:
                        system("cls");
                        eliminar(opcion, conectar);
                        break;

                    case 5:
                        system("cls");
                        mostrar(opcion, conectar);
                    }
                } while (a != 6);
            }
        } while (opcion != 3);
    }
    else {
        cout << "conexion fallida" << endl;
    }
}

void ingresar(int opcion, MYSQL* conectar) {
    string insert;
    if (opcion == 1) {
        cout << "----TABLA MARCA---" << endl;
        string marca;
        cout << "INGRESE EL NOMBRE DE LA MARCA :";
        cin.ignore();
        getline(cin, marca);
        insert = "insert into marcas(marca) values('" + marca + "')";
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "INGRESO EXITOSO..." << endl;
        }
        else
        {
            cout << "ERROR AL INGRESAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "---TABLA PRODUCTOS----" << endl;
        string producto, descripcion,imagen;
        string idmarca, existencia;
        string precio_costo, precio_venta;
        string anio, mes, dia, hora, minutos, segundos;
        fflush(stdin);
        cout << "INGRESE NOMBRE DEL PRODUCTO: ";
        cin.ignore();
        getline(cin, producto);
        cout << "INGRESE EL ID DE LA MARCA (ESTE DEBE EXISTIR EN LA TABLA MARCA): ";
        cin >> idmarca;
        fflush(stdin);
        cout << "INGRESE LA DESCRIPCION DEL PRODUCTO: ";
        cin.ignore();
        getline(cin, descripcion);
        cout << "INGRESE NOMBRE DE LA IMAGEN (imagen.jpg): ";
        cin.ignore();
        getline(cin, imagen);
        cout << "INGRESE EL PRECIO DE COSTO DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
        cin >> precio_costo;
        cout << "INGRESE EL PRECIO DE VENTA DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
        cin >> precio_venta;
        cout << "INGRESE LA CANTIDAD DE PRODUCTO QUE HAY EN EXISTENCIA: ";
        cin >> existencia;
        cout << "INGRESE LA FECHA Y HORA: " << endl;
        cout << "FECHA Y HORA ACTUAL INGRESE        [1]" << endl;
        cout << "FECHA Y HORA PERSONALIZADA INGRESE [2]" << endl;
        int a;
        cin >> a;
        switch (a) {
        case 1:
            insert = "INSERT INTO productos (producto,idMarca,descripcion,imagen,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + imagen + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "',now())";
            break;
        case 2:
            cout << "DIA: ";
            cin >> dia;
            cout << "MES: ";
            cin >> mes;
            cout << "ANIO: ";
            cin >> anio;
            cout << "HORA: ";
            cin >> hora;
            cout << "MINUTOS: ";
            cin >> minutos;
            cout << "SEGUNDOS: ";
            cin >> segundos;
            insert = "INSERT INTO productos (producto,idMarca,descripcion,imagen,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + imagen + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "','" + anio + "-" + mes + "-" + dia + " " + hora + ":" + minutos + ":" + segundos + "')";
            break;
        default:
            cout << "OPCION NO VALIDA, SE INGRESARA FECHA Y HORA ACTUALES ";
            insert = "INSERT INTO productos (producto,idMarca,descripcion,imagen,precio_costo,precio_venta,existencia,fecha_ingreso) values('" + producto + "'," + idmarca + ",'" + descripcion + "','" + imagen + "','" + precio_costo + "','" + precio_venta + "','" + existencia + "',now())";
            break;
        }
        const char* i = insert.c_str();
        q_estado = mysql_query(conectar, i);
        if (!q_estado) {
            cout << "INGRESO EXITOSO..." << endl;
        }
        else
        {
            cout << "ERROR AL INGRESAR..." << endl;
        }
    }
    system("pause");
}
void buscar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from marcas where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from productos where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | IMAGEN     | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t\t" << fila[2] << "\t\t" << fila[3] << "\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t\t" << fila[7] <<"\t"<<fila[8]<< endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void modificar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string modificar;
    string id;
    char respuesta;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA MODIFICAR SUS DATOS: ";
        cin >> id;
        consulta = "select * from marcas where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
            cout << "SEGURO QUE QUIERES MODIFICAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                string marca;
                cout << "INGRESE EL NOMBRE DE LA MARCA :";
                cin.ignore();
                getline(cin, marca);
                modificar = "update marcas set marca='" + marca + "' where (idmarca='" + id + "');";
                const char* i = modificar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "MODIFICACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL MODIFICAR..." << endl;
                }

            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DEL PRODUCTO PARA VER SU INFORMACION: ";
        cin >> id;
        string consulta = "select * from productos where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | IMAGEN     | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t" << fila[3] << "\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t\t" << fila[7] << "\t" << fila[8] << endl;
            }
            cout << "SEGURO QUE QUIERES MODIFICAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                string producto, descripcion,imagen;
                string idmarca, existencia;
                string precio_costo, precio_venta;
                string anio, mes, dia, hora, minutos, segundos;
                fflush(stdin);
                cout << "INGRESE NOMBRE DEL PRODUCTO: ";
                cin.ignore();
                getline(cin, producto);
                cout << "INGRESE EL ID DE LA MARCA (ESTE DEBE EXISTIR EN LA TABLA MARCA): ";
                cin >> idmarca;
                fflush(stdin);
                cout << "INGRESE LA DESCRIPCION DEL PRODUCTO: ";
                cin.ignore();
                getline(cin, descripcion);
                cout << "INGRESE NOMBRE DE LA IMAGEN (imagen.jpg): ";
                cin.ignore();
                getline(cin, imagen);
                cout << "INGRESE EL PRECIO DE COSTO DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
                cin >> precio_costo;
                cout << "INGRESE EL PRECIO DE VENTA DEL PRODUCTO(UNICAMENTE CON 2 PUNTOS DECIMALES): ";
                cin >> precio_venta;
                cout << "INGRESE LA CANTIDAD DE PRODUCTO QUE HAY EN EXISTENCIA: ";
                cin >> existencia;
                cout << "INGRESE LA FECHA Y HORA: " << endl;
                cout << "FECHA Y HORA ACTUAL INGRESE        [1]" << endl;
                cout << "FECHA Y HORA PERSONALIZADA INGRESE [2]" << endl;
                int a;
                cin >> a;
                switch (a) {
                case 1:
                    modificar = "UPDATE productos SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "',imagen= '"+imagen+"', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso = now() WHERE (idProducto = '" + id + "');";
                    break;
                case 2:
                    cout << "DIA: ";
                    cin >> dia;
                    cout << "MES: ";
                    cin >> mes;
                    cout << "ANIO: ";
                    cin >> anio;
                    cout << "HORA: ";
                    cin >> hora;
                    cout << "MINUTOS: ";
                    cin >> minutos;
                    cout << "SEGUNDOS: ";
                    cin >> segundos;
                    modificar = "UPDATE productos SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "',imagen= '" + imagen + "', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso ='" + anio + "-" + mes + "-" + dia + " " + hora + ":" + minutos + ":" + segundos + "' WHERE (idProducto = '" + id + "');";
                    break;
                default:
                    cout << "OPCION NO VALIDA, SE INGRESARA FECHA Y HORA ACTUALES ";
                    modificar = "UPDATE productos SET producto = '" + producto + "', idMarca = '" + idmarca + "', descripcion = '" + descripcion + "',imagen= '" + imagen + "', precio_costo = '" + precio_costo + "', precio_venta = '" + precio_venta + "', existencia = '" + existencia + "', fecha_ingreso = now() WHERE (idProducto = '" + id + "');";
                    break;
                }
                const char* i = modificar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "MODIFICACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL MODIFICAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void eliminar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    string id;
    char respuesta;
    string eliminar;
    if (opcion == 1) {
        cout << "POR FAVOR INGRESE EL ID DE LA MARCA PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from marcas where idmarca =" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            while (fila = mysql_fetch_row(resultado)) {
                cout << "ID MARCA  | MARCA" << endl;
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;

            }
            cout << "SEGURO QUE QUIERES ELIMINAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                eliminar = "delete  from marcas where idmarca=" + id + ";";
                const char* i = eliminar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "ELIMINACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL ELIMINAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        cout << "POR FAVOR INGRESE EL ID DEL PRODUCTO PARA VER SU INFORMACION: ";
        cin >> id;
        consulta = "select * from productos where idProducto=" + id + ";";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | IMAGEN     | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t" << fila[3] << "\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t\t" << fila[7] << "\t" << fila[8] << endl;
            }
            cout << "SEGURO QUE QUIERES ELIMINAR ESTE REGISTRO [S/N]" << endl;
            cin >> respuesta;
            if ((respuesta == 's') || (respuesta == 'S')) {
                eliminar = "delete  from productos where idProducto=" + id + ";";
                const char* i = eliminar.c_str();
                q_estado = mysql_query(conectar, i);
                if (!q_estado) {
                    cout << "ELIMINACION EXITOSA..." << endl;
                }
                else
                {
                    cout << "ERROR AL ELIMINAR..." << endl;
                }
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}
void mostrar(int opcion, MYSQL* conectar) {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    if (opcion == 1) {
        string consulta = "select * from marcas";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID MARCA  | MARCA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t   " << fila[1] << endl;
                cout << "--------------------------------------------" << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    if (opcion == 2) {
        string consulta = "select * from productos";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conectar, c);
        if (!q_estado) {
            resultado = mysql_store_result(conectar);
            cout << "ID PRODUCTO    | PRODUCTO\t      | ID MARCA      | DESCRIPCION          | IMAGEN     | PRECIO COSTO | PRECIO VENTA | EXISTENCIA | FECHA Y HORA" << endl;
            while (fila = mysql_fetch_row(resultado)) {
                cout << fila[0] << "\t\t" << fila[1] << "\t\t" << fila[2] << "\t\t" << fila[3] << "\t" << fila[4] << " \t\t" << fila[5] << "\t\t" << fila[6] << "\t\t" << fila[7] << "\t" << fila[8] << endl;
            }
        }
        else
        {
            cout << "ERROR AL CONSULTAR..." << endl;
        }
    }
    system("pause");
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
