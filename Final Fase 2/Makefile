CC = gcc
CFLAGS = -Wall -Wextra -g -Wno-unused-parameter -O3 $(shell pkg-config --cflags glib-2.0)  # Adicione quaisquer outras flags de compilação necessárias
LDFLAGS = $(shell pkg-config --libs glib-2.0)  # Adicione quaisquer outras flags de linking necessárias

# Lista dos arquivos .c
SOURCES =  src/program.c src/main.c src/user.c src/catalogUser.c src/queries.c src/utils.c src/music.c src/catalogMusic.c src/artist.c src/catalogArtist.c src/validation.c src/album.c src/catalogAlbum.c src/history.c src/catalogHistory.c
# Objetos correspondentes aos arquivos .c
OBJECTS = $(SOURCES:.c=.o)

# Nome do executável
EXECUTABLE = programa-principal

# Regra de compilação para cada arquivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude

# Regra para o executável
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) -Iinclude $(LDFLAGS)

# Remove arquivos .o e o executável
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)