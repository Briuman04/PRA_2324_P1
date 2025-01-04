#include <ostream>
#include "List.h"

template <typename T> 
class ListArray : public List<T> {

    private:
        // miembros privados
        T* arr;
        int max;
        int n;
        static const int MINSIZE = 2;

        //Metodo para redimensionar el array dinamico	
	    void resize(int new_size){
            if (new_size <= max){
                return; //Si nuevo tamaño es menor o igual al actual, no hacemos nada
            }

            T* new_arr = new T[new_size];//Reservamos nueva memoria
            for (int i = 0;i <n;i++){
                new_arr[i] = arr[i]; //Copiamos contenido del array en el nuevo array
            }

            delete[] arr; //liberamos memoria del antiguo array
            arr = new_arr; // Puntero apunta nuevo array
            max = new_size; //Actualizamos cap max
        }

    public:
        // miembros públicos, incluidos los heredados de List<T>
        ListArray() {
            max = MINSIZE;
            arr = new T[max];
            n = 0;
        }

        ~ListArray() {
            delete[] arr;
        }

        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango.");
            } else {
                return arr[pos];
            }
        }

        friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
            out << "[";
            for (int i = 0; i < list.n; i++) {
                out << list.arr[i];
                if (i < list.n - 1) {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }

        void insert(int pos,T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("La posición está fuera del rango.");
            }
            // Desplaza los elementos a la derecha para hacer espacio
            for (int i = n; i > pos; --i) {
                arr[i] = arr[i - 1];
            }
            arr[pos] = e;

            n++;
        }

        void append(T e) override{
           insert(n, e);  // Insertar al final	
        }

        void prepend(T e) override{
            insert(0, e);  // Insertar al principio
        }

        T remove(int pos) override{
            if ( pos < 0 || pos >= n){
                throw std::out_of_range("La posición está fuera de rango.");
            }

            // Guarda el elemento a eliminar para devolverlo
            T removedElement = arr[pos];

            // Desplaza los elementos a la izquierda para llenar el hueco
            for (int i = pos; i < n - 1; ++i) {
                arr[i] = arr[i + 1];
            }

            n--;
            return removedElement;
        }

        T get(int pos) const override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("La posición está fuera del rango.");
            }
            T get = arr[pos];
        
            return get;	
        }

        int search(T e) const override {
            for(int i =0; i< n;i++) {
                if(arr[i] == e) {
                    return i;
                }
            }
            return -1;
        }

        bool empty() const override{

            return n == 0;
        }

        int size() const override{
        
            return n;
        }
};