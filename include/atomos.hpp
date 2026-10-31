#ifndef ATOMOS_HPP
#define ATOMOS_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>

class DiccionarioAtomos {
public:
    // Mapa que relaciona la frase en lenguaje natural con su variable lógica
    std::map<std::string, std::string> atomos;

    DiccionarioAtomos() {
        // 20 átomos inicializados como placeholders.
        // Cuando quieras, cambia la primera cadena por tu frase.
        // Ejemplo: atomos["es de noche"] = "A";
        atomos["es de dia"] = "A";
        atomos["hay luz"] = "B";
        atomos["hace calor"] = "C";
        atomos["es de noche"] = "D";
        atomos["hay niebla"] = "E";
        atomos["hace viento"] = "F";
        atomos["llueve"] = "G";
        atomos["nieva"] = "H";
        atomos["hay trueno"] = "I";
        atomos["J"] = "J";
        atomos["K"] = "K";
        atomos["L"] = "L";
        atomos["M"] = "M";
        atomos["N"] = "N";
        atomos["O"] = "O";
        atomos["P"] = "P";
        atomos["Q"] = "Q";
        atomos["R"] = "R";
        atomos["S"] = "S";
        atomos["T"] = "T";
    }

    // Función para traducir el texto de entrada reemplazando frases por variables
    std::string traducirTexto(std::string texto) {
        // Extraemos las claves y las ordenamos por longitud de mayor a menor.
        // Esto evita que si tienes "gato" y "gato negro", reemplace solo una parte.
        std::vector<std::string> frases;
        for (const auto& par : atomos) {
            frases.push_back(par.first);
        }
        
        std::sort(frases.begin(), frases.end(), [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });

        // Reemplazar las frases encontradas en el texto por la variable
        for (const auto& frase : frases) {
            std::string variable = atomos[frase];
            size_t pos = 0;
            
            // Busca y reemplaza todas las coincidencias
            while ((pos = texto.find(frase, pos)) != std::string::npos) {
                texto.replace(pos, frase.length(), variable);
                pos += variable.length();
            }
        }
        
        return texto;
    }
};

#endif // ATOMOS_HPP