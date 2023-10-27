SDIR= src
ODIR= output
INC= includeFile

#在變量定義下 展開通配符 可以檢索到所有檔名後綴為.c的檔案 形成一個列表
sources := $(wildcard $(SDIR)/*.c)
#根據列表(sources) 將符合第一個變數的檔名 後綴替換為.output
targets := $(patsubst $(SDIR)/%.c, $(ODIR)/%.output, $(sources))

CC= gcc
CFLAGS= -O3 -std=c11 -Wall

#編譯在SDIR下.c檔
$(SDIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%.output: $(SDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $<

all: check $(targets)

check:
	mkdir -p $(ODIR)

.PHONY: check all clean

clean:
	rm -f $(SDIR)/*.o $(INC)/*.o $(ODIR)/*.output