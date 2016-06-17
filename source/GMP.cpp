/*
GMP.cpp
Copyright (C) <2016> <Carlos Andres Garnica Salazar>
El software GMP (Gestión y Manejo de Parqueaderos) es un software el cual va a permitir
a los administradores de los establecimientos de parqueaderos tener una herramienta util, 
la cual podrán tener lso datos en tiempo real de lo que pasa en sus aparcamientos.

Este software se ofrece sin ningún tipo de garantía implícita o explicita y el autor, autores, o colaboradores, 
no se hacen responsables por los daños que puedan ocasionarse producto del uso debido o indebido que se le pueda dar. 
Este programa es software libre, además no comercial y se distribuye bajo la Licencia Pública General Reducida de GNU y la 
Licencia Pública General de GNU, ambas licencias con la versión 3; que puede encontrar. 
en <http://www.gnu.org/licenses/>.

*/



#include <iostream>//ENTRADA Y SALIDA DE LA CONSOLA - CIN Y COUT
#include <string.h>//CREACION DE CADENAS STRING
#include <windows.h>//USO PARA LA FUNCION DE COLOR DE LA CONSOLA, REDIMENSION DE LA CONSOLA, Y OTROS
#include <stdio.h>//USO PARA FFLUSH
#include <stdlib.h>//USO DEL SYSTEM
#include <conio.h>//USO DEL GETCH
#include <ctime>//IMPRIMIR EL TIEMPO DEL SISTEMA, CREACION DEL CRONOMETRO
#include <fstream>//USO PARA LECTURA Y ESCRITURA DE ARCHIVOS
#include <direct.h>//USO DEL MKDIR

//Colores de hexadecimal a decimal en fondo negro, usarlos luego en la funcion void color(int x), y luego desde cualquier funcion con color(X).
#define Color_Rojo 12
#define Color_Defecto 15
#define Color_Amarillo 14
#define Color_Verde 10
#define Color_Azul 9
#define Color_Aguamarina 11
#define Color_Purpura 14//CORREGIDO EL COLOR PURPURA AL COLOR AMARILLO PARA MEJORAR VISIBILIDAD

//DEFINICIONES PARA ARREGLOS STRUCT AUTOMOVIL
#define arrmarca 20
#define arrplaca 8
#define arrcliente 200
#define arrlugarparking 3
#define arrfEntrada 200

//DEFINICIONES PARA ARREGLOS STRUCT PARQUEADERO
#define arrnombrepar 100
#define arrpropietario 100
#define arrnit
#define arrdireccion 100
#define arrcolumnas 2
#define arrfilas 4

//DEFINICIONES PARA ARREGLO ADMIN
#define arrnombre 200
#define arrclave 20
#define arremail 120
#define arrtelefono 20
#define arrcelular 20

using namespace std;

//Estructura Cuenta de administrador
typedef struct {
	char nick_admin[arrnombre];
	char nombreCompleto[arrnombre];
	char clave_admin[arrclave];
	char email[arremail];
	char telefono[arrtelefono];
	int contadorAdmin;
	char celular[arrcelular];

}administrador;
administrador * admin = new administrador[100];

//Estructura Asistente de Configuracion
typedef struct {
	//DATOS DEL PARQUEADERO
	char nombre_parqueadero[arrnombrepar];
	char propietario[arrpropietario];
	char nit[arrnit];
	char direccion [arrdireccion];
	//CARACTERISTICAS FISICAS DL PARQUEADERO
	int filas;
	int columnas;
	int pisoParqueadero;
	int tipoParqueadero;
	int tipoPisoParqueadero;
	int espacioParqueoAutos;
	int espacioParqueoMotos;
	//GANACIAS
	int gananciaDia;
	int ActivoInicial;
	int gananciaTotal;
	int ganaciaMes;
	int precioLimiteCarros;
    int precioLimiteMotos;
	//DEMANDA ZONAL
	float demandaZonal;
	//CAPACIDAD MAXIMA DE AUTOS Y MOTOS
	short int max_motos;//MAXIMO DE MOTOS
	short int max_carros;//MAXIMO DE CARROS
}parqueadero;
parqueadero * x= new parqueadero[100];

//Estructura para el registro de automoviles
typedef struct {
	int ticket;
	char marca[arrmarca];
	char placa[arrplaca];
	char cliente[arrcliente];
	char cedula[13];
	int filaparqueadero;
	int columnaparqueadero;
	clock_t tiempoauto;
	char fecha_entrada[arrfEntrada];
	int pico_placa;
	int precio;
	int subtotal;
}automovil;
int maxautos=x[0].max_carros;

//Estructura para el registro de automoviles
typedef struct {
	int ticket;
	char marca[arrmarca];
	char placa[arrplaca];
	char cliente[arrcliente];
	char cedula[13];
	int filaparqueadero;
	int columnaparqueadero;
	clock_t tiempomoto;
	char fecha_entrada[arrfEntrada];
	int precio;
	int subtotal;
}motocicleta;
int maxmotos=x[0].max_motos;

typedef struct{
    float descuentos;
    float impuestos;
}impuesto;

impuesto *ImpuestoVenta = new impuesto[0];

typedef struct{
	char cliente[arrcliente];
	char cedula[13];

}cliFrecuente;

cliFrecuente *clienteFrecuente = new cliFrecuente[100];

//VAR MATRICES
int columna=0,fila=0,columnaMotos=0,columnaAutos=0;

//VAR CONTADORAS
int contClienteFrecuente=0;

//variables booleanas
bool repeticion=true;
//VAR ARREGLOS (ENTRADA MOTOS, CARROS)

int arrauto=0;
int arrmoto=0;

//VARIABLES PARA EL REGISTRO DE AUTO
int filamatriz=-1,columnamatriz=0;
int contador=0;

//VARIABLES PARA EL REGISTRO DE MOTOS
int filamatrizMoto=-1,columnamatrizMoto=0;
int contadorMoto=0, contadorColumna=0;

//variables globales string
string usuario=" ";
char clave[128]=" ";

//FUNCIONES ASISTENTE DE CONFIGURACION
int configurar(int &max_carros);
int asis_configurar(int &max_carros);
void admin_configurar();

//FUNCION LOGUEO
void loguear();

//funciones menu
void menu_auto_gestionar();
void entrar_menu_principal();
void entrar_menu_administrar();
void menu_usuario();

//funciones estéticas
void color(int X);
void escuhar_sonido_de_entrada();
bool AjustarVentana(int Ancho, int Alto);

//funciones de menu principal
void entrar_usuario();
void administrar(automovil *carro, motocicleta *moto, int **matriz, int **matrizmoto, int fila, int columna);
//REGISTRO DE VEHICULOS Y AUTOS
void auto_registrar(automovil *p, int **matriz, int fila,int columna, int cantidadDeAutos);
void menu_auto_registrar();
void moto_registrar(motocicleta *moto, int **matriz, int fila, int columna, int cantidadmotos, int cantidadDeAutos);
void moto_salir(motocicleta *moto,int cantidadmotos);
void auto_salir(automovil *m, int cantidadautos);
//FUNCION ENCABEZADO
void encabezado();

//FUNCION APARCAMIENTO
int lugar_aparcar(int x,int y,int z, int *t);
char convertir_filaparqueadero(automovil *carro, int x, int bucle);
char convertir_filaparqueadero_moto(motocicleta *m, int x, int bucle);

//FUNCIONES USUARIOS
void mostrarVehiculo(automovil *aut, motocicleta *moto, int cantcarros, int cantmotos, int **matriz, int **matrizmoto,int fila, int columna, int cantidadautos, int cantidadmotos);
void mostrarVehiculoCarro(int cantcarros, automovil *aut, motocicleta *moto, int **matriz, int fila, int columna, int cantidadautos);
void mostrarVehiculoMoto(int cantcarros, motocicleta *moto, int **matriz, int fila, int columna, int cantidadmotos);

//FUNCION RECORRER USUARIOS
bool recorrerCadena(char cadena[], int tipoCadena);

//FUNCIONES DEMANDA ZONAL
void DemandaZonalCarros();
void DemandaZonalMotos();

//CLIENTE FRECUENTE
void VerClienteFrecuente();

//FUNCIONES DE ADMINISTRAR
void administrar(automovil *carro, motocicleta *moto, int **matriz, int **matrizmoto, int fila, int columna);
void GenerarInforme(automovil *carro, motocicleta *moto, int **matriz, int **matrizmoto, int fila, int columna);
void AgregarAdministrador();
void AgregarClienteFrecuente();
void FlujoCaja(automovil *carro, motocicleta *moto);
void reiniciar(automovil *carro, motocicleta *moto);
void ReiniciarDia(automovil *carro , motocicleta *moto);
void ReiniciarTotal(automovil *carro, motocicleta *moto);
void ReiniciarAyuda();
void BorrarArchivos();
void VerificarArchivos();
void modificarInformacionParqueadero();
void modificarUsuario();

//FUNCION ACERCA DE - MUESTRA LA INFORMACION DEL SOFTWARE
void AcercaDe();


//FUNCIONES LECTURA ARCHIVOS
void leerArchivos(automovil *carro,  motocicleta *moto, int cantidadMotos, int cantidadAutos);
void escribirArchivos(automovil *carro,  motocicleta *moto, int cantidadMotos, int cantidadAutos);




void salir();

int main(){
    //VARIABLES BADERA
	bool limpiar=true;
	int zx=1;

	//VARIABLES PARA LA SELECCION DE MENU
	int opc=-1;
	int opc2=-1;
	int opc3=-1;
	int cont=0;
	int contparcial=0;

	//VARIABLES PARA EL AJUSTE DE LA VENTANA
	int ancho=0, alto=0;

	//VARIABLES PARA FILAS Y COLUMNAS
	int filamain=0,miColumna=0,columna=0;

	//VARIABLES DONDE SE GUARDARA LA CANTIDAD DE AUTOS Y MOTOS
	int cantidadDeCarros=0,cantidadDeMotos=0;
	//PARTE COMETADA, DESHABILITABA EL ALMACENAMIENTO DE LETRAS EN LA CONSOLA (DESHABILITABA LA BARRA DE DESPLAZAMIENTO)
	//AJUSTE DE LA VENTANA
    //ancho = GetSystemMetrics(SM_CXSCREEN);
    //alto = GetSystemMetrics(SM_CYSCREEN);

    /*if(ancho>=1360&&alto>=768){//SI LA RESOLUCION ES MAYOR O IGUAL A 1360X768
    	AjustarVentana(170, 58);
	}else{//SI LA RESOLUCION ES MENOR A 1360X768
		AjustarVentana(150, 50);
	}
    */

	//ciclo para limpiar toda la estructura de la estructura automovil
	/*memset es una función que llena toda una sección de memoria que quieras,
	con el valor que quieras, en este caso, cero.*/
	
	
	//FORMATEO DE LAS ESTRUCTURAS DE ADMINISTRADOR, PARQUEADERO, IMPUESTO Y CLIFRECUENTE
	memset(admin, 0,sizeof(administrador));
	memset(x, 0,sizeof(parqueadero));
	memset(ImpuestoVenta, 0, sizeof(impuesto));
	memset(clienteFrecuente, 0, sizeof(cliFrecuente));


	//INCIO DEL PROGRAMA
	
	//LECTURA DE ARCHIVOS. SI LOS ARCHIVOS ESTÁN, LA APRTE DEL ASISTENTE DE CONFIGURACION NO SE EJECUTARÁ, SI NO ESTÁN, SE EJECUTARÁ
	ifstream verificacionAsistente;
	verificacionAsistente.open("parqueadero.dat", ios::in|ios::binary);
	if(verificacionAsistente.is_open()){
        fstream leerAdmin("admin.dat", ios::in| ios::binary);
        if(leerAdmin.is_open()){
            leerAdmin.read((char*)admin, 100*sizeof(administrador));
            verificacionAsistente.read((char*)x, 100*sizeof(parqueadero));
        }
        leerAdmin.close();
        verificacionAsistente.close();
        loguear();
	}else{
        cantidadDeMotos=configurar(cantidadDeCarros);
        fstream leerAsis("parqueadero.dat", ios::in|ios::binary);
        if(leerAsis.is_open()){
            leerAsis.read((char*)x, 100*sizeof(parqueadero));
        }
        leerAsis.close();

        ofstream VarAutosMotos;
        VarAutosMotos.open("varCantidad.txt", ios::out);
        if(VarAutosMotos.is_open()){
        	VarAutosMotos<<cantidadDeCarros<<" ";
        	VarAutosMotos<<cantidadDeMotos<<" ";
        	VarAutosMotos<<x[0].filas<<" ";
        	VarAutosMotos<<fila<<" ";
		}
		VarAutosMotos.close();
        loguear();

	}

	//LECTURA DEL ARCHIVO Y CARGA DE LOS VALORES DE LAS VARIABLES DE ESE ARCHIVO A LAS DEL PROGRAMA
	ifstream leerVarAutosMotos;
	leerVarAutosMotos.open("varCantidad.txt", ios::in);
	if(leerVarAutosMotos.is_open()){
		leerVarAutosMotos>>cantidadDeCarros;
		leerVarAutosMotos>>cantidadDeMotos;
	 	leerVarAutosMotos>>x[0].filas;
        leerVarAutosMotos>>fila;
		leerVarAutosMotos>>cantidadDeCarros;
		leerVarAutosMotos.close();
	}
	//RE-DENOMINACIÓN DE LAS ESTRUCTURAS, CREACIÓN Y ASIGNACIÓN POR MEMORIA DINÁMICA
    automovil * carro = new automovil[cantidadDeCarros];
    motocicleta * mot = new motocicleta[cantidadDeMotos];
    //LIMPIEZA DE LAS ESTRUCTURAS AUTOMOVIL Y MOTICICLETA
    memset(carro, 0, sizeof(automovil));
	memset(mot, 0, sizeof(motocicleta));

	//PASAR CONFIGURACIONES DESDE FICHEROS A VARIABLES DEL PROGRAMA
	leerArchivos(carro,mot,cantidadDeMotos,cantidadDeCarros);
	
	//ESCRITURA DE LAS ESTRUCTURAS PARQUEADERO Y ADMINISTRADOR A LOS ARCHIVOS CORRESPONDIENTES
    fstream escrituraAdministrador("admin.dat", ios::binary|ios::out);
    if(escrituraAdministrador.is_open()){
        escrituraAdministrador.write((char*)admin, 100*sizeof(administrador));
        escrituraAdministrador.close();
    }

	//PASO POR DIRECIÓN DE LA VARIABLE miColumna.
	filamain=lugar_aparcar(x[0].filas,x[0].columnas,0,&miColumna);
	columna=x[0].columnas;
	fila=x[0].filas=fila;
	
	//CONTPARCIAL ES LA VARIABLE DE ACUMULADORA CONTROLADORA DEL CICLO.
	//CICLO QUE AYUDA A CONTROLAR LOS LUGARES DE APARCAMIENTO.
	//CUANDO I SEA IGUAL A FILA, ACTUA A ACUMULADORA CONTMOTOS, E I VUELVE A 0.
	//ESTO ES PARA HACER LA DIVISION DE LA MATRIZ DE LOS LUGARES DE APARCAMIENTO
	for(int i=0;contparcial<=cantidadDeCarros;i++){
		contparcial++;
		if(i==fila){
			columnaMotos++;
			i=0;
		}
	}
	columnaAutos=columnaMotos;
	columnaMotos=columna-columnaMotos;
	Sleep(150);
	
	//DIVISIONES DE LAS MATRICES
	//DECLARACION MATRIZ DONDE SE IMPRIMIRA EL APARCAMIENTO
	int**aparcamientos = new int*[fila];

    for (int i = 0; i<fila; i++){
        aparcamientos[i] = new int[columnaAutos];
    }

	for(int i=0;i<fila;i++){
		for(int j=0;j<columnaAutos;j++){
			aparcamientos[i][j]=0;
		}
	}

	Sleep(200);
	
	//MATRIZ PARA LUGARES DE APARCAMIENTO DE MOTOS
	int **aparcamientoMotos = new int *[fila];
	for (int i=0;i<fila;i++){
		aparcamientoMotos[i]= new int [columnaMotos];
	}
	for(int i=0;i<fila;i++){
		for(int j=0;j<columnaMotos;j++){
			aparcamientoMotos[i][j]=0;
		}
	}
	//CREACION DE DIRECTORIOS
	//NECESARIO PARA GUARDAR DATOS DEL PROGRAMA
	mkdir("usuario");
	mkdir("logs");
	mkdir("info");



	do{
		entrar_menu_principal();
		cin>>opc;
		switch(opc){
			//GESTION DE VEHICULOS
			case 1:

				do{
					menu_auto_gestionar();
					cin>>opc2;
					switch (opc2){
						case 1:
							auto_registrar(carro,aparcamientos,filamain,columna, cantidadDeCarros);//REGISTRO DE UN AUTO DE INGRESO AL PARQUEADERO
							break;
						case 2:
							moto_registrar(mot,aparcamientoMotos,filamain,columna, cantidadDeMotos,cantidadDeCarros);//REGISTRO DE UNA MOTO DE INGRESO AL PARQUEADERO
							break;
						case 3:
							auto_salir(carro,cantidadDeCarros);//IMPRESION DEL RECIBO Y SALIR UN AUTO
							break;
						case 4:
							moto_salir(mot,cantidadDeMotos);//IMPRESION DE RECIBO Y SALIR DE UN AUTO
                            break;
						case 5:
							break;
						default:
							cout<<"Ingrese una opcion correcta"<<endl;
							system("pause");
					}
				}while(opc2!=5);
				break;
			//USUARIOS
			case 2:
				do{
					menu_usuario();
					cin>>opc3;
					switch(opc3){
						case 1:
							mostrarVehiculo(carro, mot, cantidadDeCarros, cantidadDeMotos, aparcamientos,aparcamientoMotos , filamain,columna, cantidadDeCarros, cantidadDeMotos);//MUESTRA EL ESTADO DEL PARQUEADERO PARA CATTOS Y MOTOS
							break;
						case 2:
							break;
						case 3:
							VerClienteFrecuente();
							break;
						case 4:
							break;
						default:
							cout<<"Ingrese una opcion valida..."<<endl;
							system("pause");
							break;
					}
				}while(opc3!=4);

				break;
			//PANEL DE ADMINISTRACION
			case 3:
				administrar(carro,mot,aparcamientos, aparcamientoMotos,fila,columna);
				break;
			//SALIR
			case 4:
				AcercaDe();
				break;
			case 5:
				salir();
				break;
			default:
				cout<<"Ingrese un valor valido."<<endl;
				system("pause");

		}
	}while(opc!=5);

	return 0;
}
//FUNCION ASISTENTE DE CONFIGURACION
int configurar(int &maxcarros){
	char decision='\0';
	int maxmotos;


	color(Color_Defecto);
	system("cls");
	encabezado();
	cout<<endl;
	color(Color_Rojo);
	//TERMINOS Y CONDICIONES
	cout<<"\tBienvenido al mejor software de parqueaderos para su establecimiento..."<<endl;
	cout<<"A continuacion lo ayudaremos a configurar este software ingresando datos basicos sobre su parqueadero."<<endl;
	cout<<"Copyright (C) <2016> <Carlos Andres Garnica Salazar>"<<endl;
	cout<<"ACUERDO DE LICENCIA: "<<endl;
	cout<<"Este software se ofrece sin ningún tipo de garantía implícita o explicita y el autor, autores, o colaboradores, ";
	cout<<"Este programa es software libre, además no comercial y se distribuye bajo la Licencia Pública General Reducida de GNU y la ";
	cout<<"Licencia Pública General de GNU, ambas licencias con la versión 3; que puede encontrar. ";
	cout<<"en <http://www.gnu.org/licenses/>.";
	cout<<"El programa le pedira datos basicos de los administradores, empleados y clientes de su establecimiento. Aun asi, este software ";
	cout<<"no difundira sus datos a ninguna persona. \nEsos datos se guardan en archivos legibles en su computador donde esta ejecutando este ";
	cout<<"software."<<endl;
	cout<<"Este programa sigue las normas de parqueadero del Distrito de Bogota D.C. Por lo tanto, el programa le asignara un valor maximo ";
	cout<<"dependiendo de como sea su establecimiento. \nEstos valores son dados por los Decretos 474,550 y concepto 3810 de 2015, por el cual ";
	cout<<"el distrito vigila y controla las tarifas maximas de los establecimientos, asi mismo como impuestos, los cuales en la actualidad no \n";
	cout<<"aplican. Aun asi, usted como administrador, puede elegir un valor para su parqueadero inferior al permitido por el Distrito"<<endl;

	color(Color_Verde);
	//CICLO BANDERA PARA REPETIR EN CASO DE QUE EL USUARIO INGRESE MAL UNA OPCION
	while(repeticion){
        color(Color_Verde);
		cout<<"Si esta de acuerdo, presione S, de lo contrario presione N"<<endl;
		cin>>decision;
		color(Color_Defecto);
		if(decision=='S'||decision=='s'){
			cout<<"Has aceptado los terminos y condiciones"<<endl;
			system("pause");
			system("cls");
			maxmotos=asis_configurar(maxcarros);
			admin_configurar();
			system("cls");
			cout<<"Espere mientras se guarda la configuracion..."<<endl;
			Sleep(1200);
			cout<<"La configuracion se ha guardado con exito. "<<endl;
			cout<<"Presione una tecla para continuar..."<<endl;
			getch();
			repeticion=false;
		}else if(decision=='n'||decision=='N'){
			for(int i=10;i>=0;i--){
				cout<<"No has aceptado los terminos y condiciones."<<endl;
				cout<<"El programa se va a cerrar en "<<i<<" segundos"<<endl;
				Sleep(1000);
				system("cls");
			}
			repeticion=false;
			salir();
		}else {
		    cout<<"Ingrese un valor correcto"<<endl;
		    system("pause");
            repeticion=true;
		}
	}
	return maxmotos;
}
void entrar_menu_principal(){
	color(Color_Defecto);//Usando la funcion void color(int x), donde X es el numero decimal del color, convertido desde hexadecimal.
	system("cls");
	encabezado();
	cout<<endl;
	cout<<"                                                                       "<<endl;
    cout<<"      (1) GESTION DE VEHICULOS           ||     ||  ||     ||   ||||||||  "<<endl;
    cout<<"      (2) USUARIOS                       ||     ||  ||     ||   ||        "<<endl;
    cout<<"      (3) PANEL DE ADMINISTRACION        ||     ||  ||     ||   ||        "<<endl;
    cout<<"      (4) ACERCA DE...                   ||     ||  ||     ||   ||        "<<endl;
    cout<<"      (5) SALIR                          ||     ||  ||     ||   ||        "<<endl;
	cout<<"                                         ||     ||  ||     ||   ||        "<<endl;
    cout<<"                                         |||||||||  |||||||||   ||||||||  "<<endl;
	color(Color_Rojo);
	cout<<"\n				                	"<<x[0].nombre_parqueadero<<endl;
	escuhar_sonido_de_entrada();
	color(Color_Verde);
	cout<<"OPCION>>      ";
}

void entrar_menu_administrar(){
	system("cls");
	encabezado();
	color(Color_Verde);
	cout<<"\t\t\t<--------------- PANEL DE ADMINISTRACION ---------------->"<<endl;
	cout<<"\t\t(1) Generar Informe del parqueadero                         "<<endl;
	cout<<"\t\t(2) Modificar la informacion del parqueadero                "<<endl;
	cout<<"\t\t(3) Flujo de caja                                           "<<endl;
	cout<<"\t\t(4) Cambiar usuario y contraseña	                           "<<endl;
	cout<<"\t\t(5) Agregar nuevo usuario de administrador o empleado       "<<endl;
	cout<<"\t\t(6) Agregar Cliente Frecuente                               "<<endl;
	cout<<"\t\t(7) Ver clientes apartados                                  "<<endl;
	cout<<"\t\t(8) Verificar la condicion de los archivos del software     "<<endl;
	cout<<"\t\t(9) Reiniciar el sistema                                    "<<endl;
	cout<<"\t\t(10) Regresar al menu principal                              "<<endl;
	cout<<endl;
	cout<<"\t\tOPCION>>      ";
}

void menu_auto_gestionar(){
	system("cls");
	encabezado();
	color(Color_Verde);
	cout<<"\t\t<--------------- Menu de gestion de vehiculos del parking ----------------->			  "<<endl;
	cout<<endl;
	cout<<"\t\t(1) Registrar auto entrante"<<endl;
	cout<<"\t\t(2) Registrar motocicleta entrante"<<endl;
	cout<<"\t\t(3) Acabar tiempo del auto saliente"<<endl;
	cout<<"\t\t(4) Acabar tiempo de motocicleta saliente"<<endl;
	cout<<"\t\t(5) Regresar al menu principal"<<endl;
	cout<<"OPCION>>		";
}
void menu_usuario(){
    system("cls");
	encabezado();
	color(Color_Amarillo);
	cout<<"------------------------------------------------------"<<endl;
	cout<<"\t\t(1) Vehiculos y motos en este momento"<<endl;
	cout<<"\t\t(2) Apartar un lugar en el parqueadero"<<endl;
	cout<<"\t\t(3) Buscar clientes frecuentes"<<endl;
	cout<<"\t\t(4) Volver al menu principal"<<endl;
	cout<<"OPCION>>      ";
}


int asis_configurar(int &max_carros){
	int miColumnas;
	bool seguir=false, verificacion=false, seguir2=false;
	char opcNum[10];
	int opc=-1;
    encabezado();
	color(Color_Amarillo);
	cout<<"\t\t----------------------------------------------------------------------------	"<<endl;
	cout<<"\t\t\t<<<<<<<<<<< ASISTENTE DE CONFIGURACION >>>>>>>>>>>>>                          "<<endl;
	cout<<"\t\t----------------------------------------------------------------------------	"<<endl;
    fstream escrituraParqueadero("parqueadero.dat", ios::out|ios::binary);
    if(escrituraParqueadero.is_open()){
        cout<<"Ingrese el Nombre del Parqueadero: ";
        fflush(stdin);
        cin.getline(x[0].nombre_parqueadero,arrnombrepar);
        do{
            cout<<"Ingrese el nombre completo del propietario: ";
            fflush(stdin);
            cin.getline(x[0].propietario,arrpropietario);
            verificacion=recorrerCadena(x[0].propietario, 1);//EN EL SEGUNDO PARAMETRO DEFINE SI EL CARACTER TIENE QUE SER NUMEROS SOLAMENTE O LETRAS SOLAMENTE
        }while(verificacion);                                //ESTE PARAMEMETRO ES int TipoCadena. 1 ES PARA SOLAMENTE LETRAS, 0 ES PARA NUMEROS SOLAMENTE
        verificacion=false;

        do{
            cout<<"Ingrese el nit de su establecimiento: ";
            fflush(stdin);
            cin>>x[0].nit;
            verificacion=recorrerCadena(x[0].nit, 0);
        }while(verificacion);
        verificacion=false;



        cout<<"Ingrese la direccion de su establecimiento: ";
        fflush(stdin);
        cin.getline(x[0].direccion,arrdireccion);

        system("pause");
        system("cls");
        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\tELECCION DE LA DEMANDA ZONAL"<<endl;
                cout<<"\t1. USAQUEN                 "<<endl;
                cout<<"\t2. CHAPINERO               "<<endl;
                cout<<"\t3. SANTA FE                "<<endl;
                cout<<"\t4. SAN CRISTOBAL           "<<endl;
                cout<<"\t5. USME                    "<<endl;
                cout<<"\t6. TUNJUELITO              "<<endl;
                cout<<"\t7. BOSA                    "<<endl;
                cout<<"\t8. KENNEDY                 "<<endl;
                cout<<"\t9. FONTIBON                "<<endl;
                cout<<"\t10. ENGATIVA               "<<endl;
                cout<<"\t11. SUBA                   "<<endl;
                cout<<"\t12. BARRIOS UNIDOS         "<<endl;
                cout<<"\t13. TEUSAQUILLO            "<<endl;
                cout<<"\t14. LOS MARTIRES           "<<endl;
                cout<<"\t15. ANTONIO NARINIO        "<<endl;
                cout<<"\t16. PUENTE ARANDA          "<<endl;
                cout<<"\t17. LA CANDELARIA          "<<endl;
                cout<<"\t18. RAFAEL URIBE URIBE     "<<endl;
                cout<<"\t19. CIUDAD BOLIVAR         "<<endl;
                cout<<"\t20. SUMAPAZ                "<<endl;
                cout<<"OPCION:  ";
                cin>>opcNum;

                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);

            verificacion=false;
            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }
            switch(opc){
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 16:
                case 18:
                case 19:
                case 20:
                    x[0].demandaZonal=0.8;
                    break;
                case 1:
                case 2:
                case 3:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    x[0].demandaZonal=1;
                    break;
                default:
                    cout<<"Ingrese un valor correcto"<<endl;
                    system("pause");
                    seguir=true;
            }
        }while(seguir);


        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\tELECCION DEL PISOS DEL PARQUEADERO"<<endl;
                cout<<"\t1. A NIVEL"<<endl;
                cout<<"\t2. SUBTERRANEO"<<endl;
                cout<<"\t3. 1 PISO"<<endl;
                cout<<"\t4. 2 PISOS"<<endl;
                cout<<"\t5. 3 PISOS"<<endl;
                cout<<"\t6. 4 O MAS PISOS"<<endl;
                cout<<"OPCION:  ";
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);

            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }
            if(opc>6||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].pisoParqueadero=opc;
                seguir=false;
            }
        }while(seguir);


        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\t\tELECCION DEL TIPO DE PARQUEADERO"<<endl;
                cout<<"\t1. PARQUEADERO CUBIERTO"<<endl;
                cout<<"\t2. PARQUEADERO ABUERTO"<<endl;
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum , "%d", &opc);
            }

            if(opc>2||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].tipoParqueadero=opc;
                seguir=false;
            }
        }while(seguir);

        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\t\tELECCION TIPO DE PISO DEL PARQUEADERO"<<endl;
                cout<<"\t1. PISO EN ASFALTO"<<endl;
                cout<<"\t2. PISO EN CONCRETO"<<endl;
                cout<<"\t3. PISO EN GRAVILLA"<<endl;
                cout<<"\t4. PISO EN CESPED"<<endl;
                cout<<"\t5. PISO EN AFIRMADO"<<endl;
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);

            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }

            if(opc>5||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].tipoPisoParqueadero=opc;
                seguir=false;
            }
            system("pause");
            system("cls");
        }while(seguir);

        DemandaZonalCarros();
        DemandaZonalMotos();
        do{
            color(Color_Rojo);
            cout<<"OJO: La multiplicación de las filas y las columnas de su parqueadero deben coincidir con la sumatoria del maximo de autos y moticicletas."<<endl<<endl;
            color(Color_Amarillo);

            do{
                cout<<"Cuantas filas de aparcamientos tiene su establecimiento?: ";
                fflush(stdin);
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum,"%d",&fila);
                x[0].filas=fila;
            }

            do{
                cout<<"Cuantas columnas de aparcamientos tiene su establecimiento?: ";
                fflush(stdin);
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum, 0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &columna);
                x[0].columnas=columna;
            }



            lugar_aparcar(fila,columna,0,&miColumnas);

            do{
                do{
                    cout<<"Ingrese la cantidad de carros que soporta su estacionamiento. Con autos cuente particulares, camiones, SUVs, entre otros. "<<endl;
                    cout<<"La cantidad de carros debe ser mínimo de 20 AUTOS: ";
                    fflush(stdin);
                    cin>>opcNum;//x[0].max_carros;
                    verificacion=recorrerCadena(opcNum,0);

                }while(verificacion);
                verificacion=false;

                if(!verificacion){
                    sscanf(opcNum, "%d", &x[0].max_carros);
                }
                if(x[0].max_carros<20){
                    cout<<"Recuerde que la cantidad mínima de autos es de 20..."<<endl<<endl;
                    seguir=true;
                }else{
                    max_carros=x[0].max_carros;
                    seguir=false;
                }
            }while(seguir);

            do{
                cout<<"Ingrese la cantidad de motocicletas que soporta su establecimiento. ";
                cout<<"La cantidad de motocicletas debe ser mínimo de 10 motocicletas: ";
                fflush(stdin);
                cin>>x[0].max_motos;

                if(x[0].max_motos<10){
                    cout<<"Recuerde que la cantidad mínima de motocicletas es de 10..."<<endl;
                }else{
                    seguir=false;
                }

            }while(seguir);

            if((x[0].max_motos+x[0].max_carros)!=(x[0].filas*x[0].columnas)){
                cout<<"La multiplicacion de las filas y columnas del parqueadero no coincide con la sumatoria de numero de autos y motos."<<endl<<endl;
                seguir2=true;
            }else{
                seguir2=false;
            }
        }while(seguir2);
        escrituraParqueadero.write((char*)x, 100*sizeof(parqueadero));

    }
    escrituraParqueadero.close();
	cout<<"Presione una tecla para seguir con la configuracion..."<<endl;
	getch();
	escrituraParqueadero.close();

	return x[0].max_motos;
}

void admin_configurar(){
	system("cls");
	color(Color_Verde);
	bool verificacion=false;

	cout<<"\t\t----------------------------------------------------------------------------	"<<endl;
	cout<<"\t\t\t<<<<<<<<<<< ASISTENTE DE CONFIGURACION >>>>>>>>>>>>>                          "<<endl;
	encabezado();
	cout<<endl;
	cout<<"Ahora empezara el asistente de configuracion para el usuario administrador."<<endl;
	cout<<"Te pediremos datos basicos, es recomendable que antes de empezar leas bien los campos."<<endl;
	cout<<endl;

	cout<<"Ingrese el nuevo usuario de administrador. Recuerde que el usuario no debe tener espacios: ";
	fflush(stdin);
	cin>>admin[0].nick_admin;

	cout<<"Ingrese una nueva contrase¤a de administrador: ";
	fflush(stdin);
	cin>>admin[0].clave_admin;//AGREGAR CLAVE CON ASTERISCOS DESPUES

	cout<<"Ingrese su email: ";
	fflush(stdin);
	cin>>admin[0].email;

	do{
		cout<<"Ingrese un telefono fijo de contacto, en caso de no tener telefono ponga el de su celular: ";
		fflush(stdin);
		cin>>admin[0].telefono;
		verificacion=recorrerCadena(admin[0].telefono,0);
	}while(verificacion);
	verificacion=false;

	do{
		cout<<"Ingrese un numero de celular, en caso de no tener ingrese un telefono fijo o rellene de cualquier valor: ";
		fflush(stdin);
		cin>>admin[0].celular;
		verificacion=recorrerCadena(admin[0].celular,0);
	}while(verificacion);


	cout<<"Espere procesamos la informacion..."<<endl;

	Sleep(512);

	cout<<"Nuevo usuario creado con exito."<<endl;
	cout<<"Presione una tecla para terminar la configuracion...";
	getch();
}

//funciones estéticas
void color(int X) //funcion creada para aplicar color
{
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}
void escuhar_sonido_de_entrada(){

    Beep(523,500);
    Beep(587,500);
    Beep(659,500);
    Beep(698,500);
    Beep(784,500);

}
//funcion logueo
void loguear(){

	repeticion=false;
	bool error=false;
	system("cls");


	do{
		system("cls");
		color(Color_Defecto);
    	cout<<"\t\t----------------------------------------------------------------------	        "<<endl;
		cout<<"\t\t\t<<<<<<<<<<< LOGUEO DE GESTION DE PARQUEADEROS >>>>>>>>>>>>>                    "<<endl;
		cout<<"\t\t----------------------------------------------------------------------	        "<<endl;

		cout<< "NOMBRE: ";
	    fflush(stdin);
	    getline(cin,usuario);

	    cout<< "CONTRASENA: ";
		for (int i = 0; i < 128; i++) {
			clave[i] = getch();

			cout.flush();
			if (clave[i] == '\r') {
				clave[i] = 0;
				break;
			}
			cout << "*";
		}
		cout<<endl;
		for(int i=0;i<100;i++){
			if (!strcmp(clave, admin[i].clave_admin)) {
				if(usuario==admin[i].nick_admin){
					cout << "Usuario y clave correctos!!"<<endl;
					system("pause");
					error=false;
					break;
				}

			}else{
				cout << "Usuario o clave son incorrectos!!"<<endl;
				error=true;
				system("pause");
				break;
			}
		}
	}while(error);
}
//REGISTRO DE VEHICULOS Y AUTOS
void auto_registrar(automovil *p, int **matriz, int fila,int columna, int cantidadDeAutos){
	//DATO BOOLEANO, NO TOCAR
	repeticion=false;
	//LIMPIEZA DE LA CONSOLA
	system("cls");
	//Color de la interfaz
	color(Color_Aguamarina);
	//VARIABLES LOCALES

	int miColumna;
	bool seguir=true,continuar=false,repetir=false, verificacion=false;
	char tecla[1];
	char opcion[1];

	//tiempo
	time_t rawtime;
	struct tm *tiempo;
 	int dia;
 	int mes;
 	int anio;

 	time_t fecha_sistema;
 	time(&fecha_sistema);
 	tiempo=localtime(&fecha_sistema);

 	anio=tiempo->tm_year + 1900;
 	mes=tiempo->tm_mon + 1;
 	dia=tiempo->tm_mday;
	//VARIABLES INCIADAS PARA FILAS Y COLUMNAS DE PARQUEADERO
	int filapar_char=0;
	bool cambioValorFila=true;
	encabezado();
	color(Color_Verde);
	cout<<"			<--------------- REGISTRO ENTRANTE DE VEHICULOS  ----------------->			  "<<endl;
	cout<<endl;
	cout<<"Vas a registrar un vehiculo entrante"<<endl;
	system("pause");

	//APERTURA DEL ARCHIVO DE TEXTO
	ifstream leervariables;
	leervariables.open("varauto.txt", ios::in);
    if(leervariables.is_open()){
    	leervariables>>arrauto;
    	leervariables>>filamatriz;
		leervariables>>columnamatriz;
		leervariables>>contador;
	}
	leervariables.close();

	fstream vehiculos("vehiculos.dat", ios::out|ios::app| ios::binary);
	if(vehiculos.is_open()){
		if(arrauto<=cantidadDeAutos){
			do{
				//ARRAUTO ES VAR GLOBAL
				arrauto=arrauto+1;
				//fflush( stdin ) es para limpia el buffer de entrada de datos,
				//sirve para cuando necesita tomar muchos datos seguidos y se generan saltos de línea automáticos que se guardan en este buffer

				system("cls");

				p[arrauto-1].ticket=arrauto;//ID Autogenerado
				cout<<"Ticket: "<<p[arrauto-1].ticket<<endl;


				cout<<"Marca del vehiculo: ";
				fflush(stdin);
				cin.getline(p[arrauto-1].marca, arrmarca);

				cout<<"Placa del vehículo: ";
				fflush(stdin);
				cin.getline(p[arrauto-1].placa, arrplaca);


				int numero=(int)p[arrauto-1].placa[6];
				if(numero%2==0){
					if(dia%2==0){
						p[arrauto-1].pico_placa=1;

					}else{
						if(dia%2!=0){
							p[arrauto-1].pico_placa=0;
						}
					}
				}
				do{
					cout<<"Nombre del cliente/propietario del vehículo: ";
					fflush(stdin);
					cin.getline(p[arrauto-1].cliente, arrcliente);
					verificacion=recorrerCadena(p[arrauto-1].cliente, 1);
				}while(verificacion);
				verificacion=false;

				do{
					cout<<"Cedula de Ciudadania del cliente: ";
					fflush(stdin);
					cin>>p[arrauto-1].cedula;
					verificacion=recorrerCadena(p[arrauto-1].cedula,0);
				}while(verificacion);

				cout<<"Espere..."<<endl;
				Sleep(450);
				system("pause");

				cout<<"Datos Ingresados con Exito."<<endl;
				Sleep(1000);
				do{
					do{
						cout<<"Ahora presiona S para empezar a registrar el tiempo del vehículo y darle paso... ";
						cin>>tecla;
						verificacion=recorrerCadena(tecla,1);
					}while(verificacion);

					verificacion=false;

					for(int i=0;i<1;i++){
						if (tecla[i]=='s'||tecla[i]=='S'){
						seguir=false;
						}
					}

				}while(seguir);
				cout<<endl;

				//GUARDAR LA FECHA EN ESTRUCTURA AUTOMOVIL
				int a1 = time(0);
				tm* tm1 = localtime((const long*)&a1);
				strcpy(p[arrauto-1].fecha_entrada, asctime(tm1));

				cout<<"La fecha de ingreso del vehiculo es "<<p[arrauto-1].fecha_entrada<<endl;
				cout<<"Se empezó a registrar el tiempo del vehículo entrante"<<endl;

				//CRONOMETRO INICIADO
				p[arrauto-1].tiempoauto=clock();


				if(contador!=cantidadDeAutos){

					if(cambioValorFila==false){
						filamatriz=0;
						filapar_char=filamatriz+65;
						columnamatriz=columnamatriz+1;
						matriz[filamatriz][columnamatriz]=1;
						cambioValorFila=true;
					}else{
						filamatriz++;
						filapar_char=filamatriz+65;
						matriz[filamatriz][columnamatriz]=1;
						cambioValorFila=true;
					}
					if(filamatriz==(x[0].filas)-1){
						filamatriz=0;
						cambioValorFila=false;
					}
				}
				p[arrauto-1].filaparqueadero=filamatriz;
				p[arrauto-1].columnaparqueadero=columnamatriz;
				contador++;


				cout<<"El Lugar asignado dentro del parqueadero fue: "<<char(filapar_char)<<"-"<<columnamatriz+1<<endl;
				cout<<endl;


				vehiculos.write((char*)p, cantidadDeAutos*sizeof(automovil));

				do{
					do{
						cout<<"Desea ingresar otro vehiculo (S/N)?: ";
						cin>>opcion;
						verificacion=recorrerCadena(opcion,1);
					}while(verificacion);
					verificacion=false;

					for(int i=0;i<1;i++){

						if(opcion[i]=='s'||opcion[i]=='S'){
							repetir=true;
							continuar=false;
						}else{

							if(opcion[i]=='n'||opcion[i]=='N'){
								vehiculos.close();
								continuar=false;
								repetir=false;
							}
						}

						if(opcion[i]!='S'&&opcion[i]!='s'&&opcion[i]!='N'&&opcion[i]!='n'){
							cout<<"Ingrese un valor correcto, S para continuar y n para no seguir registranado mas vehiculos"<<endl;
							continuar=true;
						}
					}

				}while(continuar);
			}while(repetir);
		}else{
			cout<<"SE HA ALCANZADO EL MAXIMO DE AUTOS REGISTRADOS."<<endl;
			system("pause");
		}
	}else{
		cout<<"No se ha podido abrir el archivo para la ejecicion de las instrucciones."<<endl;
		system("pause");
	}
	vehiculos.close();

	ofstream variables;
	variables.open("varauto.txt",ios::out);
    if(variables.is_open()){
    	variables<<arrauto<<" ";
    	variables<<filamatriz<<" ";
		variables<<columnamatriz<<" ";
		variables<<contador<<" ";
	}
	variables.close();
	system("pause");
}


void moto_registrar(motocicleta *moto, int **matriz, int fila, int columna, int cantidadmotos, int cantidadDeAutos){
	repeticion=false;
	system("cls");
	color(Color_Aguamarina);
	//SEMILLA PARA GENERAR NUMERO ALEATORIO DE TICKET
	srand(time(NULL));

	int ticket_gen;
	int miColumna,filaparqueadero=0,columnaparqueadero=0,filapar_char=0;
	bool seguir=true,todobien=true,repetir=true,continuar=true,verificacion=false;
	char tecla[1];
	char opcion[1];
	bool cambioValorFila=true;

	//tiempo
	time_t rawtime;
	struct tm * timeinfo;
	//estructura automoviles

	encabezado();
	cout<<"			<--------------- REGISTRO ENTRANTE DE MOTOCICLETAS  ----------------->			  "<<endl;
	cout<<endl;
	cout<<"Vas a registrar una motocicleta entrante"<<endl;
	system("pause");

	//APERTURA PARA EL ARCHIVO MOTOS
	fstream motos("motos.dat", ios::out|ios::app|ios::binary);
	if(motos.is_open()){
		if(arrmoto<=cantidadmotos){
			do{
				arrmoto=arrmoto+1;

				//DEFINICION VARIABLES PARA IMPREMIR TIEMPO
		  		time ( &rawtime );
		  		timeinfo = localtime ( &rawtime );
				//fflush( stdin ) es para limpia el buffer de entrada de datos,
				//sirve para cuando necesitas tomar muchos datos seguidos y se generan saltos de línea automáticos que se guardan en este buffer

				system("cls");

				moto[arrmoto-1].ticket=arrmoto;//ID Autogenerado
				cout<<"Ticket: "<<moto[arrmoto-1].ticket<<endl;
				cout<<"Marca del vehiculo: ";
				fflush(stdin);
				cin.getline(moto[arrmoto-1].marca, arrmarca);

				cout<<"Placa del vehículo: ";
				fflush(stdin);
				cin.getline(moto[arrmoto-1].placa, arrplaca);

				do{
					cout<<"Nombre del cliente/propietario del vehículo: ";
					fflush(stdin);
					cin.getline(moto[arrmoto-1].cliente, arrcliente);
					verificacion=recorrerCadena(moto[arrmoto-1].cliente, 1);
				}while(verificacion);
				verificacion=false;

				do{
					cout<<"Cedula de Ciudadania del cliente: ";
					fflush(stdin);
					cin.getline(moto[arrmoto-1].cedula,13);
					verificacion=recorrerCadena(moto[arrmoto-1].cedula, 0);
				}while(verificacion);
				verificacion=false;


				cout<<"Espere..."<<endl;
				Sleep(450);
				system("pause");
				cout<<"Datos Ingresados con Exito."<<endl;
				Sleep(1000);

				do{

					do{
						cout<<"Ahora presiona S para empezar a registrar el tiempo del vehículo y darle paso... ";
						cin>>tecla;
						verificacion=recorrerCadena(tecla, 1);
					}while(verificacion);
					verificacion=false;

					for(int i=0;i<1;i++){
						if (tecla[i]=='s'||tecla[i]=='S'){
							seguir=false;
						}
					}
				}while(seguir);
				cout<<endl;

				int a1 = time(0);
				tm* tm1 = localtime((const long*)&a1);
				strcpy(moto[arrmoto-1].fecha_entrada, asctime(tm1));

				cout<<"La fecha de ingreso del vehiculo es "<<moto[arrmoto-1].fecha_entrada<<endl;
				cout<<"Se empezó a registrar el tiempo del vehículo entrante"<<endl;

				//CRONOMETRO INICIADO
				moto[arrmoto-1].tiempomoto=clock();

				//CONSTRUCCION DE LA MATRIZ
				if(contadorMoto<=cantidadmotos){

					if(cambioValorFila==false){
						filamatrizMoto=0;
						filapar_char=filamatrizMoto+65;
						columnamatrizMoto=columnamatrizMoto+1;
						contadorColumna=contadorColumna+1;
						matriz[filamatrizMoto][columnamatrizMoto]=1;
						cambioValorFila=true;
					}else{
						filamatrizMoto++;
						filapar_char=filamatrizMoto+65;
						matriz[filamatrizMoto][columnamatrizMoto]=1;
						cambioValorFila=true;
					}
					if(filamatrizMoto==(x[0].filas)-1){
						filamatrizMoto=0;
						cambioValorFila=false;
					}
				}
				moto[arrauto-1].filaparqueadero=filamatrizMoto;
				moto[arrauto-1].columnaparqueadero=columnamatrizMoto;
				contadorMoto++;

				cout<<"El Lugar asignado dentro del parqueadero fue: "<<char(filapar_char)<<"-"<<columnaparqueadero+1<<endl;
				cout<<endl;

				motos.write((char*)moto, cantidadmotos*sizeof(motocicleta));
				system("pause");
				do{
					do{
						cout<<"Desea ingresar otro vehiculo (S/N)?: ";
						cin>>opcion;
						verificacion=recorrerCadena(opcion, 1);
					}while(verificacion);
					verificacion=false;

					for(int i=0;i<1;i++){
						if(opcion[i]=='s'||opcion[i]=='S'){
							repetir=true;
							continuar=false;
						}else{
							if(opcion[i]=='n'||opcion[i]=='N'){
								continuar=false;
								repetir=false;
							}
						}
						if(opcion[i]!='S'&&opcion[i]!='s'&&opcion[i]!='N'&&opcion[i]!='n'){
							cout<<"Ingrese un valor correcto, S para continuar y n para no seguir registrnado mas vehiculos"<<endl;
							continuar=true;
						}
					}

				}while(continuar);
			}while(repetir);

		}else{
			cout<<"No se pueden registrar mas vehiculos... SE HA ALCANZADO EL MAXIMO DE VEHICULOS"<<endl;
			system("pause");
		}

	}else{
		cout<<"No se ha podido abrir el archivo para la ejecicion de las instrucciones."<<endl;
	}
	motos.close();

	ofstream variablesmoto;

	variablesmoto.open("varmoto.txt", ios::out);
    if(variablesmoto.is_open()){
        variablesmoto<<arrmoto<<" ";
    	variablesmoto<<filamatrizMoto<<" ";
		variablesmoto<<columnamatrizMoto<<" ";
		variablesmoto<<contadorMoto<<" ";
		variablesmoto<<contadorColumna<<" ";
	}
	variablesmoto.close();
	system("pause");
}

void moto_salir(motocicleta *moto,int cantidadmotos){
	system("cls");
	color(Color_Aguamarina);

	int cast[10];
	struct tm *tiempo;
 	int dia;
 	int mes;
 	int anio;

 	time_t fecha_sistema;
 	time(&fecha_sistema);
 	tiempo=localtime(&fecha_sistema);

 	anio=tiempo->tm_year + 1900;
 	mes=tiempo->tm_mon + 1;
 	dia=tiempo->tm_mday;
 	int filapar_char=0;
 	int hr=0,segundo=0,minuto=0;
 	char placa[arrplaca];
 	char opcion[1];
 	bool verificacion=false, repetir=false;
 	string strdescuento;
	cout<<"Vas dejar salir un auto."<<endl;

	cout<<"Ingrese la PLACA de la moto a salir: ";
	fflush(stdin);
	cin.getline(placa, arrplaca);

	for(int i=0;i<cantidadmotos;i++){
		if(strcmp(moto[i].placa,placa)==0){

			cout<<"Se ha encontrado el carro"<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
			cout<<"INFORMACION DEL AUTOMOVIL: "<<endl;
			cout<<"Ticket: "<<moto[i].ticket<<"\t\t\t*"<<endl;
			cout<<"Marca: "<<moto[i].marca<<"\t\t\t*"<<endl;
			cout<<"Placa: "<<moto[i].placa<<"\t\t\t*"<<endl;
			cout<<"Cliente: "<<moto[i].cliente<<"\t\t\t*"<<endl;
			cout<<"Cedula: "<<moto[i].cedula<<"\t\t\t*"<<endl;

			filapar_char=convertir_filaparqueadero_moto(moto ,65, i);
			cout<<"Lugar de aparcamiento: "<<char(filapar_char)<<"-"<<moto[i].columnaparqueadero<<endl;

			moto[i].tiempomoto=clock()-moto[i].tiempomoto;//Cronometro EN PAUSA
			cout<<"El tiempo en que estuvo su moto fue de: ";//IMPRESION DEL TIEMPO EN SEGUNDOS
            segundo=int(moto[i].tiempomoto)/CLOCKS_PER_SEC;
            hr = segundo / (60*60);
            segundo %= 60*60;
            minuto = segundo / 60;
            segundo %= 60;
            cout << hr << " hora";
            if(hr != 1){
                cout << "s";
            }
            cout << " " << minuto << " minuto";
            if(minuto != 1){
                cout << "s";
            }
            cout << " y " << segundo << " segundo";
            if(segundo != 1){
                cout << "s"<<endl;
            }
            //CALCULO DE LOS PRECIOS DE VENTA
            moto[i].precio=((minuto*x[0].precioLimiteMotos))-ImpuestoVenta[0].descuentos;
            moto[i].subtotal= minuto*x[0].precioLimiteMotos;
            if(ImpuestoVenta[0].descuentos>=1&&ImpuestoVenta[0].impuestos>=0.1){
                strdescuento="Si";
            }else{
                strdescuento="No";
            }

			cout<<"------------------------------------------------------------------------------------------"<<endl;
        	cout<<"*     Subtotal: "<<moto[i].subtotal<<" COP."<<endl;
        	cout<<"*     Descuentos: "<<strdescuento<<endl;
        	cout<<"*     Impuestos: "<<strdescuento<<endl;
            cout<<"*     Total a pagar es: "<<moto[i].precio<<" COP."<<endl;
            cout<<"*     Gracias por confiar en el parqueadero "<<x[0].nombre_parqueadero<<endl;
            cout<<"*     Vuelva Pronto..."<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
			//ACUMULACION DE LAS GANACIAS
			x[0].gananciaDia=x[0].gananciaDia+moto[i].precio;

			do{
				do{
					cout<<"Desea que el auto salga? (S/N)"<<endl;
					cin>>opcion;
					verificacion=recorrerCadena(opcion, 1);
				}while(verificacion);
				verificacion=false;

				for(int i=0;i<1;i++){
					if(opcion[i]=='s'||opcion[i]=='S'){
						cout<<endl;
						cout<<"Espere...";

						//BORRADO ELEMENTO DEL AUTO A SALIR
						for (int j = i; j < 10-1; j++){
							moto[j] = moto[j+1];
						}

						Sleep(1200);

						cout<<"El auto ha salido..."<<endl;
						cout<<"Guardando Cambios..."<<endl;

						//LECTURA-ESCRITURA DE ARCHIVOS PARA MOTOS, GUARDADO DE VARIABLES EN ARCHIVO DE TEXTO
						fstream motoentrada("motos.dat", ios::app|ios::out|ios::binary);
						if(motoentrada.is_open()){
							motoentrada.write((char*)moto, cantidadmotos*sizeof(motocicleta));
							motoentrada.close();
						}

						ofstream variables;
						variables.open("varmoto.txt",ios::out);
						   if(variables.is_open()){
						   	variables<<arrmoto;
						}
						variables.close();

						fstream motosalida("motos.dat", ios::binary|ios::in);
						if(motosalida.is_open()){
							motosalida.read((char*)moto, cantidadmotos*sizeof(motocicleta));
							motosalida.close();
						}
						repetir=false;
					}else{
						if(opcion[i]=='n'||opcion[i]=='N'){
							repetir=false;
						}else{
							cout<<"Ingrese un opcion Correcta..."<<endl;
							repetir=true;
						}
					}
				}
			}while(repetir);
		}else{
				cout<<"No se ha encontrado la motocicleta registrada."<<endl;
		}
	}
	cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;


	system("pause");
}
void auto_salir(automovil *m, int cantidadautos){
	//VARIABLES PARA CONVERTIR EL TIEMPO DE SEGUNDOS
	int hr=0, minuto=0, segundo=0;

	system("cls");
	color(Color_Aguamarina);
	char tecla='\n';
	char placa[arrplaca];
	struct tm *tiempo;
 	int dia;
 	int mes;
 	int anio;

 	time_t fecha_sistema;
 	time(&fecha_sistema);
 	tiempo=localtime(&fecha_sistema);

 	anio=tiempo->tm_year + 1900;
 	mes=tiempo->tm_mon + 1;
 	dia=tiempo->tm_mday;
 	int filapar_char;
	bool repetir=false, verificacion=false;
	char opcion[1];
 	string strdescuento;
	cout<<"Vas dejar salir un auto."<<endl;
	cout<<"Ingrese el PLACA del auto a salir: ";
	fflush(stdin);
	cin.getline(placa, arrplaca);

	for(int i=0;i<cantidadautos;i++){
		if(strcmp(m[i].placa,placa)==0){

			cout<<"Se ha encontrado el carro"<<endl;
			system("pause");
			system("cls");
			cout<<"Parqueadero "<<x[0].nombre_parqueadero<<endl;
            cout<<"NIT: "<<x[0].nit<<endl;
            cout<<"CAJERO ACTUAL: "<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
			cout<<"*     INFORMACION DE LA MOTOCICLETA:                                                     *"<<endl;
			cout<<"*     Ticket: "<<m[i].ticket<<endl;
			cout<<"*     Marca: "<<m[i].marca<<endl;
			cout<<"*     Placa: "<<m[i].placa<<endl;
			int numero=(int)m[i].placa[6];
				if(numero%2==0){
					if(dia%2==0){
						cout<<"*     El auto tiene pico y placa."<<endl;

					}else{
						if(dia%2!=0){
							cout<<"*     El auto no tiene pico y placa"<<endl;
						}
					}
				}
			cout<<"*     Cliente: "<<m[i].cliente<<endl;
			cout<<"*     Cedula: "<<m[i].cedula<<endl;

			filapar_char=convertir_filaparqueadero(m ,66, i);
			cout<<"*     Lugar de aparcamiento: "<<char(filapar_char)<<"-"<<m[i].columnaparqueadero+1<<endl;
            cout<<"*     Tiempo de Ingreso del auto: "<<m[i].fecha_entrada<<endl;

			m[i].tiempoauto=clock()-m[i].tiempoauto;//Cronometro EN PAUSA

			cout<<"*     El tiempo en que estuvo su auto fue de: ";//IMPRESION DEL TIEMPO EN SEGUNDOS
            segundo=-1*(int(m[i].tiempoauto)/CLOCKS_PER_SEC);

            //CALCULO PARA HORAS, MUNUTOS Y SEGUNDOS

			hr = segundo / (60*60);
            segundo %= 60*60;
            minuto = segundo / 60;
            segundo %= 60;
            cout << hr << " hora";
            if(hr != 1){
                cout << "s";
            }
            cout << " " << minuto << " minuto";
            if(minuto != 1){
                cout << "s";
            }
            cout << " y " << segundo << " segundo";
            if(segundo != 1){
                cout << "s"<<endl;
            }
            //CALCULO DE LOS PRECIOS DE VENTA
            m[i].precio=((minuto*x[0].precioLimiteCarros))-ImpuestoVenta[0].descuentos;
            m[i].subtotal=minuto*x[0].precioLimiteCarros;
            if(ImpuestoVenta[0].descuentos>=1&&ImpuestoVenta[0].impuestos>=0.1){
                strdescuento="Si";
            }else{
                strdescuento="No";
            }

			cout<<"------------------------------------------------------------------------------------------"<<endl;
        	cout<<"*     Subtotal: "<<m[i].subtotal<<" COP."<<endl;
        	cout<<"*     Descuentos: "<<strdescuento<<endl;
        	cout<<"*     Impuestos: "<<strdescuento<<endl;
            cout<<"*     Total a pagar es: "<<m[i].precio<<" COP."<<endl;
            cout<<"*     Gracias por confiar en el parqueadero "<<x[0].nombre_parqueadero<<endl;
            cout<<"*     Vuelva Pronto..."<<endl;
			cout<<"-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
			//ACUMULACION DE LAS GANACIAS
			x[0].gananciaDia=x[0].gananciaDia+m[i].precio;

			do{
				do{
					cout<<"Desea que el auto salga? (S/N)"<<endl;
					cin>>opcion;
					verificacion=recorrerCadena(opcion, 1);
				}while(verificacion);
				verificacion=false;

				for(int i=0;i<1;i++){
					if(opcion[i]=='s'||opcion[i]=='S'){
						cout<<endl;
						cout<<"Espere...";
						//BORRADO ELEMENTO DEL AUTO A SALIR
						for (int j = i; j < 10-1; j++){
							m[j] = m[j+1];
						}
						Sleep(1200);
						cout<<"El auto ha salido..."<<endl;
						cout<<"Guardando Cambios..."<<endl;
						//LECTURA-ESCRITURA DE ARCHIVOS PARA
						fstream vehiculoentrada("vehiculos.dat", ios::app|ios::out|ios::binary);
						if(vehiculoentrada.is_open()){
							vehiculoentrada.write((char*)m, cantidadautos*sizeof(automovil));
							vehiculoentrada.close();
						}

						ofstream variables;
						variables.open("varauto.txt",ios::out);
						   if(variables.is_open()){
						   	variables<<arrauto;
						}
						variables.close();

						fstream vehiculosalida("vehiculos.dat", ios::binary|ios::in);
						if(vehiculosalida.is_open()){
							vehiculosalida.read((char*)m, cantidadautos*sizeof(automovil));
							vehiculosalida.close();
						}
						repetir=false;
					}else{
						if(opcion[i]=='n'||opcion[i]=='N'){
							repetir=false;
						}else{
							cout<<"Ingrese una opcion valida..."<<endl;
							system("pause");
							repetir=true;
						}
					}
				}
			}while(repetir);
		}else{
			cout<<"No se ha encontrado el vehiculo...";
		}
	}

	cout<<endl;
	system("pause");

}

//FUNCIONES DE ADMINISTRADORES
void administrar(automovil *carro, motocicleta *moto, int **matriz, int **matrizmoto, int fila, int columna){

	repeticion=false;
	bool error=false;
	int opc_administrar=-1;

	do{
		system("cls");
    	encabezado();
		cout<<endl;
		color(Color_Rojo);
		cout<<"PARA INGRESAR AL PANEL DEBES AGREGAR UN USUARIO Y CLAVE"<<endl;
		color(Color_Defecto);
		cout<< "NOMBRE: ";
	    fflush(stdin);
	    getline(cin,usuario);

	    cout<< "CONTRASENA: ";
		for (int i = 0; i < 128; i++) {
			clave[i] = getch();

			cout.flush();
			if (clave[i] == '\r') {
				clave[i] = 0;
				break;
			}
			cout << "*";
		}
		cout<<endl;
		for(int i=0;i<100;i++){
			if (!strcmp(clave, admin[i].clave_admin)) {
				if(usuario==admin[i].nick_admin){
					do{
						entrar_menu_administrar();
						cin>>opc_administrar;
						switch(opc_administrar){
							case 1:
								GenerarInforme(carro,moto,matriz,matrizmoto , fila,columna);
								break;
							case 2:
                                modificarInformacionParqueadero();
								break;
							case 3:
								FlujoCaja(carro,moto);
								break;
							case 4:
                                modificarUsuario();
								break;
							case 5:
								AgregarAdministrador();
								break;
							case 6:
								AgregarClienteFrecuente();
								break;
							case 7:
								VerClienteFrecuente();
								break;
							case 8:
								VerificarArchivos();
								break;
							case 9:
								reiniciar(carro,moto);
								break;
							case 10:

								break;
							default:
								cout<<"Ingrese una opcion correcta"<<endl;
								system("pause");
						}
					}while(opc_administrar!=10);

					break;
				}
			}else{
				cout << "Usuario o clave son incorrectos!!"<<endl;
				error=true;
				system("pause");
				break;
			}
		}
	}while(error);
}
//FUNCION ENCABEZADO
void encabezado(){
    const char* dS[7] = {"Domingo","Lunes","Martes","Miercoles",
                  "Jueves","Viernes","Sabado"};
    time_t tSac = time(NULL);       // instante actual
    struct tm* tmP = localtime(&tSac);

    color(Color_Aguamarina);
    cout << dS[tmP->tm_wday]<<"\t\t";//DIA SEMANA
    color(Color_Amarillo);
    cout << tmP->tm_mday << "-" << tmP->tm_mon+1 << "-" << tmP->tm_year+1900<<"\t\t";//FECHA
    color(Color_Purpura);
    cout << tmP->tm_hour<< ":" << tmP->tm_min << ":"<< tmP->tm_sec << endl;//HORA
    color(Color_Defecto);
	cout<<"			 -------------------------------------------------------------		"<<endl;
	cout<<"		            <<<<<<<<<<< GESTION DE PARQUEADEROS >>>>>>>>>>>>>            "<<endl;
	cout<<"                                           <<<<PARQUEADERO: "<<x[0].nombre_parqueadero<<">>>>      "<<endl;
	cout<<"			 -------------------------------------------------------------		"<<endl;
}

//FUNCION APARCAMIENTO
int lugar_aparcar(int x,int y,int z, int *t){
	int aparcamientos[x][y];
	*t=y;
	return x;
}
char convertir_filaparqueadero(automovil *carro, int x, int bucle){
	int fila=0;

	fila=(carro[bucle].filaparqueadero+x)-1;
	fila= char(fila);
	return fila;

}
char convertir_filaparqueadero_moto(motocicleta *m, int x, int bucle){
	int fila=0;
	fila=(m[bucle].filaparqueadero+x)-1;
	fila=char (fila);
	return fila;
}

void mostrarVehiculo(automovil *aut, motocicleta *moto, int cantcarros, int cantmotos, int **matriz, int **matrizmoto,int fila, int columna, int cantidadautos, int cantidadmotos){
	int opc=-1;
	cout<<endl;
	do{
        system("cls");
		encabezado();
		color(Color_Purpura);
		cout<<"\t\t(1) Mostrar todos los vehiculos en el parqueadero"<<endl;
		cout<<"\t\t(2) Mostrar todas motocicletas en el parqueadero"<<endl;
		cout<<"\t\t(3) Volver al menu anterior"<<endl;
		cout<<"OPCION>>     ";cin>>opc;
		switch(opc){
			case 1:
				mostrarVehiculoCarro(cantcarros,aut,moto,matriz,fila,columna,cantidadautos);
				break;
			case 2:
				mostrarVehiculoMoto(cantcarros,moto,matrizmoto,fila,columna,cantidadmotos);
				break;
			case 3:
				break;
			default:
				cout<<"Ingrese una opción correcta..."<<endl;
				system("pause");
		}
	}while(opc!=3);

}

void mostrarVehiculoCarro(int cantcarros, automovil *aut, motocicleta *moto, int **matriz, int fila, int columna, int cantidadautos){
	system("pause");
    system("cls");
    color(Color_Aguamarina);
	int filapar_char=0, i=0;
    fstream lecturaVehiculos("vehiculos.dat", ios::in|ios::binary);
    if(lecturaVehiculos.is_open()){
        lecturaVehiculos.read((char*)aut, cantidadautos*sizeof(automovil));
        while(!lecturaVehiculos.eof()){
        	filapar_char=convertir_filaparqueadero(aut,66,i);
        	cout<<"_____________________________________________________________"<<endl;
        	cout<<"TICKET....................: "<<aut[i].ticket<<endl;
	        cout<<"MARCA:....................: "<<aut[i].marca<<endl;
	        cout<<"PLACA:....................: "<<aut[i].placa<<endl;
	        cout<<"CLIENTE:..................: "<<aut[i].cliente<<endl;
	        cout<<"CEDULA:...................: "<<aut[i].cedula<<endl;
	        cout<<"ESTADO DE PICO Y PLACA....: "<<aut[i].pico_placa<<endl;
	        cout<<"VALOR ACTUAL..............: "<<aut[i].precio<<endl;
	        cout<<"LUGAR DEL PARQUEADERO.....: "<<char(filapar_char)<<"-"<<aut[i].columnaparqueadero+1<<endl;
	        cout<<"TIEMPO TRANSCURRIDO.......: "<<int(aut[i].tiempoauto)/CLOCKS_PER_SEC<<endl;
	        cout<<"VALOR ACTUAL..............: "<<aut[i].precio<<endl;
	        cout<<"FECHA DE ENTRADA..........: "<<aut[i].fecha_entrada<<endl;
	        cout<<"_____________________________________________________________"<<endl;
	        i++;
	        cout<<endl;
	        lecturaVehiculos.read((char*)aut, cantidadautos*sizeof(automovil));
		}
    }
    lecturaVehiculos.close();
}

void mostrarVehiculoMoto(int cantcarros, motocicleta *moto, int **matriz, int fila, int columna, int cantidadmotos){
	system("cls");
	system("pause");
	color(Color_Aguamarina);
	int filapar_char=0, i=0;;
    fstream lecturaVehiculos("motos.dat", ios::in|ios::binary);
    if(lecturaVehiculos.is_open()){
        lecturaVehiculos.read((char*)moto, cantidadmotos*sizeof(motocicleta));
        while(!lecturaVehiculos.eof()){
        	filapar_char=convertir_filaparqueadero_moto(moto,66,i);
        	cout<<"_____________________________________________________________"<<endl;
        	cout<<"TICKET....................: "<<moto[i].ticket<<endl;
	        cout<<"MARCA:....................: "<<moto[i].marca<<endl;
	        cout<<"PLACA:....................: "<<moto[i].placa<<endl;
	        cout<<"CLIENTE:..................: "<<moto[i].cliente<<endl;
	        cout<<"CEDULA:...................: "<<moto[i].cedula<<endl;
	        cout<<"LUGAR DEL PARQUEADERO.....: "<<char(filapar_char)<<"-"<<moto[i].columnaparqueadero<<endl;
	        cout<<"TIEMPO TRANSCURRIDO.......: "<<int(moto[i].tiempomoto)/CLOCKS_PER_SEC<<endl;
	        cout<<"VALOR ACTUAL..............: "<<moto[i].precio<<endl;
	        cout<<"FECHA DE ENTRADA..........: "<<moto[i].fecha_entrada<<endl;
	        cout<<"_____________________________________________________________"<<endl;
	        cout<<endl;
	        i++;
	        lecturaVehiculos.read((char*)moto, cantidadmotos*sizeof(motocicleta));
		}
    }else{
    	cout<<"No se pudo encontrar el archivo"<<endl;
	}
    lecturaVehiculos.close();
    system("pause");
}

bool recorrerCadena(char cadena[], int tipoCadena){
	bool revision = true;
	if(tipoCadena==1){//CONDICIONAL PARA EJECUTAR Y REVISAR CADENAS QUE TIENEN QUE SER DE SOLO LETRAS
		for (int i = 0; i < strlen(cadena); i++) {
			if (isalpha(cadena[i])) {
				revision = false;
				break;
			}
		}
		if (revision){
			cout << "ESTA INFORMACION SOLO DEBE CONTENER LETRAS DEL ALFABETO"<<endl;
			system("pause");
		}
	}else{//CONDICIONAL PARA EJECUTAR Y REVISAR CADENAS QUE TIENE QUE SER DE SOLO NUMEROS
		for (int i = 0; i < strlen(cadena); i++) {
			if (!isalpha(cadena[i])) {
				revision = false;
				break;
			}
		}
		if (revision) {
			cout << "ESTE DATO DEBE CONTENER SOLO NUMEROS"<<endl;
			system("pause");
		}
	}

	return revision;

}
//FUNCIONES DEMANDA ZONAL
void DemandaZonalCarros(){
	//DEFINICION DE LIMITES DE PRECIO PARA CARROS
	//DEMANZA ZONAL EN 1.0
	if(x[0].demandaZonal==1.0&&(x[0].pisoParqueadero==2||x[0].pisoParqueadero==3||x[0].pisoParqueadero==4||x[0].pisoParqueadero==5||x[0].pisoParqueadero==6)){
        x[0].precioLimiteCarros=87;
	}
    if(x[0].demandaZonal==1.0&&(x[0].pisoParqueadero==1&&(x[0].tipoPisoParqueadero==1||x[0].tipoPisoParqueadero==2||x[0].tipoPisoParqueadero==3))){
        x[0].precioLimiteCarros=61;
    }
    if(x[0].demandaZonal==1.0&&((x[0].pisoParqueadero==1)&&(x[0].tipoPisoParqueadero==4||x[0].tipoPisoParqueadero==5))){
        x[0].precioLimiteCarros=43;
	}

    //DEMANDA ZONAL EN 0.8
    if(x[0].demandaZonal==0.8&&(x[0].pisoParqueadero==2||x[0].pisoParqueadero==3||x[0].pisoParqueadero==4||x[0].pisoParqueadero==5||x[0].pisoParqueadero==6)){
        x[0].precioLimiteCarros=69;
    }
    if(x[0].demandaZonal==0.8&&(x[0].pisoParqueadero==1&&(x[0].tipoPisoParqueadero==1||x[0].tipoPisoParqueadero==2||x[0].tipoPisoParqueadero==3))){
        x[0].precioLimiteCarros=49;
    }
    if(x[0].demandaZonal==0.8&&((x[0].pisoParqueadero==1)&&(x[0].tipoPisoParqueadero==4||x[0].tipoPisoParqueadero==5))){
        x[0].precioLimiteCarros=35;
	}

}

void DemandaZonalMotos(){
	//PRECIOS LIMITES PARA MOTOS
	//DEMANDA ZONAL 0.8
    if(x[0].demandaZonal==0.8&&(x[0].pisoParqueadero==2||x[0].pisoParqueadero==3||x[0].pisoParqueadero==4||x[0].pisoParqueadero==5||x[0].pisoParqueadero==6)){
        x[0].precioLimiteMotos=61;
    }
    if(x[0].demandaZonal==0.8&&(x[0].pisoParqueadero==1&&(x[0].tipoPisoParqueadero==1||x[0].tipoPisoParqueadero==2||x[0].tipoPisoParqueadero==3))){
        x[0].precioLimiteMotos=42;
    }
    if(x[0].demandaZonal==0.8&&((x[0].pisoParqueadero==1)&&(x[0].tipoPisoParqueadero==4||x[0].tipoPisoParqueadero==5))){
        x[0].precioLimiteMotos=30;
	}

	//DEMANDA ZONAL EN 1.0
    if(x[0].demandaZonal==1.0&&(x[0].pisoParqueadero==2||x[0].pisoParqueadero==3||x[0].pisoParqueadero==4||x[0].pisoParqueadero==5||x[0].pisoParqueadero==6)){
        x[0].precioLimiteMotos=49;
    }
    if(x[0].demandaZonal==1.0&&(x[0].pisoParqueadero==1&&(x[0].tipoPisoParqueadero==1||x[0].tipoPisoParqueadero==2||x[0].tipoPisoParqueadero==3))){
        x[0].precioLimiteMotos=34;
    }
    if(x[0].demandaZonal==1.0&&((x[0].pisoParqueadero==1)&&(x[0].tipoPisoParqueadero==4||x[0].tipoPisoParqueadero==5))){
        x[0].precioLimiteMotos=24;
	}
}

void VerClienteFrecuente(){

    int i=0;
	fstream lecturaCliente ("usuario/cliente_Frecuente.dat", ios::in|ios::binary);
	if(lecturaCliente.is_open()){
		lecturaCliente.read((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
		while(!lecturaCliente.eof()){
				cout<<"__________________________________________________________________"<<endl;
				cout<<"NOMBRE DEL CLIENTE FRECUENTE: "<<clienteFrecuente[i].cliente<<endl;
				cout<<"CEDULA DEL CLIENTE FRECUENTE: "<<clienteFrecuente[i].cedula<<endl;
				cout<<"__________________________________________________________________"<<endl;
				i++;
			lecturaCliente.read((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
		}
		lecturaCliente.close();
	}else{
		cout<<"No se ha podido abrir el archivo"<<endl;
		system("pause");
	}
	system("pause");
}

void GenerarInforme(automovil *carro, motocicleta *moto, int **matriz, int **matrizmoto, int fila, int columna){
	int cuposLibresAutos=0,cuposLibresMotos=0;
	char tecla[1];
	bool verificacion=false, repetir=false;
	system("cls");

	cuposLibresAutos=x[0].max_carros-carro[arrauto-1].ticket;
	cuposLibresMotos=x[0].max_motos-moto[arrmoto-1].ticket;

	ifstream cuposParqueadero("cuposLibres.txt", ios::in);
	if(cuposParqueadero.is_open()){
		cuposParqueadero>>cuposLibresAutos;
		cuposParqueadero>>cuposLibresMotos;
		cuposParqueadero>>cuposLibresAutos;
		cuposParqueadero.close();
	}

	ofstream leerCupos;
	leerCupos.open("cuposLibres.txt", ios::out);
	if(leerCupos.is_open()){
		leerCupos<<cuposLibresAutos<<" ";
		leerCupos<<cuposLibresMotos<<" ";
		leerCupos.close();
	}
	color(Color_Aguamarina);
	int filamatriz=x[0].filas;
	int columnamatriz=x[0].columnas;
	color(Color_Amarillo);
	cout<<"PARQUEADERO "<<x[0].nombre_parqueadero<<endl;
	color(Color_Aguamarina);
	cout<<"\tINFORME DE PARQUEADERO"<<endl;
	cout<<"Hora actual: ";
	system("time /t");
	cout<<"Fecha Actual: ";
	system("date /t");
	cout<<"Autos registrados en este momento: "<<arrauto<<endl;
	cout<<"Motos Registradas en este momento: "<<arrmoto<<endl;
	cout<<"Cupos libres en el parqueadero para Autos: "<<cuposLibresAutos<<endl;
	cout<<"Cupos libres el el parqueadero para Motos: "<<cuposLibresMotos<<endl;
	cout<<"Ganancias hasta ahora: "<<x[0].gananciaDia<<endl;
	cout<<endl;
	cout<<"APARCAMIENTO DE AUTOS"<<endl;
	for(int i=0;i<filamatriz;i++){
		for(int j=0;j<columnaAutos;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"APARCAMIENTO DE MOTOS"<<endl<<endl;
	for(int i=0;i<filamatriz;i++){
		for(int j=0;j<columnaMotos;j++){
			cout<<matrizmoto[i][j]<<" ";
		}
		cout<<endl;
	}

	do{
		do{
			cout<<"Desea generar este informe en formato de texto? (S/N)"<<endl;
			cin>>tecla;
			verificacion=recorrerCadena(tecla, 1);
		}while(verificacion);
		verificacion=false;

		for(int i=0;i<1;i++){
			if(tecla[i]=='s'||tecla[i]=='S'){
				ofstream informe;
				mkdir("usuario");
				informe.open("usuario/informe.txt",ios::out);
				if(informe.is_open()){
					informe<<"PARQUEADERO "<<x[0].nombre_parqueadero<<endl;
					color(Color_Aguamarina);
					informe<<"\tINFORME DE PARQUEADERO"<<endl;
					informe<<"Hora actual: "<<system("time /t")<<endl;
					informe<<"Fecha Actual: "<<system("date /t")<<endl;
					informe<<"Autos registrados en este momento: "<<arrauto<<endl;
					informe<<"Motos Registradas en este momento: "<<arrmoto<<endl;
					informe<<"Ganancias hasta ahora: "<<x[0].gananciaDia<<endl;
					informe<<"Archivo Generado por el software de "<<x[0].nombre_parqueadero<<endl;
					informe.close();
				}else{
					cout<<"No se pudo abrir el archivo"<<endl;
					system("pause");
					repetir=false;
				}
			}else{
				if(tecla[i]=='n'||tecla[i]=='N'){
					repetir=false;
				}else{
					cout<<"Seleccione una opcion que sea correcta"<<endl;
					repetir=true;
				}
			}

		}
	}while(repetir);

	system("pause");
}

void AgregarAdministrador(){
    system("cls");
    color(Color_Amarillo);
    char tam[1];
    bool verificacion=false;
    int contador=0;
    encabezado();
    cout<<"\t\t\t<--------AGREGAR UN ADMINISTRADOR------------>"<<endl<<endl;
    cout<<"\tVas a agregar un nuevo administrador o empleado"<<endl;
    cout<<"\tRecuerda que cuando vas a agregar un nuevo administrador tendra derecho a todas las funciones del sofotware"<<endl;
    cout<<endl;

    ifstream leerVaradmin;
    leerVaradmin.open("varadmin.txt", ios::in);
    if(leerVaradmin.is_open()){
    	leerVaradmin>>contador;
    	leerVaradmin>>contador;
    	leerVaradmin.close();
	}

    if(admin[contador].contadorAdmin<=100){
    	do{
	    	cout<<"Ingrese usuarios de administrador a ingresar: ";
	    	cin>>tam;
	    	verificacion=recorrerCadena(tam, 0);
		}while(verificacion);

	    admin[0].contadorAdmin++;
	    contador=admin[0].contadorAdmin;

	    cout<<"Ingrese el nuevo usuario de administrador: "<<contador<<": ";
	    fflush(stdin);
	    cin.getline(admin[contador].nick_admin, arrnombre);

		cout<<"Ingrese la nueva clave: "<<contador<<": ";
	    cin>>admin[contador].clave_admin;

	    do{
	    	cout<<"Ingrese el nuevo telefono: "<<contador<<": ";
		    cin>>admin[contador].telefono;
		    verificacion=recorrerCadena(admin[contador].telefono, 0);
		}while(verificacion);
		verificacion=false;


	    cout<<"Ingrese el nuevo email del administrador "<<contador<<": ";
	    cin>>admin[contador].email;

	    do{
	    	cout<<"Ingrese el celular del nuemo administrador "<<contador<<": ";
	    	cin>>admin[contador].celular;
	    	verificacion=recorrerCadena(admin[contador].celular , 0);
		}while(verificacion);
		verificacion=false;
	}

    ofstream varadmin;

    varadmin.open("varadmin.txt", ios::out);
    if(varadmin.is_open()){
    	varadmin<<contador;
    	varadmin.close();
	}


    system("pause");

}

void FlujoCaja(automovil *carro, motocicleta *moto){
	system("cls");
	//DECLARACION DE VARIABLES LOCALES PARA FLOJO DE CAJA. CALCULO DE PRECIOS Y PROMEDIOS
	int promedioCarro=0,promedioMoto=0,gananciaCarro=0, gananciaMoto=0;
	char tecla[1];
	bool verificacion=false;
	bool repetir=false;
	//ENCABEZADO DEL PROGRAMA
	encabezado();
	cout<<"\t\t\t<<<<<<<<< FLUJO DE CAJA >>>>>>>>>>>"<<endl;

	if(moto[0].precio<=0){
		for(int i=0;i<arrauto;i++){
			moto[i].precio=0;
			moto[i].subtotal=0;
		}
	}
	//GANANCIA DE VEHICULOS
	for(int i=0; i<=arrauto;i++){

		gananciaCarro=gananciaCarro+carro[i].precio;
	}
	//GANACIA POR MOTICICLETA
	for(int i=0; i<arrmoto;i++){
		gananciaMoto=gananciaMoto+moto[i].precio;
	}
	//INICIO DEL CUERPO DEL PROGRAMA
	color(Color_Rojo);
	cout<<"\tVALOR INICIAL EN CAJA: "<<x[0].ActivoInicial<<" COP."<<endl<<endl;
	color(Color_Amarillo);
	cout<<"\tGANANCIA ACTUAL: "<<x[0].gananciaDia<<" COP."<<endl<<endl;
	/*if(gananciaCarro==0||carro[arrauto-1].ticket==0){
		promedioCarro=0;
	}else{
		promedioCarro=gananciaCarro/carro[arrauto-1].ticket;//PROMEDIO DE PRECIO POR CARRO
	}

	cout<<"\tGANANCIA PROMEDIO POR CARRO: "<<promedioCarro<<endl<<endl;
	promedioMoto=gananciaMoto/moto[arrauto-1].ticket;//PROMEDIO DE PRECIO POR MOTO
	cout<<"\tGANACIA PROMEDIO POR MOTO: "<<promedioMoto<<endl<<endl;
*///COMENBTADO POR ERROR DE EXCEPCION DE OPERACION ARITMETICA
	do{
			do{
			cout<<"Desea exportar el informe del flujo de caja a archivo de texto? (S/N): ";
			cin>>tecla;
			verificacion=recorrerCadena(tecla, 1);
		}while(verificacion);

		for(int i=0;i<1;i++){
			if(tecla[i]=='s'||tecla[i]=='S'){
				ofstream flujoDeCaja;
				flujoDeCaja.open("usuario/Flujo_caja.txt", ios::out);
				if(flujoDeCaja.is_open()){
					flujoDeCaja<<"\t\t\t<<<<<<<<< FLUJO DE CAJA >>>>>>>>>>>"<<endl;
					flujoDeCaja<<"\tVALOR INICIAL EN CAJA: "<<x[0].ActivoInicial<<" COP."<<endl;
					flujoDeCaja<<"\tGANANCIA ACTUAL: "<<x[0].gananciaDia<<" COP."<<endl;
					flujoDeCaja<<"\tGANANCIA PROMEDIO POR CARRO: "<<promedioCarro<<endl;
					flujoDeCaja<<"\tGANACIA PROMEDIO POR MOTO: "<<promedioMoto<<endl;
				}
				flujoDeCaja.close();
				repetir=false;
			}else{
				if(tecla[i]=='n'||tecla[i]=='N'){
					cout<<"Has seleccionado no exportar el informe del flujo de caja"<<endl;
					system("pause");
					repetir=false;
				}else{
					cout<<"Seleccione una opcion correcta..."<<endl;
					system("pause");
					repetir=true;
				}
			}
		}
	}while(repetir);

}

void AgregarClienteFrecuente(){
	char opc[1];
	int opcion=0;
	bool verificacion=false, repetir=false;
	system("cls");
	color(Color_Purpura);
	encabezado();
	cout<<"\t\t\t<<<<<<<<<<-- AGREGAR CLIENTE FRECUENTE -->>>>>>>>>>>>"<<endl;
	cout<<"___________________________________________________________"<<endl;
	cout<<endl;
	color(Color_Rojo);
	cout<<"Vas a agregar un cliente frecuente de tu parqueadero"<<endl;
	system("pause");
	system("cls");
	do{
		do{
			cout<<"Ingresar el nombre del cliente: ";
			fflush(stdin);
			cin.getline(clienteFrecuente[contClienteFrecuente].cliente, arrcliente);
			verificacion=recorrerCadena(clienteFrecuente[contClienteFrecuente].cliente, 1);
		}while(verificacion);
		verificacion=false;

		do{
			cout<<"Ingrese el la cedula del cliente: ";
			fflush(stdin);
			cin.getline(clienteFrecuente[contClienteFrecuente].cedula, 13);
			verificacion=recorrerCadena(clienteFrecuente[contClienteFrecuente].cedula, 0);

		}while(verificacion);
		verificacion=false;

		system("pause");
		color(Color_Amarillo);
		system("cls");

		fstream cliente ("usuario/cliente_Frecuente.dat", ios::out|ios::app|ios::binary);
		if(cliente.is_open()){
			cliente.write((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
			cliente.close();
		}else{
			cout<<"No se ha podido abrir el archivo"<<endl;
		}

		fstream lecturaCliente ("usuario/cliente_Frecuente.dat", ios::in|ios::binary);
		if(cliente.is_open()){
			lecturaCliente.read((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
			lecturaCliente.close();
		}else{
			cout<<"No se ha podido abrir el archivo"<<endl;
		}

		contClienteFrecuente++;

		do{
			do{
				cout<<"Desea registrar otro cliente?. 1 para si, 0 para no: ";
				cin>>opc;
				verificacion=recorrerCadena(opc,0);
			}while(verificacion);

			if(!verificacion){
				sscanf(opc, "%d", &opcion);
			}

			if(opcion!=1&&opcion!=0){
				cout<<"Ingrese una opcion valida..."<<endl;
				system("pause");
				repetir=true;
			}
		}while(repetir);
	}while(opcion==1);

	ofstream lecturaContadora;
	lecturaContadora.open("contClientesFrecuentes.txt", ios::out);
	if(lecturaContadora.is_open()){
		lecturaContadora<<contClienteFrecuente;
		lecturaContadora.close();
	}

}

void reiniciar(automovil *carro , motocicleta *moto){
	int opc=0;
	char opcion[1];
	bool verificacion=false;

	do{
		system("cls");
		color(Color_Rojo);
		cout<<"\t\t\tREINICIO DEL SISTEMA..."<<endl;
		color(Color_Defecto);
		encabezado();
		color(Color_Amarillo);
		do{
			cout<<"\t(1)Reincio del Sistema por cierre de Día"<<endl;
			cout<<"\t(2)Reinicio del sistema a la configuracion inicial"<<endl;
			cout<<"\t(3)AYUDA!"<<endl;
			cout<<"\t(4)Regresar al anterior menu"<<endl;
			cin>>opcion;
			verificacion=recorrerCadena(opcion, 0);
		}while(verificacion);

		if(!verificacion){
			sscanf(opcion, "%d", &opc);
		}

		switch(opc){
			case 1://CIERRE DE CAJA
				ReiniciarDia(carro,moto);
				break;
			case 2://REINICIO DEL PROGRAMA COMPLETAMENTE
				ReiniciarTotal(carro,moto);
				break;
			case 3://IMPRIME LA AYUDA DE LAS FUNCIONES REINICIAR
				ReiniciarAyuda();
				break;
			case 4://REGRESAR EL MENU ANTERIOR

				break;
			default:
				cout<<"Ingrese una opcion correcta"<<endl;
				system("pause");
		}
	}while(opc!=4);


}

//ADMINISTRAR- METODOS DE REINICIO
void ReiniciarDia(automovil *carro , motocicleta *moto){
	system("cls");
	color(Color_Defecto);
	encabezado();
	color(Color_Rojo);
	cout<<"Vas a cerrar el el parqueadero por el día."<<endl;
	system("pause");
	system("cls");
	color(Color_Verde);
	cout<<"Se ha cerrado la caja el dia "<<system("date /t")<<" en al hora"<< system("time /t");
	cout<<"Se va a guardar un archivo con el historial del cierre del dia.";
	system("pause");

	cout<<"Guardando cambios en archivos..."<<endl;
	leerArchivos(carro,moto,x[0].max_motos,x[0].max_carros);
	Sleep(1200);

	//CREACION DEL ARCHIVO DE HISTORIALES DE CIERRE
	ofstream logCierre;
	logCierre.open("logs/logcierre.txt", ios::out| ios::app);
	if(logCierre.is_open()){
		logCierre<<"Cierre de la caja: "<<system("date /t")<<" "<<system("time /t");
		logCierre<<endl;
		logCierre.close();
	}
	system("cls");
}

void ReiniciarTotal(automovil *carro, motocicleta *moto){
	system("cls");
	color(Color_Defecto);
	encabezado();

	color(Color_Rojo);
	cout<<"ATENCION: VAS A REINICIAR EL SOFTWARE COMPLETAMENTE."<<endl;
	cout<<"Esta opcion solo se debe usar cuando el programa falle, se escriban malos datos en tu pc, manipulacion de terceros sin permiso ";
	cout<<"o simplemente si tienes otro parqueadero y quieres utilizar este software en ese nuevo establecimiento."<<endl;
	cout<<endl;
	cout<<"Presione Una Tecla Para Empezar El Reseteo Del Software..."<<endl;
	getch();

	color(Color_Verde);
	cout<<"Este procedimiento tardará unos cuantos minutos..."<<endl;
	cout<<"El Software se empezará a reiniciar...";
	Sleep(1000);
	//CONTADOR REGRESIVO DE REINICIO
	for(int i=10; i>=0;i--){
		color(Color_Amarillo);
		cout<<"El software se empezará a reiniciar en "<<i<<" segundos..."<<endl;
		Sleep(1000);
		system("cls");
	}

	color(Color_Verde);
	cout<<"Este procedimiento tardará unos cuantos minutos..."<<endl;
	cout<<"BORRANDO INFORMACION ALMACENADA EN MEMORIA...";
	memset(carro, 0, sizeof(automovil));

	memset(admin, 0,sizeof(administrador));

	memset(x, 0,sizeof(parqueadero));

	memset(moto, 0, sizeof(motocicleta));

	memset(ImpuestoVenta, 0, sizeof(impuesto));

	memset(clienteFrecuente, 0 , sizeof(cliFrecuente));

	Sleep(6545);
	cout<<"MEMORIA HA SIDO LIMPIADA CON EXITO..."<<endl<<endl;
	system("pause");

	cout<<"ELIMINANDO INFORMACION ALMACENADA EN ARCHIVOS...";
	BorrarArchivos();
	Sleep(3500);

	cout<<"VERIFICANDO..."<<endl;

	Sleep(1300);
	color(Color_Amarillo);
	system("pause");
	system("cls");
	cout<<"Presione una tecla para cerrar el programa. Esto es necesario para liberar memoria totalmente."<<endl;
	getch();

	system("exit");


}

void ReiniciarAyuda(){
	system("cls");
	encabezado();
	cout<<"\t\t\t--FUNCION REINICIAR - AYUDA..."<<endl<<endl;
	color(Color_Aguamarina);
	cout<<"Las opciones de reinciar se instalaron en el programa para facilitar la ayuda del usuario en caso de que el programa falle."<<endl;
	cout<<"Aun asi, no todas las opciones de reinicio hacen caso a esta afirmacion, a continuacion te explicaremos el porqué..."<<endl;
	cout<<"\t1- REINICIO DE DIA: Esta funcion del programa cierra la caja del dia, es decir, asegura que se guarden todas las ganancias y que se carguen los archivos ";
	cout<<"correspondientes para mejorar el funcionamiento y preparar el programa para el proximo dia de funcionamiento."<<endl;
	cout<<"\t2- REINICIO TOTAL DEL SISTEMA: Tambien conocido como Reinicio total del sistema a la configuracion inicial. Este sistema borra toda la configuracion hecha por ";
	cout<<"el usuario, asi como las motos, autos, precios, ganancias, clientes y demas datos guardados tanto en memoria como el los archivos del software. Vuelve el programa a ";
	cout<<"la configuracion de inicio, es decir, la primera vez que usted lo inicio. Esta opcion se debe utilizar solamente cuando el programa tenga errores, manipulacion sin permiso ";
	cout<<"de terceros, o bien si usted tiene un establecimiento aparte y quiere usar este software en el otro parqueadero, podra usar esta opcion."<<endl;
	cout<<endl;
	system("pause");
	system("cls");
}

void VerificarArchivos(){
	system("cls");
	encabezado();
	cout<<"\t\t\t<---VERIFICAR ARCHIVOS DEL SISTEMA--->"<<endl<<endl;
	cout<<"VERIFICANDO..."<<endl;
	Sleep(1800);

	fstream lecturaVehiculos ("vehiculos.dat", ios::in|ios::binary);

    if(lecturaVehiculos.good()){
        cout<<"El archivo vehiculos.dat se encuentra en buen estado"<<endl<<endl;

    }else{
    	cout<<"El archivo vehiculos.dat se encuentra en mal estado"<<endl<<endl;
	}
	lecturaVehiculos.close();
	Sleep(1200);
    fstream lecturaMotos ("motos.dat", ios::binary|ios::in);

    if(lecturaMotos.good()){
        cout<<"El archivo motos.dat se encuentra en buen estado"<<endl<<endl;

    }else{
    	cout<<"El archivo motos.dat se encuentra en mal estado"<<endl<<endl;
	}
    lecturaMotos.close();
    Sleep(1200);

	fstream lecturaParqueadero ("parqueadero.dat", ios::binary| ios::in);

    if(lecturaParqueadero.good()){
        cout<<"El archivo parqueadero.dat se encuentra en buen estado"<<endl<<endl;

    }else{
    	cout<<"El archivo parqueadero.dat se encuentra en mal estado"<<endl<<endl;
	}
	lecturaParqueadero.close();
	Sleep(1200);

    fstream lecturaAdministrador("admin.dat", ios::binary|ios::in);
    if(lecturaAdministrador.good()){
        cout<<"El archivo admin.dat se encuentra en buen estado"<<endl<<endl;

    }else{
    	cout<<"El archivo admin.dat se encuentra en mal estado"<<endl<<endl;
	}
    lecturaAdministrador.close();
    Sleep(1200);

    fstream lecturaCliente ("usuario/cliente_Frecuente.dat", ios::in|ios::binary);

	if(lecturaCliente.good()){
		cout<<"El archivo cliente_Frecuente.dat se encuentra en buen estado"<<endl<<endl;
	}else{
		cout<<"El archivo cliente_Frecuente.dat se encuentra en mal estado"<<endl<<endl;
	}
	lecturaCliente.close();
	Sleep(1200);

    ifstream varautos;
    varautos.open("varauto.txt", ios::in);
    if(varautos.good()){
		cout<<"El archivo varauto.txt se encuentra en buen estado"<<endl<<endl;
	}else{
		cout<<"El archivo varauto.txt se encuentra en mal estado"<<endl<<endl;
	}
	varautos.close();
	Sleep(1200);

	ifstream varmotos;
    varmotos.open("varmoto.txt", ios::in);
    if(varmotos.good()){
 		cout<<"El archivo varmoto.txt se encuentra en buen estado"<<endl<<endl;
	}else{
		cout<<"El archivo varautos.txt se encuentra en mal estado"<<endl<<endl;
	}
	varmotos.close();
	Sleep(1200);

	ifstream lecturaContadora;
	lecturaContadora.open("contClientesFrecuentes.txt", ios::in);
	if(lecturaContadora.good()){
		cout<<"El archivo contClientesFrecuentes.txt se encuentra en buen estado"<<endl<<endl;
	}else{
		cout<<"El archivo contClientesFrecuentes.txt se encuentra en mal estado"<<endl<<endl;
	}
	lecturaContadora.close();
	Sleep(1200);
	system("pause");
}

void BorrarArchivos(){
	DeleteFile("vehiculos.dat");
	DeleteFile("motos.dat");
	DeleteFile("parqueadero.dat");
	DeleteFile("admin.dat");
	DeleteFile("usuario/cliente_Frecuente.dat");
	DeleteFile("contClientesFrecuentes.txt");
	Sleep(1200);
	DeleteFile("varauto.txt");
	DeleteFile("varmoto.txt");
	DeleteFile("logs/logcierre.txt");
	DeleteFile("usuario/Flujo_caja.txt");
	DeleteFile("usuario/informe.txt");
}

void modificarUsuario(){
    system("cls");
    char usuarioBusqueda[30];
    bool verificacion=false;
    cout<<"Ingrese el nick del usuario administrador a cambiar: ";
    cin>>usuarioBusqueda;

    for(int i=0; i<100;i++){
        if(strcmp(admin[i].nick_admin,usuarioBusqueda)){
            system("pause");
            system("cls");
            cout<<"Ingrese el nuevo usuario de administrador. Recuerde que el usuario no debe tener espacios: ";
            fflush(stdin);
            cin>>admin[i].nick_admin;

            cout<<"Ingrese una nueva contrase¤a de administrador: ";
            fflush(stdin);
            cin>>admin[i].clave_admin;//AGREGAR CLAVE CON ASTERISCOS DESPUES

            cout<<"Ingrese su email: ";
            fflush(stdin);
            cin>>admin[i].email;

            do{
                cout<<"Ingrese un telefono fijo de contacto, en caso de no tener telefono ponga el de su celular: ";
                fflush(stdin);
                cin>>admin[i].telefono;
                verificacion=recorrerCadena(admin[i].telefono,0);
            }while(verificacion);
            verificacion=false;

            do{
                cout<<"Ingrese un numero de celular, en caso de no tener ingrese un telefono fijo o rellene de cualquier valor: ";
                fflush(stdin);
                cin>>admin[i].celular;
                verificacion=recorrerCadena(admin[i].celular,0);
            }while(verificacion);


            cout<<"Espere procesamos la informacion..."<<endl;

            Sleep(512);

            cout<<"Usuario modificado con exito."<<endl;
            cout<<"Presione una tecla para terminar la configuracion...";
            getch();
            }
            break;
            fstream cargarAdmin("admin.dat", ios::out| ios::binary|ios::app);
            if(cargarAdmin.is_open()){
                cargarAdmin.write((char*)admin, 100*sizeof(administrador));
            }
            cargarAdmin.close();

            fstream subirAdmin("admin.dat", ios::in|ios::binary);
            if(subirAdmin.is_open()){
                subirAdmin.read((char*)admin, 100*sizeof(administrador));
            }
            subirAdmin.close();
    }

}
//FUNCION ESCRITURA DE ARCHIVOS
void escribirArchivos(automovil *carro,  motocicleta *moto, int cantidadMotos, int cantidadAutos){

    fstream escrituraVehiculos ("vehiculos.dat", ios::out |ios::app |ios::binary);
    if(escrituraVehiculos.is_open()){
        escrituraVehiculos.write((char*)carro, cantidadAutos*sizeof(automovil));
        escrituraVehiculos.close();
    }
    fstream escrituraMotos ("motos.dat", ios::binary|ios::out | ios::app);
    if(escrituraMotos.is_open()){
        escrituraMotos.write((char*)moto, cantidadMotos*sizeof(motocicleta));
        escrituraMotos.close();
    }
    fstream escrituraParqueadero ("parqueadero.dat", ios::binary| ios::out| ios::app);
    if(escrituraParqueadero.is_open()){
        escrituraParqueadero.write((char*)x, 0*sizeof(parqueadero));
        escrituraParqueadero.close();
    }

    fstream escrituraAdministrador("admin.dat", ios::binary|ios::out|ios::app);
    if(escrituraAdministrador.is_open()){
        escrituraAdministrador.write((char*)admin, 100*sizeof(administrador));
        escrituraAdministrador.close();
    }
    fstream cliente ("usuario/cliente_Frecuente.dat", ios::out|ios::app|ios::binary);
	if(cliente.is_open()){
		cliente.write((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
		cliente.close();
	}

}

//FUNCION LECTURA DE ARCHIVOS
void leerArchivos(automovil *carro,  motocicleta *moto, int cantidadMotos, int cantidadAutos){
    fstream lecturaVehiculos ("vehiculos.dat", ios::in|ios::binary);
    if(lecturaVehiculos.is_open()){
        lecturaVehiculos.read((char*)carro, cantidadAutos*sizeof(automovil));
        lecturaVehiculos.close();
    }
    fstream lecturaMotos ("motos.dat", ios::binary|ios::in);
    if(lecturaMotos.is_open()){
        lecturaVehiculos.read((char*)moto, cantidadMotos*sizeof(motocicleta));
        lecturaMotos.close();
    }
    fstream lecturaParqueadero ("parqueadero.dat", ios::binary| ios::in);
    if(lecturaParqueadero.is_open()){
        lecturaParqueadero.read((char*)x, 100*sizeof(parqueadero));
        lecturaParqueadero.close();
    }

    fstream lecturaAdministrador("admin.dat", ios::binary|ios::in);
    if(lecturaAdministrador.is_open()){
        lecturaAdministrador.read((char*)admin, 100*sizeof(administrador));
        lecturaAdministrador.close();
    }

    fstream lecturaCliente ("usuario/cliente_Frecuente.dat", ios::in|ios::binary);
	if(lecturaCliente.is_open()){
		lecturaCliente.read((char*)clienteFrecuente, 100*sizeof(cliFrecuente));
		lecturaCliente.close();
	}

    ifstream varautos;
    varautos.open("varauto.txt", ios::in);
    if(varautos.is_open()){
    	varautos>>arrauto;
    	varautos>>filamatriz;
		varautos>>columnamatriz;
		varautos>>contador;
		varautos>>arrauto;
    	varautos.close();
	}

	ifstream varmotos;
    varmotos.open("varmoto.txt", ios::in);
    if(varmotos.is_open()){
        varmotos>>arrmoto;
    	varmotos>>filamatrizMoto;
		varmotos>>columnamatrizMoto;
		varmotos>>contadorMoto;
		varmotos>>contadorColumna;
		varmotos>>arrmoto;
    	varmotos.close();
	}

	ifstream lecturaContadora;
	lecturaContadora.open("contClientesFrecuentes.txt", ios::in);
	if(lecturaContadora.is_open()){
		lecturaContadora>>contClienteFrecuente;
		lecturaContadora>>contClienteFrecuente;
		lecturaContadora.close();
	}
}

bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}

void AcercaDe(){
	system("cls");
	string linea;
	encabezado();
	cout<<"\t\t\t<-----------ACERCA DE------------>"<<endl<<endl;
	color(Color_Aguamarina);
	
	cout<<"\t\t\tSISTEMA DE GESTION DE PARQUEADEROS"<<endl;
	cout<<"Este sistema de parqueaderos ofrece un servicio eficaz y sencillo, personalizado por el administrador o el encargado del parqueadero."<<endl;
	cout<<"VERSION:1.8.1.2016 BETA"<<endl;
	cout<<"DESARROLLADORES: Carlos Andres Garnica Salazar"<<endl;
	cout<<"Copyright (C) <2016> <Carlos Andres Garnica Salazar>"<<endl;
	ifstream acercade;
	acercade.open("info/changelog.license", ios::in);
	if(acercade.is_open()){
		while(getline(acercade, linea)){
			cout<<linea<<endl;
			acercade.clear();
		}

	}
	acercade.close();
	system("pause");
}

void modificarInformacionParqueadero(){
    encabezado();
    bool verificacion=false, seguir=false, seguir2=false;
    char tecla[1];
    char opcNum[10];
	int opc=-1, max_carros=0;

    cout<<"\t<--MOFICICAR INFORMACION DE PARQUEADERO-->"<<endl<<endl;
    do{
        cout<<"Presione uan tecla para continuar, de lo contrario pulse s para volver al menu administrar"<<endl;
        cin>>tecla;
        verificacion=recorrerCadena(tecla,1);
        getch();
        for(int i=0;i<1;i++){
            if(tecla[i]=='S'||tecla[i]=='s'){
                cout<<"Presione una opcion valida"<<endl;
                system("pause");
            }
        }

    }while(verificacion);
    verificacion=false;

    fstream escrituraParqueadero("parqueadero.dat", ios::out|ios::binary);
    if(escrituraParqueadero.is_open()){
        cout<<"Ingrese el nuevo Nombre del Parqueadero: ";
        fflush(stdin);
        cin.getline(x[0].nombre_parqueadero,arrnombrepar);
        do{
            cout<<"Ingrese el nuevo nombre completo del propietario: ";
            fflush(stdin);
            cin.getline(x[0].propietario,arrpropietario);
            verificacion=recorrerCadena(x[0].propietario, 1);//EN EL SEGUNDO PARAMETRO DEFINE SI EL CARACTER TIENE QUE SER NUMEROS SOLAMENTE O LETRAS SOLAMENTE
        }while(verificacion);                                //ESTE PARAMEMETRO ES int TipoCadena. 1 ES PARA SOLAMENTE LETRAS, 0 ES PARA NUMEROS SOLAMENTE
        verificacion=false;

        do{
            cout<<"Ingrese el nuevo nit de su establecimiento: ";
            fflush(stdin);
            cin>>x[0].nit;
            verificacion=recorrerCadena(x[0].nit, 0);
        }while(verificacion);
        verificacion=false;



        cout<<"Ingrese la nueva direccion de su establecimiento: ";
        fflush(stdin);
        cin.getline(x[0].direccion,arrdireccion);

        system("pause");
        system("cls");
        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\tELECCION DE LA NUEVA DEMANDA ZONAL"<<endl;
                cout<<"\t1. USAQUEN                 "<<endl;
                cout<<"\t2. CHAPINERO               "<<endl;
                cout<<"\t3. SANTA FE                "<<endl;
                cout<<"\t4. SAN CRISTOBAL           "<<endl;
                cout<<"\t5. USME                    "<<endl;
                cout<<"\t6. TUNJUELITO              "<<endl;
                cout<<"\t7. BOSA                    "<<endl;
                cout<<"\t8. KENNEDY                 "<<endl;
                cout<<"\t9. FONTIBON                "<<endl;
                cout<<"\t10. ENGATIVA               "<<endl;
                cout<<"\t11. SUBA                   "<<endl;
                cout<<"\t12. BARRIOS UNIDOS         "<<endl;
                cout<<"\t13. TEUSAQUILLO            "<<endl;
                cout<<"\t14. LOS MARTIRES           "<<endl;
                cout<<"\t15. ANTONIO NARINIO        "<<endl;
                cout<<"\t16. PUENTE ARANDA          "<<endl;
                cout<<"\t17. LA CANDELARIA          "<<endl;
                cout<<"\t18. RAFAEL URIBE URIBE     "<<endl;
                cout<<"\t19. CIUDAD BOLIVAR         "<<endl;
                cout<<"\t20. SUMAPAZ                "<<endl;
                cout<<"OPCION:  ";
                cin>>opcNum;

                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);

            verificacion=false;
            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }
            switch(opc){
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 16:
                case 18:
                case 19:
                case 20:
                    x[0].demandaZonal=0.8;
                    break;
                case 1:
                case 2:
                case 3:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                    x[0].demandaZonal=1;
                    break;
                default:
                    cout<<"Ingrese un valor correcto"<<endl;
                    system("pause");
                    seguir=true;
            }
        }while(seguir);


        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\tELECCION DEL PISOS DEL PARQUEADERO"<<endl;
                cout<<"\t1. A NIVEL"<<endl;
                cout<<"\t2. SUBTERRANEO"<<endl;
                cout<<"\t3. 1 PISO"<<endl;
                cout<<"\t4. 2 PISOS"<<endl;
                cout<<"\t5. 3 PISOS"<<endl;
                cout<<"\t6. 4 O MAS PISOS"<<endl;
                cout<<"OPCION:  ";
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);

            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }
            if(opc>6||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].pisoParqueadero=opc;
                seguir=false;
            }
        }while(seguir);


        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\t\tELECCION DEL NUEVO TIPO DE PARQUEADERO"<<endl;
                cout<<"\t1. PARQUEADERO CUBIERTO"<<endl;
                cout<<"\t2. PARQUEADERO ABUERTO"<<endl;
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum , "%d", &opc);
            }

            if(opc>2||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].tipoParqueadero=opc;
                seguir=false;
            }
        }while(seguir);

        do{
            do{
                cout<<"--------------------------------------------------------------"<<endl;
                cout<<"\t\tELECCION TIPO DE PISO DEL PARQUEADERO"<<endl;
                cout<<"\t1. PISO EN ASFALTO"<<endl;
                cout<<"\t2. PISO EN CONCRETO"<<endl;
                cout<<"\t3. PISO EN GRAVILLA"<<endl;
                cout<<"\t4. PISO EN CESPED"<<endl;
                cout<<"\t5. PISO EN AFIRMADO"<<endl;
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);

            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &opc);
            }

            if(opc>5||opc<=0){
                cout<<"Ingrese un valor valido..."<<endl;
                system("pause");
                seguir=true;
            }else{
                x[0].tipoPisoParqueadero=opc;
                seguir=false;
            }
            system("pause");
            system("cls");
        }while(seguir);

        DemandaZonalCarros();
        DemandaZonalMotos();
        do{
            color(Color_Rojo);
            cout<<"OJO: La multiplicación de las filas y las columnas de su parqueadero deben coincidir con la sumatoria del maximo de autos y moticicletas."<<endl<<endl;
            color(Color_Amarillo);

            do{
                cout<<"Ingrese las nuevas filas de aparcamiento: ";
                fflush(stdin);
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum,0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum,"%d",&fila);
                x[0].filas=fila;
            }

            do{
                cout<<"Ingrese las nuevas columnas de su aparcamiento: ";
                fflush(stdin);
                cin>>opcNum;
                verificacion=recorrerCadena(opcNum, 0);
            }while(verificacion);
            verificacion=false;

            if(!verificacion){
                sscanf(opcNum, "%d", &columna);
                x[0].columnas=columna;
            }

            do{
                do{
                    cout<<"Ingrese la cantidad de carros que soporta su estacionamiento. Con autos cuente particulares, camiones, SUVs, entre otros. "<<endl;
                    cout<<"La cantidad de carros debe ser mínimo de 20 AUTOS: ";
                    fflush(stdin);
                    cin>>opcNum;//x[0].max_carros;
                    verificacion=recorrerCadena(opcNum,0);

                }while(verificacion);
                verificacion=false;

                if(!verificacion){
                    sscanf(opcNum, "%d", &x[0].max_carros);
                }
                if(x[0].max_carros<20){
                    cout<<"Recuerde que la cantidad mínima de autos es de 20..."<<endl<<endl;
                    seguir=true;
                }else{
                    max_carros=x[0].max_carros;
                    seguir=false;
                }
            }while(seguir);

            do{
                cout<<"Ingrese la cantidad de motocicletas que soporta su establecimiento. ";
                cout<<"La cantidad de motocicletas debe ser mínimo de 10 motocicletas: ";
                fflush(stdin);
                cin>>x[0].max_motos;

                if(x[0].max_motos<10){
                    cout<<"Recuerde que la cantidad mínima de motocicletas es de 10..."<<endl;
                }else{
                    seguir=false;
                }

            }while(seguir);

            if((x[0].max_motos+x[0].max_carros)!=(x[0].filas*x[0].columnas)){
                cout<<"La multiplicacion de las filas y columnas del parqueadero no coincide con la sumatoria de numero de autos y motos."<<endl<<endl;
                system("pause");
                seguir2=true;
            }else{
                seguir2=false;
            }
        }while(seguir2);
        escrituraParqueadero.write((char*)x, 100*sizeof(parqueadero));

    }
    escrituraParqueadero.close();

    fstream lecturaParking("parqueadero.dat", ios::in|ios::binary);
    if(lecturaParking.is_open()){
        lecturaParking.read((char*)x, 100*sizeof(parqueadero));
    }
}

void salir (){
	color(Color_Defecto);
	cout<<"Vas a salir del programa"<<endl;
	system("pause");
}
