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

    int precio_total (){
        int n= 0;
        int precio_d= 0;
        while(platos[n].precio != 0){
            precio_d += platos[n].precio;
            n+=1;
        };
        return precio_d;
    } ; // retorna la suma del precio de todos los platos del pedido

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
};

class Registro {
    private :
    Pedido *pedidos ; // arreglo de pedidos , tamaño inicial n (cantidad de mesas)
    size_t size ;
    void ajustar_arreglo () ; // ajusta el tamaño de la tabla de hashing
    int ganancias ;

    public :
    Registro (): size(0), ganancias(0){}

    ~ Registro (){
        delete[] pedidos;
    }

    void agregar_pedido ( Pedido * pedido ){
        bool ocupada= false;
        bool insertado= false;
        int total_casillas= 0;
        int x= 0;

        for(int z= 0; pedidos[z].dar_id()!=0; z++){
            if(pedido->dar_id()==pedidos[z].dar_id()&&pedido->dar_tf()==pedidos[z].dar_tf()){
                ocupada = true;
            }
            total_casillas+=1;
            cout<<total_casillas<<endl;
        }

        if(pedido->dar_tf()==true){
            x= pedido->dar_id()-1;
        }

        if(ocupada==false){
            while(insertado!=true){
                if(pedidos[x].dar_id()==-1){
                    pedidos[x]= *pedido;
                    insertado=true;
                }
                else{
                    x= (x+1)%total_casillas;
                }
            }
        }
        cout<<x<<endl;
        cout<<pedidos[x].dar_id()<<endl;
        cout<<pedidos[x].dar_tf()<<endl;
    } ;

    Pedido * get_pedido ( int id , bool tipo ){
        int w = 0; /*<- positción del pedido en el arreglo*/
        while( pedidos[w].dar_id() != id && pedidos[w].dar_tf() != tipo && w<size){
            w++;
        }

        if(pedidos[w].dar_id() == id && pedidos[w].dar_tf() == tipo){
            cout<<"se encontro el pedido "<<&pedidos[w]<<endl;
            return &pedidos[w];
        }

        else{
            cout<<"no se encontro el pedido solicitado"<<endl;
            return nullptr;
        }
    } ; // Retorna el pedido según id y tipo ( servir true llevar false )

    Pedido * eliminar_pedido ( int id , bool tipo ) ; // Elimina el pedido según id y tipo
    
    void mesas_empezar (int mesas_iniciales){
        size= mesas_iniciales;
        pedidos = new Pedido[size];
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
    





    delete[] Orden;
    delete[] l_m;
    file.close();
    return 0;
}