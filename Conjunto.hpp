
template <class T>
Conjunto<T>::Conjunto() {
    // Completar
    _raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    destr_Aux(_raiz);
}

//ayudante del destructor
template <class T>
void Conjunto<T>::destr_Aux(Nodo* nodo){
    if(nodo == nullptr){
        return;
    }
    //llamo recursivamente a la funcion con sus hijos
    destr_Aux(nodo->izq);
    destr_Aux(nodo->der);
    //borro al nodo en cuestion
    delete nodo;
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if(_raiz == nullptr){
        return false;
    }else{
        return perteneceAux(clave, _raiz);
    }
}
template <class T>
bool Conjunto<T>::perteneceAux(const T& clave, const Nodo* nodo) const {
    //si el nodo buscado coincide con el actual
    if (clave == nodo->valor){
        return true;
    }else{
        if(clave > nodo->valor){
            //en caso de que la key buscada sea mayor al nodo acutal,
            //me muevo hacia la derecha
            //si descubro que alli no hay nada, entonces la key buscada no puede
            //estar en el ABB, pues de estarlo deberia estar a la derecha del
            //nodo anterior
            if(nodo->der == nullptr){
                return false;
            }else{
                //sigo buscando por las ramas derechas
                return perteneceAux(clave, nodo->der);
            }
        }else{
            //en caso de que la key buscada sea menor al nodo acutal,
            //me muevo hacia la izquierda
            //si descubro que alli no hay nada, entonces la key buscada no puede
            //estar en el ABB, pues de estarlo deberia estar a la izquierda del
            //nodo anterior
            if(nodo->izq == nullptr){
                return false;
            }else{
                //sigo buscando por las ramas izquierdas
                return perteneceAux(clave, nodo->izq);
            }
        }
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    //antes que nada, debo asegurarme que la key que quiere insertar
    //el usuario no pertenezca ya a mi arbol
    if (pertenece(clave)){
        return;
    }else{
        //si el root pointer no apunta a nada, significa que nuestro
        //arbol esta vacio. El nuevo nodo que se esta creando debe
        //ser entonces la raiz del arbol
        if (_raiz == nullptr){
            _raiz = new Nodo(clave);
        }else{
            //en caso de que el arbol no este vacio, insertamos
            //acordemente, manteniendo la estructura del BST
            insertarAux(clave, _raiz);
        }
    }
}

template <class T>
void Conjunto<T>::insertarAux(const T& clave, Nodo* nodo) {
    if(clave > nodo->valor){
        //voy a la derecha
        //y me fijo si alli no hay nada. En caso de que no lo haya,
        //inserto el elemento dado por el usuario
        if (nodo->der == nullptr){
            //no es necesario crear una nueva variable en el stack, is just for the laughs
            //lo que si es necesario es crear una nueva variable en el heap
            Nodo* new_nodo = new Nodo(clave);
            nodo->der = new_nodo;
            //y salgo de la funcion
            return;
        }else{
            //continuo la busqueda, como este nodo de la derecha no apunta al null,
            //puedo pasarlo sin problemas a la funcion sin miedo de caer en un
            //segmentation fault cuando quiera ver sus hijos a derecha y a izquierda
            //(al hacer el nodo->righ o nodo->left)
            insertarAux(clave, nodo->der);
        }
    }else{
        //voy a la izquierda
        //y me fijo si alli no hay nada. En caso de que no lo haya,
        //inserto el elemento dado por el usuario
        if (nodo->izq == nullptr){
            Nodo* new_nodo = new Nodo(clave);
            nodo->izq = new_nodo;
            //y salgo de la funcion
            return;
        }else{
            //continuo la busqueda, como este nodo de la izquierda no apunta al null,
            //puedo pasarlo sin problemas a la funcion sin miedo de caer en un
            //segmentation fault cuando quiera ver sus hijos a derecha y a izquierda
            //(al hacer el nodo->righ o nodo->left)
            insertarAux(clave, nodo->izq);
        }
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    removerAux(clave, _raiz);
}

template <class T>
void Conjunto<T>::removerAux(const T& clave, Nodo* padre) {
    if (_raiz != nullptr){ //si el arbol es no vacio
        if(_raiz->valor == clave){
            //si la key a eliminar es la raiz
            eliminarRaiz();
            return;
        }else{  //si la key a eliminar no es la raiz, veo si la encuentro, y actuo en consecuencia
            if((clave < padre->valor) && (padre->izq != nullptr)){
                //si la llave que busco es menor al nodo donde estoy parado,
                //entonces la clave, si esta, va a estar a la izquierda
                //No solo eso, antes de avanzar debo asegurarme que el nodo
                //hijo de la izquierda no apunte al null. No importa que
                //la clave sea menor en el nodo donde estoy parado si al avanzar
                //no llego a nada.


                //EL problema es que no puedo volver para atras.
                //EL nodo padre anterior va a seguir apuntando a la direccion
                //de memoria que acabo de liberar.
                //La solucion esta en ir mirando desde atras para adelante. Si miro desde el padre
                //y me doz cuenta que alguno de mis hijos es aquel que debe ser borrado,
                //voy a poder no solo liberar ese espacio de memoria, sino que voy a poder
                //apuntar mi brazo que apuntaba a ese hijo al nullptr ahora.
                if (padre->izq->valor == clave){
                    //encontramos al nodo a borrar, a izquierda del padre
                    return eliminarMatch(padre, padre->izq, true);
                }else{
                    //no encontramos al nodo, seguimos buscando por la izquierda, donde sabemos
                    //que hay un hijo
                    return removerAux(clave, padre->izq);
                }

            }else if(padre->der != nullptr){ //si no era menor, debe ser mayor. SOlo debo cheuqear que haya algo a derecha
                //si la clave que busco es mayor al nodo donde estoy parado,
                //entonces la clave, si esta, esta a la derecha
                if(padre->der->valor == clave){
                    //encontramos al nodo a borrar, a derecha del padre
                    return eliminarMatch(padre, padre->der, false);
                }else{
                    //no encontramos al nodo, seguimos buscando por la derecha, donde sabemos
                    //que hay algo
                    return removerAux(clave, padre->der);
                }
            }else{ //si no habia nada ni a izquierda ni derecha, ya no vamos a encontrar a ese elemento
                //cout << "La key " << clave << " no esta en el arbol" << endl;
                return;
            }
        }
    }else{
        //cout << "El arbol esta vacio" << endl;
        return;
    }
}
template <class T>
void Conjunto<T>::eliminarMatch(Nodo* padre, Nodo* match, const bool izq) {
    if(_raiz != nullptr){
        Nodo* aBorrar;
        int matchKey = match->valor;

        //caso 0 - 0 hijos
        if(match->izq == nullptr && match->der == nullptr){
            //este caso se va a encargar tanto de si el nodo a borrar
            //es hoja izquierda o derecha del nodo padre
            //(es decir, es un hijo suyo que no tiene hijos y debe ser borrado
            //por virgacho)
            aBorrar = match;
            izq == true ?	//si es hoja izquierda
                    padre->izq = nullptr :   //el padre apunta por izquierda al null ahora
                    padre->der = nullptr;	//si no es hoja izquierda, el padre apunta al null por derecha ahora
            //ahora que nos aseguramos que el padre ya no apunta a este hijo hoja,
            //liberamos la memoria del nodo match hoja
            delete aBorrar;
        }else if(match->izq == nullptr && match->der != nullptr){   //caso 1 - 1 hijo (el derecho)
            //Vamos a conectar al padre con su nieto, dejando al hijo match fuera del loop.
            //Luego borramos al hijo que tuvo un solo hijo.
            //En palabras de la catedra: "El hijo se convierte en padre"
            izq == true ?
                    padre->izq = match->der : //si el hijo match es el hijo izquierdo, ahora el padre apunta a su nieto por izquierda
                    padre->der = match->der; //si es el derecho, ahora el padre apunta a su nieto por derecha
            //si bien no es necesario hacer que el match apunte al null en vez de a su unico
            //hijo (ya que lo vamos a borrar), lo hacemos
            match->der = nullptr;
            aBorrar = match; //esto no es necesario, pero es buena practica borrar aquello
            //que el pointer borrador apunta a borrar
            delete aBorrar;
        }else if(match->izq != nullptr && match->der == nullptr){   //caso 1 - 1 hijo (el izquierdo)
            //Vamos a conectar al padre con su nieto, dejando al hijo match fuera del loop.
            //Luego borramos al hijo que tuvo un solo hijo.
            //En palabras de la catedra: "El hijo se convierte en padre"
            izq == true ?
                    padre->izq = match->izq : //si el hijo match es el hijo izquierdo, ahora el padre apunta a su nieto por izquierda
                    padre->der = match->izq; //si es el derecho, ahora el padre apunta a su nieto por derecha
            //si bien no es necesario hacer que el match apunte al null en vez de a su unico
            //hijo (ya que lo vamos a borrar), lo hacemos
            match->izq = nullptr;
            aBorrar = match; //esto no es necesario, pero es buena practica borrar aquello
            //que el pointer borrador apunta a borrar
            delete aBorrar;
        }else{   //caso 3 - 2 hijos
            //la idea aca es buscar al sucesor inmediato del match, y reemplazar su data
            //en el nodo match, para despues eliminar ese nodo de donde sacamos la data
            int keySucesorMatch = getMinimoSubArbol(match->der);
            //eliminamos ese nodo, a partir del arbol del match
            removerAux(keySucesorMatch, match);
            //reemplazamos la data
            match->valor = keySucesorMatch;

        }

    }else{
        //cout << "No pude remover el nodo" << endl;
        return;
    }
}

template <class T>
void Conjunto<T>::eliminarRaiz() {
    if (_raiz != nullptr){
        Nodo* aBorrar = _raiz;
        int rootKey = _raiz->valor;

        //caso 0 - 0 hijos:
        if(_raiz->izq == nullptr && _raiz->der == nullptr){
            //apuntamos el root al null, ya no queremos que apunte
            //al nodo que tiene la raiz
            _raiz = nullptr;
            //por esto guardamos la direccion del root, ahora podemos liberar
            //ese espacio al que acabamos de dejar de apuntar con root
            delete aBorrar;
        }else if(_raiz->izq == nullptr && _raiz->der != nullptr){         //caso 1 - 1 hijo
            //el hijo unico se convierte en padre. Para ello,
            //el root pasa a apuntar al hijo derecho (el unico en este caso)
            _raiz = _raiz->der;
            //sin embargo, el nodo que antes era root sigue apuntando al que ahora
            //es el padre. Debemos hacer que apunte al null
            aBorrar->der = nullptr; //esto no es necesario, pero better safe than sorry
            //liberamos la memoria en la direccion del root que acabamos de perder,
            //pero que guardamos en la variable aBorrar en el stack
            delete aBorrar;
        }else if(_raiz->izq != nullptr && _raiz->der == nullptr){         //caso 1 - 1 hijo
            //el hijo unico se convierte en padre. Para ello,
            //el root pasa a apuntar al hijo izquierdo (el unico en este caso)
            _raiz = _raiz->izq;
            //sin embargo, el nodo que antes era root sigue apuntando al que ahora
            //es el padre. Debemos hacer que apunte al null
            aBorrar->izq = nullptr; //esto no es necesario, pero better safe than sorry
            //liberamos la memoria en la direccion del root que acabamos de perder,
            //pero que guardamos en la variable aBorrar en el stack
            delete aBorrar;
        }else{   //caso 2 -- 2 hijos
            //el sucesor es el menor de los mayores, es decir, el menor
            //del arbol hijo derecho (de la raiz en este caso)
            int keySucesorRaiz = getMinimoSubArbol(_raiz->der);
            //como este nodo es una hoja, puedo eliminarlo sin que afecte
            //a otros nodos
            //para hacerlo correctamente y asegurarme que el nodo anterior
            //al sucesor apunte al null, uso la funcion que construi antes,
            //buscando este valor a borrar en todo el arbol
            removerAux(keySucesorRaiz, _raiz);
            //sobreescribo la info de la raiz con la info del sucesor inmediato de la raiz
            _raiz->valor = keySucesorRaiz;
            //no necesito liberar mas nada, porque sigo usando el nodo raiz, solo que
            //le cambie la data, la cara. Liberar ya libere al nodo sucesor
            //inmediato de la raiz, al usar la funcion eliminarAux.
        }



    }else{
        //cout << "No se puede eliminar la raiz de un arbol vacio" << endl;
        return;
    }
}


template <class T>
const T& Conjunto<T>::getMinimoSubArbol(Conjunto<T>::Nodo* padre) const {
    if(padre != nullptr){
        if(padre->izq == nullptr){
            return padre->valor;
        }else{
            return getMinimoSubArbol(padre->izq);
        }
    }else{
        return 0;
    }
}

template <class T>
const T& Conjunto<T>::getMaximoSubArbol(Conjunto<T>::Nodo* padre) const {
    if(padre != nullptr){
        if(padre->der == nullptr){
            return padre->valor;
        }else{
            return getMaximoSubArbol(padre->der);
        }
    }else{
        return 0;
    }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    return siguienteAux(_raiz, nullptr,clave);
}

template <class T>
const T& Conjunto<T>::siguienteAux(Nodo* parent, Nodo* succ, const T& key) const{
    //caso base
    if (parent == nullptr) {
        return succ->valor;
    }
    if (parent->valor == key){
        //si se encuentra el nodo buscado, el sucesor es el minimo del subarbol de la derecha
        //(si es que tiene)
        if (parent->der != nullptr) {
            //si hay subarbol derecho, doy el minimo de dicho subarbol
            return getMinimoSubArbol(parent->der);
        }
    } else if (key < parent->valor) {
        //en caso de que el nodo actual sea menor a la clave a la cual queremos
        // encontrar el sucesor, sigo buscando por la izq.
        //me guardo el ultimo giro a la izquierda, y continuo la recursion
        succ = parent;
        return siguienteAux(parent->izq, succ, key);
    } else {
        //si la clave a la cual queremos encontrar el sucesor es mayor que el nodo
        //actual, continuamos la recursion por la derecha
        return siguienteAux(parent->der, succ, key);
    }
    //devuelvo al sucesor
    return succ->valor;
}
/*
 Si ocurriera que despues de dar un giro a la izquierda continua bajando por la derecha
 y llega a un nodo que no tiene subarbol derecho ni izquierdo, devuelve lo que guardo
 del ultimo giro a la iquierda antes de seguir avanzando por la derecha
 */

template <class T>
const T& Conjunto<T>::minimo() const {
    return getMinimoSubArbol(_raiz);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return getMaximoSubArbol(_raiz);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalAux(_raiz);
}
template <class T>
unsigned int Conjunto<T>::cardinalAux(const Nodo* nodo) const {
    if(nodo == nullptr){
        return 0;
    }
    return 1 + cardinalAux(nodo->izq) + cardinalAux(nodo->der);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

