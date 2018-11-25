#include <emmintrin.h>
#include <stdio.h>


// this cannot compiled
void setbytes(char* p, int c) {
    __m128i i = _mm_set_epi8(c, c, c, c,
                            c, c, c, c,
                            c, c, c, c,
                            c, c, c, c);
    _mm_stream_si128((__m128i *)&p[0], i);
    _mm_stream_si128((__m128i *)&p[16], i);
    _mm_stream_si128((__m128i *)&p[32], i);
    _mm_stream_si128((__m128i *)&p[48], i);
}

char Arr[10000];
int main(int argc, const char *argv[]){
    setbytes(Arr, 100);
    for (int i = 0; i < 128; ++i) {
        if(i % 16 == 0 && i != 0)
            printf("\n");
        printf("%4d ", Arr[i]);
    }
    return 0;
}
