#include <stdio.h>
#include <stdint.h>

void usage();
uint32_t read(char *fileName);
uint32_t ntoh(uint32_t x);

int main(int argc, char* argv[])
{
    if(argc != 3){
        usage();
        return -1;
    }

    uint32_t x, y;

    x = read(argv[1]);
    y = read(argv[2]);

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", x, x, y, y, x+y, x+y);

    return 0;
}

void usage()
{
    printf("syntax : add-nbo <file1> <file2>\n");
    printf("sample : add-nbo a.bin c.bin\n");
}

uint32_t read(char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    uint32_t x;

    fread(&x, 32, 1, file);
    x = ntoh(x);

    fclose(file);

    return x;
}

uint32_t ntoh(uint32_t x)
{
    uint32_t x_=0;

    for(int i=0; i<4; i++){
        x_ = (x_<<8) + (x & 0xff);
        x = x>>8;
    }

    return x_;
}