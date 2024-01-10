#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "ListLinked.h"
using namespace std;

template <typename V> class HashTable : public Dict<V> {
    
    private:

        int n;
        int max;
        ListLinked<TableEntry<V> >* table;

        int h(string h) {
            int result = 0;
            int size = h.length();
            for(int i = 0; i < size; i++)
                result += int(h[i]);
            return result%max;
        } 

    public:

        HashTable(int size) {
            table = new ListLinked<TableEntry<V> >[size];
            max = size;
            n = 0;  
        } 

        ~HashTable() {
            delete[] table; 
        }

        int capacity() {
            return max;
        } 
        
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
            out << "==============" << endl << endl;
            for(int i = 0; i < th.max; i++){
                out << "== Cubeta " << i << " =="<< endl << endl;
                out << "List => [ ";
                for(int j = 0; j < th.table[i].size(); j++){
                    out <<	"('" << th.table[i][j].key << "' => " << th.table[i][j].value << ")";
                } 
                out << " ]" << endl << endl;
            }  
            out << "==============" << endl << endl;
			return out;
	    }

        V operator[](string key) {
            V value = search(key);
            return value;
        }

        void insert(string key, V value) override {
            int position = h(key); 
            for(int i = 0; i < table[position].size(); i++) {
                if(table[position][i].key == key) 
                    throw runtime_error("Key ya estaba");
            } 
            TableEntry<V> nodo(key, value);
            table[position].append(nodo); 
            n++; 
        }

        V search(string key) override {  
            int position = h(key);
            V value = -1;
            for(int i = 0; i < table[position].size(); i++){
                if(table[position][i].key == key){
                    value = table[position][i].value;
                    break; 
                } 
            } 
            if(value == -1)throw runtime_error("Clave no encontrada");
            return value;
        }    

        V remove(string key) override {
            int i;
            int position = h(key);
            for(i = 0; i < table[position].size(); i++) {
                if(table[position][i].key == key) 
                    break;
            }
            if(i == (table[position].size())) 
                throw runtime_error("Clave no encontrada");
            V result = (table[position].remove(i)).value; 
            n--; 
            return result; 
        }

        int entries() override {
            return n;
        } 

}; 

#endif
