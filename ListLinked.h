#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
    private:
	    Node<T>* first;
	    int max;
	    int n;

    public:
	    ListLinked() {
		    first = nullptr;
		    n = 0;
	    }

	    ~ListLinked(){
		    Node<T>* current = first;
		    Node<T>* next;

            while (current != nullptr){
                next = current->next;
                delete current;
                current = next;
            }

            first = nullptr;
            n = 0;
	    }

	    T operator[](int pos) {
		    if(pos < 0 || pos >= n) {
			    throw std::out_of_range ("El valor está fuera del intervalo.");
		    } else {
			    Node<T>* current = first;

                for (int i = 0; i < pos; ++i) {
                    current = current->next;
                }

                return current->data;
		    }
	    }

	    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            Node<T>* actual = list.first;
            
            if (actual == nullptr) {  
                out << "La lista está vacía.";
                return out;
            }
            
            while (actual != nullptr) {
                out << actual->data;

                if (actual->next != nullptr) {
                    out << " -> ";  
                }
                actual = actual->next;  
            }

            return out;
        }

        void insert(int pos, T e)  override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("El índice no se encuentra dentro del intervalo.");
            }

            if (pos == 0) {
                prepend(e);
            } else {
                Node<T>* current = first;
                for (int i = 0; i < pos - 1; ++i) {
                    current = current->next;
                }
                Node<T>* newNode = new Node<T>(e, current->next);
                current->next = newNode;
                n++;
            }
   	    }

        void append(T e) override {
		    insert(n, e);
	    }

	    void prepend(T value) override {
            Node<T>* newNode = new Node<T>(value, first);
            first = newNode;
            n++;
        }

        T remove (int pos) override {
            Node<T>* current = first;
        	T removedData;

            if (pos < 0 || pos >= n) {
           	    throw std::out_of_range("El índice está fuera del intervalo.");
        	}
        	
        	if (pos == 0) {
                removedData = first->data;
                first = first->next;
            	delete current;
        	} else {
                for (int i = 0; i < pos - 1; ++i) {
                    current = current->next;
            	}
            	Node<T>* nodeToRemove = current->next;
            	removedData = nodeToRemove->data;
            	current->next = nodeToRemove->next;
            	delete nodeToRemove;
        	}

        	n--;
        	return removedData;
	    }

        T get(int pos) const override {
		    Node<T>* current = first;
            
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("La posición está fuera del rango.");
            }
            

            for (int i = 0;i < pos; i++) {
                current = current -> next;
            }

            return current->data;
        }

        int search(T e) const override {
            Node<T>* current = first;
        	int index = 0;

        	while (current != nullptr) {
            	if (current->data == e) {
                	return index;
            	}
            	
                current = current->next;
                index++;
        	}	
        	
		    return -1;
	    }

        bool empty() const override {
            if(size() == 0) {
                return true;
            } else {
                return false;
            }
	    }

	    int size() const override {
            return n;
	    }
};