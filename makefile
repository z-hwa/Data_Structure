SDIR= src
ODIR= output

#�b�ܶq�w�q�U �i�}�q�t�� �i�H�˯���Ҧ��ɦW���.c���ɮ� �Φ��@�ӦC��
sources := $(wildcard $(SDIR)/*.c)
#�ھڦC��(sources) �N�ŦX�Ĥ@���ܼƪ��ɦW ��������.output
targets := $(patsubst $(SDIR)/%.c, $(ODIR)/%.output, $(sources))

CC= gcc
CFLAGS= -O3 -std=c11 -Wall

#�sĶ�bSDIR�U�Ҧ�.c��
$(SDIR)/%.o: $(SDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/%.output: $(SDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $<

all: check $(targets)

check:
	mkdir -p $(ODIR)

.PHONY: check all clean

clean:
	rm -f $(SDIR)/*.o $(ODIR)/*.output