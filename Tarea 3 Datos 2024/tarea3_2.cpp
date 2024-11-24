#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M;  // Tamaño de la tabla hash, se definirá dinámicamente

#define VACIA -1  // Valor que indica que la ranura está vacía

typedef int tipoClave;

struct tipoInfo {
    // Información del pedido (solo un ejemplo, podrías agregar más detalles)
    int id;
    bool tipo;  // true para servir, false para llevar
    int precio_total;
};

struct ranura {
    tipoClave clave;
    tipoInfo info;
};

ranura* HT;  // Puntero a la tabla hash dinámica

// Función hash (simple mod)
int h(tipoClave k) {
    return k % M;
}

// Función para insertar en la tabla hash
int hashInsert(ranura HT[], tipoClave k, tipoInfo I) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++) {
        pos = (inicio + i) % M;  // Siguiente ranura en la secuencia
    }
    if (HT[pos].clave == k)
        return 0;  // Inserción no exitosa: clave repetida
    else {
        HT[pos].clave = k;
        HT[pos].info = I;
        return 1;  // Inserción exitosa
    }
}

// Función para buscar en la tabla hash
tipoInfo hashSearch(ranura HT[], tipoClave k) {
    int inicio, i;
    int pos = inicio = h(k);
    for (i = 1; HT[pos].clave != VACIA && HT[pos].clave != k; i++) {
        pos = (inicio + i) % M;  // Siguiente ranura en la secuencia
    }
    if (HT[pos].clave == k)
        return HT[pos].info;  // Registro encontrado, búsqueda exitosa
    else {
        tipoInfo noEncontrado;
        noEncontrado.id = -1;
        return noEncontrado;  // Clave no encontrada
    }
}

// Definición de las clases

struct Plato {
    std::string nombre;
    int precio;
};

class Pedido {
private:
    Plato *platos;
    bool servir;  // true para servir, false para llevar
    size_t cant_platos;
    int id;

public:
    Pedido() : platos(new Plato[25]), servir(false), cant_platos(0), id(-1) {}

    ~Pedido() {
        delete[] platos;
    }

    void agregar_plato(Plato *plato) {
        platos[cant_platos].nombre = plato->nombre;
        platos[cant_platos].precio = plato->precio;
        cant_platos += 1;
    }

    int precio_total() {
        int precio_d = 0;
        for (size_t n = 0; n < cant_platos; ++n) {
            precio_d += platos[n].precio;
        }
        return precio_d;
    }

    void definir_TFyID(int Puesto, bool tf) {
        id = Puesto;
        servir = tf;
    }

    int dar_id() {
        return id;
    }

    bool dar_tf() {
        return servir;
    }

    Plato *get_platos() {
        return platos;
    }

    void establecer_cant_platos(size_t cantidad) {
        cant_platos = cantidad;
    }
};

class Registro {
private:
    int ganancias;

public:
    Registro() : ganancias(0) {}

    void agregar_pedido(Pedido *pedido) {
        tipoInfo info;
        info.id = pedido->dar_id();
        info.tipo = pedido->dar_tf();
        info.precio_total = pedido->precio_total();

        // Inserción del pedido en la tabla hash
        int resultado = hashInsert(HT, info.id, info);
        if (resultado == 1) {
            cout << "Pedido insertado exitosamente." << endl;
        } else {
            cout << "Error: Pedido ya existe." << endl;
        }
    }

    Pedido *get_pedido(int id, bool tipo) {
        tipoInfo info = hashSearch(HT, id);
        if (info.id != -1 && info.tipo == tipo) {
            cout << "Pedido encontrado: " << info.id << endl;
            Pedido *pedido = new Pedido();
            pedido->definir_TFyID(info.id, info.tipo);
            return pedido;
        } else {
            cout << "Pedido no encontrado." << endl;
            return nullptr;
        }
    }

    void eliminar_pedido(int id, bool tipo) {
        tipoInfo info = hashSearch(HT, id);
        if (info.id != -1 && info.tipo == tipo) {
            cout << "Pedido eliminado: " << info.id << endl;
            ganancias += info.precio_total;
            // Remover el pedido de la tabla hash
            info.id = VACIA;
            cout << "Ganancias: " << ganancias << endl;
        } else {
            cout << "Pedido no encontrado." << endl;
        }
    }

    float dar_fc() {
        int total_ocupadas = 0;
        for (int i = 0; i < M; i++) {
            if (HT[i].clave != VACIA) {
                total_ocupadas++;
            }
        }
        return (float)total_ocupadas / M;
    }

    // Modificación para ajustar el tamaño de la tabla hash dinámicamente
    void mesas_empezar(int mesas_iniciales) {
        M = mesas_iniciales;  // Asignar el tamaño de la tabla hash según las mesas
        HT = new ranura[M];   // Crear la tabla hash con el nuevo tamaño
        for (int i = 0; i < M; i++) {
            HT[i].clave = VACIA;  // Inicializar las ranuras como vacías
        }
    }
};

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
        cout << l_m[i] << endl;
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

    // Crear la instancia de Registro
    Registro *testing = new Registro();
    
    // Llamar a mesas_empezar con un número de mesas, por ejemplo, 50
    int mesas_iniciales = 10;
    testing->mesas_empezar(mesas_iniciales);  // Tamaño de la tabla hash ajustado
    cout << "Tabla hash de tamaño " << M << " creada." << endl;

    Pedido *prueba = new Pedido();
    prueba->agregar_plato(&Orden[0]);
    prueba->agregar_plato(&Orden[4]);
    prueba->definir_TFyID(4, true);

    testing->agregar_pedido(prueba);
    testing->get_pedido(4, true);
    cout << "Factor de carga: " << testing->dar_fc() << endl;
    testing->eliminar_pedido(4, true);
    
    Registro *Main;
    bool flag = true;
    bool primera_vez= true;
    while(flag){
        string input , acción , exacta, mas_exacta, exacta_res;
        getline(cin,input);
        if(primera_vez==true){
            Main->mesas_empezar(stoi(input));
            primera_vez= false;
        }

        if(input == "cerrar"){
            break;
        }

        size_t espacio_pos = input.find(' ');
        acción = input.substr(0,espacio_pos);
        exacta = input.substr(espacio_pos + 1);
        size_t espacio_pos2= exacta.find(' ');
        mas_exacta= exacta.substr(espacio_pos2+1);
        exacta_res= exacta.substr(0,espacio_pos2);


        if(acción == "registrar"){
            bool sol;
            if(exacta_res=="mesa"){
                sol= true;
            }
            if(exacta_res=="llevar"){
                sol= false;
            }
            Pedido *temporal= new Pedido();
            temporal->definir_TFyID(sol, stoi(mas_exacta));
            bool flag_2= true;
            while(flag_2){
                string frase, orden, plato;
                getline(cin,frase);

                if(frase=="pedir"){
                    Main->agregar_pedido(temporal);
                    cout<<exacta+" Registrado"<<endl;
                    delete[] temporal;
                    break;
                }
                size_t pos_act = frase.find(' ');
                orden = frase.substr(0,pos_act);
                plato = frase.substr(pos_act + 1);
                if(orden=="agregar"){
                    for(int p= 0; p<plat_act; p++){
                        if(Orden[p].nombre==plato){
                            temporal->agregar_plato(&Orden[p]);
                        }
                    }
                }
            }
        }

        if(acción == "sm"){
        
        }

        if(acción == "br"){
        
        }

        if(acción == "wr"){
        
        }
    }


    delete[] Orden;
    delete[] l_m;
    file.close();
    delete testing;  // Liberar memoria
    return 0;
}
