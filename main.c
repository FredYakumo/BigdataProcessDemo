// Author: FredYakumo f17011311
// Time: 20200926
// Tools: Microsoft Visual studio code.(editor)
// Dev environment: gcc 9.2.0 (mingw64) / Windows 10 pro
// C standard = ISO C99


// Inputs:

// 1: Generated float arrary size, limit: maxium value of int32(2147483648)
// 2: random float minimun value
// 3: random float maximum value

// example:
//     10 2.5 20

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define STR_BUFFER_SIZE 255

#define OUTPUT_ALL_DATA(BUFFER, SZ) { for (bufferSize_t i = 0; i != SZ; ++i) printf("%f ", BUFFER[i]); } while(0)

typedef int32_t bufferSize_t;


// Get array size from standard input.
// @return: user input's arrary buffer size.
bufferSize_t getArrarySizeInput()
{
	bufferSize_t temp;
	scanf("%d", &temp);
	return temp;
}

// Allocate the data block for a float arrary.
// @return: first float pointer to the allocated float arrary data block.
float* allocArrary(bufferSize_t size)
{
	return (float*)malloc(size * sizeof(float));
}

// Generate a random float value.
// @return: random float value.
float getRandomFloat(float min, float max)
{
	float scale = rand() / (float) RAND_MAX;
	return min + scale * ( max - min );
}

void fillArraryDataWithRandom(float *buffer, bufferSize_t arrarySize, float min, float max)
{
	for (int32_t i = 0; i != arrarySize; ++i)
	{
		buffer[i] = getRandomFloat(min, max);
	}
}

// Save float arrary data to file.
// @returns: 
//     0 if success;

//     -1 open file failed.
int saveBufferDataToFile(const char *fileName, float *buffer, bufferSize_t size)
{
	FILE *file = fopen(fileName, "w");
	if (file == NULL)
		return -1;

	for (bufferSize_t i = 0; i != size; ++i)
	{
		fprintf(file, "%f ", buffer[i]);
	}
	fclose(file);
	return 0;
}

// Read all data from file
// Remenber to free buffer, after use the data buffer.
// @returns:
//     0 if success;
//     -1 open file failed
int readDataFromFile(const char *filename, float **outBuffer, bufferSize_t *outSize)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
		return -1;

	bufferSize_t allocSz = 8;
	
	float *buffer = (float*)malloc(allocSz * sizeof(float));
	bufferSize_t readSz = 0;
	while (!feof(file))
	{
		fscanf(file, "%f", buffer + readSz);
		if (++readSz == allocSz)
		{
			allocSz *= 2;
			float *newBuffer = (float*)malloc(allocSz * sizeof(float));
			for (bufferSize_t i = 0; i != readSz; ++i)
				newBuffer[i] = buffer[i];
			free(buffer);
			buffer = newBuffer;
		}
	}
	*outBuffer = buffer;

	// fixed size
	// when the while loop end, readSz has always been plus 1.
	*outSize = readSz - 1;
	return 0;
}

void insertionSort(float *data, bufferSize_t sz)
{
	float key;
	for (bufferSize_t i = 1, j; i != sz; ++i)
	{
		key = data[i];
		j = i - 1;
		while((j>=0) && (data[j] > key))
		{
			data[j+1] = data[j];
			--j;
		}
		data[j+1] = key;
	}
}

float getAverage(float *buffer, bufferSize_t sz)
{
	float sum = 0;
	for (bufferSize_t i = 0; i != sz; ++i)
		sum += buffer[i];
	return sum / sz;
}

float getVariance(float *buffer, bufferSize_t sz)
{
	float aver = getAverage(buffer, sz);
	float ret = 0;
	for (bufferSize_t i = 0; i != sz; ++i)
		ret += powf((buffer[i] - aver), 2);
	return sqrtf(ret / sz);
}

int main(void)
{
	srand(time(NULL));

	char arrarySizeStr[STR_BUFFER_SIZE];
	float *bufferData = NULL;

	bufferSize_t sz = getArrarySizeInput();
	bufferData = allocArrary(sz);
	
	float randomMin = 0.0f;
	float randomMax = 0.0f;
	scanf("%f%f", &randomMin, &randomMax);
	
	fillArraryDataWithRandom(bufferData, sz, randomMin, randomMax);
	
	printf("Generated float arrary datas:\n");
	OUTPUT_ALL_DATA(bufferData, sz);
	puts("\n\n");

	saveBufferDataToFile("data.txt", bufferData, sz);

	// Remove buffer
	free(bufferData);




	readDataFromFile("data.txt", &bufferData, &sz);

	printf("Float arrary read from file datas:\n");
	OUTPUT_ALL_DATA(bufferData, sz);
	puts("\n\n");

	insertionSort(bufferData, sz);

	printf("Sorted:\n");
	OUTPUT_ALL_DATA(bufferData, sz);
	puts("\n\n");
	
	float midValue = (sz % 2) ? (bufferData[sz / 2 + 1]) : ((bufferData[sz / 2 ] + bufferData[sz / 2 + 1]) / 2);
	printf("Maximum value: %f, minimum value: %f, mid value: %f, Average: %f, Variance: %f\n\n", 
		bufferData[0], bufferData[sz - 1], midValue, 
		getAverage(bufferData, sz), getVariance(bufferData, sz));
	
	return 0;
}
