#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Plato {
    std::string nombre ;
    int precio ;
};

//int cant_mesas; // variable que nos va a servir para formar el arreglo inicial y que no genere errores en caso que se trate de hacer un pedido a la mesa n+1, cuando solo hay n mesas

class Pedido {
    private :
    Plato * platos ; // arreglo de platos en el pedido , tamaño inicial 25
    bool servir ; // true para servir , false para llevar
    size_t cant_platos ;
    int id;

    public :
    Pedido (): platos(new Plato[25]), servir(servir), cant_platos(0), id(-1) {

    };

    ~ Pedido (){
        delete[] platos;
    } ;
    
    void agregar_plato ( Plato* plato ){
        platos[cant_platos].nombre = plato->nombre;
        platos[cant_platos].precio = plato->precio;
        cant_platos += 1;

        cout<<platos[cant_platos-1].nombre<<endl;
    } ; // agrega un plato al pedido

    int precio_total() {
    int precio_d = 0;
    for (size_t n = 0; n < cant_platos; ++n) {
        precio_d += platos[n].precio;
    }
    return precio_d;
    }

    void definir_TFyID(int Puesto, bool tf){
        id= Puesto;
        servir= tf;
        cout<<id<<endl;
        cout<<servir<<endl;
    }

    int dar_id(){
        return id;
    }

    bool dar_tf(){
        return servir;
    }

    Plato* get_platos() {
        return platos;  // Devuelve el arreglo de platos
    }

    void establecer_cant_platos(size_t cantidad) {
        cant_platos = cantidad;
    }
};

class Registro {
    private :
    Pedido *pedidos ; // arreglo de pedidos , tamaño inicial n (cantidad de mesas)
    size_t size ;
    void ajustar_arreglo (); // ajusta el tamaño de la tabla de hashing
    int ganancias ;
    bool ocupa_libr;

    public :
    Registro (): size(0), ganancias(0), pedidos(nullptr){}

    ~Registro (){
        delete[] pedidos;
    }

    void agregar_pedido(Pedido* pedido) {
        bool insertado = false;
        int x = pedido->dar_id() - 1;  // Índice inicial basado en el ID del pedido
        int total_casillas = size;

        while (!insertado) {
            // Verificamos si la casilla está vacía o ya contiene un pedido con la misma ID y tipo
            if (pedidos[x].dar_id() == -1 || (pedidos[x].dar_id() == pedido->dar_id() && pedidos[x].dar_tf() == pedido->dar_tf())) {
                pedidos[x] = *pedido;  // Insertamos el pedido
                insertado = true;
            } 
            else{
                x = (x + 1) % total_casillas;  // Sondeo lineal: nos movemos a la siguiente casilla
            }
        }
        cout << "Pedido insertado en la posición: " << x << endl;
    }

    Pedido* get_pedido(int id, bool tipo) {
        int x = id - 1;  // Índice basado en el ID
        int total_casillas = size;

        while (pedidos[x].dar_id() != -1 && (pedidos[x].dar_id() != id || pedidos[x].dar_tf() != tipo)) {
            x = (x + 1) % total_casillas;  // Sondeo lineal
            if (pedidos[x].dar_id() == -1) {
                cout << "Pedido no encontrado" << endl;
                return nullptr;
            }
        }

        if (pedidos[x].dar_id() == id && pedidos[x].dar_tf() == tipo){
            cout << "Pedido encontrado en la posición: " << x << endl;
            return &pedidos[x];
        }
        return nullptr;
    }

    Pedido* eliminar_pedido(int id, bool tipo) {
        int x = id - 1;  // Índice basado en el ID
        int total_casillas = size;

        while (pedidos[x].dar_id() != -1 && (pedidos[x].dar_id() != id || pedidos[x].dar_tf() != tipo)) {
            x = (x + 1) % total_casillas;  // Sondeo lineal
            if (pedidos[x].dar_id() == -1) {
                cout << "Pedido no encontrado" << endl;
                return nullptr;
            }
        }

        if (pedidos[x].dar_id() == id && pedidos[x].dar_tf() == tipo) {
            // Guardamos los platos y los mostramos antes de eliminar
            Plato* platos = pedidos[x].get_platos();
            int ganan_total = pedidos[x].precio_total();
            for (int i = 0; i < 25; i++) {
                if (platos[i].precio != 0) {
                    cout << platos[i].nombre << " - " << platos[i].precio << endl;
                }
            }

            // Se elimina el pedido
            Plato* platos_eliminar = pedidos[x].get_platos();
            for (int i = 0; i < 25; i++) {
                platos_eliminar[i].nombre = '\0';
                platos_eliminar[i].precio = 0;
            }

            pedidos[x].establecer_cant_platos(0);
            pedidos[x].definir_TFyID(-1, false);  // Indicamos que la casilla está vacía

            float factor_c = dar_fc();
            cout << "Total: " << ganan_total << endl;
            cout << "Propina: " << ganan_total / 10 << endl;
            cout << "Total + Propina: " << ganan_total + (ganan_total / 10) << endl;
            cout << "Factor de carga: " << factor_c << endl;

            ganancias += (ganan_total + (ganan_total / 10));  // Acumulamos las ganancias
            cout << "Pedido eliminado correctamente." << endl;
            return nullptr;
        }

        return nullptr;  // Pedido no encontrado
    }
    
    void mesas_empezar(int mesas_iniciales) {
        size = mesas_iniciales;
        pedidos = new Pedido[size];
        for (int i = 0; i < size; ++i) {
            pedidos[i].definir_TFyID(-1, false);  // Inicializamos todas las casillas como vacías
        }
    }

    float dar_fc() {
        int total_casillas = size;
        int total_ocupadas = 0;

        for (int i = 0; i < total_casillas; ++i) {
            if (pedidos[i].dar_id() != -1) {
                total_ocupadas++;
            }
        }

        return static_cast<float>(total_ocupadas) / total_casillas;
    }
};

int main(){
    ifstream file;
    file.open("Menu.txt");

    if(!file.is_open()){
        cout<<"error al abrir el archivo"<<endl;
        return 1;
    }

    int cant_platos;
    string line , pa, pe, *l_m;
    getline(file, line);
    cant_platos = stoi(line);

    cout<<cant_platos<<endl;

    Plato* Orden;
    Orden = new Plato[cant_platos];
    l_m = new string[cant_platos];

    for(int i = 0; i<cant_platos; i++){
        getline(file,line);
        l_m[i] = line;
        l_m[i] += ' ';

        cout<<l_m[i]<<endl; 
    }

    for(int j = 0; j<cant_platos; j++){
        int posac = 0;
        pa = "";
        pe = ""; 
        for(l_m[j][posac]; l_m[j][posac] != '-' ; posac++){
            pe += l_m[j][posac]; 
        }
        Orden[j].nombre = pe;
        cout<<Orden[j].nombre<<endl;

        posac +=1;
        for(l_m[j][posac]; l_m[j][posac] != ' '; posac++){
            pa += l_m[j][posac];
        }
        Orden[j].precio = stof(pa);

        cout<<Orden[j].precio<<endl;
    }

    Pedido* prueba= new Pedido();
    prueba->agregar_plato(&Orden[0]);
    prueba->agregar_plato(&Orden[4]);
    cout<<prueba->precio_total()<<endl;
    prueba->definir_TFyID(4,true);

    Registro* testing= new Registro();
    testing->mesas_empezar(10);
    testing->agregar_pedido(prueba);
    testing->get_pedido(4 , true);
    testing->get_pedido(0 , false);
    cout<<testing->dar_fc()<<endl;
    testing->eliminar_pedido(4 , true);

    prueba->agregar_plato(&Orden[0]);
    prueba->agregar_plato(&Orden[4]);
    cout<<prueba->precio_total()<<endl;
    prueba->definir_TFyID(4,true);
    testing->get_pedido(4,true);
    cout<<testing->dar_fc()<<endl;




    delete[] Orden;
    delete[] l_m;
    file.close();
    return 0;
}