#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M;
#define VACIA -1
typedef int tipoClave;

struct Plato {
    std::string nombre;
    int precio;
};

struct tipoInfo {
    int id;
    bool tipo;
    int precio_total;
    Plato *platos;

    tipoInfo(): platos(new Plato[25]){};
};

struct ranura {
    tipoClave clave;
    tipoInfo info;
};

ranura* HT;

/* ****
* int h
******
* Resumen Función
* Calcula la posición de una clave en la tabla hash usando el algoritmo de dispersión módulo.
******
* Input :
* tipoClave k : Clave a insertar o buscar en la tabla hash.
******
* Returns :
* int, Posición de la clave en la tabla hash.
**** */
int h(tipoClave k) {
    return k % M;
}

/* ****
* int hashInsert
******
* Resumen Función
* Inserta una clave y su información asociada en la tabla hash. Si la clave ya existe, no se realiza la inserción.
******
* Input :
* ranura HT[] : Tabla hash donde se realiza la inserción.
* tipoClave k : Clave que se insertará en la tabla.
* tipoInfo I : Información asociada a la clave que se insertará.
******
* Returns :
* int, 1 si la inserción fue exitosa, 0 si la clave ya existía en la tabla.
**** */
int hashInsert(ranura HT[], tipoClave k, tipoInfo I) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++) {
        pos = (inicio + i) % M; 
    }
    if (HT[pos].clave == k)
        return 0;
    else {
        HT[pos].clave = k;
        HT[pos].info = I;
        return 1;
    }
}

/* ****
* tipoInfo hashSearch
******
* Resumen Función
* Busca una clave en la tabla hash y devuelve la información asociada a la clave si existe.
******
* Input :
* ranura HT[] : Tabla hash donde se realizará la búsqueda.
* tipoClave k : Clave a buscar en la tabla.
******
* Returns :
* tipoInfo, Información asociada a la clave encontrada. Si la clave no se encuentra, devuelve un objeto `tipoInfo` con `id` igual a -1.
**** */
tipoInfo hashSearch(ranura HT[], tipoClave k) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++) {
        pos = (inicio + i) % M;
    }
    if (HT[pos].clave == k)
        return HT[pos].info;
    else {
        tipoInfo noEncontrado;
        noEncontrado.id = -1;
        return noEncontrado;
    }
}

/* ****
* Pedido::Pedido
******
* Resumen Función
* Constructor de la clase Pedido, inicializa los atributos de la clase con valores predeterminados.
******
* Input :
* Ninguno.
******
* Returns :
* Ninguno.
**** */
class Pedido {
private:
    Plato *platos;
    bool servir;
    size_t cant_platos;
    int id;

public:
    /* ****
    * Pedido::Pedido
    ******
    * Resumen Función
    * Constructor de la clase Pedido, inicializa los atributos de la clase con valores predeterminados.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    *Ninguno.
    **** */
    Pedido() : platos(new Plato[25]), servir(false), cant_platos(0), id(-1) {}

    /* ****
    * Pedido::~Pedido
    ******
    * Resumen Función
    * Destructor de la clase Pedido, libera la memoria reservada para los platos.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * Ninguno.
    **** */
    ~Pedido() {
        delete[] platos;
    }

    /* ****
    * void Pedido::agregar_plato
    ******
    * Resumen Función
    * Agrega un plato al pedido, copiando su nombre y precio en el arreglo de platos.
    ******
    * Input :
    * Plato *plato : Puntero al plato a agregar.
    ******
    * Returns :
    * Ninguno.
    **** */
    void agregar_plato(Plato *plato) {
        platos[cant_platos].nombre = plato->nombre;
        platos[cant_platos].precio = plato->precio;
        cant_platos += 1;
    }

    /* ****
    * int Pedido::precio_total
    ******
    * Resumen Función
    * Calcula el precio total del pedido sumando el precio de cada plato en el arreglo de platos.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * int, Precio total del pedido.
    **** */
    int precio_total() {
        int precio_d = 0;
        for (size_t n = 0; n < cant_platos; ++n) {
            precio_d += platos[n].precio;
        }
        return precio_d;
    }

    /* ****
    * void Pedido::definir_TFyID
    ******
    * Resumen Función
    * Define el ID y el tipo de un pedido (mesa o llevar).
    ******
    * Input :
    *int Puesto : ID del pedido.
    * bool tf : Tipo del pedido (true para mesa, false para llevar).
    ******
    * Returns :
    * Ninguno.
    **** */
    void definir_TFyID(int Puesto, bool tf) {
        id = Puesto;
        servir = tf;
    }

    /* ****
    * void Pedido::definir_Pl
    ******
    * Resumen Función
    * Define los platos del pedido, asignando un nuevo arreglo de platos.
    ******
    * Input :
    * Plato *todo : Puntero al nuevo arreglo de platos.
    ******
    * Returns :
    * Ninguno.
    **** */
    void definir_Pl(Plato *todo){
        platos= todo;
    }

    /* ****
    * int Pedido::dar_id
    ******
    * Resumen Función
    * Devuelve el ID del pedido.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * int, ID del pedido.
    **** */
    int dar_id() {
        return id;
    }

    /* ****
    * bool Pedido::dar_tf
    ******
    * Resumen Función
    * Devuelve el tipo del pedido (mesa o llevar).
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * bool, Tipo del pedido (true para mesa, false para llevar).
    **** */
    bool dar_tf() {
        return servir;
    }

    /* ****
    * Plato* Pedido::get_platos
    ******
    * Resumen Función
    * Devuelve el arreglo de platos del pedido.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * Plato*, Puntero al arreglo de platos del pedido.
    **** */
    Plato *get_platos() {
        return platos;
    }

    /* ****
    * void Pedido::establecer_cant_platos
    ******
    * Resumen Función
    * Establece la cantidad de platos en el pedido.
    ******
    * Input :
    * size_t cantidad : Número de platos en el pedido.
    ******
    * Returns :
    * Ninguno.
    **** */
    void establecer_cant_platos(size_t cantidad) {
        cant_platos = cantidad;
    }

    /* ****
    * void Pedido::recuento
    ******
    * Resumen Función
    * Muestra los platos del pedido y su precio total, incluyendo una propina del 10%.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * Ninguno.
    **** */
    void recuento(){
        int suma_f= 0;
        for(int j;platos[j].nombre!= ""; j++){
            cout<<platos[j].nombre<<endl;
            suma_f+= platos[j].precio;
        }
        cout<<"precio total: "<<suma_f<<endl;
    }
};

class Registro {
private:
    int ganancias;
    Pedido *pedidos;
    size_t size;

public:
    /* ****
    * Registro::Registro
    ******
    * Resumen Función
    * Constructor de la clase Registro, inicializa los atributos de la clase con valores predeterminados.
    ******
    * Input :
    * Ninguno.
    ******
    * Returns :
    * Ninguno.
    **** */
    Registro() :size(0), ganancias(0) {}


/* ****
* void Registro::agregar_pedido
******
* Resumen Función
* Agrega un pedido a la tabla hash. Si el pedido ya existe, muestra un mensaje de error.
******
* Input :
* Pedido *pedido : Puntero al pedido a agregar.
******
* Returns :
* Ninguno.
**** */
    void agregar_pedido(Pedido *pedido) {
        tipoInfo info;
        info.id = pedido->dar_id();
        info.tipo = pedido->dar_tf();
        info.precio_total = pedido->precio_total();
        info.platos= pedido->get_platos();

        int resultado = hashInsert(HT, info.id, info);
        if (resultado == 1) {
        } else {
            cout << "Error: Pedido ya existe." << endl;
        }
    }

/* ****
* Pedido* Registro::get_pedido
******
* Resumen Función
* Busca un pedido en la tabla hash según su ID y tipo. Si lo encuentra, lo devuelve, de lo contrario muestra un mensaje de error.
******
* Input :
* int id : ID del pedido a buscar.
* bool tipo : Tipo del pedido (mesa o llevar).
******
* Returns :
* Pedido*, Puntero al pedido encontrado, o nullptr si no se encuentra.
**** */

    Pedido *get_pedido(int id, bool tipo) {
        tipoInfo info = hashSearch(HT, id);
        if (info.id != -1 && info.tipo == tipo) {
            Pedido *pedido = new Pedido();
            pedido->definir_TFyID(info.id, info.tipo);
            pedido->definir_Pl(info.platos);
            
            return pedido;
        } else {
            cout << "Pedido no encontrado." << endl;
            return nullptr;
        }
    }

/* ****
* void Registro::eliminar_pedido
******
* Resumen Función
* Elimina un pedido de la tabla hash y muestra detalles como el precio total y propina.
******
* Input :
* int id : ID del pedido a eliminar.
* bool tipo : Tipo del pedido (mesa o llevar).
******
* Returns :
* Ninguno.
**** */
    void eliminar_pedido(int id, bool tipo) {
        tipoInfo info = hashSearch(HT, id);
        int profit= 0;
        if (info.id != -1 && info.tipo == tipo) {
            for(int l= 0; info.platos[l].nombre!=""; l++){
                cout<<info.platos[l].nombre<<" - "<<info.platos[l].precio<<endl;
                profit+= info.platos[l].precio;
                info.platos[l].nombre= "";
                info.platos[l].precio= 0;
            }
            ganancias+= profit;
            info.id = -1;
            info.precio_total= 0;
            cout << "total: " << profit << endl;
            cout << "propina: " << (profit/10) << endl;
            cout << "total + propina: " << (profit+(profit/10)) << endl;
        } else {
            cout << "Pedido no encontrado." << endl;
        }
        ganancias += (profit+(profit/10));
    }

/* ****
* float Registro::dar_fc
******
* Resumen Función
* Calcula el factor de ocupación de la tabla hash, es decir, la proporción de ranuras ocupadas.
******
* Input :
* Ninguno.
******
* Returns :
* float, Factor de ocupación de la tabla hash.
**** */
    float dar_fc() {
        int total_ocupadas = 0;
        for (int i = 0; i < M; i++) {
            if (HT[i].clave != VACIA) {
                total_ocupadas++;
            }
        }
        return (float)total_ocupadas / M;
    }

/* ****
* void Registro::mesas_empezar
******
* Resumen Función
* Inicializa la tabla hash y la cantidad de mesas disponibles.
******
* Input :
* int mesas_iniciales : Número de mesas que se deben inicializar.
******
* Returns :
* Ninguno.
**** */
    void mesas_empezar(int mesas_iniciales) {
        M = mesas_iniciales; 
        HT = new ranura[M];
        for (int i = 0; i < M; i++) {
            HT[i].clave = VACIA;
        }
        pedidos= new Pedido[M];
    };
};

/* ****
* int main
******
* Resumen Función
* Función principal que gestiona la entrada del usuario, el registro de pedidos y la manipulación de mesas.
******
* Input :
* Ninguno.
******
* Returns :
* int, Código de salida del programa.
**** */
int main() {
    ifstream file;
    file.open("Menu.txt");

    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int cant_platos, plat_act;
    string line, pa, pe, *l_m;
    getline(file, line);
    cant_platos = stoi(line);
    plat_act= cant_platos;

    Plato *Orden;
    Orden = new Plato[cant_platos];
    l_m = new string[cant_platos];

    for (int i = 0; i < cant_platos; i++) {
        getline(file, line);
        l_m[i] = line;
        l_m[i] += ' ';
    }

    for (int j = 0; j < cant_platos; j++) {
        int posac = 0;
        pa = "";
        pe = "";
        for (l_m[j][posac]; l_m[j][posac] != '-'; posac++) {
            pe += l_m[j][posac];
        }
        Orden[j].nombre = pe;

        posac += 1;
        for (l_m[j][posac]; l_m[j][posac] != ' '; posac++) {
            pa += l_m[j][posac];
        }
        Orden[j].precio = stof(pa);
    }


    Registro *testing = new Registro();
    Pedido *prueba = new Pedido();
    int mesas_iniciales;
    
    bool flag = true;
    bool primera_vez = true;

    while(flag) {
        string input, acción, exacta, mas_exacta, exacta_res;
        getline(cin, input);

        if (primera_vez == true) {
            try {

                mesas_iniciales = stoi(input);
                testing->mesas_empezar(mesas_iniciales);
                primera_vez = false;
            } 
            catch (const std::invalid_argument& e) {
                cout << "Error: Entrada no válida para el número de mesas." << endl;
                continue;
            }
            catch (const std::out_of_range& e) {
                cout << "Error: Número de mesas fuera de rango." << endl;
                continue;
            }
        }

        if(input == "cerrar") {
            cout<<"pedidos pendientes: "<<endl;
            break;
        }

        size_t espacio_pos = input.find(' ');
        acción = input.substr(0, espacio_pos);
        exacta = input.substr(espacio_pos + 1);
        size_t espacio_pos2 = exacta.find(' ');
        mas_exacta = exacta.substr(espacio_pos2 + 1);
        exacta_res = exacta.substr(0, espacio_pos2);

        if (acción == "registrar") {
            bool sol;
            if (exacta_res == "mesa") {
                sol = true;
            }
            else if (exacta_res == "llevar") {
                sol = false;
            }

            try {
                prueba->definir_TFyID(stoi(mas_exacta), sol);
            } catch (const std::invalid_argument& e) {
                cout << "Error: ID de mesa o llevar no válido." << endl;
                continue;
            }

            bool flag_2 = true;
            while(flag_2) {
                string frase, orden, plato;
                getline(cin, frase);

                if (frase == "pedir") {
                    testing->agregar_pedido(prueba);
                    cout << exacta + " Registrado" << endl;
                    break;
                }

                size_t pos_act = frase.find(' ');
                orden = frase.substr(0, pos_act);
                plato = frase.substr(pos_act + 1);
                if (orden == "agregar") {
                    for (int p = 0; p < plat_act; p++) {
                        if (Orden[p].nombre == plato) {
                            prueba->agregar_plato(&Orden[p]);
                        }
                    }
                }
            }
        }

        if(acción== "info"){
            bool sol_i;
            if (exacta_res == "mesa") {
                sol_i = true;
            }
            else if (exacta_res == "llevar") {
                sol_i = false;
            }
            (testing->get_pedido(stoi(mas_exacta), sol_i))->recuento();
        }

        if(acción== "pagar"){
            bool sol_a;
            if (exacta_res == "mesa") {
                sol_a = true;
            }
            else if (exacta_res == "llevar") {
                sol_a = false;
            }
            testing->eliminar_pedido(stoi(mas_exacta),sol_a);
            cout<<testing->dar_fc()<<endl;
        }
    }




    delete[] Orden;
    delete[] l_m;
    file.close();
    delete testing;
    return 0;
}
