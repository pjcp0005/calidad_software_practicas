//
// Created by jmart on 18/10/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <string_view>

namespace utils{

     /**
     * @brief Convierte un carácter a minúscula de forma segura.
     * @param c Carácter de entrada (debe ser convertible a unsigned char).
     * @return El mismo carácter en minúscula (si procede).
     * @post Usa std::tolower pero recibiendo 'unsigned char' para evitar comportamiento indefinido.
     */
    char toLow(unsigned char c);

    /**
     * @brief Convierte una cadena a minúsculas "in-place".
     * @param s Cadena a normalizar (se modificará).
     * @post Todas las letras ASCII de 's' quedan en minúscula.
     * @warning No realiza normalización Unicode (solo transformación byte a byte).
     */
    void toLowerInPlace(std::string &s);

    /**
     * @brief Devuelve una COPIA de la cadena en minúsculas.
     * @param s Cadena de entrada (se pasa por valor para copiar).
     * @return Nueva cadena idéntica a 's' pero con letras en minúscula.
     * @post No modifica el argumento del llamante, trabaja sobre la copia.
     */
    std::string lowerCopy(std::string s);

    /**
     * @brief Comprueba si 'haystack' contiene 'needle' sin distinguir mayúsculas/minúsculas.
     * @param haystack Cadena "pajar" donde buscar.
     * @param needle   Cadena "aguja" a localizar como subcadena.
     * @return true si 'needle' aparece en 'haystack' (case-insensitive); false en caso contrario.
     * @post La búsqueda se hace convirtiendo copias a minúsculas y usando std::string::find.
     * @note Política con needle vacío: devuelve true (toda cadena contiene la subcadena vacía).
     */
    bool iContains(const std::string &haystack,const std::string &needle);

}

#endif //UTILS_H
