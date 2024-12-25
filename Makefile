# Nome dell'eseguibile e cartella di output
TARGET = bin/SpaceInvaders

# Cartelle
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include
DATADIR = bin/data  # Cartella per i file di gioco (dentro bin)

# File sorgenti
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# File oggetto corrispondenti
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Opzioni del compilatore
CXX = g++
CXXFLAGS = -Wall -g -I$(INCDIR)   # Include la cartella include per i file .h
LDFLAGS = -lraylib                 # Linka la libreria raylib

# Regola principale per creare l'eseguibile
$(TARGET): $(OBJS) | $(BINDIR) $(DATADIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regola per compilare i file .cpp in file oggetto .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creazione delle directory di output (bin, obj, e data)
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DATADIR):
	mkdir -p $(DATADIR)

# Pulizia
clean:
	rm -rf $(OBJDIR) $(TARGET)
