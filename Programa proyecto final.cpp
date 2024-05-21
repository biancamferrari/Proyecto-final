#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void crearBin() {
  string usuario = "1";

  // crear usuario.bin si usuario.bin no existe
  ifstream a("usuario.bin", ios::binary);
  if (!a.is_open()) {
    ofstream salida("usuario.bin", ios::app | ios::binary);

    int tam = static_cast<int>(usuario.size());
    salida.write((char *)&tam, sizeof(int));
    salida.write(usuario.c_str(), tam);

    tam = static_cast<int>(usuario.size());
    salida.write((char *)&tam, sizeof(int));
    salida.write(usuario.c_str(), tam);
    salida.close();
  }
  a.close();
}

void registrar() {
  string usuario;

  cout << "Ingresar usuario a registrar:\n";
  cin >> usuario;

  ofstream salida("usuario.bin", ios::app | ios::binary);

  int tam = static_cast<int>(usuario.size());
  salida.write((char *)&tam, sizeof(int));
  salida.write(usuario.c_str(), tam);

  cout << "Ingrese la contrasena:\n";
  cin >> usuario;

  tam = static_cast<int>(usuario.size());
  salida.write((char *)&tam, sizeof(int));
  salida.write(usuario.c_str(), tam);

  salida.close();
}

void iniciarSesion(string &usuario) {
  string contrasena;
  int tamano;
  string decision;
  bool si = true;
  while (si) {
    cout << "Inicio de sesion:\nUsuario:\n";
    cin >> usuario;
    ifstream entrada("usuario.bin", ios::binary);
    while (entrada.read((char *)&tamano, sizeof(int))) {
      char cadena[tamano];
      entrada.read((char *)cadena, tamano);
      string comparar = string(cadena, tamano);
      if (comparar == usuario) {
        entrada.read((char *)&tamano, sizeof(int));
        char cadena[tamano];
        entrada.read((char *)cadena, tamano);
        string comparar = string(cadena, tamano);
        while (si) {
          cout << "Contrasena:\n";
          cin >> contrasena;
          if (comparar == contrasena) {
            cout << "\nAcceso concedido.\n\n!Bienvenid@ " << usuario << "!"
                 << endl;
            si = false;
            break;
          } else
            cout << "Contrasena incorrecta, vuelva a intentarlo\n";
        }
      }
    }
    entrada.close();
    if (si == true) {
      cout << "Usuario no encontrado, desea intentarlo de nuevo (1) o "
              "registrarse en el programa (2)?";
      while (si) {
        getline(cin, decision);
        if (decision == "2") {
          registrar();
        }
        if (decision != "1" && decision != "2") {
          cout << "Opcion no valida, por favor elija (1) o (2)\n";
        } else
          break;
      }
    }
  }
}

void crearTxt(string usuario) {
  ofstream salida("salida.txt");
  salida << "Archivo de salida\nRegistro realizado por el usuario <<" << usuario
         << ">>\n\nReporte de las operaciones realizadas:\n\n";
  salida.close();
}

// Función para mostrar el menú y obtener la opción del usuario
char menu() {
  char opcion;
  cout << "\n\t\t\t\t\t\t\t\t\tMenu:" << endl;
  cout << "===================================================================="
          "========"
       << endl;
  cout << "| 1. Ingresar nuevos datos a la base de datos meteorológicos.       "
          "       |"
       << endl;
  cout << "| 2. Ver temperatura máxima en un rango de tiempo dado.             "
          "       |"
       << endl;
  cout << "| 3. Ver temperatura mínima en un rango de tiempo dado.             "
          "       |"
       << endl;
  cout << "| 4. Ver promedio de temperatura en un mes determinado.             "
          "       |"
       << endl;
  cout << "| 5. Ver porcentaje mayor de humedad en un mes dado, con una "
          "condición     |"
       << endl;
  cout << "|    meteorológica predeterminada.                                  "
          "       |"
       << endl;
  cout << "| 6. Ver porcentaje menor de humedad en un mes dado, con una "
          "condición     |"
       << endl;
  cout << "|    meteorológica predeterminada.                                  "
          "       |"
       << endl;
  cout << "| 7. Ver probabilidad de incendio, dada la temperatura, velocidad "
          "del      |"
       << endl;
  cout << "|    viento y la condición meteorológica en un día determinado.     "
          "       |"
       << endl;
  cout << "| 8. Ver probabilidad de una tormenta, dada la presión atmosférica, "
          "       |"
       << endl;
  cout << "|    humedad y condición meteorológica de un día determinado.       "
          "       |"
       << endl;
  cout << "===================================================================="
          "========"
       << endl;

  cout << "Opcion a elegir: ";
  cin >> opcion;
  return opcion;
}

void ordenarTxT() {
  string textoEntrada, textoUltimo = " 0-0-0", textoComparar, textoEncabezado;
  int dia, mes, ano, dia2 = 0, mes2 = 0, ano2 = 0, dia3, mes3, ano3,
                     contador = 1, fecha1, fecha2 = 0, fecha3;
  char guion;
  ofstream escribir("datos_ordenados.txt");
  for (int i = 0; i < contador; i++) {
    textoComparar = "3000-3000-3000";
    ifstream leer("datos_meteorologicos.txt", ios::in);
    if (i == 0) {
      getline(leer, textoEncabezado);
      escribir << textoEncabezado << endl;
      contador--;
    }
    while (getline(leer, textoEntrada)) {
      if (i == 0) {
        contador++;
      }
      istringstream dividir1(textoEntrada);
      dividir1 >> ano >> guion >> mes >> guion >> dia;
      fecha1 = ano * 10000 + mes * 100 + dia;

      istringstream dividir2(textoComparar);
      dividir2 >> ano2 >> guion >> mes2 >> guion >> dia2;
      fecha2 = ano2 * 10000 + mes2 * 100 + dia2;

      istringstream dividir3(textoUltimo);
      dividir3 >> ano3 >> guion >> mes3 >> guion >> dia3;
      fecha3 = ano3 * 10000 + mes3 * 100 + dia3;

      if (fecha1 < fecha2 && fecha1 > fecha3) {
        textoComparar = textoEntrada;
      }
    }
    leer.close();
    escribir << textoComparar << endl;
    textoUltimo = textoComparar;
  }
  escribir.close();
  ifstream leerOrdenar("datos_ordenados.txt", ios::in);
  ofstream ordenar("datos_meteorologicos.txt");
  while (getline(leerOrdenar, textoEntrada)) {
    ordenar << textoEntrada << endl;
  }
  leerOrdenar.close();
  ordenar.close();
}
// Estructura para representar los datos meteorológicos
struct datos_meteorologicos {
  int anio;
  char guion_1;
  int mes;
  char guion_2;
  int dia;
  float temperatura;
  long humedad;
  long velocidad_viento;
  long presion;
  string condicion_meteorologica;
};

bool validar_estructura(string linea) {
  istringstream ss(linea);

  // istringstream llamado ss, se utiliza para leer datos en una cadena de
  // caracteres en una linea, algo asi como un cin
  // lo que hace es mirar por espacios y tipo de datos ingresados

  datos_meteorologicos datos;

  // Extraer los datos de la línea
  if (!(ss >> datos.anio >> datos.guion_1 >> datos.mes >> datos.guion_2 >>
        datos.dia >> datos.temperatura >> datos.humedad >>
        datos.velocidad_viento >> datos.presion >>
        datos.condicion_meteorologica)) {
    cout << "Error: La linea no tiene la estructura correcta." << endl;
    return false;
  }

  // Verificar que los datos estén en rangos válidos
  if (datos.anio < 0 || datos.mes < 1 || datos.mes > 12 || datos.dia < 1 ||
      datos.dia > 31 || datos.temperatura < 0 || datos.temperatura > 100 ||
      datos.humedad < 0 || datos.humedad > 100 || datos.velocidad_viento < 0 ||
      datos.velocidad_viento > 200 || datos.presion < 600 ||
      datos.presion > 1200 ||
      !(datos.condicion_meteorologica == "Lluvioso" ||
        datos.condicion_meteorologica == "Soleado" ||
        datos.condicion_meteorologica == "Nublado")) {
    cout << "Error: Los datos estan fuera del rango." << endl;
    return false;
  }
  return true;
}

// Función para permitir al usuario introducir nuevas lineas de datos en un
// archivo de texto
void agregar_lineas_archivo() {
  // Abrir el archivo en modo de escritura (ios::app para agregar al final del
  // archivo)
  bool existe = false;
  string texto;
  ofstream archivo;
  archivo.open("datos_meteorologicos.txt", ios::app);

  if (archivo.is_open()) {

    cout << "                                      \nIntroducir nuevos datos"
         << endl;
    cout << "=================================================================="
            "========================================"
         << endl;
    cout << "Por favor, introduzca las nuevas líneas de datos meteorologicos "
            "de la siguiente manera:\n";
    cout << "- ANIO-MES-DIA,(2020-01-01)\n - Temperatura(C)(17.9)\n"
            "- Humedad(%)(74)\n - Velocidad del viento(km/h)(7)\n- Presion "
            "atmosferica (hPa)(1008)\n - Condicion meteorologica(primer letra "
            "en "
            "mayuscula(Nublado, Soleado, Lluvioso)\n";
    cout << "Ejemplo a introducir: 2020-01-02 18.7 64 19 1028 Lluvioso\n";
    cout << "(escriba 'Fin' o 'FIN' para finalizar la introduccion de nuevos "
            "datos)"
         << endl;
    cout << "=============================" << endl;

    // Pedir al usuario que introduzca las nuevas líneas de datos
    string nueva_linea;
    while (true) {
      cout << "-> ";
      getline(cin, nueva_linea);
      if (nueva_linea == "FIN" || nueva_linea == "Fin" ||
          nueva_linea == "fin") {
        break; // Salir del bucle si el usuario escribe 'fin'
      }

      if (!validar_estructura(nueva_linea)) {
        continue; // Volver a pedir al usuario que introduzca la línea
                  // correctamente
      }
      ifstream leer("datos_meteorologicos.txt", ios::in);
      while (getline(leer, texto)) {
        leer >> texto;
        if (nueva_linea.substr(0, 10) == texto) {
          cout << "esta fecha ya existe" << endl;
          existe = true;
        }
      }
      leer.close();
      if (existe == false) {
        archivo << endl << nueva_linea;
      } // Escribir la nueva línea en el archivo
    }
    ordenarTxT();
    // Cerrar el archivo
    archivo.close();

    cout << "=========================================" << endl;
    cout << "Datos agregados correctamente al archivo." << endl;
    cout << "=========================================" << endl;
  } else {
    cout << "Error al abrir \"datos meteorologicos.txt\"" << endl;
  }
}

// Función para validar la estructura de una línea de datos meteorológicos
void mayorTemp() {
  string fecha1;
  bool encontrarfecha1 = false, encontrarfecha2 = false;
  string fecha2;
  float comparar = 0;
  string texto;
  string fecha3;
  float temp = 0;

  cout << "Ingrese la primer fecha con el formato (ano-mes-dia) "
          "ej:(2020-01-01):\n";
  getline(cin, fecha1);

  cout << "Ingrese la segunda fecha con el formato (ano-mes-dia) "
          "ej:(2020-01-02):\n";
  getline(cin, fecha2);

  ifstream datos("datos_meteorologicos.txt");
  if (datos) {
    while (getline(datos, texto)) { // 1ra vez, salta linea de unidades, de ahí
                                    // en adelante hace un salto de linea
      datos >> texto;               // ingreso de la fecha del txt
      if (texto == fecha1) {
        encontrarfecha1 = true;
      }
      if (encontrarfecha1) {
        datos >> comparar; // ingreso de temperatura del txt

        // encontrar mayor temperatura
        if (comparar > temp) {
          temp = comparar;
          fecha3 = texto;
        }
        // cerrar si se llega a fecha2
        if (texto == fecha2) {
          encontrarfecha2 = true;
          break;
        }
      }
    }
    if (encontrarfecha1 == false) {
      cout << "Fecha 1 no encontrada\n";
    }
    if (encontrarfecha2 == false) {
      cout << "Fecha 2 no encontrada\n";
    } else if (encontrarfecha1 == true && encontrarfecha2 == true) {
      ofstream salida("salida.txt", ios::app);
      salida << "-> Mayor temperatura registrada de " << fecha1 << " a "
             << fecha2 << ":\n"
             << temp << "C° en " << fecha3 << endl
             << endl;
      salida.close();
      cout << "\nTemperatura mayor registrada de " << fecha1 << " a " << fecha2
           << ":\n"
           << temp << "C° en " << fecha3 << endl
           << endl;
    }
  } else
    cout << "Error al abrir \"datos meteorologicos.txt\"" << endl;
}

void menorTemp() {
  string fecha1;
  bool encontrarfecha1 = false, encontrarfecha2 = false;
  string fecha2;
  string texto;
  string fecha3;
  float comparar = 0;
  float temp = 100;

  cout << "Ingrese la primer fecha con el formato (ano-mes-dia) "
          "ej:(2020-01-01):\n";
  getline(cin, fecha1);

  cout << "Ingrese la segunda fecha con el formato (ano-mes-dia) "
          "ej:(2020-01-02):\n";
  getline(cin, fecha2);

  ifstream datos("datos_meteorologicos.txt");
  if (datos) {
    while (getline(datos, texto)) { // 1ra vez, salta linea de unidades, de ahí
                                    // en adelante hace un salto de linea
      datos >> texto;               // ingreso de la fecha del txt
      if (texto == fecha1) {
        encontrarfecha1 = true;
      }
      if (encontrarfecha1) {
        datos >> comparar; // ingreso de temperatura del txt

        // encontrar menor temperatura
        if (comparar < temp) {
          temp = comparar;
          fecha3 = texto;
        }
        // cerrar si se llega a fecha2
        if (texto == fecha2) {
          encontrarfecha2 = true;
          break;
        }
      }
    }
    if (encontrarfecha1 == false) {
      cout << "\nFecha 1 no encontrada\n";
    }
    if (encontrarfecha2 == false) {
      cout << "\nFecha 2 no encontrada\n";
    } else if (encontrarfecha1 == true && encontrarfecha2 == true) {
      ofstream salida("salida.txt", ios::app);
      salida << "-> Menor temperatura registrada de " << fecha1 << " a "
             << fecha2 << ":\n"
             << temp << "C° en " << fecha3 << endl
             << endl;
      salida.close();
      cout << "\nMenor temperatura registrada de " << fecha1 << " a " << fecha2
           << ":\n"
           << temp << "C° en " << fecha3 << endl
           << endl;
    }
  } else
    cout << "Error al abrir \"datos meteorologicos.txt\"" << endl;
}

void promedioTempMes() {
  int ano;
  int ano2;
  int mes;
  int mes2;
  bool encontrarfecha1 = false;
  string texto;
  float temp = 0;
  int contador = 0;
  float sumaTemp = 0;

  cout << "Ingrese el numero del mes a buscar ej:(01):\n";
  cin >> mes;
  cout << "Ingrese de que ano ej:(2020):\n";
  cin >> ano;

  ifstream datos("datos_meteorologicos.txt");
  if (datos) {
    while (getline(datos, texto)) {
      istringstream dividir(texto);
      dividir >> ano2 >> mes2 >> temp >> temp;
      if (ano == ano2 && mes == mes2 * -1) {
        encontrarfecha1 = true;
        contador++;
        sumaTemp += temp;
      }
    }
    ofstream salida("salida.txt", ios::app);
    if (encontrarfecha1 == false) {
      cout << "fecha 1 no encontrada\n";
    } else {
      salida << "\n-> Promedio de temperatura del mes " << mes << " del ano "
             << ano << ":\n"
             << sumaTemp / contador << endl
             << endl;
      salida.close();
      cout << "\nPromedio de temperatura del mes " << mes << " del ano " << ano
           << ":\n"
           << sumaTemp / contador << endl
           << endl;
    }
  } else
    cout << "Error, no se pudo encontrar el archivo "
            "\"datos_meteorologicos.txt\"\n";
}

void mayorPromedioHumedad() {
  string mesBuscado;
  string condicion_meteorologica;

  float humedad, humedadSoleado = 0, humedadLluvioso = 0, humedadNublado = 0,
                 promedioSoleado, promedioLluvioso, promedioNublado;
  int contadorSoleado = 0, contadorLLuvioso = 0, contadorNublado = 0;
  bool encontrado = false; // Bandera para determinar si se encontro el mes
  string texto,
      linea; // Variables auxiliares para manejo de texto
             // Variables para leer la condicion meteorologica y humedad
  cout << "Ingrese el mes con el formato (ano-mes) ej:(2020-01):\n";
  getline(cin, mesBuscado); // Se lee el mes (ej. 2023-01)

  ifstream datos("datos_meteorologicos.txt"); // Se abre el archivo de datos
  if (datos) {               // Verifica si el archivo se abrio correctamente
    getline(datos, texto);   // salta primera linea
    while (datos >> texto) { // Se lee una fecha del archivo
      if (texto.substr(0, 7) ==
          mesBuscado) { // Compara la fecha leida con el mes buscado
        encontrado = true;
        datos >> humedad >> humedad >> condicion_meteorologica >>
            condicion_meteorologica >> condicion_meteorologica;
        if (condicion_meteorologica == "Nublado") {
          contadorNublado++;
          humedadNublado += humedad;
        }
        if (condicion_meteorologica == "Soleado") {
          contadorSoleado++;
          humedadSoleado += humedad;
        }
        if (condicion_meteorologica == "Lluvioso") {
          contadorLLuvioso++;
          humedadLluvioso += humedad;
        }
      }
    }
    if (!encontrado) { // Si no se encontra el mes, se notifica al usuario
      cout << "Mes no encontrado o sin datos para el mes especificado";
    } else {
      ofstream salida("salida.txt", ios::app);
      promedioNublado = humedadNublado / contadorNublado;
      promedioSoleado = humedadSoleado / contadorSoleado;
      promedioLluvioso = humedadLluvioso / contadorLLuvioso;
      if (promedioNublado > promedioSoleado &&
          promedioNublado > promedioLluvioso) {
        cout << "\nCondicion con mayor humedad en el mes (" << mesBuscado
             << "): Nublado (" << promedioNublado << "%)";
        salida << "\n-> Condicion con mayor humedad en el mes (" << mesBuscado
               << "): Nublado ()" << promedioNublado << "%)\n";
      }
      if (promedioSoleado > promedioNublado &&
          promedioSoleado > promedioLluvioso) {
        cout << "\nCondicion con mayor humedad en el mes (" << mesBuscado
             << "): Soleado (" << promedioSoleado << "%)";
        salida << "\n-> Condicion con mayor humedad en el mes (" << mesBuscado
               << "): Soleado(" << promedioSoleado << "%)\n";
      }
      if (promedioLluvioso > promedioNublado &&
          promedioLluvioso > promedioSoleado) {
        cout << "\nCondicion con mayor humedad en el mes (" << mesBuscado
             << "): Lluvioso(" << promedioLluvioso << "%)";
        salida << "\n-> Condicion con mayor humedad en el mes (" << mesBuscado
               << "): Lluvioso(" << promedioLluvioso << "%)\n";
      }
    }
  } else {
    cout << "Error al abrir el archivo"; // Se notifica al usuario si el archivo
                                         // no se pudo abrir
  }
}
void menorPromedioHumedad() {
  string mesBuscado; // Array para el mes buscado
  string condicion_meteorologica;

  float humedad, humedadSoleado = 0, humedadLluvioso = 0, humedadNublado = 0,
                 promedioSoleado, promedioLluvioso, promedioNublado;
  int contadorSoleado = 0, contadorLLuvioso = 0, contadorNublado = 0;
  bool encontrado = false; // Bandera para determinar si se encontro el mes
  string texto,
      linea; // Variables auxiliares para manejo de texto
             // Variables para leer la condicion meteorologica y humedad

  cout << "Ingrese el mes con el formato (ano-mes) ej:(2020-01):\n";
  getline(cin, mesBuscado); // Se lee el mes (ej. 2023-01)

  ifstream datos("datos_meteorologicos.txt"); // Se abre el archivo de datos
  if (datos) {               // Verifica si el archivo se abrio correctamente
    getline(datos, texto);   // salta primera linea
    while (datos >> texto) { // Se lee una fecha del archivo
      if (texto.substr(0, 7) ==
          mesBuscado) { // Compara la fecha leida con el mes buscado
        encontrado = true;
        datos >> humedad >> humedad >> condicion_meteorologica >>
            condicion_meteorologica >> condicion_meteorologica;
        if (condicion_meteorologica == "Nublado") {
          contadorNublado++;
          humedadNublado += humedad;
        }
        if (condicion_meteorologica == "Soleado") {
          contadorSoleado++;
          humedadSoleado += humedad;
        }
        if (condicion_meteorologica == "Lluvioso") {
          contadorLLuvioso++;
          humedadLluvioso += humedad;
        }
      }
    }
    if (!encontrado) { // Si no se encontra el mes, se notifica al usuario
      cout << "Mes no encontrado o sin datos para el mes especificado";
    } else {
      ofstream salida("salida.txt", ios::app);
      promedioNublado = humedadNublado / contadorNublado;
      promedioSoleado = humedadSoleado / contadorSoleado;
      promedioLluvioso = humedadLluvioso / contadorLLuvioso;
      if (promedioNublado < promedioSoleado &&
          promedioNublado < promedioLluvioso) {
        cout << "\nCondicion con menor humedad en el mes (" << mesBuscado
             << ") es: Nublado (" << promedioNublado << "%)";
        salida << "\n-> Condicion con menor humedad en el mes (" << mesBuscado
               << ") es: Nublado (" << promedioNublado << "%)\n";
      }
      if (promedioSoleado < promedioNublado &&
          promedioSoleado < promedioLluvioso) {
        cout << "\nCondicion con menor humedad en el mes (" << mesBuscado
             << ") es: Soleado (" << promedioSoleado << "%)";
        salida << "\n-> Condicion con menor humedad en el mes (" << mesBuscado
               << ") es: Soleado(" << promedioSoleado << "%)\n";
      }
      if (promedioLluvioso < promedioNublado &&
          promedioLluvioso < promedioSoleado) {
        cout << "\nCondicion con menor humedad en el mes (" << mesBuscado
             << ") es: Lluvioso(" << promedioLluvioso << "%)";
        salida << "\n-> Condicion con menor humedad en el mes (" << mesBuscado
               << ") es: Lluvioso(" << promedioLluvioso << "%)\n";
      }
    }
  } else {
    cout << "Error al abrir el archivo"; // Se notifica al usuario si el archivo
                                         // no se pudo abrir
  }
}

// Función para calcular la probabilidad de incendio
void probabilidad_incendio() {
  string fecha;
  string texto;
  string fecha1;
  string condicion_meteorologica;
  float temperatura;
  float velocidad_viento;
  bool fechaEncontrada=false;
  cout << "Ingrese una fecha cualquiera con el siguiente formato "
          "(ano-mes-dia):\n";
  getline(cin, fecha);

  ifstream datos("datos_meteorologicos.txt");
  if (!datos.is_open()) {
    cout << "Error al abrir el archivo de datos meteorológicos" << endl;
    return;
  }
  if (datos) {
    while (getline(datos, texto)) {
      istringstream ss(texto);
      ss >> fecha1;
      if (fecha == fecha1) {
        fechaEncontrada = true;
        ss >> temperatura >> velocidad_viento >> velocidad_viento >>
            condicion_meteorologica >> condicion_meteorologica;
        // Calcular la probabilidad de incendio
        ofstream salida("salida.txt", ios::app);
        if (!salida.is_open()) {
          cout << "Error al abrir el archivo de salida" << endl;
          return;
        }
        if (temperatura > 35 && condicion_meteorologica == "Soleado" &&
          velocidad_viento >= 7 && velocidad_viento <= 10) {
          cout << "\nCon la temperatura de " << temperatura
               << "C°, la velocidad del viento " << velocidad_viento
               << ",y la condicion meterologica "
               << "(" << condicion_meteorologica << ")" << endl;
          cout << "Probabilidad de incendio : ALTA" << endl;
          cout << "Hay una alta probabilidad de incendio." << endl;
          salida << " -> Probabilidad de incendio: \"ALTA\"\n";
        } 
        else if (velocidad_viento >= 3 && velocidad_viento <= 5 &&
                   temperatura >= 25 && temperatura <= 35 &&
                   condicion_meteorologica == "Soleado") {
          cout << "\nCon la temperatura de " << temperatura
               << "C°, la velocidad del viento " << velocidad_viento
               << ",y la condicion meterologica "
               << "(" << condicion_meteorologica << ")" << endl;
          cout << "Probabilidad de incendio : MEDIA" << endl;
          cout << "Existe la probabilidad de incendio." << endl;
          salida << "\n-> Probabilidad de incendio: \"MEDIA\"\n";
        } 
        else if (velocidad_viento <= 2 && temperatura >= 15 &&
                   temperatura < 25 && condicion_meteorologica == "Soleado") {
          cout << "\nCon la temperatura de " << temperatura
               << "C°, la velocidad del viento " << velocidad_viento
               << ",y la condicion meterologica "
               << "(" << condicion_meteorologica << ")" << endl;
          cout << "Probabilidad de incendio: BAJA." << endl;
          cout << "No hay probabilidad de incendio." << endl;
          salida << "\n-> Probabilidad de incendio: \"BAJA\"\n";
        } 
        else {cout << "\nCon la temperatura de " << temperatura
               << "C°, la velocidad del viento " << velocidad_viento
               << ",y la condicion meterologica "
               << "(" << condicion_meteorologica << ")"
               << "\nNo hay información suficiente para hacer una deduccion "
                  "sobre la probabilidad de incendio."
               << endl;
          salida << "\n-> Probabilidad de incendio: \"N/A\"\n";
        }
        salida << "Velocidad del viento:\n"
               << velocidad_viento << " km/h\nTemperatura:\n"
               << temperatura << endl
               << endl;
        salida.close();
      }
    }
    if(!fechaEncontrada){
      cout << "Fecha no encontrada" << endl;
    }
  }  
}

// Función para calcular la probabilidad de tormenta

void probabilidad_tormenta() {
  string fecha;
  string texto;
  string fecha1;
  string condicion_meteorologica;
  int presion_atmosferica;
  float humedad;

  cout << "Ingrese una fecha cualquiera con el siguiente formato "
          "(ano-mes-dia):\n";
  getline(cin, fecha);

  ifstream datos("datos_meteorologicos.txt");
  if (!datos.is_open()) {
    cout << "Error al abrir el archivo de datos meteorológicos" << endl;
    return;
  }

  bool datos_encontrados = false;
  while (getline(datos, texto)) {
    istringstream ss(texto);
    ss >> fecha1;
    if (fecha == fecha1) {
      ss >> humedad >> humedad >> presion_atmosferica >> presion_atmosferica >>
          condicion_meteorologica;

      // Se llama a la función para calcular la probabilidad de tormenta
      ofstream salida("salida.txt", ios::app);
      if (!salida.is_open()) {
        cout << "Error al abrir el archivo de salida" << endl;
        return;
      }

      if (presion_atmosferica >= 1010 &&
          condicion_meteorologica == "Lluvioso" && humedad >= 70) {
        cout << "Con la presion atmosferica de " << presion_atmosferica
             << " y la humedad de " << humedad
             << "%, y la condicion meteorologica (" << condicion_meteorologica
             << ")" << endl;
        cout << "Hay alta probabilidad de tormenta." << endl;
        salida << "\n-> Probabilidad de tormenta: \"ALTA\"\n";

      } else if (presion_atmosferica <= 1010 &&
                 condicion_meteorologica == "Lluvioso" && humedad >= 70) {
        cout << "Con la presion atmosferica de " << presion_atmosferica
             << " y la humedad de " << humedad
             << "%, y la condicion meteorologica (" << condicion_meteorologica
             << ")" << endl;
        cout << "Existe la probabilidad de lluvia fuerte." << endl;
        salida << "\n-> Probabilidad de tormenta: \"LLUVIA FUERTE\"\n";

      } else {
        cout << "Con la presion atmosferica de " << presion_atmosferica
             << " y la humedad de " << humedad
             << "%, y la condicion meteorologica (" << condicion_meteorologica
             << ")" << endl;
        cout
            << "\nNo hay información suficiente para hacer una deducción sobre "
               "la "
               "probabilidad de tormenta."
            << endl;
        salida << "\n-> Probabilidad de tormenta: \"N/A\"\n";
      }
      salida << "Presion atmosferica: " << presion_atmosferica << " hPa\n"
             << "Humedad: " << humedad << " %\n"
             << endl;
      salida.close();
      datos_encontrados = true;
      break;
    }
  }

  if (!datos_encontrados) {
    cout << "No se encontraron datos para la fecha especificada." << endl;
  }
}

// Funcion para preguntar al usuario si desea continuar
bool continuar_programa() {
  string respuesta;
  bool terminar = true;
  bool salida = true;
  cout << "\n¿Desea continuar con el programa? (S/N): ";
  while (terminar) {
    getline(cin, respuesta);
    if (respuesta != "S" && respuesta != "N") {
      cout << "Opcion no valida, por favor ingrese una opcion valida, (S/N): ";
    } else
      terminar = false;
    if (respuesta == "N") {
      salida = false;
    }
  }
  return salida;
}

int main() {
  bool si = true;
  char decision;
  crearBin();
  string usuario;
  // iniciar sesion o registrar usuario
  cout << "\t\t¡Bienvenid@ al programa de prediccion meteorologica! \n" << endl;
  cout << "¿Desea iniciar sesion o registrarse dentro del programa? \n(en caso "
          "de iniciar sesion introduzca 1, si desea registrarse introduzca 2): "
       << endl;

  while (si) {
    cin >> decision;
    if (decision != '1' && decision != '2') {
      cout << "Opcion no valida, por favor elija 1 o 2\n";
    } else
      break;
  }
  // inicio de sesion
  if (decision == '1') {
    iniciarSesion(usuario);
  }
  // registrar usuario
  else {
    registrar();
    iniciarSesion(usuario);
  }
  crearTxt(usuario);
  // menu
  bool terminar = true;
  while (terminar) {

    // Mostrar menú y obtener la opción del usuario
    char opcion = menu();
    cin.ignore();
    // Realizar la opción elegida por el usuario
    switch (opcion) {
    case '1':
      agregar_lineas_archivo();
      break;
    case '2':
      mayorTemp();
      break;
    case '3':
      menorTemp();
      break;
    case '4':
      promedioTempMes();
      break;
    case '5':
      mayorPromedioHumedad();
      break;
    case '6':
      menorPromedioHumedad();
      break;
    case '7':
      probabilidad_incendio();
      break;
    case '8':
      probabilidad_tormenta();
      break;

    default:
      cout << "Opcion invalida. Por favor, intentelo de nuevo." << endl;
    }

    if (!continuar_programa()) {
      terminar = false;
      cout << "\nGracias por utilizar el programa meteorologico. ¡Hasta luego "
              ":)!"
           << endl;

      cout << "\n Nota: usted encontrara el archivo salida.txt' con todas las "
              "operaciones que realizo en el programa."
           << endl;
    }
  }
  return 0;
}
