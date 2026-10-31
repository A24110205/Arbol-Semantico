#ifndef REGLAS_HPP
#define REGLAS_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>

class GestorDeReglas {
public:
    // Mapa para traducir conectores de lenguaje natural a símbolos formales
    std::map<std::string, std::string> conectores;
    
    // Lista de reglas de ejemplo predefinidas utilizando átomos de la A a la T
    std::vector<std::string> baseDeConocimiento;

    GestorDeReglas() {
        // --- 1. DICCIONARIO DE CONECTORES ---
        // Usamos espacios alrededor para evitar reemplazar letras dentro de las palabras
        // Ejemplo: evitar que la "y" de "ayer" se convierta en "a∧er"
        conectores[" y "] = " & ";
        conectores[" o "] = " ∨ ";
        conectores[" entonces "] = " → ";
        conectores[" si y solo si "] = " ↔ ";
        conectores["no "] = "¬";

        // --- 2. REGLAS SIN CONTRADICCIONES (A - T) ---
        // Este es un conjunto satisfacible. No chocan entre sí.
        baseDeConocimiento.push_back("A → B");
        baseDeConocimiento.push_back("B & C → D");
        baseDeConocimiento.push_back("D ∨ E");
        baseDeConocimiento.push_back("E → F");
        baseDeConocimiento.push_back("¬F ∨ G");
        baseDeConocimiento.push_back("G → H");
        baseDeConocimiento.push_back("H ↔ I");
        baseDeConocimiento.push_back("I & J → K");
        baseDeConocimiento.push_back("K → L");
        baseDeConocimiento.push_back("L ∨ M");
        baseDeConocimiento.push_back("M → N");
        baseDeConocimiento.push_back("N ↔ O");
        baseDeConocimiento.push_back("O → P");
        baseDeConocimiento.push_back("P & Q → R");
        baseDeConocimiento.push_back("R → S");
        baseDeConocimiento.push_back("S ↔ T");
        baseDeConocimiento.push_back("A & J → T"); // Regla que conecta extremos
    }

    // Función para estandarizar los conectores en el texto
    std::string traducirConectores(std::string texto) {
        std::vector<std::string> frases;
        for (const auto& par : conectores) {
            frases.push_back(par.first);
        }
        
        // Ordenamos por longitud de mayor a menor para reemplazar " si y solo si " antes que " y "
        std::sort(frases.begin(), frases.end(), [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });

        // Buscar y reemplazar
        for (const auto& frase : frases) {
            std::string simbolo = conectores[frase];
            size_t pos = 0;
            while ((pos = texto.find(frase, pos)) != std::string::npos) {
                texto.replace(pos, frase.length(), simbolo);
                pos += simbolo.length();
            }
        }
        return texto;
    }
};

#endif // REGLAS_HPP