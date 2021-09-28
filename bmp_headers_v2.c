#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("4.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img4_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    int hb[256]; 
    int hg[256];
    int hr[256];
    int hgray[256];

    //Limpiamos arreglos
    for (int i = 0; i<256;i++){
      hb[i]=0;
      hg[i]=0;
      hr[i]=0;
      hgray[i]=0;
    }

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18]; //Original
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22]; //Original
    //ancho = (long)xx[10]*65536+(long)xx[19]*256+(long)xx[18];
    //alto = (long)xx[9]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      hb[(int)b]+=1;
      hg[(int)g]+=1;
      hr[(int)r]+=1;
     // printf(" %i ",(int)b);
      //printf(" %i ",(int)g);
      //printf(" %i \n",(int)r);


      unsigned char pixel = 0.21*r+0.72*g+0.07*b;
      hgray[(int)pixel]++;

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r


      cuenta++;

    }
    //printf("La cuenta es %i ", cuenta-1);                                        

    //Grises
    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }

    //Impresion
    printf("\n n \t r \t g \t b \t gray \t ");
    for (int i = 0;i<256;i++){

      printf("\n %i\t %i\t %i\t %i\t %i \t",i ,hr[i], hg[i], hb[i],hgray[i]);
    }

    free(ptr);
    fclose(image);
    fclose(outputImage);
    return 0;
}
