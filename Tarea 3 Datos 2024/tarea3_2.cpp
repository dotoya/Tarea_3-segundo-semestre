#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Plato {
    std::string nombre ;
    int precio ;
};

class Pedido {
    private :
    Plato * platos ; // arreglo de platos en el pedido , tama ñ o inicial 25
    bool servir ; // true para servir , false para llevar
    size_t cant_platos ;

    public :
    Pedido (bool servir) : platos(new Plato[25]), servir(servir), cant_platos(0) {

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
    int precio_total (){
        int n= 0;
        int precio_d= 0;
        while(platos[n].precio != 0){
            precio_d += platos[n].precio;
            n+=1;
        };
        return precio_d;
    } ; // retorna la suma del precio de todos los platos del pedido
};

class Registro {
    private :
    Pedido * pedidos ; // arreglo de pedidos , tama ñ o inicial n ( cantidad de mesas )
    size_t size ;
    void ajustar_arreglo () ; // ajusta el tama ñ o de la tabla de hashing
    int ganancias ;

    public :
    Registro () ;
    ~ Registro () ;
    void agregar_pedido ( Pedido * pedido ) ;
    Pedido * get_pedido ( int id , bool tipo ) ; // Retorna el pedido según id y tipo ( servir true llevar false )
    Pedido * eliminar_pedido ( int id , bool tipo ) ; // Elimina el pedido seg ú n id y tipo
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

    Pedido* prueba= new Pedido(true);
    prueba->agregar_plato(&Orden[0]);
    prueba->agregar_plato(&Orden[4]);
    cout<<prueba->precio_total()<<endl;




    delete[] Orden;
    delete[] l_m;
    file.close();
    return 0;
}