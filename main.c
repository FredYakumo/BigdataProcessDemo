// Author: FredYakumo
// 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define STR_BUFFER_SIZE 255

char g_ArrarySizeStr[STR_BUFFER_SIZE];

int32_t g_ArrarySize = 0;
float *g_BufferData = NULL;

// Get array size from standard input.
int getArrarySizeInput() {
	scanf("%d", &g_ArrarySize);
}

void allocArrary() {
	g_BufferData = (float*)malloc(g_ArrarySize);
}

// Generate a random float value.
float getRandomFloat(float min, float max) {
	float scale = rand() / (float) RAND_MAX;
	return min + scale * ( max - min );
}

void fillArraryDataWithRandom(int32_t arrarySize) {
	for (int32_t i = 0; i < arrarySize; ++i) {
		g_BufferData[i] = getRandomFloat()
	}
}

int main(void) {
	srand(time(NULL));
	
	getArrarySizeInput();
	
	float randomMin = 0.0f;
	float randomMax = 0.0f;
	scanf("%f%f", &randomMin, &randomMax);
	
	fillArraryDataWithRandom(g_ArrarySize);
	
	for (int i = 0; i < g_ArrarySize; ++i) {
		
	}
	
	
	return 0;
}
