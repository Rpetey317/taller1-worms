#include "CommonMapParser.h"

#include <stdlib.h>
#define VIGA_CORTA 0
#define VIGA_LARGA 1
#include <iostream>
/**
 *
 *  tipo_viga(1) angulo(3) posicion_x(4) posicion_y(4)
 *   0 -> viga corta
 *   1 -> viga larga
 *   2 -> un gusanito, el angulo se va a ignorar para este
 *   proporciones viga: alto -> 19 pixeles. ancho -> 64 pixeles para viga corta, 128 pixeles para
 * viga larga
 *
 */


CommonMapParser::CommonMapParser() {}

std::vector<Tile> CommonMapParser::get_map(std::string file_name) {
    std::fstream archivo;
    std::vector<Tile> map;
    archivo.open(file_name);

    if (!archivo.is_open()) 
        return map;
    
    
    
    char scape;
    char type = ' ';
    char angle[4];
    char pos_x[5];
    char pos_y[5];
    while (!archivo.eof()) {
        archivo.get(type);
        archivo.get(scape);
        archivo.get(angle[0]);
        archivo.get(angle[1]);
        archivo.get(angle[2]);
        angle[3] = 0;
        archivo.get(scape);
        archivo.get(pos_x[0]);
        archivo.get(pos_x[1]);
        archivo.get(pos_x[2]);
        archivo.get(pos_x[3]);
        pos_x[4] = 0;
        archivo.get(scape);
        archivo.get(pos_y[0]);
        archivo.get(pos_y[1]);
        archivo.get(pos_y[2]);
        archivo.get(pos_y[3]);
        pos_y[4] = 0;
        archivo.get(scape);
        Tile tile = {type, atoi(angle), atoi(pos_x), atoi(pos_y)};
        map.emplace_back(tile);
    }

    return map;
}
