#include<iostream>
#include<fstream>
using namespace std;

struct Plato {
    std :: string nombre ;
    int precio ;
};

class Pedido {
    private :
    Plato * platos ; // arreglo de platos en el pedido , tama ñ o inicial 25
    bool servir ; // true para servir , false para llevar
    size_t cant_platos ;

    public :
    Pedido () ;
    ~ Pedido () ;
    void agregar_plato ( Plato * plato ) ; // agrega un plato al pedido
    int precio_total () ; // retorna la suma del precio de todos los platos del pedido
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

    int cant_platos , *precio;
    string line , pa , *plato , *l_m;
    getline(file, line);
    cant_platos = stoi(line);

    cout<<cant_platos<<endl;

    precio = new int[cant_platos];
    plato = new string[cant_platos];
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
        for(l_m[j][posac]; l_m[j][posac] != '-' ; posac++){
            plato[j] += l_m[j][posac]; 
        }

        cout<<plato[j]<<endl;

        posac +=1;
        for(l_m[j][posac]; l_m[j][posac] != ' '; posac++){
            pa += l_m[j][posac];
        }
        precio[j] = stof(pa);

        cout<<precio[j]<<endl;
    }



    delete[] precio;
    delete[] plato;
    delete[] l_m;
    file.close();
    return 0;
}