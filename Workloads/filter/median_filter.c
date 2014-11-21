#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <roi.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


//-----------------------------------------------
#include <time.h>
#include <stdio.h>


struct timespec timeDiff(struct timespec start, struct timespec end);
double tsFloat(struct timespec time);
void startLocalTimer();
void stopLocalTimer();

struct timespec localStart, localStop, globalStart, globalStop, fullTime;
unsigned long long startCycle = 0, stopCycle = 0;

#define CYCLECOUNT

#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

struct timespec timeDiff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) 
    {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

double tsFloat(struct timespec time)
{
    return ((double) time.tv_sec + (time.tv_nsec / 1000000000.0));
}

void startLocalTimer()
{
#ifndef CYCLECOUNT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &localStart);
#else
    startCycle = rdtsc();
    /*printf("[Cycle] Start: %llu ",startCycle);*/
#endif
}


void stopLocalTimer()
{
#ifndef CYCLECOUNT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &localStop);
    fullTime = timeDiff(localStart,localStop);
    printf("[Timer] Local: %f\n", tsFloat(fullTime));
#else
    stopCycle = rdtsc();
    printf("[Cycle] Diff: %llu\n", stopCycle - startCycle);
    startCycle = 0;
    stopCycle = 0;
#endif
}


//-----------------------------------------------
typedef struct { unsigned char r, g, b; } rgb_t;
typedef struct {
	int w, h;
	rgb_t **pix;
} image_t, *image;
 
typedef struct {
	int r[256], g[256], b[256];
	int n;
} color_histo_t;
 
image in, out, out2, out3;




int write_ppm(image im, char *fn)
{
	FILE *fp = fopen(fn, "w");
	if (!fp) return 0;
	fprintf(fp, "P6\n%d %d\n255\n", im->w, im->h);
	fwrite(im->pix[0], 1, sizeof(rgb_t) * im->w * im->h, fp);
	fclose(fp);
	return 1;
}
 
image img_new(int w, int h)
{
	int i;
	image im = malloc(sizeof(image_t) + h * sizeof(rgb_t*)
			+ sizeof(rgb_t) * w * h);
	im->w = w; im->h = h;
	im->pix = (rgb_t**)(im + 1);
	for (im->pix[0] = (rgb_t*)(im->pix + h), i = 1; i < h; i++)
		im->pix[i] = im->pix[i - 1] + w;
	return im;
}







/*
**
* Applying finding edges and then emboss
*  
*
*
*
 */
image edgefilter(image im, image out)
{
	
double filter[3][3] =
{
    -1, -1,  -1,
    -1,  8,  1,
     -1,  1,  1
};

double factor = 1.0;
double bias = 0;

	double red = 0.0, green = 0.0, blue = 0.0; 

	int row,col,filterX,filterY;

	for (row = 0; row < in->h; row ++) {
		for (col = 0; col < in->w; col++) {
			red = 0.0; green = 0.0; blue = 0.0;
        //multiply every value of the filter with corresponding image pixel 
        for(int filterX = 0; filterX < 3; filterX++) 
        for(int filterY = 0; filterY < 3; filterY++) 
        { 
            int imageX = ((row - 3) / 2 + 3 + in->w) % in->w; 
            int imageY = ((col - 3) / 2 + 3 + in->h) % in->h; 
            rgb_t *pix; 
            pix = im->pix[imageX]+imageY;

            red   += pix->r * filter[filterX][filterY]; 
            green += pix->g * filter[filterX][filterY]; 
            blue  += pix->b  * filter[filterX][filterY]; 
        } 

       rgb_t* outpix;
       outpix=out->pix[row]+col;        
        //truncate values smaller than zero and larger than 255 
        outpix->r= min(max(rint(factor * red + bias), 0), 255); 
        outpix->g= min(max(rint(factor * green + bias), 0), 255); 
        outpix->b= min(max(rint(factor * blue + bias), 0), 255);
       // outpix->r = red;
       // outpix->g = green;
       // outpix->b = blue;
     }    
 }
 return out;
}









 
int read_num(FILE *f)
{
	int n;
	while (!fscanf(f, "%d ", &n)) {
		if ((n = fgetc(f)) == '#') {
			while ((n = fgetc(f)) != '\n')
				if (n == EOF) break;
			if (n == '\n') continue;
		} else return 0;
	}
	return n;
}
 
image read_ppm(char *fn)
{
	FILE *fp = fopen(fn, "r");
	int w, h, maxval;
	image im = 0;
	if (!fp) return 0;
 
	if (fgetc(fp) != 'P' || fgetc(fp) != '6' || !isspace(fgetc(fp)))
		goto bail;
 
	w = read_num(fp);
	h = read_num(fp);
	maxval = read_num(fp);
	if (!w || !h || !maxval) goto bail;
 
	im = img_new(w, h);
	fread(im->pix[0], 1, sizeof(rgb_t) * w * h, fp);
bail:
	if (fp) fclose(fp);
	return im;
}
 
void del_pixels(image im, int row, int col, int size, color_histo_t *h)
{
	int i;
	rgb_t *pix;
 
	if (col < 0 || col >= im->w) return;
	for (i = row - size; i <= row + size && i < im->h; i++) {
		if (i < 0) continue;
		pix = im->pix[i] + col;
		h->r[pix->r]--;
		h->g[pix->g]--;
		h->b[pix->b]--;
		h->n--;
	}
}
 
void add_pixels(image im, int row, int col, int size, color_histo_t *h)
{
	int i;
	rgb_t *pix;
 
	if (col < 0 || col >= im->w) return;
	for (i = row - size; i <= row + size && i < im->h; i++) {
		if (i < 0) continue;
		pix = im->pix[i] + col;
		h->r[pix->r]++;
		h->g[pix->g]++;
		h->b[pix->b]++;
		h->n++;
	}
}
 
void init_histo(image im, int row, int size, color_histo_t*h)
{
	int j;
 
	memset(h, 0, sizeof(color_histo_t));
 
	for (j = 0; j < size && j < im->w; j++)
		add_pixels(im, row, j, size, h);
}
 
int median(const int *x, int n)
{
	int i;
	for (n /= 2, i = 0; i < 256 && (n -= x[i]) > 0; i++);
	return i;
}
 
void median_color(rgb_t *pix, const color_histo_t *h)
{
	pix->r = median(h->r, h->n);
	pix->g = median(h->g, h->n);
	pix->b = median(h->b, h->n);
}
 
image median_filter(image in,int size, image out)
{
	int row, col;
	color_histo_t h;
 
	for (row = 0; row < in->h; row ++) {
		for (col = 0; col < in->w; col++) {
			if (!col) init_histo(in, row, size, &h);
			else {
				del_pixels(in, row, col - size, size, &h);
				add_pixels(in, row, col + size, size, &h);
			}
			median_color(out->pix[row] + col, &h);
		}
	}
 
	return out;
}
 
int main(int c, char **v)
{
	int size;
	if (c <= 3) {
		printf("Usage: %s size ppm_in ppm_out\n", v[0]);
		return 0;
	}
	size = atoi(v[1]);
	printf("filter size %d\n", size);
	if (size < 0) size = 1;
 
	in = read_ppm(v[2]);
	__app_roi_begin();
    startLocalTimer();
    image out  = img_new(in->w,in->h); 
	image out2 = img_new(in->w, in->h);
	stopLocalTimer();

    startLocalTimer();
    median_filter(in,size,out);
	stopLocalTimer();
	
    startLocalTimer();
    edgefilter(out,out2);
	stopLocalTimer();
    
    
    __app_roi_end();
	write_ppm(out2, v[3]);
	free(in);
	free(out);
 
	return 0;
}
