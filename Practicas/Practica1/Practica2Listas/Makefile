# Makefile para MediExpress
# --------------------------------------------------

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = 

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Archivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BUILD_DIR)/MediExpress

# --------------------------------------------------
# Regla principal
all: $(EXECUTABLE)

# Compilar ejecutable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorio build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar objetos y ejecutable
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)

# Limpiar todo (opcional, si hubiera archivos temporales)
distclean: clean
	rm -rf $(BUILD_DIR)

.PHONY: all clean distclean