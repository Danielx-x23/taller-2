#include <iostream>
using namespace std;

// El cajón que guarda el número y el gancho al siguiente
struct Nodo {
    int info;      // El número que guarda el cajón
    Nodo* liga;    // El gancho que apunta al próximo
};

// ========== ACTIVIDAD 1 ==========
// Meter al principio de la fila
void insertar_inicio(Nodo* &P, int dato) {
    Nodo* nuevo = new Nodo;     // Hacer un cajón nuevo
    nuevo->info = dato;         // Meterle el número
    nuevo->liga = P;            // El nuevo apunta al que era primero
    P = nuevo;                  // Ahora el nuevo es el primero
    cout << "  Metido " << dato << " al principio.\n";
}

// Mostrar la fila completa
void imprimir(Nodo* P) {
    if (!P) {
        cout << "  La fila esta vacia\n";
        return;
    }
    cout << "  ";
    while (P) {                         // Mientras no se acabe la fila
        cout << P->info;                // Cantar el número
        if (P->liga) cout << " -> ";    // Si hay otro, poner flecha
        P = P->liga;                    // Saltar al siguiente
    }
    cout << " -> NIL\n";                // NIL es el final, como un punto
}

// ========== ACTIVIDAD 2 ==========
// Meter un número DESPUES de otro específico
void insertar_despues_X(Nodo* P, int X, int dato) {
    while (P && P->info != X) P = P->liga;   // Buscar a X
    if (!P) {                                 // Si no lo encontró
        cout << "  Ni mierda, " << X << " no ta en la lista\n";
        return;
    }
    Nodo* nuevo = new Nodo;          // Hacer cajón nuevo
    nuevo->info = dato;              // Ponerle el número
    nuevo->liga = P->liga;           // El nuevo apunta al que seguía
    P->liga = nuevo;                 // El de antes apunta al nuevo
    cout << "  Metido " << dato << " despues de " << X << "\n";
}

// ========== ACTIVIDAD 3 ==========
// Sacar al primero de la fila
void elimina_inicio(Nodo* &P) {
    if (!P) {
        cout << "  Fila vacia, no hay quien sacar\n";
        return;
    }
    Nodo* temp = P;      // Agarrar al primero
    P = P->liga;         // El segundo ahora es el primero
    cout << "  Sacado " << temp->info << " del principio\n";
    delete temp;         // Tirar el cajón viejo
}

// Sacar al último de la fila
void elimina_ultimo(Nodo* &P) {
    if (!P) {
        cout << "  Fila vacia, no hay quien sacar\n";
        return;
    }
    if (!P->liga) {                      // Si solo hay uno
        cout << "  Sacado " << P->info << " (era el unico)\n";
        delete P;
        P = NULL;
        return;
    }
    Nodo* actual = P;
    while (actual->liga->liga) actual = actual->liga;  // Llegar al penúltimo
    cout << "  Sacado " << actual->liga->info << " del final\n";
    delete actual->liga;     // Tirar el último
    actual->liga = NULL;     // El penúltimo ahora es el último
}

// ========== ACTIVIDAD 4 ==========
// Sacar un número específico de la fila
void elimina_X(Nodo* &P, int X) {
    if (!P) {
        cout << "  Fila vacia\n";
        return;
    }
    if (P->info == X) {          // Si el que buscan es el primero
        elimina_inicio(P);       // Usar la función de arriba
        return;
    }
    Nodo* prev = P;              // El de atrás
    Nodo* curr = P->liga;        // El de ahora
    while (curr && curr->info != X) {   // Buscar a X
        prev = curr;
        curr = curr->liga;
    }
    if (!curr) {
        cout << "  " << X << " no ta en la lista\n";
        return;
    }
    prev->liga = curr->liga;     // Saltarse al que van a sacar
    cout << "  Sacado " << X << "\n";
    delete curr;                 // Tirar el cajón
}

// Sacar el que está ANTES de un número específico
void elimina_antes_X(Nodo* &P, int X) {
    if (!P) {
        cout << "  Fila vacia\n";
        return;
    }
    if (P->info == X) {
        cout << "  " << X << " es el primero, no hay nadie antes\n";
        return;
    }
    if (P->liga && P->liga->info == X) {  // Si X es el segundo
        elimina_inicio(P);                // Sacar al primero
        return;
    }
    Nodo* R = P;      // El de atrás atrás
    Nodo* T = P->liga; // El de en medio (el que van a sacar)
    Nodo* Q = T->liga; // El de adelante (el que tiene el X)
    while (Q && Q->info != X) {   // Mover los tres
        R = T;
        T = Q;
        Q = Q->liga;
    }
    if (!Q) {
        cout << "  " << X << " no ta en la lista\n";
        return;
    }
    cout << "  Sacado " << T->info << " (el que taba antes de " << X << ")\n";
    R->liga = Q;        // El de atrás apunta al de adelante, saltándose el de en medio
    delete T;           // Tirar el del medio
}

// Sacar el que está DESPUES de un número específico
void elimina_despues_X(Nodo* P, int X) {
    while (P && P->info != X) P = P->liga;   // Buscar a X
    if (!P) {
        cout << "  " << X << " no ta en la lista\n";
        return;
    }
    if (!P->liga) {
        cout << "  " << X << " es el ultimo, no hay nadie despues\n";
        return;
    }
    Nodo* temp = P->liga;                // Agarrar al que sigue
    cout << "  Sacado " << temp->info << " (el que taba despues de " << X << ")\n";
    P->liga = temp->liga;               // Saltarse al que van a sacar
    delete temp;                        // Tirar el cajón
}

// ========== EL MENÚ ==========
int main() {
    Nodo* lista = NULL;   // La fila empieza vacia
    int opcion, dato, X;
    
    cout << "\n==========================================\n";
    cout << "   LABORATORIO #2 - LISTAS ENLAZADAS\n";
    cout << "==========================================\n\n";
    
    do {
        cout << "\n--- QUE QUIERES HACER ---\n";
        cout << "1. Meter al principio\n";
        cout << "2. Meter despues de X\n";
        cout << "3. Sacar el primero\n";
        cout << "4. Sacar el ultimo\n";
        cout << "5. Sacar un numero X\n";
        cout << "6. Sacar el que ta ANTES de X\n";
        cout << "7. Sacar el que ta DESPUES de X\n";
        cout << "8. Ver la fila\n";
        cout << "9. Salir\n";
        cout << "Elige: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                cout << "  Numero a meter: ";
                cin >> dato;
                insertar_inicio(lista, dato);
                imprimir(lista);
                break;
            case 2:
                cout << "  Meter despues de: ";
                cin >> X;
                cout << "  Numero a meter: ";
                cin >> dato;
                insertar_despues_X(lista, X, dato);
                imprimir(lista);
                break;
            case 3:
                elimina_inicio(lista);
                imprimir(lista);
                break;
            case 4:
                elimina_ultimo(lista);
                imprimir(lista);
                break;
            case 5:
                cout << "  Numero a sacar: ";
                cin >> X;
                elimina_X(lista, X);
                imprimir(lista);
                break;
            case 6:
                cout << "  Sacar el que ta ANTES de: ";
                cin >> X;
                elimina_antes_X(lista, X);
                imprimir(lista);
                break;
            case 7:
                cout << "  Sacar el que ta DESPUES de: ";
                cin >> X;
                elimina_despues_X(lista, X);
                imprimir(lista);
                break;
            case 8:
                imprimir(lista);
                break;
            case 9:
                cout << "  Chao...\n";
                break;
            default:
                cout << "  Esa opcion no vale\n";
        }
    } while(opcion != 9);
    
    return 0;
}