#include <stdio.h>
#include <stdlib.h>
#pragma GCC optimize ("Ofast")
#define b1 0.2126
#define b2 0.7152
#define b3 0.0722
#define xd 51
typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;
typedef struct
{
    unsigned short w;
    unsigned short h;
    unsigned short con;
    pixel* value;
} image;

int main (int argc,char* argv[])
{
FILE* file=fopen(argv[1],"rb");
image picture;
if (fscanf(file, "P6 %hu %hu %hu\n", &(picture.w), &(picture.h), &(picture.con))<3)
{
    fprintf(stderr, "ERROR: Wrong input!");
    return -1;
}
picture.value=(pixel*)malloc(picture.w*picture.h*sizeof(pixel));
if (!picture.value)
{
    fprintf(stderr, "ERROR: Wrong allocation!");
    return -1;
}
if(!fread(picture.value, sizeof(pixel)*picture.w, picture.h, file))
{
    return -1;
}
fclose(file);

image picture2;
picture2.value=(pixel*)malloc(picture.w*picture.h*sizeof(pixel));
int histogram[]={0,0,0,0,0};
register int index;
register int i=0;
register int x=2;
short r;
short g;
short b;

while (i<picture.w)
{
    picture2.value[i]=picture.value[i];
    index=(b1*picture2.value[i].red+b2*picture2.value[i].green+b3*picture2.value[i].blue+0.5)/xd;
    index=index>4 ? 4 : index;
    i++;
    histogram[index]++;
}
while (i<picture.w*picture.h-picture.h)
{
    picture2.value[i]=picture.value[i];
    index=(b1*picture2.value[i].red+b2*picture2.value[i].green+b3*picture2.value[i].blue+0.5)/xd;
    index=index>4 ? 4 : index;
    i++;
    histogram[index]++;
    while (i<picture.w*x-1)
    {
        r=-picture.value[i-picture.w].red-picture.value[i-1].red+5*picture.value[i].red-picture.value[i+1].red-picture.value[i+picture.w].red;
        g=-picture.value[i-picture.w].green-picture.value[i-1].green+5*picture.value[i].green-picture.value[i+1].green-picture.value[i+picture.w].green;
        b=-picture.value[i-picture.w].blue-picture.value[i-1].blue+5*picture.value[i].blue-picture.value[i+1].blue-picture.value[i+picture.w].blue;
        picture2.value[i].red=(r<0 ? 0 : (r>255 ? 255 : r));
        picture2.value[i].green=(g<0 ? 0 : (g>255 ? 255 : g));
        picture2.value[i].blue=(b<0 ? 0 : (b>255 ? 255 : b));
        index=(b1*picture2.value[i].red+b2*picture2.value[i].green+b3*picture2.value[i].blue+0.5)/xd;
        index=index>4 ? 4 : index;
        i++;
        histogram[index]++;

    }
    picture2.value[i]=picture.value[i];
    index=(b1*picture2.value[i].red+b2*picture2.value[i].green+b3*picture2.value[i].blue+0.5)/xd;
    index=index>4 ? 4 : index;
    i++;
    histogram[index]++;
    x++;

}
while (i<picture.w*picture.h)
{
    picture2.value[i]=picture.value[i];
    index=(b1*picture2.value[i].red+b2*picture2.value[i].green+b3*picture2.value[i].blue+0.5)/xd;
    index=index>4 ? 4 : index;
    i++;
    histogram[index]++;
}
file=fopen("output.ppm","wb");
fprintf(file,"P6\n%d %d\n255\n",picture.w,picture.h);
fwrite(picture2.value, sizeof(pixel) * picture.w, picture.h, file);
fclose(file);
free(picture.value);
free(picture2.value);
file=fopen("output.txt","wb");
fprintf(file,"%d %d %d %d %d", histogram[0], histogram[1], histogram[2], histogram[3], histogram[4]);
fclose(file);
return 0;
}