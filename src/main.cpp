#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "atomos.hpp"
#include "reglas.hpp"

// Librería necesaria para arreglar la consola en Windows
#ifdef _WIN32
#include <windows.h>
#endif

// Estructura para los nodos del árbol semántico
struct LogicNode {
    std::string text;
    sf::Vector2f position;
    std::vector<std::shared_ptr<LogicNode>> children;

    LogicNode(std::string t) : text(t) {}
};

// Función para calcular posiciones de manera recursiva (diseño básico)
void calculatePositions(std::shared_ptr<LogicNode> node, float x, float y, float xOffset) {
    if (!node) return;
    node->position = sf::Vector2f(x, y);
    
    float startX = x - (xOffset * (node->children.size() - 1)) / 2.0f;
    for (size_t i = 0; i < node->children.size(); ++i) {
        calculatePositions(node->children[i], startX + (i * xOffset), y + 100.0f, xOffset / 1.5f);
    }
}

// Función recursiva para dibujar el árbol
void drawTree(sf::RenderWindow& window, std::shared_ptr<LogicNode> node, const sf::Font& font) {
    if (!node) return;

    // Dibujar líneas hacia los hijos
    for (auto& child : node->children) {
        sf::Vertex line[] = {
            sf::Vertex(node->position + sf::Vector2f(0, 15), sf::Color::White),
            sf::Vertex(child->position - sf::Vector2f(0, 15), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, child, font); // Llamada recursiva
    }

    // Dibujar el nodo (Texto)
    sf::Text textNode;
    textNode.setFont(font);
    
    // CORRECCIÓN SFML: Le decimos explícitamente que el texto está en UTF-8
    textNode.setString(sf::String::fromUtf8(node->text.begin(), node->text.end()));
    
    textNode.setCharacterSize(18);
    textNode.setFillColor(sf::Color::Green);
    
    // Centrar el texto
    sf::FloatRect textRect = textNode.getLocalBounds();
    textNode.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textNode.setPosition(node->position);

    // Fondo del nodo
    sf::RectangleShape bg(sf::Vector2f(textRect.width + 20, textRect.height + 10));
    bg.setOrigin(bg.getSize().x / 2.0f, bg.getSize().y / 2.0f);
    bg.setPosition(node->position);
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setOutlineThickness(1);
    bg.setOutlineColor(sf::Color::White);

    window.draw(bg);
    window.draw(textNode);
}

std::shared_ptr<LogicNode> buildMockSemanticTree(std::string rootText) {
    auto root = std::make_shared<LogicNode>(rootText);
    
    // Nodo simulado (Nota que ahora podemos usar ¬ directamente aquí si queremos)
    auto notP = std::make_shared<LogicNode>("¬P");
    auto q = std::make_shared<LogicNode>("Q");
    root->children.push_back(notP);
    root->children.push_back(q);

    return root;
}

int main() {
    // CORRECCIÓN CONSOLA: Forzar a la consola de Windows a usar UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Instanciamos ambos diccionarios
    DiccionarioAtomos diccAtomos;
    GestorDeReglas gestorReglas;
    
    // Configuramos los átomos para esta prueba
    diccAtomos.atomos["es de dia"] = "A";
    diccAtomos.atomos["hay luz"] = "B";
    diccAtomos.atomos["hace calor"] = "C";
    
    std::string textoEntrada;
    
    std::cout << "--------------------------------------------------\n";
    std::cout << "Ejemplo de ingreso: es de dia y hace calor entonces hay luz\n";
    std::cout << "Frase: ";
    std::getline(std::cin, textoEntrada);
    
    // --- PIPELINE DE TRADUCCIÓN ---
    std::string textoFase1 = diccAtomos.traducirTexto(textoEntrada);
    std::string textoFinal = gestorReglas.traducirConectores(textoFase1);
    // ------------------------------
    
    std::cout << "\n[Fase 1] Sustitucion de Atomos: " << textoFase1 << "\n";
    std::cout << "[Fase 2] Estandarizacion Logica: " << textoFinal << "\n";
    std::cout << "Abriendo ventana grafica...\n";
    std::cout << "--------------------------------------------------\n";

    sf::RenderWindow window(sf::VideoMode(800, 600), "Arbol Semantico - SFML");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("segoeui.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
        return -1;
    }

    auto treeRoot = buildMockSemanticTree(textoFinal);
    calculatePositions(treeRoot, 400.0f, 50.0f, 250.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(30, 30, 30));
        drawTree(window, treeRoot, font);
        window.display();
    }

    return 0;
}