#include <stdio.h>
#include <stdlib.h>
//# define PIX(x,y) raster[(x) + (y)*wd] 
unsigned  *raster;
//int raster[1000];
unsigned wd, ht, maxval;
int a;
int rgb;
int rgb2;
int rgb3;
int rgb4;
int x1, y11;
unsigned array[1000][1000];
unsigned PIX(int x, int y){
return raster[(x) + (y)*wd];
}

void rec_rot(int x, int y, int s) { int i, j;
s >>= 1;
unsigned temp;
for (i = 0 ; i < s ; ++i)
for (j = 0 ; j < s ; ++j) {
 rgb = raster[(x+i)+(y+j)*wd];
temp=raster[(x+i)+(y+j+s)*wd];
raster[(x+i)+(y+j)*wd] = temp;
temp=raster[(x+i+s)+(y+j+s)*wd];
raster[(x+i)+(y+j+s)*wd] = temp;
raster[(x+i+s)+(y+j+s)*wd] = raster[(x+i+s)+(y+j)*wd];
raster[(x+i+s)+(y+j)*wd] = rgb;
}
if (s <= 1) return;
rec_rot(x,y+s,s); rec_rot(x+s,y+s,s); rec_rot(x+s,y,s); rec_rot(x,y,s);
}
void iter_rot() {
int x, y, s;
s = wd >> 1;//devided by two;
for (y = 0 ; y < s ; ++y)
for (x = 0 ; x < s ; ++x) {
 rgb2 = raster[(x)+(y)*wd];
raster[(x)+(y)*wd]=raster[(y)+(ht-x-1)*wd];
raster[(y)+(ht-x-1)*wd]=raster[(wd-x-1)+(ht-y-1)*wd];
raster[(wd-x-1)+(ht-y-1)*wd]=raster[(wd-y-1)+(x)*wd];
raster[(wd-y-1)+(x)*wd]=rgb2;
} }
void read_ppm() {
//int x, y;
//a=0;
//printf("--read ppm--\n");
scanf("P6 %d %d %d ",&wd,&ht, &maxval);
wd=8;ht=8;maxval=255;
raster = (unsigned *)malloc(wd * ht * sizeof(int)); 
//wd=2;ht=2;maxval=5;

printf("read--%d",wd,"--%d",ht,"--%d",maxval,"\n");
for (y11 = 0 ; y11 < ht ; ++y11)
for (x1 = 0 ; x1 < wd ; ++x1) { 
 rgb3 = getchar() << 16;//multiplies by 2^16; 
rgb3 |= getchar()<< 8;//multiplies by 2^8;
rgb3 |= getchar();
raster[(x1)+(y11)*wd] = rgb3; }
}
void write_ppm() {
int x2, y2;
printf("write--%d",wd,"--%d",ht,"--%d",maxval,"\n");
printf("P6\n%d %d\n%d\n", wd, ht, maxval); 
for (y2 = 0 ; y2 < ht ; ++y2)
for (x2 = 0 ; x2 < wd ; ++x2) { 
 rgb4 = raster[(x2)+(y2)*wd];
//int z=rgb; 
putchar(rgb4 >> 16);
//rgb=rgb >> 16;
//z=rgb;
putchar((rgb4 >> 8) & 0xff);
//z=rgb;
//rgb=(rgb >> 8) & 0xff;
putchar(rgb4 & 0xff);
//rgb=rgb & 0xff;
} }
int main(int argc, char** argv) {
if (argc != 2 || (argv[1][0] != 'r' && argv[1][0] != 'i')) {
printf("USAGE: rotate [ir]\n"), exit(0);
}
read_ppm();
if (argv[1][0] == 'r') rec_rot(0, 0, wd); else iter_rot(); write_ppm();
return 0; 

}
